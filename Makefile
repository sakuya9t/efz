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

clean:
	rm -rf build

.PHONY: all diff link check play clean
.SECONDARY:
.DELETE_ON_ERROR:
