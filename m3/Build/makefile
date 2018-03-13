
PREFIX = arm-none-eabi-
REMOVE_CMD = rm
#start file
STARTUP_C = Hw_StartUp.c
#target file (output file name)
TARGET = main
#build folder
OUTDIR = ./Build
#extra header folder
EXTRAINCDIRS = 


SRC_HW = ../LIB_HW/Hw_Core/$(STARTUP_C)              \
         


SRC_LB = ../LIB/Ld_printf.c                          \
         ../LIB/Util.c                               \

         
SRC_AP =

SRC_MENU =  


#source file 
SRC =$(SRC_HW) $(SRC_LB) $(SRC_MENU) $(SRC_AP)
#thumb mode
THUMB = -mthumb
#include header
INCLUDE = -I./include -I.

#C compiler option
CC = $(PREFIX)gcc
CPP = $(PREFIX)g++
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump
OBJNM = $(PREFIX)nm
SIZE = $(PREFIX)size
REMOVE = $(REMOVE_CMD) -rf

# Compiler flags.
#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)
#cpu type 설정 및 thumb 모드 설정 arch 설정 하는 플레이그
CFLAGS  = -gdwarf-2 -O2 -mcpu=cortex-m3 -mthumb-interwork -DSTM32F10X_MD 

# -mfloat-abi=name
#    Specifies which floating-point ABI to use.
#    "soft": Causes GCC to generate output containing library calls for
#            floating-point operations. Same as -msoft-float.
#    "softfp": Allows the generation of code using hardware floating-point
#            instructions, but still uses the soft-float calling conventions.
#    "hard": Allows generation of floating-point instructions and uses
#            FPU-specific calling conventions. Same as -mhard-float
#    Note that the hard-float and soft-float ABIs are not link-compatible;
#    you must compile your entire program with the same ABI, and link with a
#    compatible set of libraries.
#
# -msoft-float, -mhard-float: Use -mfloat-abi=name instead.
#
# -mfpu=fpv4-sp-d16
#    Specify which FPU is available. I think, this is clear from the
#    -mcpu= but OTOH, we explicitly link to fpv4-sp-d16 libraries, so let's
#    keep it in there to be sure.
#
# -fsingle-precision-constant
#    Ensure that 1.0 is treated as 1.0f. Avoids that intermediate DOUBLE
#    floats are generated. Writing the 'f' suffix is better but error-prone.
#
# -mfix-cortex-m3-ldrd
#    Is automatically enabled for Cortex-M3.
#
# -fno-common : unclear if needed
#
# -lm -lc
#    Required during linking for sqrtf() etc.
#

#Need to put this pack in CFLAGS????
#-D"assert_param(x)="
#float add ??? 
#CFLAGS  = -march=armv7-m -mthumb-interwork -gdwarf-2 -O2 -mfloat-abi=soft -msoft-float
#CPU_SPEC  += -mfloat-abi=soft
# Hardware float support
#CPU_SPEC  += -mfloat-abi=hard -mfpu=fpv4-sp-d16  -ffast-math
#CFLAGS += -fsingle-precision-constant -Wdouble-promotion
#CFLAGS += -mfpu=fpv4-sp-d16 -mfloat-abi=hard

#CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls -msoft-float
CFLAGS += $(INCLUDE) -mlong-calls -ffunction-sections -fdata-sections -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredundant-decls 
CFLAGS += -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=start_stm32f10x.lst -MD -MP -MF $(TARGET).elf.d
#header file add 경로는 자동으로 해서 참조
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))
#무엇인지 확인
# flags only for C
CONLYFLAGS += -Wnested-externs 
# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
CONLYFLAGS += -std=gnu99
# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
#LDFLAGS = -Map=$(TARGET).map --cref
#이게 맞는지? 정적 파일과 lib 사용과 startfile 사용을 하지 않는다고 선언 하는 것 -nostdlib 라이브러리 사용 하지 않는다는 flag
LDFLAGS = -static -nostdlib -nostartfiles -Wl,-Map=$(TARGET).map,--cref,--gc-sections -L./ -lc  -lm  -lc -lgcc -T.//STM32F10x_flash.ld
#LDFLAGS = -static -nostdlib -nostartfiles -u _printf_float --specs=nano.specs -lc -lnosys -Wl,-Map=$(TARGET).map,--cref,--gc-sections -L./ -lc  -lm  -lc -lgcc -T.//STM32F10x_flash.ld
#LDFLAGS += --specs=nano.specs -lc -lnosys
#LDFLAGS += -u _printf_float
#ELF32_LDFLAGS = -Wl,-T,stm32f10x.ld


ELFSIZE = $(SIZE) -A $(TARGET).elf

# Define Messages
# English
MSG_LOAD_FILE = Creating load file:
MSG_EXTENDED_LISTING = Creating Extended Listing/Disassembly:
MSG_SYMBOL_TABLE = Creating Symbol Table:
MSG_LINKING = ---- Linking :
MSG_CLEANING = Cleaning project:
MSG_ASMFROMC = "Creating asm-File from C-Source:"

# List of all source files.
ALLSRC     =  $(SRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
#ALLOBJ = $(addprefix $(OUTDIR)/, $(addsuffix .o, $(ALLSRCBASE)))
ALLOBJ = $(addsuffix .o, $(ALLSRCBASE))


# Default target.
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

# Create output directories.
createdirs:
	-@md $(OUTDIR) >NUL 2>&1 || echo "" >NUL
	-@md $(OUTDIR)\dep >NUL 2>&1 || echo "" >NUL

# Create final output file (.hex) from ELF output file.
%.hex: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O ihex $< $@
	
# Create final output file (.bin) from ELF output file.
%.bin: %.elf
	@echo $(MSG_LOAD_FILE) $@
	$(OBJCOPY) -O binary $< $@

# Create extended listing file/disassambly from ELF output file.
# using objdump testing: option -C
%.lss: %.elf
	@echo $(MSG_EXTENDED_LISTING) $@
	$(OBJDUMP) -h -S -C -r $< > $@
#	$(OBJDUMP) -x -S $< > $@

# Create a symbol table from ELF output file.
%.sym: %.elf
	@echo $(MSG_SYMBOL_TABLE) $@
	$(OBJNM) -n $< > $@

# Link: create ELF output file from object files.
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


