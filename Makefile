# Build recovered sources with Visual C++ .NET 2003 and compare them to the original.
#   make            compile src/*.cpp to build/*.obj
#   make diff       compare every annotated function with $(EFZ_DIR)/efz.exe
#   make diff F=X   only functions whose name contains X
#   make link       link build/efz.exe
#   make check      link and compare it with $(EFZ_DIR)/efz.exe: they are identical
#   make play       play build/efz.exe under wine on $(DISPLAY) (tools/play.sh)
#   make trace      build/trace/efz.exe: efz.exe with the replay test's harness
#   make native     the native game (CMakeLists.txt, docs/native.md) for Linux, and
#                   make native-windows for Windows, built in docker (tools/native.sh)
# One-time setup: toolchain/setup.sh

# Compiler flags confirmed by matching WinMain (0x401000).  The original was built by
# the Standard Edition compiler, which has no optimiser, so /Od reproduces its code.
# /MT doesn't change the code; it makes the objects ask for the multithreaded static
# CRT (libcmt), which the original links (it imports CreateThread and the Tls functions).
CFLAGS = /nologo /c /Od /GS /W3 /Zi /MT /D WIN32 /D NDEBUG /D _WINDOWS /D _MBCS

SRCS := $(filter-out src/trace.cpp,$(wildcard src/*.cpp))
HDRS := $(wildcard src/*.h)
OBJS := $(SRCS:src/%.cpp=build/%.obj)

all: $(OBJS)

# Sources are UTF-8; the compiler gets Shift-JIS (code page 932) copies, so Japanese
# string literals come out as the original's bytes.
build/src/%: src/% | build/src
	iconv -f UTF-8 -t CP932 $< > $@

# tools/stdstamp.py marks the objects as the Standard Edition's, as in the original's
# Rich header; the code is the same.
build/%.obj: build/src/%.cpp $(HDRS:src/%=build/src/%) Makefile | build
	tools/msvc cl $(CFLAGS) /Fo$@ /Fdbuild/$*.pdb $<
	python3 tools/stdstamp.py $@

build build/src:
	mkdir -p $@

# The objects in the original's address order, which the linker keeps.
CHARACTERS = shiori sayuri nayuki nanase nagamori mizukab mizuka misuzu mishio misaki mio \
	minagi mayu makoto mai kaori kano kanna ikumi exnanase ayu akane akiko nayukib
LINK_ORDER = main effect file config game graphics input sound player playerobj \
	$(foreach c,$(CHARACTERS),$(c)_vf6 $(c)) \
	bg01 bg10 bg12 bg16 scene1 scene6 scene3_draw scene3 scene2 scene8 scene5 scene7 scene0
# winmm.lib first: the import directory lists the DLLs in the order of their libraries.
LIBS = winmm.lib kernel32.lib user32.lib gdi32.lib ddraw.lib dinput.lib dsound.lib dxguid.lib

link: build/efz.exe

# /debug, as the original has a PDB record; it also makes /opt:noref the default, which
# keeps the CRT functions nothing calls, as in the original. The PDB goes where the
# original's was (tools/msvc maps D: to build/d), since efz.exe records its path.
# The PDB is made afresh (an existing one would raise the age the exe records), and
# tools/postlink.py sets the timestamp, the PDB's GUID and the Rich header's object
# count, which the build can't reproduce.
build/efz.exe: $(OBJS) build/efz.res
	mkdir -p build/d/nonotaro/works/EFZ
	rm -f build/d/nonotaro/works/EFZ/EFZ.pdb
	tools/msvc link /nologo /subsystem:windows /debug /incremental:no \
		'/pdb:D:\nonotaro\works\EFZ\EFZ.pdb' /out:$@ /map:build/efz.map \
		$(LINK_ORDER:%=build/%.obj) build/efz.res $(LIBS)
	python3 tools/postlink.py $@

check: build/efz.exe
	@test -n "$(EFZ_DIR)" || { echo 'set EFZ_DIR to the folder containing the original efz.exe' >&2; exit 1; }
	cmp build/efz.exe '$(EFZ_DIR)/efz.exe'
	@sha256sum build/efz.exe

play: build/efz.exe
	EFZ_DIR='$(EFZ_DIR)' tools/play.sh

native:
	tools/native.sh linux

native-windows:
	tools/native.sh windows

# The compatibility test's harness (src/trace.cpp, docs/compat.md): efz.exe's objects,
# but main, scene3 and input compiled again with its hooks (EFZ_TRACE), and trace.obj,
# which also replaces `new` (zeroed memory) and sin, cos and atan2 (correctly rounded).
# Every other function is the original's code, byte for byte.
TRACE_HOOKED = main scene3 input
trace: build/trace/efz.exe

build/trace/%.obj: build/src/%.cpp $(HDRS:src/%=build/src/%) Makefile | build/trace
	tools/msvc cl $(CFLAGS) /D EFZ_TRACE /Fo$@ /Fdbuild/trace/$*.pdb $<

build/trace:
	mkdir -p $@

# sin, cos and atan2 for the harness: port/x87.cpp's, which MinGW builds (tools/x87ref.cpp).
build/trace/x87ref.obj: tools/x87ref.cpp port/x87.cpp port/x87.h | build/trace
	docker run --rm -u "$$(id -u):$$(id -g)" -v "$$PWD:/work" -w /work efz-native \
		i686-w64-mingw32-g++ -std=c++17 -O2 -msse2 -mfpmath=sse -mstackrealign \
		-ffp-contract=off -fno-exceptions -fno-asynchronous-unwind-tables -c $< -o $@

build/trace/efz.exe: $(OBJS) $(TRACE_HOOKED:%=build/trace/%.obj) build/trace/trace.obj build/trace/x87ref.obj build/efz.res
	tools/msvc link /nologo /subsystem:windows /incremental:no /out:$@ \
		$(foreach o,$(LINK_ORDER),$(if $(filter $(o),$(TRACE_HOOKED)),build/trace,build)/$(o).obj) \
		build/trace/trace.obj build/trace/x87ref.obj build/efz.res $(LIBS)

# The icon, efz.exe's only resource, comes from the original.
build/efz.ico: | build
	@test -n "$(EFZ_DIR)" || { echo 'set EFZ_DIR to the folder containing the original efz.exe' >&2; exit 1; }
	EFZ_DIR='$(EFZ_DIR)' python3 tools/icon.py $@

build/efz.res: src/efz.rc build/efz.ico
	tools/msvc rc /fo$@ src/efz.rc

diff: $(OBJS)
	@test -n "$(EFZ_DIR)" || { echo 'set EFZ_DIR to the folder containing the original efz.exe' >&2; exit 1; }
	@status=0; for obj in $(OBJS); do \
		EFZ_DIR='$(EFZ_DIR)' python3 tools/funcdiff.py $$obj $(F) || status=1; \
	done; exit $$status

# --- EfzRevival 1.02h (docs/revival.md) -------------------------------------------
#   make revival            compile the recovered launcher sources and protobuf
#   make revival-diff       compare them function by function with $(REVIVAL_DIR)
# One-time setup: toolchain/setup-vs2012.sh; revival-diff also needs a Ghidra export
# of the original (build/revival/EfzRevival.exe.functions.json, made by Ghidra's
# analyzeHeadless with tools/ghidra/ExportFunctions.java; GHIDRA_HOME locates it).

REVIVAL_DIR ?= $(HOME)/.local/share/efz-decomp/revival/1.02h
GHIDRA_HOME ?= $(HOME)/tools/ghidra_12.1.4_PUBLIC
GHIDRA_PROJECTS ?= $(HOME)/tools/efz-ghidra

# The launcher's own sources, as observed: VS2012's Release options (/O2 /Oy- /GS /sdl
# /Gy /MT /EHsc), but no /GL, no inlining (/Ob0), SSE but not SSE2 (/arch:SSE) and strict
# floating point (/fp:strict). It found protobuf in C:\Programming (tools/msvc11 maps
# that drive path).
LAUNCHER_CFLAGS = /nologo /c /O2 /Ob0 /Oy- /GS /sdl /Gy /MT /EHsc /arch:SSE /W3 \
	/Zc:wchar_t /Zc:forScope /fp:strict /D WIN32 /D NDEBUG /D _CONSOLE /D _UNICODE \
	/D UNICODE '/IC:\Programming\protobuf-2.6.1\src' '/IC:\Programming\zlib-1.2.8'
LAUNCHER_SRCS := $(wildcard revival/EfzRevivalLauncher/*.cc revival/EfzRevivalLauncher/*.cpp)
LAUNCHER_OBJS := $(patsubst revival/EfzRevivalLauncher/%,build/revival/launcher/%.obj,$(basename $(LAUNCHER_SRCS)))

# protobuf 2.6.1's lite runtime and gzip stream, built from its vsprojects directory
# with the defaults of its libprotobuf-lite project (/O2, inlining on), /MT and HAVE_ZLIB:
# their __FILE__ strings are relative to it.
PROTOBUF_CFLAGS = /nologo /c /O2 /Oi /Oy- /GS /Gy /MT /EHsc /W3 /Zc:wchar_t /Zc:forScope \
	/fp:precise /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D LIBPROTOBUF_EXPORTS \
	/D HAVE_ZLIB=1 /wd4244 /wd4267 /wd4018 /wd4355 /wd4800 /wd4251 /wd4996 /wd4146 \
	/wd4305 '/I..\src' /I. '/IC:\Programming\zlib-1.2.8'
PROTOBUF_SRCS = io/coded_stream stubs/common extension_set generated_message_util \
	message_lite stubs/once stubs/atomicops_internals_x86_msvc repeated_field \
	wire_format_lite io/zero_copy_stream io/zero_copy_stream_impl_lite \
	stubs/stringprintf io/gzip_stream
PROTOBUF_OBJS = $(PROTOBUF_SRCS:%=build/revival/protobuf/%.obj)

# Where each recovered launcher object's code lies in the original.
LAUNCHER_RANGE_EfzPackets.pb = 0x4102a0 0x414710
LAUNCHER_RANGE_protobuf = 0x44a710 0x44eb50

revival: $(LAUNCHER_OBJS) $(PROTOBUF_OBJS)

# Every launcher source, EfzPackets.pb.cc included, is compiled with the precompiled
# header stdafx.h (forced in with /FI), which stdafx.cpp makes: observed in which header
# statics and inline functions each object emits (stdafx.h). With debug information
# (the original was linked /DEBUG): /Z7 gives the image /Zi gives, and builds in
# parallel without a PDB server.
LAUNCHER_PCH = build/revival/launcher/EfzRevivalLauncher.pch
LAUNCHER_DEBUG = /Z7
LAUNCHER_USE_PCH = /Yustdafx.h /FIstdafx.h /Fp../../$(LAUNCHER_PCH)
LAUNCHER_HDRS := $(wildcard revival/EfzRevivalLauncher/*.h)

build/revival/launcher/stdafx.obj: revival/EfzRevivalLauncher/stdafx.cpp revival/EfzRevivalLauncher/stdafx.h Makefile
	mkdir -p $(@D)
	cd revival/EfzRevivalLauncher && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) $(LAUNCHER_DEBUG) \
		/Ycstdafx.h /Fp../../$(LAUNCHER_PCH) /Fo../../$@ stdafx.cpp

$(LAUNCHER_PCH): build/revival/launcher/stdafx.obj

build/revival/launcher/%.obj: revival/EfzRevivalLauncher/%.cc $(LAUNCHER_PCH) $(LAUNCHER_HDRS) Makefile
	mkdir -p $(@D)
	cd revival/EfzRevivalLauncher && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) $(LAUNCHER_DEBUG) \
		$(LAUNCHER_USE_PCH) /Fo../../$@ $*.cc

build/revival/launcher/%.obj: revival/EfzRevivalLauncher/%.cpp $(LAUNCHER_PCH) $(LAUNCHER_HDRS) Makefile
	mkdir -p $(@D)
	cd revival/EfzRevivalLauncher && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) $(LAUNCHER_DEBUG) \
		$(LAUNCHER_USE_PCH) /Fo../../$@ $*.cpp

build/revival/protobuf/%.obj:
	mkdir -p $(@D)
	MSVC11_QUIET=1 MSVC11_DIR=/opt/tc/protobuf-2.6.1/vsprojects tools/msvc11 cl $(PROTOBUF_CFLAGS) \
		'/FoZ:\work\$(subst /,\,$@)' '..\src\google\protobuf\$(subst /,\,$*).cc'

build/revival/%.functions.json:
	mkdir -p $(@D) $(GHIDRA_PROJECTS)
	$(GHIDRA_HOME)/support/analyzeHeadless $(GHIDRA_PROJECTS) revival-1.02h \
		-import '$(REVIVAL_DIR)/$*' -overwrite -scriptPath tools/ghidra \
		-postScript ExportFunctions.java $(CURDIR)/$@ > $@.log 2>&1

revival-diff: revival build/revival/EfzRevival.exe.functions.json
	@status=0; for obj in $(LAUNCHER_OBJS); do \
		name=$$(basename $$obj .obj); \
		python3 tools/revdiff.py '$(REVIVAL_DIR)/EfzRevival.exe' \
			build/revival/EfzRevival.exe.functions.json $$obj \
			$$(make -s --no-print-directory revival-range N=$$name) $(PROTOBUF_OBJS) || status=1; \
	done; for obj in $(PROTOBUF_OBJS); do \
		REVDIFF_LIBRARY=1 python3 tools/revdiff.py '$(REVIVAL_DIR)/EfzRevival.exe' \
			build/revival/EfzRevival.exe.functions.json $$obj \
			$(LAUNCHER_RANGE_protobuf) $(PROTOBUF_OBJS) || status=1; \
	done; exit $$status

# Names for the original's library and template code: probes (tools/probes) compiled
# with the launcher's options and placed, with the recovered objects, by
# tools/revmatch.py. revival-decomp then exports Ghidra's decompilation with them.
PROBE_OBJS := $(patsubst tools/probes/%.cpp,build/revival/probe/%.obj,$(wildcard tools/probes/launcher_*.cpp))
REVIVAL_EXE_DATA = build/revival/EfzRevival.exe

build/revival/probe/%.obj: tools/probes/%.cpp
	mkdir -p $(@D)
	cd tools/probes && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) /wd4244 /wd4099 /Fo../../$@ $*.cpp

revival-names: $(LAUNCHER_OBJS) $(PROTOBUF_OBJS) $(PROBE_OBJS) $(REVIVAL_EXE_DATA).functions.json
	python3 tools/revmatch.py '$(REVIVAL_DIR)/EfzRevival.exe' $(REVIVAL_EXE_DATA).functions.json \
		$(LAUNCHER_OBJS) $(PROTOBUF_OBJS) $(PROBE_OBJS) --range 0x401000 0x44a000 \
		--out $(REVIVAL_EXE_DATA).names.json
	python3 tools/revnames.py $(REVIVAL_EXE_DATA).names.json > $(REVIVAL_EXE_DATA).labels.json

revival-decomp: revival-names
	$(GHIDRA_HOME)/support/analyzeHeadless $(GHIDRA_PROJECTS) revival-1.02h \
		-process EfzRevival.exe -noanalysis -scriptPath tools/ghidra \
		-postScript ExportDecomp.java $(CURDIR)/$(REVIVAL_EXE_DATA).labels.json \
		$(CURDIR)/$(REVIVAL_EXE_DATA).c 0x401000 0x44a000 > $(REVIVAL_EXE_DATA).c.log 2>&1

# --- EfzRevival.exe: the whole launcher ---------------------------------------------
#   make revival-launcher         link build/revival/launcher/EfzRevival.exe from the objects
#   make revival-launcher-check   and compare it with $(REVIVAL_DIR)'s, byte for byte
#   make revival-launcher-order   remake the order file after the sources change
# Link order is the project's: its files in alphabetical order (case-insensitive), so
# stdafx.obj (the precompiled header's) and Unused.obj (code the link drops) last, then
# protobuf as a static library.
LAUNCHER_LINK_ORDER = Config Console EfzPackets.pb EfzRevivalLauncher GameProcess NetPeers \
	Network ProtocolContext ProtocolState ProtocolStateClientConnect ProtocolStateEnd \
	ProtocolStateHostConnect ProtocolStatePlay ProtocolStateSpecConnect ProtocolStateSpecPlay \
	ProtocolStateTestDelay stdafx Unused
LAUNCHER_LIBS = user32.lib winmm.lib ws2_32.lib

build/revival/protobuf/libprotobuf-lite.lib: $(PROTOBUF_OBJS)
	tools/msvc11 lib /nologo /OUT:$@ $(PROTOBUF_OBJS) > /dev/null

build/revival/launcher/EfzRevival.ico:
	mkdir -p $(@D)
	python3 tools/icon.py $@ '$(REVIVAL_DIR)/EfzRevival.exe'

build/revival/launcher/EfzRevivalLauncher.res: revival/EfzRevivalLauncher/EfzRevivalLauncher.rc build/revival/launcher/EfzRevival.ico
	tools/msvc11 rc /nologo /fo$@ $< > /dev/null

# The link of the launcher, without its order file: OUT is the image, ORDER the option.
LAUNCHER_LINK = tools/msvc11 link /nologo /SUBSYSTEM:CONSOLE,5.01 /OPT:REF /OPT:ICF /DYNAMICBASE \
	/NXCOMPAT /MACHINE:X86 /SAFESEH /DEBUG '/PDB:C:\Git\efz_2022\Release\EfzRevivalLauncher.pdb' \
	/MANIFEST:EMBED "/MANIFESTUAC:level='asInvoker' uiAccess='false'" \
	$(LAUNCHER_LINK_ORDER:%=build/revival/launcher/%.obj) build/revival/launcher/EfzRevivalLauncher.res \
	build/revival/protobuf/libprotobuf-lite.lib $(LAUNCHER_LIBS)
LAUNCHER_INPUTS = $(LAUNCHER_LINK_ORDER:%=build/revival/launcher/%.obj) \
	build/revival/protobuf/libprotobuf-lite.lib build/revival/launcher/EfzRevivalLauncher.res

# The functions' order (/ORDER) is the original's: which of several identical functions
# the link keeps (/OPT:ICF) depends on every function in it, dead code included, which
# the sources no longer have (docs/revival.md, "Identical functions"). The order file
# names our functions in the original's order; make revival-launcher-order remakes it
# from a link without it (tools/revorder.py) after the sources change. Only the
# launcher's own objects are ordered (up to protobuf, 0x44a710): protobuf's static
# functions can't be named, so protobuf keeps the link's order, which is the original's.
LAUNCHER_ORDER = revival/EfzRevivalLauncher/EfzRevival.order

build/revival/launcher/EfzRevival.exe: $(LAUNCHER_INPUTS) $(LAUNCHER_ORDER)
	mkdir -p build/revival/c/Git/efz_2022/Release
	rm -f build/revival/c/Git/efz_2022/Release/EfzRevivalLauncher.pdb
	$(LAUNCHER_LINK) /MAP:build/revival/launcher/EfzRevival.map /OUT:$@ /ORDER:@$(LAUNCHER_ORDER) \
		| { grep -v 'LNK4037' || true; }
	python3 tools/revpostlink.py $@

build/revival/launcher/natural/EfzRevival.exe: $(LAUNCHER_INPUTS)
	mkdir -p $(@D) build/revival/c/Git/efz_2022/Release
	rm -f build/revival/c/Git/efz_2022/Release/EfzRevivalLauncher.pdb
	$(LAUNCHER_LINK) /MAP:$(@D)/EfzRevival.map /OUT:$@

# Like make check: the linked launcher is the original, byte for byte (not yet).
revival-launcher-check: build/revival/launcher/EfzRevival.exe
	cmp $< '$(REVIVAL_DIR)/EfzRevival.exe'
	@sha256sum $<

# The order a link without one suggests changes which identical functions the link folds
# (listing them changes their sort), so the order is made again from a link with it.
LAUNCHER_REORDER = python3 tools/revorder.py '$(REVIVAL_DIR)/EfzRevival.exe' $(1).exe $(1).map \
	$(REVIVAL_EXE_DATA).functions.json 0x401000 0x44eb47 --until 0x44a710 --order $(LAUNCHER_ORDER)
revival-launcher-order: build/revival/launcher/natural/EfzRevival.exe $(REVIVAL_EXE_DATA).functions.json
	$(call LAUNCHER_REORDER,build/revival/launcher/natural/EfzRevival)
	mkdir -p build/revival/launcher/ordered
	rm -f build/revival/c/Git/efz_2022/Release/EfzRevivalLauncher.pdb
	$(LAUNCHER_LINK) /MAP:build/revival/launcher/ordered/EfzRevival.map \
		/OUT:build/revival/launcher/ordered/EfzRevival.exe /ORDER:@$(LAUNCHER_ORDER) | { grep -v 'LNK4037' || true; }
	$(call LAUNCHER_REORDER,build/revival/launcher/ordered/EfzRevival)

revival-launcher: build/revival/launcher/EfzRevival.exe

# --- EfzRevival.dll: link-time code generation (docs/revival.md) ----------------------
#   make revival-dll        compile revival/EfzRevival with /GL and link EfzRevival.dll
#   make revival-dll-diff   compare its annotated functions with $(REVIVAL_DIR)'s (F=filter)
# Observed: no inlining (/Ob0), no security cookies (/GS-: only the CRT reads it), no
# function-level linking (/Gy-: the developer's
# functions follow the CRT, after the import thunks), no string pooling (/GF-), SSE but
# not SSE2 (/arch:SSE: cmov, x87 floating point), no RTTI (/GR-: no complete object
# locators before its vtables, only the type descriptors exceptions need); functions
# defined in headers stay out-of-line COMDATs at the start. ATL (atlbase.h, Music.h) is
# Visual Studio's, in the toolchain's vs2012/atlmfc (a v110_xp build's include and library
# paths have it, and the toolset defines _USING_V110_SDK71_).
DLL_CFLAGS = /nologo /c /O2 /Ob0 /Oy- /GS- /GL /Gy- /GF- /GR- /MT /EHsc /arch:SSE /fp:strict \
	/W3 /Zc:wchar_t /Zc:forScope /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D _UNICODE \
	/D UNICODE /D _USING_V110_SDK71_ /IZ:/opt/tc/vs2012/atlmfc/include
# The objects in link order: the project's files in alphabetical order (case-insensitive),
# which is also the order of their code, and stdafx.obj last (as in the launcher). Every
# source is compiled with the Visual Studio template's precompiled header, stdafx.h (/Yu),
# which stdafx.cpp makes (/Yc). Observed:
# with a precompiled header the compiler lists the symbols an object refers to in the
# order it first refers to them (without one, in its symbol table's order), and link-time
# code generation lays out those defined in a later object in that order
# (docs/revival.md, "How link-time code generation orders functions").
DLL_LINK_ORDER = Config Detours dllmain EfzGame EfzPalettes EfzReplay EfzRevival GameState GameStateBuffer \
	Hook Music MusicList OnlineSession OnlineSpectatorSession OnlineSync PracticeSession Process \
	Recorder ReplaySession Session TournamentSession stdafx
DLL_OBJS := $(DLL_LINK_ORDER:%=build/revival/dll/%.obj)
DLL_PCH = build/revival/dll/EfzRevival.pch
# Until every source exists the link leaves calls to missing functions unresolved.
DLL_LINK_EXTRA = /FORCE:UNRESOLVED
# The project's own libraries, then Visual Studio's default ones (the import directory
# lists the DLLs in the order of their libraries: WINMM, PSAPI, DDRAW, QUARTZ, KERNEL32,
# USER32, ole32, then WS2_32, which asio's headers ask for with #pragma comment).
DLL_LIBS = winmm.lib psapi.lib DDRAW.lib quartz.lib strmiids.lib kernel32.lib user32.lib \
	gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib \
	uuid.lib odbc32.lib odbccp32.lib /LIBPATH:Z:/opt/tc/vs2012/atlmfc/lib

# Every header counts.
DLL_DEPS = $(wildcard revival/EfzRevival/*.h revival/EfzRevivalLauncher/*.h \
	revival/DDRAW/*.h)
build/revival/dll/stdafx.obj: revival/EfzRevival/stdafx.cpp $(DLL_DEPS)
	mkdir -p $(@D)
	cd revival/EfzRevival && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DLL_CFLAGS) /Ycstdafx.h \
		/Fp../../$(DLL_PCH) /Fo../../$@ stdafx.cpp

$(DLL_PCH): build/revival/dll/stdafx.obj

build/revival/dll/%.obj: revival/EfzRevival/%.cpp $(DLL_PCH) $(DLL_DEPS)
	mkdir -p $(@D)
	cd revival/EfzRevival && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DLL_CFLAGS) /Yustdafx.h \
		/Fp../../$(DLL_PCH) /Fo../../$@ $*.cpp

# DDRAW.dll's import library comes from linking DDRAW.dll, as in the original.
build/revival/dll/DDRAW.lib: build/revival/ddraw/DDRAW.dll
	mkdir -p $(@D)
	cp build/revival/ddraw/DDRAW.lib $@

# Release defaults: debug information into the PDB the original names (C:\Git is
# build/revival/c/Git, see tools/msvc11; made afresh, as an existing one would raise the
# age), the manifest embedded (the original's only resource), and v110_xp's subsystem
# version, 5.01 (the headers' OS and subsystem versions).
DLL_LINK_FLAGS = /nologo /DLL /LTCG /OPT:REF /OPT:ICF /MACHINE:X86 /DEBUG \
	'/PDB:C:\Git\efz_2022\Release\EfzRevival.pdb' /MANIFEST:EMBED \
	"/MANIFESTUAC:level='asInvoker' uiAccess='false'" /SUBSYSTEM:WINDOWS,5.01
build/revival/dll/EfzRevival.dll: $(DLL_OBJS) build/revival/dll/DDRAW.lib revival/EfzRevival/EfzRevival.def
	mkdir -p build/revival/c/Git/efz_2022/Release
	rm -f build/revival/c/Git/efz_2022/Release/EfzRevival.pdb
	tools/msvc11 link $(DLL_LINK_FLAGS) $(DLL_LINK_EXTRA) \
		/DEF:revival/EfzRevival/EfzRevival.def /MAP:build/revival/dll/EfzRevival.map \
		/LIBPATH:build/revival/dll /OUT:$@ $(DLL_OBJS) $(DLL_LIBS) | grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088'; test -f $@

revival-dll: build/revival/dll/EfzRevival.dll

# The whole image, byte for byte: the link, the fields no build reproduces
# (tools/revdllpostlink.py), then a comparison with the original (tools/pecmp.py).
build/revival/dll/EfzRevival.final.dll: build/revival/dll/EfzRevival.dll
	cp $< $@
	python3 tools/revdllpostlink.py $@

revival-dll-check-image: build/revival/dll/EfzRevival.final.dll
	python3 tools/pecmp.py '$(REVIVAL_DIR)/EfzRevival.dll' $< build/revival/dll/EfzRevival.map

revival-dll-diff: build/revival/dll/EfzRevival.dll build/revival/EfzRevival.dll.functions.json
	python3 tools/revltcg.py '$(REVIVAL_DIR)/EfzRevival.dll' $< build/revival/dll/EfzRevival.map \
		revival/EfzRevival build/revival/EfzRevival.dll.functions.json $(V) $(F)

# While several people work on the DLL: compile only the given sources (S=a.cpp,b.cpp),
# link every object that exists into OUT (each worker its own) and report the given
# sources' functions. Objects of other sources are used as they are, stale or not.
OUT ?= build/revival/dll-check
revival-dll-check: build/revival/dll/DDRAW.lib build/revival/EfzRevival.dll.functions.json
	@for s in $(subst $(comma), ,$(S)); do $(MAKE) -s --no-print-directory \
		build/revival/dll/$${s%.cpp}.obj || exit 1; done
	@mkdir -p $(OUT)
	@tools/msvc11 link /nologo /DLL /LTCG /OPT:REF /OPT:ICF /MACHINE:X86 $(DLL_LINK_EXTRA) \
		/DEF:revival/EfzRevival/EfzRevival.def /MAP:$(OUT)/EfzRevival.map /LIBPATH:build/revival/dll \
		/OUT:$(OUT)/EfzRevival.dll $(DLL_OBJS) $(DLL_LIBS) \
		| grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088' || true
	@python3 tools/revltcg.py '$(REVIVAL_DIR)/EfzRevival.dll' $(OUT)/EfzRevival.dll \
		$(OUT)/EfzRevival.map revival/EfzRevival build/revival/EfzRevival.dll.functions.json \
		--only $(S) $(V) $(F)
comma := ,

# --- DDRAW.dll: link-time code generation, like EfzRevival.dll but with function-level
# linking (/Gy: its functions are COMDATs, at the start), string pooling (/GF) and SSE2
# (the default); no RTTI (/GR-); linked without /OPT:REF or /OPT:ICF (/DEBUG's defaults:
# unreferenced functions and identical copies are all in the original). ----------------
#   make revival-ddraw          compile revival/DDRAW and link DDRAW.dll
#   make revival-ddraw-diff     compare its annotated functions (F=filter, V=-v)
#   make revival-ddraw-layout   how much of its code lines up with the original's
#   make revival-ddraw-check    compare the two images byte for byte
DDRAW_CFLAGS = /nologo /c /O2 /Ob0 /Oy- /GS- /GL /Gy /GF /GR- /MT /EHsc /fp:strict \
	/W3 /Zc:wchar_t /Zc:forScope /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D DDRAW_EXPORTS \
	/D _UNICODE /D UNICODE
# The objects in link order, which is the order of their code (with /Gy each object's
# functions come in the order the compiler emits them: its own in the order of their
# definitions, then the templates it instantiates, then what it uses of the precompiled
# header). Not alphabetical: the files shared with the other projects come first, then
# the Visual Studio template's (DDRAW.cpp, dllmain.cpp), then the rest; stdafx.obj's code
# is all in earlier objects. dllmain.cpp is compiled without the precompiled header, as
# the template sets it: the inline functions it uses come first in its object, in the
# order of their definitions (the system error category's, 0x1001ba30). .rdata follows
# the same order, each object's strings before its vtables (hence the three
# myIDirectDraw files).
DDRAW_LINK_ORDER = Config Process Detours Hook EfzRender SoftwareSurface DDRAW dllmain \
	EfzFixes myIDirectDraw myIDirectDrawPalette myIDirectDrawSurface stdafx
DDRAW_OBJS := $(DDRAW_LINK_ORDER:%=build/revival/ddraw/%.obj)
DDRAW_PCH = build/revival/ddraw/DDRAW.pch
DDRAW_DEPS = $(wildcard revival/DDRAW/*.h)
# The import directory lists the DLLs in the order of their libraries: the project's
# (WINMM, d3d9 and d3dx9 from the DirectX SDK, whose directory comes first), then Visual
# Studio's defaults (KERNEL32, USER32, SHELL32), then WS2_32, which asio asks for with
# #pragma comment.
DDRAW_LIBS = winmm.lib d3d9.lib d3dx9.lib DxErr.lib kernel32.lib user32.lib gdi32.lib \
	winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib \
	odbc32.lib odbccp32.lib
DDRAW_LINK_FLAGS = /nologo /DLL /LTCG /MACHINE:X86 /DEBUG '/PDB:C:\Git\efz_2022\Release\DDRAW.pdb' \
	/SUBSYSTEM:WINDOWS,5.01 /DYNAMICBASE /NXCOMPAT /SAFESEH /MANIFEST:EMBED \
	"/MANIFESTUAC:level='asInvoker' uiAccess='false'" '/LIBPATH:Z:\opt\tc\dxsdk2010\Lib'

build/revival/ddraw/stdafx.obj: revival/DDRAW/stdafx.cpp $(DDRAW_DEPS)
	mkdir -p $(@D)
	cd revival/DDRAW && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DDRAW_CFLAGS) /Ycstdafx.h \
		/Fp../../$(DDRAW_PCH) /Fo../../$@ stdafx.cpp

$(DDRAW_PCH): build/revival/ddraw/stdafx.obj

build/revival/ddraw/%.obj: revival/DDRAW/%.cpp $(DDRAW_PCH) $(DDRAW_DEPS)
	mkdir -p $(@D)
	cd revival/DDRAW && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DDRAW_CFLAGS) /Yustdafx.h \
		/Fp../../$(DDRAW_PCH) /Fo../../$@ $*.cpp

build/revival/ddraw/dllmain.obj: revival/DDRAW/dllmain.cpp $(DDRAW_DEPS)
	mkdir -p $(@D)
	cd revival/DDRAW && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DDRAW_CFLAGS) /Fo../../$@ dllmain.cpp

build/revival/ddraw/DDRAW.dll: $(DDRAW_OBJS) revival/DDRAW/DDRAW.def
	mkdir -p build/revival/c/Git/efz_2022/Release
	rm -f build/revival/c/Git/efz_2022/Release/DDRAW.pdb
	tools/msvc11 link $(DDRAW_LINK_FLAGS) /DEF:revival/DDRAW/DDRAW.def \
		/MAP:build/revival/ddraw/DDRAW.map /IMPLIB:build/revival/ddraw/DDRAW.lib /OUT:$@ \
		$(DDRAW_OBJS) $(DDRAW_LIBS) \
		| grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088'; test -f $@

revival-ddraw: build/revival/ddraw/DDRAW.dll

revival-ddraw-diff: build/revival/ddraw/DDRAW.dll build/revival/DDRAW.dll.functions.json
	python3 tools/revltcg.py '$(REVIVAL_DIR)/DDRAW.dll' $< build/revival/ddraw/DDRAW.map \
		revival/DDRAW build/revival/DDRAW.dll.functions.json $(V) $(F)

revival-ddraw-layout: build/revival/ddraw/DDRAW.dll build/revival/DDRAW.dll.functions.json
	python3 tools/revalign.py '$(REVIVAL_DIR)/DDRAW.dll' $< build/revival/ddraw/DDRAW.map \
		build/revival/DDRAW.dll.functions.json 0x10001000 0x10020100 | tail -1

# The whole image, byte for byte: the link, then the fields no build reproduces
# (tools/ddrawpostlink.py). Like make check, it is the original; where it isn't,
# tools/pecmp.py says what differs.
build/revival/ddraw/DDRAW.final.dll: build/revival/ddraw/DDRAW.dll tools/ddrawpostlink.py
	cp $< $@
	python3 tools/ddrawpostlink.py $@

revival-ddraw-check: build/revival/ddraw/DDRAW.final.dll
	cmp $< '$(REVIVAL_DIR)/DDRAW.dll' || { python3 tools/pecmp.py '$(REVIVAL_DIR)/DDRAW.dll' $< \
		build/revival/ddraw/DDRAW.map; exit 1; }
	@sha256sum $<

# An object's range: LAUNCHER_RANGE_<name>, or a `// OBJECT: LO HI` line in its source.
revival-range:
	@r='$(LAUNCHER_RANGE_$(N))'; [ -n "$$r" ] || r=$$(sed -n \
		's#^// OBJECT: *\(0x[0-9a-fA-F]*\) *\(0x[0-9a-fA-F]*\).*#\1 \2#p' \
		$(wildcard revival/EfzRevivalLauncher/$(N).cpp revival/EfzRevivalLauncher/$(N).cc) | head -1); echo $$r

# One object: compile it, compare its functions (V=-v prints the diffs) and list the
# original's functions in its range that no object or probe produces yet.
revival-check: build/revival/launcher/$(N).obj $(PROTOBUF_OBJS) $(PROBE_OBJS)
	@python3 tools/revdiff.py '$(REVIVAL_DIR)/EfzRevival.exe' $(REVIVAL_EXE_DATA).functions.json \
		build/revival/launcher/$(N).obj $$(make -s --no-print-directory revival-range N=$(N)) \
		$(PROTOBUF_OBJS) $(V)
	@python3 tools/revmatch.py '$(REVIVAL_DIR)/EfzRevival.exe' $(REVIVAL_EXE_DATA).functions.json \
		build/revival/launcher/$(N).obj $(PROTOBUF_OBJS) $(PROBE_OBJS) --uncovered \
		--range $$(make -s --no-print-directory revival-range N=$(N)) | sed -n '/not placed/,$$p'

revival-flags:
	@echo $(LAUNCHER_CFLAGS)

clean:
	rm -rf build

.PHONY: all diff link check play clean trace native native-windows revival revival-diff revival-range revival-flags revival-names revival-decomp revival-check revival-launcher revival-launcher-check revival-launcher-order revival-dll revival-dll-diff revival-dll-check revival-dll-check-image revival-ddraw revival-ddraw-diff revival-ddraw-layout revival-ddraw-check
.SECONDARY:
.DELETE_ON_ERROR:
