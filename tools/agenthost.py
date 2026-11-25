#!/usr/bin/env python3
"""A public netplay host played by an agent (docs/netplay.md, "A public host"): the native
game on a Linux server, reached by ssh, hosting one match after another on UDP ports for
anyone to join with EfzRevival 1.02h or the native game, its side played by an agent file.

    tools/agenthost.py deploy USER@HOST --agent FILE
        builds the game there (this repository's HEAD, in docker with tools/native.sh, for
        the server's own processor), sends the game's data (once) and the agent file,
        writes the systemd unit efz-agent-host@.service and runs a host on each port,
        each restarted when its match ends; opens the ports in the server's firewall (ufw,
        or iptables with /etc/iptables/rules.v4). Again: the game and the agent updated,
        the hosts restarted (a match being played is cut), the ports given the only ones.
        --efz DIR             the game's folder (default $EFZ_DIR)
        --port N              a host on this UDP port (default 10800; again for more)
        --name NAME           what players see (default "EFZ agent"; 20 characters)
        --idle-timeout S      a match ends when the player has given no input for S
                              seconds, or hasn't got to it S seconds after connecting
                              (default 90; 0: never)
        --data-again          send the game's data even if it is there
    tools/agenthost.py status USER@HOST
        each host: running or not, waiting or playing whom; the replays so far
    tools/agenthost.py fetch USER@HOST OUT
        the matches' replays (save/replay/netplay), the battle log and each match's
        efz.log (its agent's account) into OUT, as on the server
    tools/agenthost.py remove USER@HOST [--purge]
        stops the hosts and removes the unit and the firewall rules; --purge the folder too
        (the efz-native docker image stays: `docker image rm efz-native` there)
    tools/agenthost.py oci USER@HOST [--port N]... [--remove]
        Oracle Cloud's own firewall: a network security group efz-netplay, letting UDP in
        on the ports (default: those of the hosts there), on the server's network card;
        --remove takes it off and deletes it. Needs the oci package (pip install oci) and
        ~/.oci/config; --compartment OCID where the instance isn't in the tenancy's root
    For each: --ssh-key FILE (ssh's key), --dir NAME (the folder in the server user's home,
    default efz-host).

The server needs systemd, docker (the build), curl, and sudo without a password; any
processor that Debian and SDL3 build for (x86-64, arm64). The folder has the game (efz),
its data (EFZ), the save folder (save: the agent in save/agents, the replays in
save/replay/netplay, BattleLog.txt) and the logs (logs: a folder for each match, all kept).
A cloud's firewall in front of the server must let UDP in on the ports too: `oci` does it
for Oracle Cloud; elsewhere it is the provider's console.
"""
import argparse
import os
import re
import socket
import subprocess
import sys
import tarfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
UNIT = 'efz-agent-host'
NSG = 'efz-netplay'

UNIT_TEXT = """\
# Written by tools/agenthost.py: a netplay host on UDP port %i whose side the agent plays;
# the game quits when a match ends, and systemd starts it again for the next.
[Unit]
Description=EFZ netplay host on UDP %i played by {agent}
After=network-online.target
Wants=network-online.target
StartLimitIntervalSec=0

[Service]
User={user}
WorkingDirectory={folder}
Environment=SDL_VIDEO_DRIVER=offscreen SDL_RENDER_DRIVER=software SDL_AUDIO_DRIVER=dummy
ExecStart={folder}/efz --data EFZ --save save --log-dir logs --log-keep 0 --host --port %i \
--name "{name}" --agent "{agent}" --idle-timeout {idle}
Restart=always
RestartSec=3
MemoryMax=1G

[Install]
WantedBy=multi-user.target
"""

# The server's firewall: ufw if it is on, else iptables when its INPUT chain ends in a
# REJECT or DROP (as Oracle Cloud's Ubuntu images have it), the rule put before that one
# and in /etc/iptables/rules.v4, which netfilter-persistent loads at boot.
FIREWALL = r"""
rule() { echo "-p udp -m udp --dport $1 -j ACCEPT"; }
ufw_on() { command -v ufw >/dev/null && sudo ufw status | grep -q '^Status: active'; }
open_port() {
    if ufw_on; then
        sudo ufw allow "$1/udp" comment efz-agent-host >/dev/null && echo "ufw: UDP $1 allowed"
        return
    fi
    n=$(sudo iptables -S INPUT | grep '^-A' | grep -nE -- '-j (REJECT|DROP)' | head -1 | cut -d: -f1)
    if [ -z "$n" ]; then
        echo "iptables: INPUT lets UDP $1 in already"
        return
    fi
    sudo iptables -C INPUT $(rule $1) >/dev/null 2>&1 || sudo iptables -I INPUT "$n" $(rule $1)
    f=/etc/iptables/rules.v4
    if sudo test -f $f && ! sudo grep -q -- "^-A INPUT $(rule $1)$" $f; then
        sudo sed -i "0,/^-A INPUT .*-j \(REJECT\|DROP\)/s//-A INPUT $(rule $1)\n&/" $f
    fi
    echo "iptables: UDP $1 allowed$(sudo test -f $f && echo ", in $f")"
}
close_port() {
    if ufw_on; then
        sudo ufw delete allow "$1/udp" >/dev/null 2>&1 && echo "ufw: UDP $1 closed"
    fi
    while sudo iptables -C INPUT $(rule $1) >/dev/null 2>&1; do sudo iptables -D INPUT $(rule $1); done
    f=/etc/iptables/rules.v4
    if sudo test -f $f && sudo grep -q -- "^-A INPUT $(rule $1)$" $f; then
        sudo sed -i "\|^-A INPUT $(rule $1)$|d" $f
        echo "iptables: UDP $1 closed, in $f too"
    fi
}
"""


class Remote:
    """The server, by ssh."""

    def __init__(self, target, key, folder):
        self.target = target
        self.ssh = ['ssh', '-o', 'BatchMode=yes', '-o', 'ConnectTimeout=15']
        self.scp = ['scp', '-q', '-o', 'BatchMode=yes']
        if key:
            self.ssh += ['-i', key]
            self.scp += ['-i', key]
        self.home = self.run('echo "$HOME"').strip()
        self.user = self.run('id -un').strip()
        self.folder = f'{self.home}/{folder}'

    def run(self, command, timeout=120, check=True, stdin=None):
        r = subprocess.run(self.ssh + [self.target, command], capture_output=True, text=True,
                           timeout=timeout, input=stdin)
        if check and r.returncode != 0:
            sys.exit(f'tools/agenthost.py: on {self.target}: {command.strip()[:200]}:\n'
                     f'{(r.stderr or r.stdout).strip()}')
        return r.stdout

    def bash(self, script, timeout=120, check=True):
        """A script run by bash there, from stdin (FIREWALL's functions with it)."""
        return self.run('bash -s', timeout, check, stdin=FIREWALL + script)

    def put(self, local, remote):
        subprocess.run(self.scp + [local, f'{self.target}:{remote}'], check=True, timeout=600)

    def send_tar(self, folder_in, write):
        """A tar stream of what `write(tar)` adds, extracted in folder_in there."""
        p = subprocess.Popen(self.ssh + [self.target, f'mkdir -p "{folder_in}" && '
                             f'tar -xzf - -C "{folder_in}"'], stdin=subprocess.PIPE)
        with tarfile.open(fileobj=p.stdin, mode='w|gz') as tar:
            write(tar)
        p.stdin.close()
        if p.wait() != 0:
            sys.exit(f'tools/agenthost.py: sending to {self.target}:{folder_in} failed')

    def ports(self):
        """The ports of the hosts there (their units enabled)."""
        out = self.run('ls /etc/systemd/system/multi-user.target.wants/ 2>/dev/null', check=False)
        return sorted(int(m.group(1)) for m in re.finditer(rf'{UNIT}@(\d+)\.service', out))


def server_address(target):
    host = target.rsplit('@', 1)[-1]
    try:
        return socket.gethostbyname(host)
    except OSError:
        return host


def check_name(name):
    if len(name) > 20 or not name or any(c in name for c in '"\\\n\r'):
        sys.exit('tools/agenthost.py: --name: 1-20 characters, no " or \\')
    # (systemd's specifiers and variables)
    return name.replace('%', '%%').replace('$', '$$')


