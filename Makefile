# Build recovered sources with Visual C++ .NET 2003 and compare them to the original.
#   make            compile src/*.cpp to build/*.obj
#   make diff       compare every annotated function with $(EFZ_DIR)/efz.exe
#   make diff F=X   only functions whose name contains X
#   make link       link build/efz.exe
#   make check      link and compare it with $(EFZ_DIR)/efz.exe: they are identical
#   make play       play build/efz.exe under wine on $(DISPLAY) (tools/play.sh)
# One-time setup: toolchain/setup.sh

# Compiler flags confirmed by matching WinMain (0x401000).  The original was built by
# the Standard Edition compiler, which has no optimiser, so /Od reproduces its code.
# /MT doesn't change the code; it makes the objects ask for the multithreaded static
# CRT (libcmt), which the original links (it imports CreateThread and the Tls functions).
CFLAGS = /nologo /c /Od /GS /W3 /Zi /MT /D WIN32 /D NDEBUG /D _WINDOWS /D _MBCS

SRCS := $(wildcard src/*.cpp)
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
LAUNCHER_RANGE_protobuf = 0x44a000 0x44eb50

revival: $(LAUNCHER_OBJS) $(PROTOBUF_OBJS)

build/revival/launcher/%.obj: revival/EfzRevivalLauncher/%.cc Makefile
	mkdir -p $(@D)
	cd revival/EfzRevivalLauncher && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) /Fo../../$@ $*.cc

build/revival/launcher/%.obj: revival/EfzRevivalLauncher/%.cpp Makefile
	mkdir -p $(@D)
	cd revival/EfzRevivalLauncher && MSVC11_QUIET=1 ../../tools/msvc11 cl $(LAUNCHER_CFLAGS) /Fo../../$@ $*.cpp

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
		python3 tools/revdiff.py '$(REVIVAL_DIR)/EfzRevival.exe' \
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

# --- EfzRevival.dll: link-time code generation (docs/revival.md) ----------------------
#   make revival-dll        compile revival/EfzRevival with /GL and link EfzRevival.dll
#   make revival-dll-diff   compare its annotated functions with $(REVIVAL_DIR)'s (F=filter)
# Observed: no inlining (/Ob0), no security cookies (/GS-: only the CRT reads it), no
# function-level linking (/Gy-: the developer's
# functions follow the CRT, after the import thunks), no string pooling (/GF-), SSE but
# not SSE2 (/arch:SSE: cmov, x87 floating point); functions defined in headers stay out-of-line COMDATs at the start.
DLL_CFLAGS = /nologo /c /O2 /Ob0 /Oy- /GS- /GL /Gy- /GF- /MT /EHsc /arch:SSE /fp:strict \
	/W3 /Zc:wchar_t /Zc:forScope /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D _UNICODE \
	/D UNICODE
DLL_SRCS := $(wildcard revival/EfzRevival/*.cpp)
DLL_OBJS := $(patsubst revival/EfzRevival/%.cpp,build/revival/dll/%.obj,$(DLL_SRCS))
# Until every source exists the link leaves calls to missing functions unresolved.
DLL_LINK_EXTRA = /FORCE:UNRESOLVED
DLL_LIBS = kernel32.lib user32.lib winmm.lib psapi.lib ws2_32.lib ole32.lib strmiids.lib \
	quartz.lib DDRAW.lib

# Every header (and the launcher's Config.cpp, which the DLL's includes) counts.
DLL_DEPS = $(wildcard revival/EfzRevival/*.h revival/EfzRevival/stubs/*.h \
	revival/EfzRevivalLauncher/*.h revival/EfzRevivalLauncher/Config.cpp revival/DDRAW/*.h)
build/revival/dll/%.obj: revival/EfzRevival/%.cpp $(DLL_DEPS)
	mkdir -p $(@D)
	cd revival/EfzRevival && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DLL_CFLAGS) /Fo../../$@ $*.cpp

# DDRAW.dll's import library, from a stub of its exports until DDRAW.dll is rebuilt
build/revival/dll/DDRAW.lib: revival/DDRAW/stub/DDRAW_stub.cpp revival/DDRAW/EfzRender.h revival/DDRAW/DDRAW.def
	mkdir -p build/revival/ddrawstub $(@D)
	cd revival/DDRAW/stub && MSVC11_QUIET=1 ../../../tools/msvc11 cl /nologo /c /O2 /MT /EHsc \
		/Fo../../../build/revival/ddrawstub/DDRAW_stub.obj DDRAW_stub.cpp
	tools/msvc11 link /nologo /DLL /DEF:revival/DDRAW/DDRAW.def /IMPLIB:$@ \
		/OUT:build/revival/ddrawstub/DDRAW.dll build/revival/ddrawstub/DDRAW_stub.obj \
		> /dev/null

build/revival/dll/EfzRevival.dll: $(DLL_OBJS) build/revival/dll/DDRAW.lib revival/EfzRevival/EfzRevival.def
	tools/msvc11 link /nologo /DLL /LTCG /OPT:REF /OPT:ICF /MACHINE:X86 $(DLL_LINK_EXTRA) \
		/DEF:revival/EfzRevival/EfzRevival.def /MAP:build/revival/dll/EfzRevival.map \
		/LIBPATH:build/revival/dll /OUT:$@ $(DLL_OBJS) $(DLL_LIBS) | grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088'; test -f $@

revival-dll: build/revival/dll/EfzRevival.dll

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
		/OUT:$(OUT)/EfzRevival.dll $(wildcard build/revival/dll/*.obj) $(DLL_LIBS) \
		| grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088' || true
	@python3 tools/revltcg.py '$(REVIVAL_DIR)/EfzRevival.dll' $(OUT)/EfzRevival.dll \
		$(OUT)/EfzRevival.map revival/EfzRevival build/revival/EfzRevival.dll.functions.json \
		--only $(S) $(V) $(F)
comma := ,

# --- DDRAW.dll: link-time code generation, like EfzRevival.dll but with function-level
# linking (/Gy: its functions are COMDATs, at the start) and SSE2 (the default). -------
#   make revival-ddraw-diff   compile revival/DDRAW, link DDRAW.dll, compare (F=filter)
DDRAW_CFLAGS = /nologo /c /O2 /Ob0 /Oy- /GS- /GL /Gy /GF- /MT /EHsc /fp:strict \
	/W3 /Zc:wchar_t /Zc:forScope /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL /D DDRAW_EXPORTS \
	/D _UNICODE /D UNICODE
DDRAW_SRCS := $(wildcard revival/DDRAW/*.cpp)
DDRAW_OBJS := $(patsubst revival/DDRAW/%.cpp,build/revival/ddraw/%.obj,$(DDRAW_SRCS))
DDRAW_LIBS = kernel32.lib user32.lib shell32.lib winmm.lib ws2_32.lib d3d9.lib d3dx9.lib

build/revival/ddraw/%.obj: revival/DDRAW/%.cpp $(wildcard revival/DDRAW/*.h revival/EfzRevivalLauncher/Config.*)
	mkdir -p $(@D)
	cd revival/DDRAW && MSVC11_QUIET=1 ../../tools/msvc11 cl $(DDRAW_CFLAGS) /Fo../../$@ $*.cpp

build/revival/ddraw/DDRAW.dll: $(DDRAW_OBJS) revival/DDRAW/DDRAW.def
	tools/msvc11 link /nologo /DLL /LTCG /OPT:REF /OPT:ICF /MACHINE:X86 $(DLL_LINK_EXTRA) \
		/DEF:revival/DDRAW/DDRAW.def /MAP:build/revival/ddraw/DDRAW.map \
		/IMPLIB:build/revival/ddraw/DDRAW.lib /OUT:$@ $(DDRAW_OBJS) $(DDRAW_LIBS) \
		| grep -v '^Generating code\|^Finished generating\|Creating library\|LNK4088'; test -f $@

revival-ddraw-diff: build/revival/ddraw/DDRAW.dll build/revival/DDRAW.dll.functions.json
	python3 tools/revltcg.py '$(REVIVAL_DIR)/DDRAW.dll' $< build/revival/ddraw/DDRAW.map \
		revival/DDRAW build/revival/DDRAW.dll.functions.json $(V) $(F)

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

.PHONY: all diff link check play clean revival revival-diff revival-range revival-flags revival-names revival-decomp revival-check revival-dll revival-dll-diff revival-dll-check revival-ddraw-diff
.SECONDARY:
.DELETE_ON_ERROR:
