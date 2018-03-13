PREFIX = arm-none-eabi-
REMOVE_CMD = rm

STARTUP_C = 

TARGET = main

OUTDIR = ./Build

EXTRAINCDIRS = 

SRC_HW = 

SRC_AP = 

SRC_LB = 

SRC_MENU = 


SRC = $(SRC_HW) $(SRC_AP) $(SRC_LB) $(SRC_MENU)

THUMb = -mthumb

INCLUDE = -I./include -I.



CC = $(PREFIX)gcc
C++ = $(PREFIX)g++
OBJDUMP = $(PREFIX)objdump
OBJCOPY = $(PREFIX)objcopy
OBJNM = $(PREFIX)nm
SIZE = $(PREFIX)size
REMOVE = $(REMOVE_CMD) -rf


CFLAGS = -gdwarf-2 -O2 -mcpu=cortex-m3 -mthumb-interwork -DSTM32F10X_MD
CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls
CFLAGS += -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=start_stm32f10x.lst -MD -MP -MF $(TARGET).elf.d
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

CONLYFLAGS += -Wnested-externs
CONLYFLAGS += -std=gnu99

LDFLAGS = -static -nostlib -nostratfiles -Wl,-Map=$(TARGET).map,--cref,--gc-sections -L./ -lc -lm -lc -lgcc -T.//STM32F10x_128K_20K_flash.ld

ELFSIZE = $(SIZE) -A $(TARGET).elf

MSG_LOAD_FILE = Created load file : 
MSG_EXTENDED_LISTING = Creating Extended Listing/Disassembly:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = ---- Linking :
MSG_CLEANING = Cleaning project:
MSG_ASMFROMC = "Creating asm-File from C-Source:"

ALLSRC = $(SRC)

ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))

all: createdirs build sizeinfo gcc_version

elf: $(TARGET).elf
lss: $(TARGET).lss
sym: $(TARGET).sym
hex: $(TARGET).hex
bin: $(TARGET).bin

build: elf hex bin lss sym

sizeinfo:
	@echo code size $@
	$(ELFSIZE)

gcc_version:
	@echo gcc version make $@
	$(CC) --version

createdirs:
	-@md $(OUTDIR) >NUL 2>&1 || echo "" >NUL
	-@md $(OUTDIR)\dep > NUL 2>&1 || echo "">NUL

%.hex: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O ihex $< $@

%.bin: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O binary $< $@

%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C -r $< > $@

%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	$(OBJNM) -n $< > $@
.SECONDARY : $(TARGET).elf
.PRECIOUS : $(ALLOBJ)
%.elf:  $(ALLOBJ)
	@echo $(MSG_LINKING) $@
	$(CC) $(THUMB) $(CFLAGS) $(ALLOBJ) --output $@ $(LDFLAGS)

# Compile: create object files from C source files.
define COMPILE_C_TEMPLATE
$(notdir $(basename $(1))).o : $(1)
	@echo $(MSG_COMPILING) $$< to $$@
	$(CC) -c $(THUMB) $$(CFLAGS) $$(CONLYFLAGS) $$< -o $$@ 
endef
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 


# Compile: create assembler files from C source files. ARM/Thumb
$(SRC:.c=.s) : %.s : %.c
	@echo $(MSG_ASMFROMC) $< to $@
	$(CC) $(THUMB) -S $(CFLAGS) $(CONLYFLAGS) $< -o $@
	

###################################################################################################
###################################################################################################
###################################################################################################
###################################################################################################
###################################################################################################
# Define all listing files (used for make clean).
LSTFILES   = $(addsuffix .lst, $(ALLSRCBASE))
# Define all depedency-files (used for make clean).
DEPFILES   = $(addsuffix .o.d, $(ALLSRCBASE))


# Target: clean project.
clean: clean_list

clean_list :
	@echo $(MSG_CLEANING)
	$(REMOVE) $(TARGET).map
	$(REMOVE) $(TARGET).elf
	$(REMOVE) $(TARGET).elf.d
	$(REMOVE) $(TARGET).hex
	$(REMOVE) $(TARGET).bin
	$(REMOVE) $(TARGET).sym
	$(REMOVE) $(TARGET).lss
	$(REMOVE) $(ALLOBJ)
	$(REMOVE) $(LSTFILES)
	$(REMOVE) $(DEPFILES)
	$(REMOVE) $(SRC:.c=.s)
	$(REMOVE) *.lst
	$(REMOVE) NUL
	

# Create object files directory
##$(shell mkdir $(OBJDIR) 2>/dev/null)

# Include the dependency files.
#-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)
-include $(wildcard dep/*)

# Listing of phony targets.
.PHONY : all finish \
build elf hex bin lss sym clean clean_list createdirs sizeinfo





