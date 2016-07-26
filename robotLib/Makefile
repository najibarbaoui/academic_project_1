
#########  AVR Project Makefile Template   #########
######                                        ######
######    Copyright (C) 2003, Pat Deegan,     ######
######            Psychogenic Inc             ######
######          All Rights Reserved           ######
######                                        ######
###### You are free to use this code as part  ######
###### of your own applications provided      ######
###### you keep this copyright notice intact  ######
###### and acknowledge its authorship with    ######
###### the words:                             ######
######                                        ######
###### "Contains software by Pat Deegan of    ######
###### Psychogenic Inc (www.psychogenic.com)" ######
######                                        ######
###### If you use it as part of a web site    ######
###### please include a link to our site,     ######
###### http://electrons.psychogenic.com  or   ######
###### http://www.psychogenic.com             ######
######                                        ######
###### Modifications by Jerome Collin for INF1995 ########


######Modifications par équipe 0521 INF1995  #######
###### Crée des librairies par defaut                #######
####################################################


##### This Makefile will make compiling Atmel AVR
##### micro controller projects simple with Linux
##### or other Unix workstations and the AVR-GCC
##### tools.
#####
##### It supports C, C++ and Assembly source files.
#####
##### Customize the values as indicated below and :
##### make
##### make disasm
##### make stats
##### make hex
##### make writeflash
##### make gdbinit
##### or make clean
#####
##### See the http://electrons.psychogenic.com/
##### website for detailed instructions


####################################################
#####                                          #####
#####              Configuration               #####
#####                                          #####
##### Customize the values in this section for #####
##### your project. MCU, PROJECTNAME and       #####
##### PRJSRC must be setup for all projects,   #####
##### the remaining variables are only         #####
##### relevant to those needing additional     #####
##### include dirs or libraries and those      #####
##### who wish to use the avrdude programmer   #####
#####                                          #####
##### See http://electrons.psychogenic.com/    #####
##### for further details.                     #####
#####                                          #####
####################################################

####DOSSIERS DE RECHERCHE
VPATH = $(OBJPATH) $(SRCPATH)

#####         Target Specific Details          #####
#####     Customize these for your project     #####

# Name of target controller
# (e.g. 'at90s8515', see the available avr-gcc mmcu
# options for possible values)
MCU = atmega324pa

# Name of our project
# (use a single word, e.g. 'myproject')
PROJECTNAME = librobot

