#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM)
endif

-include $(DEVKITARM)/gba_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output, if this ends with _mb a multiboot image is generated
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
# HAM Stuff no longer used ....
#
#PROGNAME =unused
#OFILES+= unused
#ADD_LIBS+= unused	

# .................
#

TARGET		:=	$(shell basename $(CURDIR))
BUILD		:=	build
SOURCES		:=	source
DATA		:=	
INCLUDES	:=	$(DEVKITARM)
GDB_DIRS	= 	$cdir:$cwd:$(ADD_GDB_SOURCE_DIRS)

ifeq ($(MAKECMDGOALS),gdb)
DEBUG_SET	:=	gdb
endif

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
#ARCH	:=	-mthumb -mthumb-interwork
ARCH	:=

ifneq ($(DEBUG_SET),gdb)
THIS_BUILD	:=	"Release Build"
CFLAGS	:=	-Wall -O2 -save-temps \
			-mcpu=arm7tdmi -mtune=arm7tdmi\
 			-fomit-frame-pointer\
			-ffast-math \
			$(ARCH)
ASFLAGS	:=	$(ARCH)
else
THIS_BUILD	:=	"Debug Build"
CFLAGS	:=	-g -Wall -O0 -save-temps \
			-mcpu=arm7tdmi -mtune=arm7tdmi\
			-ffast-math \
			$(ARCH)
ASFLAGS	:=	$(ARCH) -g
endif
CFLAGS	+=	$(INCLUDE)
CXXFLAGS := $(CFLAGS)


ifneq ($(DEBUG_SET),gdb)
LDFLAGS	=	$(ARCH) -Wl,-Map,$(notdir $@).map
else
LDFLAGS	=	-g $(ARCH) -Wl,-Map,$(notdir $@).map
endif

#---------------------------------------------------------------------------------
# path to tools - this can be deleted if you set the path to the toolchain in windows
#---------------------------------------------------------------------------------
export PATH		:=	$(DEVKITARM)/bin:$(DEVKITPRO)/msys/bin:$(PATH)

#---------------------------------------------------------------------------------
# any extra libraries we wish to link with the project
#---------------------------------------------------------------------------------
LIBS	:=

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(LIBGBA)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
					$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# automatically build a list of object files for our project
#---------------------------------------------------------------------------------
CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

export OFILES	:= $(addsuffix .o,$(BINFILES)) $(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

#---------------------------------------------------------------------------------
# build a list of include paths
#---------------------------------------------------------------------------------
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(dir)/include) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					$(foreach dir,$(CURDIR), -I$(dir)/include) \
					-I$(CURDIR)

#---------------------------------------------------------------------------------
# build a list of library paths
#---------------------------------------------------------------------------------
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean

#---------------------------------------------------------------------------------
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	make "DEBUG_SET=$(DEBUG_SET)" --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

all	: buildtype $(BUILD)

buildtype:
	@echo "Build type: " $(THIS_BUILD)

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	rm -fr $(BUILD) $(TARGET).elf $(TARGET).gba

#---------------------------------------------------------------------------------
vbawin:	clean all
	$(DEVKITPRO)/tools/win32/vbawin.exe $(TARGET).gba

#---------------------------------------------------------------------------------
runvbawin:
	$(DEVKITPRO)/tools/win32/vbawin.exe $(TARGET).gba

#---------------------------------------------------------------------------------
vba:	clean all
	$(DEVKITPRO)/tools/win32/vbaSDL/vba.exe -3 $(TARGET).gba

#---------------------------------------------------------------------------------
runvba:
	$(DEVKITPRO)/tools/win32/vbaSDL/vba.exe -3 $(TARGET).gba

#---------------------------------------------------------------------------------
startsdl:
	$(DEVKITPRO)/tools/win32/vbaSDL/vba.exe -3 -Gtcp:44444 &

#---------------------------------------------------------------------------------
makeini:
	echo "File $(TARGET).elf" > insight.ini
	echo "target remote 127.0.0.1:44444" >>insight.ini
	echo "load $(TARGET).elf" >>insight.ini
	echo "b main" >>insight.ini
	echo "directory $(GDB_DIRS)">>insight.ini
	echo "c" >>insight.ini

#---------------------------------------------------------------------------------
startinsight:
	$(DEVKITPRO)/insight/bin/arm-eabi-insight.exe --command=insight.ini $(TARGET).elf

#---------------------------------------------------------------------------------
gdb:	clean
	rm -f gdbtk.ini
	rm -f /c/gdbtk.ini
	@make "DEBUG_SET=$(DEBUG_SET)" all 
	make startsdl makeini startinsight

#---------------------------------------------------------------------------------
rungdb: startsdl makeini startinsight

testinsight: makeini startinsight

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT).gba	:	$(OUTPUT).elf

$(OUTPUT).elf	:	$(OFILES)

%.o	:	%.pcx
	echo $(notdir $<)
	$(bin2o)

-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#--------------------------------------------------------------------------------
