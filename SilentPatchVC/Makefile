# TODO: Pull the metadata from an external file
SPVC_NAME ?= SilentPatchVC
SPVC_EXT ?= .asi
SPVC_FULL_NAME ?= SilentPatch for Vice City
SPVC_REVISION_ID ?= 11
SPVC_BUILD_ID ?= 1
SPVC_COPYRIGHT ?= 2013-2024

SPVC_RCFLAGS := -DSILENTPATCH_NAME="$(SPVC_NAME)" -DSILENTPATCH_EXT="$(SPVC_EXT)"
SPVC_RCFLAGS += -DSILENTPATCH_FULL_NAME="$(SPVC_FULL_NAME)" -DSILENTPATCH_REVISION_ID="$(SPVC_REVISION_ID)"
SPVC_RCFLAGS += -DSILENTPATCH_BUILD_ID="$(SPVC_BUILD_ID)" -DSILENTPATCH_COPYRIGHT="$(SPVC_COPYRIGHT)"

SPVC_RES := $(BUILDDIR)/SilentPatchVC_res.o

SPVC_SOURCES := \
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
	$(ROOTDIR)/SilentPatchVC/ModelInfoVC.cpp \
	$(ROOTDIR)/SilentPatchVC/SilentPatchVC.cpp \
	$(ROOTDIR)/SilentPatchVC/StdAfxVC.cpp \
	$(ROOTDIR)/SilentPatchVC/VehicleVC.cpp

SPVC_INCLUDES := -I$(RWG37SDK)/include/d3d8 -I$(ROOTDIR)/SilentPatch
SPVC_CFLAGS := $(SP_CFLAGS) -D_GTA_VC

SilentPatchVC: utf8_rc $(SPVC_SOURCES)
ifeq ($(strip $(RWG37SDK)),)
	$(error Please set RWG37SDK to the RenderWare 3.7 SDK path)
endif
	
	$(WINDRES) $(SPVC_RCFLAGS) $(SPVC_INCLUDES) -i $(SP_UTF8) -o $(SPVC_RES)
	$(CXX) $(SPVC_CFLAGS) $(SPVC_RCFLAGS) -o $(BINDIR)/SilentPatchVC.asi $(SPVC_SOURCES) $(SPVC_RES) $(SPVC_INCLUDES) $(SP_LDFLAGS)
