ifeq ($(LINUX),1)
SUBDIRS		:= ip efabcfg sfcaffinity solar_clusterd
OTHER_SUBDIRS	:= unix chariot firmware
ifneq ($(ONLOAD_ONLY),1)
SUBDIRS		+= ftl unifdef misc mc-comms sfutils sfutils-linux
endif

ifeq ($(BUILDORM),1)
SUBDIRS		+= jansson-2.7 onload_remote_monitor
else
$(warning WARNING: onload_remote_monitor will not be available as dependencies are not met)
endif
endif

ifeq ($(WINDOWS),1)
SUBDIRS		:= win mc-comms
OTHER_SUBDIRS	:= misc
DRIVER_SUBDIRS    := win
INSTALLER_SUBDIRS := win
endif

ifeq ($(FREEBSD),1)
SUBDIRS		:= mc-comms
OTHER_SUBDIRS	:= 
DRIVER_SUBDIRS  := 
endif

ifeq ($(MACOSX),1)
SUBDIRS		:= sfutils
OTHER_SUBDIRS	:=
DRIVER_SUBDIRS  := 
endif

ifeq ($(SOLARIS),1)
SUBDIRS       	:= solaris sfutils
DRIVER_SUBDIRS	:=
OTHER_SUBDIRS	:= 
ifneq ($(ONLOAD_ONLY),1)
# libcitools; particularly sysdep.h does not have sparcv9 support at present
ifneq ($(ISA),sparcv9)
SUBDIRS		+= mc-comms
endif
endif
endif

ifeq ($(DOS32_UTILS)$(LINUX_UIO_UTILS),1)
SUBDIRS		:= sfutils
endif

all:
	+@$(MakeSubdirs)

clean:
	@$(MakeClean)