def deploy(args, remote):
    efz = args.efz or os.environ.get('EFZ_DIR')
    if not efz or not os.path.isdir(os.path.join(efz, 'system')) and not os.path.isdir(
            os.path.join(efz, 'System')):
        sys.exit('tools/agenthost.py: --efz (or EFZ_DIR): the game\'s folder, with its system '
                 'folder')
    if not os.path.isfile(args.agent):
        sys.exit(f'tools/agenthost.py: no agent file {args.agent}')
    agent = os.path.basename(args.agent)
    if any(c in agent for c in '"\\%$'):
        sys.exit(f'tools/agenthost.py: the agent file\'s name has " \\ % or $: rename it')
    name = check_name(args.name)
    ports = sorted(set(args.port or [10800]))
    if any(not 1 <= p <= 65535 for p in ports):
        sys.exit('tools/agenthost.py: --port: 1 to 65535')
    if subprocess.run(remote.ssh + [remote.target, 'sudo -n true'],
                      capture_output=True).returncode:
        sys.exit(f'tools/agenthost.py: {remote.target} must have sudo without a password')
    missing = remote.run('for t in systemctl curl docker tar; do command -v $t >/dev/null || '
                         'echo $t; done', check=False).split()
    if missing:
        sys.exit(f'tools/agenthost.py: {remote.target} lacks {", ".join(missing)} '
                 f'(docker: e.g. sudo apt install docker.io)')
    docker = 'docker' if subprocess.run(remote.ssh + [remote.target, 'docker info'],
                                        capture_output=True).returncode == 0 else 'sudo docker'
    f = remote.folder
    print(f'{remote.target}: {remote.run("uname -m").strip()}, into {f}')

    # The source: HEAD, the earlier build kept (its folder moved aside and back).
    print('the source (HEAD) ...')
    remote.run(f'mkdir -p "{f}" && cd "{f}" && rm -rf src.new build.keep && '
               f'{{ [ ! -d src/build ] || mv src/build build.keep; }}')
    archive = subprocess.run(['git', '-C', REPO, 'archive', '--format=tar.gz', 'HEAD'],
                             capture_output=True, check=True).stdout
    revision = subprocess.run(['git', '-C', REPO, 'rev-parse', 'HEAD'], capture_output=True,
                              text=True, check=True).stdout.strip()
    # (REVISION: the revision the game's log names, tools/buildinfo.cmake)
    p = subprocess.Popen(remote.ssh + [remote.target, f'cd "{f}" && mkdir src.new && '
                         f'tar -xzf - -C src.new && echo {revision} > src.new/REVISION'],
                         stdin=subprocess.PIPE)
    p.communicate(archive)
    if p.returncode:
        sys.exit('tools/agenthost.py: sending the source failed')
    remote.run(f'cd "{f}" && rm -rf src && mv src.new src && '
               f'{{ [ ! -d build.keep ] || mv build.keep src/build; }}')
    print(f'building it there (tools/native.sh with {docker}; the first time ~10 minutes) ...')
    out = remote.run(f'cd "{f}/src" && DOCKER="{docker}" EFZ_CTEST_ARGS="--label-exclude headless"'
                     f' tools/native.sh > build.log 2>&1; s=$?; tail -5 build.log; exit $s',
                     timeout=3600, check=False)
    if 'built build/native' not in out:
        sys.exit(f'tools/agenthost.py: the build failed ({f}/src/build.log):\n{out}')
    remote.run(f'cd "{f}" && install -m 755 src/build/native/efz efz.new && mv efz.new efz')

    # The game's data, once; the agent.
    if args.data_again or remote.run(f'[ -d "{f}/EFZ" ] && echo yes', check=False).strip() != 'yes':
        print(f'the game\'s data ({efz}) ...')
        remote.run(f'rm -rf "{f}/EFZ"')
        remote.send_tar(f, lambda tar: tar.add(efz, arcname='EFZ'))
    remote.run(f'mkdir -p "{f}/save/agents" "{f}/logs"')
    remote.put(args.agent, f'{f}/save/agents/{agent}')

    # The unit, the hosts on exactly these ports, the firewall.
    unit = UNIT_TEXT.format(user=remote.user, folder=f, name=name, agent=agent,
                            idle=max(0, args.idle_timeout))
    remote.run(f'sudo tee /etc/systemd/system/{UNIT}@.service >/dev/null', stdin=unit)
    old = [p for p in remote.ports() if p not in ports]
    script = 'sudo systemctl daemon-reload\n'
    for p in old:
        script += f'sudo systemctl disable --now {UNIT}@{p}.service\nclose_port {p}\n'
    for p in ports:
        script += f'open_port {p}\nsudo systemctl enable {UNIT}@{p}.service 2>/dev/null\n'
        script += f'sudo systemctl restart {UNIT}@{p}.service\n'
    script += 'sleep 3\n'
    script += ''.join(f'echo "{p} $(systemctl is-active {UNIT}@{p}.service)"\n' for p in ports)
    out = remote.bash(script)
    print(out.rstrip())
    down = [line for line in out.splitlines() if re.match(r'\d+ ', line)
            and not line.endswith(' active')]
    if down:
        sys.exit(f'tools/agenthost.py: not running: {down} '
                 f'(journalctl -u {UNIT}@PORT there)')
    address = server_address(remote.target)
    print(f'players join {", ".join(f"{address}:{p}" for p in ports)} (EfzRevival 1.02h or '
          f'the native game); a cloud firewall in front must let UDP in on '
          f'{", ".join(map(str, ports))} (Oracle Cloud: tools/agenthost.py oci)')


