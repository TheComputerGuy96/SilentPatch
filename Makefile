ROOTDIR := $(PWD)
BUILDDIR := $(ROOTDIR)/build
BINDIR := $(ROOTDIR)/bin

# Create the build directories if they don't already exist
SP_MKDIR := $(shell [ ! -d $(BUILDDIR) ] && mkdir -p $(BUILDDIR))
SP_MKDIR := $(shell [ ! -d $(BINDIR) ] && mkdir -p $(BINDIR))

# The CC/CXX/STRIP variables are overriden if they have a default value
# (TODO: Test compilation with llvm-mingw too)
ifeq ($(origin CC),default)
	CC := i686-w64-mingw32-gcc
else
	CC ?= i686-w64-mingw32-gcc
endif

ifeq ($(origin CXX),default)
	CXX := i686-w64-mingw32-g++
else
	CXX ?= i686-w64-mingw32-g++
endif

ifeq ($(origin STRIP),default)
	STRIP := i686-w64-mingw32-strip
else
	STRIP ?= i686-w64-mingw32-strip
endif

WINDRES ?= i686-w64-mingw32-windres

# -masm=intel: AT&T syntax makes inline assembly porting harder
# -shared: Currently all binary targets are libraries (so it makes sense as a default option)
# -O2: Reduces binary size a bit when compared to -O0 (the default)
SP_CFLAGS := -std=c++17 -masm=intel -shared -O2

# Test stack alignment flags (GCC and Clang have different ones)
SP_CFLAGS_TEST := $(shell echo 'int main(){}' | $(CC) -E -mstack-alignment=2 - > /dev/null 2>&1)

ifeq ($(.SHELLSTATUS),0)
	SP_CFLAGS += -mstack-alignment=2
endif

SP_CFLAGS_TEST := $(shell echo 'int main(){}' | $(CC) -E -mincoming-stack-boundary=2 - > /dev/null 2>&1)

ifeq ($(.SHELLSTATUS),0)
	SP_CFLAGS += -mincoming-stack-boundary=2
endif

# -DPATTERNS_USE_HINTS=1: Default Patterns option for SilentPatch
# -D_USE_MATH_DEFINES=: Make sure that M_PI gets defined
# -DUNICODE: Required by some window functions in SilentPatchSA
# -DNDEBUG: Disables some debug/enables some release features
SP_CFLAGS += -DPATTERNS_USE_HINTS=1 -D_USE_MATH_DEFINES= -DUNICODE -DNDEBUG $(CFLAGS)

# -Wl,--large-address-aware: Enables higher address space for 32-bit
# -lshlwapi: Library used by most (if not all) of SilentPatch
# THe rest: Statically link MinGW stuff to avoid runtime dependencies
SP_LDFLAGS := -Wl,--large-address-aware -lshlwapi -static-libgcc -static-libstdc++ -static -lpthread $(LDFLAGS)

SP_UTF8 := $(BUILDDIR)/SilentPatch_utf8.rc

all: DDraw SilentPatchIII SilentPatchVC .WAIT strip

utf8_rc: $(ROOTDIR)/SilentPatch/SilentPatch.rc
	iconv -f UTF-16 -t UTF-8 $(ROOTDIR)/SilentPatch/SilentPatch.rc -o $(SP_UTF8)

strip:
	$(STRIP) --strip-unneeded $(BINDIR)/*.dll $(BINDIR)/*.asi

include $(ROOTDIR)/DDraw/Makefile
include $(ROOTDIR)/SilentPatchIII/Makefile
include $(ROOTDIR)/SilentPatchVC/Makefile
include $(ROOTDIR)/SilentPatchSA/Makefile

.PHONY: utf8_rc strip DDraw SilentPatchIII SilentPatchVC sa_rc libflac SilentPatchSA
