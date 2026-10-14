# Build recovered sources with Visual C++ .NET 2003 and compare them to the original.
#   make            compile src/*.cpp to build/*.obj
#   make diff       compare every annotated function with $(EFZ_DIR)/efz.exe
#   make diff F=X   only functions whose name contains X
#   make link       link build/efz.exe (all game code at its original address; the
#                   CRT, data and header are not byte-identical yet)
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

build/%.obj: build/src/%.cpp $(HDRS:src/%=build/src/%) | build
	tools/msvc cl $(CFLAGS) /Fo$@ /Fdbuild/$*.pdb $<

build build/src:
	mkdir -p $@

# The objects in the original's address order, which the linker keeps.
LINK_ORDER = main effect file config game graphics input sound player playerobj \
	shiori sayuri nayuki nanase nagamori mizukab mizuka misuzu mishio misaki mio minagi \
	mayu makoto mai kaori kano kanna ikumi exnanase ayu akane akiko nayukib \
	bg01 bg10 bg12 bg16 scene1 scene6 scene3 scene2 scene8 scene5 scene7 scene0
LIBS = kernel32.lib user32.lib gdi32.lib winmm.lib ddraw.lib dinput.lib dsound.lib dxguid.lib

link: build/efz.exe

build/efz.exe: $(OBJS)
	tools/msvc link /nologo /subsystem:windows /OPT:REF /OPT:NOICF /out:$@ \
		/map:build/efz.map $(LINK_ORDER:%=build/%.obj) $(LIBS)

diff: $(OBJS)
	@test -n "$(EFZ_DIR)" || { echo 'set EFZ_DIR to the folder containing the original efz.exe' >&2; exit 1; }
	@status=0; for obj in $(OBJS); do \
		EFZ_DIR='$(EFZ_DIR)' python3 tools/funcdiff.py $$obj $(F) || status=1; \
	done; exit $$status

clean:
	rm -rf build

.PHONY: all diff link clean
.SECONDARY:
