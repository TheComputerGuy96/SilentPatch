# TODO: Pull the metadata from an external file
SP3_NAME ?= SilentPatchIII
SP3_EXT ?= .asi
SP3_FULL_NAME ?= SilentPatch for GTA III
SP3_REVISION_ID ?= 9
SP3_BUILD_ID ?= 2
SP3_COPYRIGHT ?= 2013-2024

SP3_RCFLAGS := -DSILENTPATCH_NAME="$(SP3_NAME)" -DSILENTPATCH_EXT="$(SP3_EXT)"
SP3_RCFLAGS += -DSILENTPATCH_FULL_NAME="$(SP3_FULL_NAME)" -DSILENTPATCH_REVISION_ID="$(SP3_REVISION_ID)"
SP3_RCFLAGS += -DSILENTPATCH_BUILD_ID="$(SP3_BUILD_ID)" -DSILENTPATCH_COPYRIGHT="$(SP3_COPYRIGHT)"

SP3_RES := $(BUILDDIR)/SilentPatchIII_res.o

SP3_SOURCES := \
	$(ROOTDIR)/SilentPatch/Common.cpp \
	$(ROOTDIR)/SilentPatch/Common_ddraw.cpp \
	$(ROOTDIR)/SilentPatch/Desktop.cpp \
	$(ROOTDIR)/SilentPatch/ParseUtils.cpp \
	$(ROOTDIR)/SilentPatch/RWGTA.cpp \
	$(ROOTDIR)/SilentPatch/StoredCar.cpp \
	$(ROOTDIR)/SilentPatch/SVF.cpp \
	$(ROOTDIR)/SilentPatch/TheFLAUtils.cpp \
	$(ROOTDIR)/SilentPatch/Timer.cpp \
	$(ROOTDIR)/SilentPatch/Utils/Patterns.cpp \
	$(ROOTDIR)/SilentPatchIII/ModelInfoIII.cpp \
	$(ROOTDIR)/SilentPatchIII/SilentPatchIII.cpp \
	$(ROOTDIR)/SilentPatchIII/StdAfxIII.cpp

SP3_INCLUDES := -I$(RWG37SDK)/include/d3d8 -I$(ROOTDIR)/SilentPatch
SP3_CFLAGS := $(SP_CFLAGS) -D_GTA_III

SilentPatchIII: utf8_rc $(SP3_SOURCES)
ifeq ($(strip $(RWG37SDK)),)
	$(error Please set RWG37SDK to the RenderWare 3.7 SDK path)
endif
	
	$(WINDRES) $(SP3_RCFLAGS) $(SP3_INCLUDES) -i $(SP_UTF8) -o $(SP3_RES)
	$(CXX) $(SP3_CFLAGS) $(SP3_RCFLAGS) -o $(BINDIR)/SilentPatchIII.asi $(SP3_SOURCES) $(SP3_RES) $(SP3_INCLUDES) $(SP_LDFLAGS)
