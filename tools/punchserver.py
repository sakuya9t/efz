#!/usr/bin/env python3
"""A hole-punching server for EfzRevival's netplay (port/netplay/protocol.h), as the
launcher uses one (EfzRevival.ini's HolePunchingServer): for tests over the internet,
and for players who want their own.

    tools/punchserver.py [--port 10800] [--bind 0.0.0.0] [--quiet]

EfzRevival 1.02h's own server isn't among its files; this one does what the launcher's
side of the exchange implies (revival/EfzRevivalLauncher/ProtocolStateHostConnect.cpp,
ProtocolStateClientConnect.cpp):

- A host pings the server once as it starts hosting (MessagePing, type 2). The server
  answers (MessagePong, type 3) and remembers where the ping came from: the host's
  address and port as the internet sees them, behind its router.
- A joiner the host hasn't answered yet sends MessagePunch (type 10, field 1 the host's
  endpoint as a 32-bit Windows boost::asio endpoint, 28 bytes) every half second. The
  server sends the host a MessagePunch with the joiner's endpoint, as it sees it, and the
  joiner one with the host's: the host pings the joiner, which opens the host's router
  to it, and the joiner sends its request to the host's endpoint (each side tries that
  port and the nine after it, one a punch).

A datagram is EfzRevival's: byte 0 is 1 when the message is zlib-compressed, byte 1 its
type, then the protobuf-lite message.
"""
import argparse
import socket
import struct
import sys
import time
import zlib

PING, PONG, PUNCH = 2, 3, 10
FORGET = 600  # seconds a host's ping is remembered


def varint(value):
    out = bytearray()
    while True:
        b = value & 0x7f
        value >>= 7
        if value:
            out.append(b | 0x80)
        else:
            out.append(b)
            return bytes(out)


def parse(data):
    """A protobuf message's fields: {number: [values]}, varints as ints, bytes as bytes."""
    fields, i = {}, 0
    while i < len(data):
        key, i = read_varint(data, i)
        number, wire = key >> 3, key & 7
        if wire == 0:
            value, i = read_varint(data, i)
        elif wire == 2:
            size, i = read_varint(data, i)
            value, i = data[i:i + size], i + size
        elif wire == 5:
            value, i = data[i:i + 4], i + 4
        elif wire == 1:
            value, i = data[i:i + 8], i + 8
        else:
            raise ValueError('wire type %d' % wire)
        fields.setdefault(number, []).append(value)
    return fields


def read_varint(data, i):
    value = shift = 0
    while True:
        b = data[i]
        i += 1
        value |= (b & 0x7f) << shift
        shift += 7
        if not b & 0x80:
            return value, i


def unpack(packet):
    if len(packet) < 2:
        return None, None
    body = packet[2:]
    if packet[0] == 1:
        body = zlib.decompress(body)
    return packet[1], parse(body)


def endpoint_bytes(address, port):
    """(address, port) as the launcher's 28 bytes: sockaddr_in or Windows' sockaddr_in6."""
    if ':' in address:
        raw = socket.inet_pton(socket.AF_INET6, address)
        mapped = raw[:12] == b'\0' * 10 + b'\xff\xff'
        if mapped:
            return struct.pack('<H', 2) + struct.pack('>H', port) + raw[12:] + bytes(20)
        return struct.pack('<H', 23) + struct.pack('>H', port) + bytes(4) + raw + bytes(4)
    return struct.pack('<H', 2) + struct.pack('>H', port) + socket.inet_aton(address) + bytes(20)


def endpoint_of(data):
    family = struct.unpack('<H', data[0:2])[0]
    port = struct.unpack('>H', data[2:4])[0]
    if family == 2:
        return socket.inet_ntoa(data[4:8]), port
    if family == 23 and len(data) >= 28:
        return socket.inet_ntop(socket.AF_INET6, data[8:24]), port
    raise ValueError('family %d' % family)


def plain(address):
    """An IPv4-mapped IPv6 address as IPv4."""
    return address[7:] if address.startswith('::ffff:') else address


def message(kind, body):
    return bytes([0, kind]) + body


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--port', type=int, default=10800)
    ap.add_argument('--bind', default='::')
    ap.add_argument('--quiet', action='store_true')
    args = ap.parse_args()
    sock = socket.socket(socket.AF_INET6, socket.SOCK_DGRAM)
    sock.setsockopt(socket.IPPROTO_IPV6, socket.IPV6_V6ONLY, 0)
    sock.bind((args.bind, args.port))
    hosts = {}  # address -> (port, when)

    def log(text):
        if not args.quiet:
            print(time.strftime('%H:%M:%S'), text, flush=True)

    log('hole-punching server on UDP %d' % args.port)
    while True:
        packet, source = sock.recvfrom(0x10000)
        address, port = plain(source[0]), source[1]
        try:
            kind, fields = unpack(packet)
        except Exception as e:
            log('%s:%d: not a message (%s)' % (address, port, e))
            continue
        if kind == PING:
            stamp = fields.get(3, [0])[-1]
            sock.sendto(message(PONG, varint(3 << 3) + varint(stamp)), source)
            if address not in hosts or hosts[address][0] != port:
                log('%s:%d pings: a host' % (address, port))
            hosts[address] = (port, time.time())
        elif kind == PUNCH:
            try:
                target = endpoint_of(fields[1][-1])
            except Exception as e:
                log('%s:%d: a punch that doesn\'t parse (%s)' % (address, port, e))
                continue
            host = hosts.get(plain(target[0]))
            if not host or time.time() - host[1] > FORGET:
                log('%s:%d wants %s:%d, which hasn\'t pinged' % (address, port, *target))
                continue
            host_address, host_port = plain(target[0]), host[0]
            to_host = message(PUNCH, varint(1 << 3 | 2) + varint(28) + endpoint_bytes(address, port))
            to_joiner = message(PUNCH, varint(1 << 3 | 2) + varint(28) +
                                endpoint_bytes(host_address, host_port))
            sock.sendto(to_host, ('::ffff:' + host_address if ':' not in host_address else host_address,
                                  host_port))
            sock.sendto(to_joiner, source)
            log('%s:%d joins %s:%d (asked for port %d)' % (address, port, host_address,
                                                            host_port, target[1]))


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        sys.exit(0)