# Source files
# List C/C++/Assembly source files:
# (list all files to compile, e.g. 'a.c b.cpp as.S'):
# Use .cc, .cpp or .C suffix for C++ files, use .S
# (NOT .s !!!) for assembly source code files.
PRJSRC = $(notdir $(wildcard $(SRCPATH)/*.cpp))

# additional includes (e.g. -I/path/to/mydir)
INC= -Iinclude

# libraries to link in (e.g. -lmylib)
LIBS = 

# Optimization level,
# use s (size opt), 1, 2, 3 or 0 (off)
OPTLEVEL = s

####Chemin vers les docs de doxygen (utilisé pour cleandoc)
DOCS = docs

####Chemin vers les objets
OBJPATH = objects

####Chemin vers les sources
SRCPATH = src



#####      AVR Dude 'writeflash' options       #####
#####  If you are using the avrdude program
#####  (http://www.bsdhome.com/avrdude/) to write
#####  to the MCU, you can set the following config
#####  options and use 'make writeflash' to program
#####  the device.


# programmer id--check the avrdude for complete list
# of available opts.  These should include stk500,
# avr910, avrisp, bsd, pony and more.  Set this to
# one of the valid "-c PROGRAMMER-ID" values
# described in the avrdude info page.
#
AVRDUDE_PROGRAMMERID = usbasp

# port--serial or parallel port to which your
# hardware programmer is attached
#
AVRDUDE_PORT = /dev/ttyS0


####################################################
#####                Config Done               #####
#####                                          #####
##### You shouldn't need to edit anything      #####
##### below to use the makefile but may wish   #####
##### to override a few of the flags           #####
##### nonetheless                              #####
#####                                          #####
####################################################


##### Flags ####

# HEXFORMAT -- format for .hex file output
HEXFORMAT=ihex

# compiler
CFLAGS=-I. $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall                                        \
	-Wa,-ahlms=$(addprefix $(OBJPATH)/, $(notdir $(firstword $(filter %.lst, $(<:.c=.lst)))))

# c++ specific flags
CPPFLAGS=-fno-exceptions -std=c++98    \
	-Wa,-ahlms=$(addprefix $(OBJPATH)/, $(notdir $(firstword         \
	$(filter %.lst, $(<:.cpp=.lst))\
	$(filter %.lst, $(<:.cc=.lst)) \
	$(filter %.lst, $(<:.C=.lst)))))

# assembler
ASMFLAGS =-I. $(INC) -mmcu=$(MCU)        \
	-x assembler-with-cpp            \
	-Wa,-gstabs,-ahlms=$(addprefix $(OBJPATH)/, $(notdir $(firstword   \
		$(<:.S=.lst) $(<.s=.lst))))


# linker
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)

#archiveur
LIBRAIRIEFLAGS=crs

##### executables ####
CC=avr-gcc
ARCHIVEUR=avr-ar
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
SIZE=avr-size
#AVRDUDE=/home/robot/avrdude/opt/avr/bin/avrdude
AVRDUDE=avrdude
REMOVE=rm -f
REMOVE_REC=rm -f -r

##### automatic target names ####
TRG=$(PROJECTNAME).out
DUMPTRG=$(PROJECTNAME).s

HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex
GDBINITFILE=gdbinit-$(PROJECTNAME)

LIBRAIRIETRG = $(PROJECTNAME).a

# Define all object files.

# Start by splitting source files by type
#  C++
CPPFILES=$(filter %.cpp, $(PRJSRC))
CCFILES=$(filter %.cc, $(PRJSRC))
BIGCFILES=$(filter %.C, $(PRJSRC))
#  C
CFILES=$(filter %.c, $(PRJSRC))
#  Assembly
ASMFILES=$(filter %.S, $(PRJSRC))


# List all object files we need to create
OBJDEPS=$(CFILES:.c=.o)    \
	$(CPPFILES:.cpp=.o)\
	$(BIGCFILES:.C=.o) \
	$(CCFILES:.cc=.o)  \
	$(ASMFILES:.S=.o)

# Define all lst files.
LST=$(filter %.lst, $(OBJDEPS:.o=.lst))

# All the possible generated assembly
# files (.s files)
GENASMFILES=$(filter %.s, $(OBJDEPS:.o=.s))


.SUFFIXES : .c .cc .cpp .C .o .out .s .S \
	.hex .ee.hex .h .hh .hpp


.PHONY: writeflash clean mrproper stats gdbinit stats cleandoc

# Make targets:
# all (librairie), executable, disasm, stats, hex, writeflash/install, clean
all: $(LIBRAIRIETRG)

executable: $(TRG)

disasm: $(DUMPTRG) stats

stats: $(TRG)
	$(OBJDUMP) -h $(TRG)
	$(SIZE) $(TRG)

hex: $(HEXROMTRG)


writeflash: hex
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	 -p $(MCU) -P $(AVRDUDE_PORT) -e        \
	 -U flash:w:$(HEXROMTRG)

install: writeflash

$(DUMPTRG): $(TRG)
	$(OBJDUMP) -S  $< > $@


$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(addprefix $(OBJPATH)/, $(OBJDEPS)) \
	-lm $(LIBS)
	
$(LIBRAIRIETRG): $(OBJDEPS)
	$(ARCHIVEUR) $(LIBRAIRIEFLAGS) $(LIBRAIRIETRG) $(addprefix $(OBJPATH)/, $(OBJDEPS))

	
#### Generating assembly ####
# asm from C
%.s: %.c
	$(CC) -S $(CFLAGS) $< -o $(addprefix $(OBJPATH)/, $(@F))

# asm from (hand coded) asm
%.s: %.S
	$(CC) -S $(ASMFLAGS) $< > $(addprefix $(OBJPATH)/, $(@F))


# asm from C++
.cpp.s .cc.s .C.s :
	$(CC) -S $(CFLAGS) $(CPPFLAGS) $< -o $(addprefix $(OBJPATH)/, $(@F))



#### Generating object files ####
# object from C
.c.o:
	$(CC) $(CFLAGS) -c $< -o $(addprefix $(OBJPATH)/, $(@F))


# object from C++ (.cc, .cpp, .C files)
.cc.o .cpp.o .C.o :
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(addprefix $(OBJPATH)/, $(@F))

# object from asm
.S.o :
	$(CC) $(ASMFLAGS) -c $< -o $(addprefix $(OBJPATH)/, $(@F))


#### Generating hex files ####
# hex files from elf
#####  Generating a gdb initialisation file    #####
.out.hex:
	$(OBJCOPY) -j .text                    \
		-j .data                       \
		-O $(HEXFORMAT) $< $(addprefix $(OBJPATH)/, $(@F))

.out.ee.hex:
	$(OBJCOPY) -j .eeprom                  \
		--change-section-lma .eeprom=0 \
		-O $(HEXFORMAT) $< $(addprefix $(OBJPATH)/, $(@F))


#####  Generating a gdb initialisation file    #####
##### Use by launching simulavr and avr-gdb:   #####
#####   avr-gdb -x gdbinit-myproject           #####
gdbinit: $(GDBINITFILE)

$(GDBINITFILE): $(TRG)
	@echo "file $(TRG)" > $(GDBINITFILE)

	@echo "target remote localhost:1212" \
		                >> $(GDBINITFILE)

	@echo "load"        >> $(GDBINITFILE)
	@echo "break main"  >> $(GDBINITFILE)
	@echo "continue"    >> $(GDBINITFILE)
	@echo
	@echo "Use 'avr-gdb -x $(GDBINITFILE)'"


#### Cleanup ####
clean:
	$(REMOVE) $(TRG) $(OBJPATH)/$(TRG).map $(OBJPATH)/$(DUMPTRG)
	$(REMOVE) $(addprefix $(OBJPATH)/, $(OBJDEPS))
	$(REMOVE) $(addprefix $(OBJPATH)/, $(LST)) $(addprefix $(OBJPATH)/, $(GDBINITFILE))
	$(REMOVE) $(addprefix $(OBJPATH)/, $(GENASMFILES))
	$(REMOVE) $(addprefix $(OBJPATH)/, $(HEXTRG))

mrproper: clean
	$(REMOVE) $(LIBRAIRIETRG)

doc:
	doxygen doxygen_config	

cleandoc:
	$(REMOVE_REC) $(DOCS)



#####                    EOF                   #####

