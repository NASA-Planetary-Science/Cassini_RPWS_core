##############################################################################
# Generic definitions for: Native Programs + Hosted Python Environment

ifeq ($(PREFIX),)
ifeq ($(HOME),)  
PREFIX:=$(USERPROFILE)
else                 
PREFIX=$(HOME)
endif                
endif                

ifeq ($(INST_ETC),)
INST_ETC=$(PREFIX)/etc
endif                 

ifeq ($(INST_SHARE),)
INST_SHARE=$(PREFIX)/share
endif                     

ifeq ($(INST_DOC),)
INST_DOC=$(PREFIX)/doc
endif

ifeq ($(INST_INC),)
INST_INC=$(PREFIX)/include
endif

ifeq ($(N_ARCH),)
N_ARCH=$(shell uname -s).$(shell uname -p)
endif

ifeq ($(H_ARCH),)
ifeq ($(PYVER),)
PYVER=$(shell python -c "import sys; print '.'.join( sys.version.split()[0].split('.')[:2] )")
endif
H_ARCH=python$(PYVER)
endif

ifeq ($(INST_NAT_BIN),)
INST_NAT_BIN=$(PREFIX)/bin/$(N_ARCH)
endif

ifeq ($(INST_NAT_LIB),)
INST_NAT_LIB=$(PREFIX)/lib/$(N_ARCH)
endif

# Gonna use the centos5 bin directory here for python scripts, cuts down on
# the size of the path argument
ifeq ($(INST_HOST_BIN),)
INST_HOST_BIN=$(PREFIX)/bin/$(N_ARCH)
endif

ifeq ($(INST_HOST_LIB),)
INST_HOST_LIB=$(PREFIX)/lib/$(H_ARCH)
endif

ifeq ($(INST_EXT_LIB),)
INST_EXT_LIB=$(PREFIX)/lib/$(N_ARCH)/$(H_ARCH)
endif

ifeq ($(MAG_DATA),)
MAG_DATA=$(PREFIX)/mag
endif

ifeq ($(INST_DAS1_DSDF),)
INST_DAS1_DSDF=$(INST_ETC)/datasetroot
endif

BD:=build.$(N_ARCH)

##############################################################################
# Native Platform specific include

UNAME = $(shell uname)

include $(UNAME).mak
