# TODO: Pull the metadata from an external file
SPSA_NAME ?= SilentPatchSA
SPSA_EXT ?= .asi
SPSA_FULL_NAME ?= SilentPatch for San Andreas
SPSA_REVISION_ID ?= 33
SPSA_BUILD_ID ?= 2
SPSA_COPYRIGHT ?= 2014-2024

SPSA_RCFLAGS := -DSILENTPATCH_NAME="$(SPSA_NAME)" -DSILENTPATCH_EXT="$(SPSA_EXT)"
SPSA_RCFLAGS += -DSILENTPATCH_FULL_NAME="$(SPSA_FULL_NAME)" -DSILENTPATCH_REVISION_ID="$(SPSA_REVISION_ID)"
SPSA_RCFLAGS += -DSILENTPATCH_BUILD_ID="$(SPSA_BUILD_ID)" -DSILENTPATCH_COPYRIGHT="$(SPSA_COPYRIGHT)"

SPSA_DIR := $(ROOTDIR)/SilentPatchSA
SPSA_RES_MAIN := $(BUILDDIR)/SilentPatch_res.o
SPSA_RES_SA := $(BUILDDIR)/SilentPatchSA_res.o

SPSA_SOURCES := \
	$(ROOTDIR)/SilentPatch/Desktop.cpp \
	$(ROOTDIR)/SilentPatch/FriendlyMonitorNames.cpp \
	$(ROOTDIR)/SilentPatch/ParseUtils.cpp \
	$(ROOTDIR)/SilentPatch/SVF.cpp \
	$(ROOTDIR)/SilentPatch/TheFLAUtils.cpp \
	$(ROOTDIR)/SilentPatch/Utils/Patterns.cpp \
	$(ROOTDIR)/SilentPatchSA/AudioHardwareSA.cpp \
	$(ROOTDIR)/SilentPatchSA/FireManagerSA.cpp \
	$(ROOTDIR)/SilentPatchSA/FLACDecoderSA.cpp \
	$(ROOTDIR)/SilentPatchSA/GeneralSA.cpp \
	$(ROOTDIR)/SilentPatchSA/ModelInfoSA.cpp \
	$(ROOTDIR)/SilentPatchSA/PedSA.cpp \
	$(ROOTDIR)/SilentPatchSA/PlayerInfoSA.cpp \
	$(ROOTDIR)/SilentPatchSA/PNGFile.cpp \
	$(ROOTDIR)/SilentPatchSA/PoolsSA.cpp \
	$(ROOTDIR)/SilentPatchSA/ScriptSA.cpp \
	$(ROOTDIR)/SilentPatchSA/SilentPatchSA.cpp \
	$(ROOTDIR)/SilentPatchSA/StdAfxSA.cpp \
	$(ROOTDIR)/SilentPatchSA/TimerSA.cpp \
	$(ROOTDIR)/SilentPatchSA/VehicleSA.cpp \
	$(ROOTDIR)/SilentPatchSA/WaveDecoderSA.cpp

SPSA_INCLUDES := \
	-I$(RWG37SDK)/include/d3d9 \
	-I$(ROOTDIR)/SilentPatch \
	-I$(SPSA_DIR) \
	-I$(SPSA_DIR)/libflac/include

SPSA_CFLAGS := $(SP_CFLAGS) -D_GTA_SA -DFLAC__NO_DLL
SPSA_LDFLAGS := $(SP_LDFLAGS)

sa_rc: utf8_rc $(SPSA_DIR)/SilentPatchSA.rc
	$(WINDRES) $(SPSA_RCFLAGS) -I$(ROOTDIR)/SilentPatch -i $(SP_UTF8) -o $(SPSA_RES_MAIN)
	iconv -f UTF-16 -t UTF-8 $(SPSA_DIR)/SilentPatchSA.rc -o $(BUILDDIR)/SilentPatchSA_utf8.rc
	$(WINDRES) $(SPSA_RCFLAGS) -I$(SPSA_DIR) -i $(BUILDDIR)/SilentPatchSA_utf8.rc -o $(SPSA_RES_SA)

LIBFLAC_RULE := libflac
LIBFLAC_FLAGS := \
	-DCMAKE_SYSTEM_NAME=Windows \
	-DBUILD_CXXLIBS=OFF \
	-DINSTALL_MANPAGES=OFF \
	-DBUILD_PROGRAMS=OFF \
	-DBUILD_EXAMPLES=OFF \
	-DBUILD_TESTING=OFF \
	-DBUILD_DOCS=OFF \
	-DWITH_OGG=OFF

ifeq ($(NO_FLAC_SUPPORT),1)
	SPSA_CFLAGS += -DNO_FLAC_SUPPORT
	LIBFLAC_RULE := 
else
	SPSA_LDFLAGS += -L"$(BUILDDIR)"/libflac/src/libFLAC -Wl,-Bstatic -lFLAC
endif

ifeq ($(NO_INLINE_OPERAND_ASM),1)
	SPSA_CFLAGS += -DNO_INLINE_OPERAND_ASM
endif

libflac: $(SPSA_DIR)/libflac/CMakeLists.txt
	[ ! -d $(BUILDDIR)/libflac ] && mkdir -p $(BUILDDIR)/libflac
	CC=$(CC) CXX=$(CXX) cmake -B $(BUILDDIR)/libflac -S $(SPSA_DIR)/libflac -G"Unix Makefiles" $(LIBFLAC_FLAGS)
	make -C $(BUILDDIR)/libflac

SilentPatchSA: sa_rc $(LIBFLAC_RULE) $(SPSA_SOURCES)
ifeq ($(strip $(RWG37SDK)),)
	$(error Please set RWG37SDK to the RenderWare 3.7 SDK path)
endif
	
ifneq ($(I_WANT_SEGFAULTS),1)
	$(error SilentPatchSA is too unstable for normal use! Set I_WANT_SEGFAULTS=1 to build it anyway)
endif
	
	$(CXX) $(SPSA_CFLAGS) $(SPSA_RCFLAGS) -o $(BINDIR)/SilentPatchSA.asi $(SPSA_SOURCES) $(SPSA_RES_MAIN) $(SPSA_RES_SA) $(SPSA_INCLUDES) $(SPSA_LDFLAGS)
