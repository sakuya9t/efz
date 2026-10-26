# Runs Visual C++ .NET 2003 (cl 13.10.3077) under 32-bit wine.
# The compiler and SDKs are not baked in: toolchain/setup.sh extracts them into a
# host directory that tools/msvc mounts at /opt/tc.
FROM debian:bookworm-slim

# winbind provides ntlm_auth: Visual C++ 2012 writes PDBs through mspdbsrv.exe over local
# RPC with NTLM authentication, which wine does through ntlm_auth. Without it, link
# /DEBUG and cl /Zi fail with LNK1101/C1902 ("incorrect MSPDB110.DLL version").

RUN dpkg --add-architecture i386 \
 && apt-get update \
 && apt-get install -y --no-install-recommends wine wine32 msitools p7zip-full cabextract innoextract python3 winbind \
 && rm -rf /var/lib/apt/lists/*

# Same uid as the host user, so build outputs in the mounted repo stay theirs.
ARG UID=1000
ARG GID=1000
RUN groupadd -g ${GID} build && useradd -m -u ${UID} -g ${GID} build
USER build
ENV WINEPREFIX=/home/build/.wine WINEARCH=win32 WINEDEBUG=-all
RUN wineboot -i && wineserver -w

WORKDIR /work