def status(args, remote):
    f = remote.folder
    ports = remote.ports()
    if not ports:
        print(f'{remote.target}: no hosts')
        return
    for p in ports:
        state = remote.run(f'systemctl is-active {UNIT}@{p}.service', check=False).strip()
        # The newest log of this port's host, and what it says last of the match.
        last = remote.run(
            f'cd "{f}/logs" && l=$(grep -l "hosting on UDP port {p}," */efz.log | tail -1) && '
            f'grep -E "net: (hosting on|playing as|the session ends|the match ran)" "$l" | tail -1',
            check=False).strip()
        m = re.match(r'(\S+ \S+)\.\d+ .*net: (.*)', last)
        what = '?'
        if m:
            when, line = m.groups()
            if line.startswith('playing as'):
                vs = re.search(r'against (.*?) \(', line)
                what = f'playing {vs.group(1) if vs else "?"} since {when}'
            elif line.startswith('hosting on'):
                what = f'waiting for a player since {when}'
            else:
                what = f'{line} ({when})'
        print(f'UDP {p}: {state}, {what}')
    count = remote.run(f'ls "{f}/save/replay/netplay" 2>/dev/null | grep -c "\\.rep$"',
                       check=False).strip() or '0'
    games = remote.run(f'grep -c " VS " "{f}/save/BattleLog.txt" 2>/dev/null', check=False).strip()
    print(f'{count} replays, {games or 0} battle log lines; {f}: '
          f'{remote.run(f"du -sh {f} | cut -f1", check=False).strip()}')


def fetch(args, remote):
    f = remote.folder
    files = ('$(ls -d save/replay save/BattleLog.txt logs/*/efz.log logs/*/session.json '
             '2>/dev/null)')
    if not remote.run(f'cd "{f}" && echo {files}', check=False).strip():
        print(f'{remote.target}: nothing yet')
        return
    os.makedirs(args.out, exist_ok=True)
    p = subprocess.Popen(remote.ssh + [remote.target, f'cd "{f}" && tar -czf - {files}'],
                         stdout=subprocess.PIPE)
    n = 0
    safe = {'filter': 'data'} if hasattr(tarfile, 'data_filter') else {}
    with tarfile.open(fileobj=p.stdout, mode='r|gz') as tar:
        for member in tar:
            parts = member.name.split('/')
            if member.name.startswith('/') or '..' in parts or not (
                    member.isfile() or member.isdir()):
                continue
            tar.extract(member, args.out, set_attrs=False, **safe)
            n += member.isfile()
    if p.wait() != 0:
        sys.exit('tools/agenthost.py: fetching failed')
    print(f'{n} files into {args.out}')


def remove(args, remote):
    ports = remote.ports()
    script = ''.join(f'sudo systemctl disable --now {UNIT}@{p}.service\nclose_port {p}\n'
                     for p in ports)
    script += f'sudo rm -f /etc/systemd/system/{UNIT}@.service\nsudo systemctl daemon-reload\n'
    if args.purge:
        script += f'rm -rf "{remote.folder}"\n'
    print(remote.bash(script).rstrip())
    print(f'{remote.target}: {len(ports)} hosts removed'
          f'{", and " + remote.folder if args.purge else ""}')


def oci_firewall(args, remote):
    try:
        import oci
    except ImportError:
        sys.exit('tools/agenthost.py: oci needs the oci package (pip install oci)')
    ports = sorted(set(args.port or remote.ports()))
    if not ports and not args.remove:
        sys.exit('tools/agenthost.py: no hosts there: --port N')
    address = server_address(remote.target)
    config = oci.config.from_file()
    compute = oci.core.ComputeClient(config)
    network = oci.core.VirtualNetworkClient(config)
    compartment = args.compartment or config['tenancy']
    vnic = None
    for instance in compute.list_instances(compartment).data:
        if instance.lifecycle_state != 'RUNNING':
            continue
        for a in compute.list_vnic_attachments(compartment, instance_id=instance.id).data:
            v = network.get_vnic(a.vnic_id).data
            if v.public_ip == address:
                vnic = v
    if not vnic:
        sys.exit(f'tools/agenthost.py: no running instance with the address {address} in '
                 f'{compartment} (--compartment)')
    vcn = network.get_subnet(vnic.subnet_id).data.vcn_id
    groups = [g for g in network.list_network_security_groups(
        compartment_id=compartment, vcn_id=vcn).data
        if g.display_name == NSG and g.lifecycle_state == 'AVAILABLE']
    if args.remove:
        for g in groups:
            if g.id in vnic.nsg_ids:
                network.update_vnic(vnic.id, oci.core.models.UpdateVnicDetails(
                    nsg_ids=[i for i in vnic.nsg_ids if i != g.id]))
            network.delete_network_security_group(g.id)
        print(f'{NSG}: {"removed" if groups else "not there"}')
        return
    if groups:
        group = groups[0]
    else:
        group = network.create_network_security_group(
            oci.core.models.CreateNetworkSecurityGroupDetails(
                compartment_id=compartment, vcn_id=vcn, display_name=NSG)).data
        group = oci.wait_until(network, network.get_network_security_group(group.id),
                               'lifecycle_state', 'AVAILABLE').data
    rules = network.list_network_security_group_security_rules(group.id).data
    have = {r.udp_options.destination_port_range.min: r.id for r in rules
            if r.udp_options and r.udp_options.destination_port_range}
    stale = [rid for port, rid in have.items() if port not in ports]
    if stale:
        network.remove_network_security_group_security_rules(
            group.id, oci.core.models.RemoveNetworkSecurityGroupSecurityRulesDetails(
                security_rule_ids=stale))
    new = [oci.core.models.AddSecurityRuleDetails(
        direction='INGRESS', protocol='17', source='0.0.0.0/0', source_type='CIDR_BLOCK',
        description='EFZ netplay host (tools/agenthost.py)',
        udp_options=oci.core.models.UdpOptions(
            destination_port_range=oci.core.models.PortRange(min=p, max=p)))
        for p in ports if p not in have]
    if new:
        network.add_network_security_group_security_rules(
            group.id, oci.core.models.AddNetworkSecurityGroupSecurityRulesDetails(
                security_rules=new))
    if group.id not in vnic.nsg_ids:
        network.update_vnic(vnic.id, oci.core.models.UpdateVnicDetails(
            nsg_ids=list(vnic.nsg_ids) + [group.id]))
    print(f'{NSG} on {address}: UDP {", ".join(map(str, ports))} from anywhere')


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('deploy', 'status', 'fetch', 'remove', 'oci'):
        p = sub.add_parser(name)
        p.add_argument('target', metavar='USER@HOST')
        p.add_argument('--ssh-key')
        p.add_argument('--dir', default='efz-host')
        if name == 'deploy':
            p.add_argument('--agent', required=True)
            p.add_argument('--efz')
            p.add_argument('--port', type=int, action='append')
            p.add_argument('--name', default='EFZ agent')
            p.add_argument('--idle-timeout', type=int, default=90)
            p.add_argument('--data-again', action='store_true')
        elif name == 'fetch':
            p.add_argument('out', metavar='OUT')
        elif name == 'remove':
            p.add_argument('--purge', action='store_true')
        elif name == 'oci':
            p.add_argument('--port', type=int, action='append')
            p.add_argument('--remove', action='store_true')
            p.add_argument('--compartment')
    args = ap.parse_args()
    if not re.fullmatch(r'[A-Za-z0-9._-]+', args.dir):
        sys.exit('tools/agenthost.py: --dir: a plain folder name')
    remote = Remote(args.target, args.ssh_key, args.dir)
    {'deploy': deploy, 'status': status, 'fetch': fetch, 'remove': remove,
     'oci': oci_firewall}[args.cmd](args, remote)


if __name__ == '__main__':
    main()
