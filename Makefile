# Build recovered sources with Visual C++ .NET 2003 and compare them to the original.
#   make            compile src/*.cpp to build/*.obj
#   make diff       compare every annotated function with $(EFZ_DIR)/efz.exe
#   make diff F=X   only functions whose name contains X
# One-time setup: toolchain/setup.sh

EFZ_DIR ?= $(error set EFZ_DIR to the folder containing the original efz.exe)
export EFZ_DIR

# Compiler flags confirmed by matching WinMain (0x401000).  The original was built by
# the Standard Edition compiler, which has no optimiser, so /Od reproduces its code.
CFLAGS = /nologo /c /Od /GS /W3 /Zi /D WIN32 /D NDEBUG /D _WINDOWS /D _MBCS

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=build/%.obj)

all: $(OBJS)

build/%.obj: src/%.cpp $(wildcard src/*.h) | build
	tools/msvc cl $(CFLAGS) /Fo$@ /Fdbuild/$*.pdb $<

build:
	mkdir -p build

diff: $(OBJS)
	@status=0; for obj in $(OBJS); do python3 tools/funcdiff.py $$obj $(F) || status=1; done; exit $$status

clean:
	rm -rf build

.PHONY: all diff clean
