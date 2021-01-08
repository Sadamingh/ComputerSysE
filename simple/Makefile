NAME = simple

CFLAGS = -I$(ENV)/include -g -Wall -Og -std=c99 -ffreestanding -mapcs-frame -fno-omit-frame-pointer
LDFLAGS = -nostdlib -T memmap -L$(ENV)/lib
LDLIBS = 


all : $(NAME).bin

%.bin: %.elf
	arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o start.o cstart.o
	arm-none-eabi-gcc $(LDFLAGS) $^ $(LDLIBS) -o $@

%.o: %.c
	arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

%.o: %.s
	arm-none-eabi-as $(ASFLAGS) $< -o $@

%.list: %.o
	arm-none-eabi-objdump --no-show-raw-insn -d $< > $@

install: $(NAME).bin
	rpi-install.py $<

clean:
	rm -f *.o *.bin *.elf *.list *~

.PHONY: all clean install
.PRECIOUS: %.elf %.o

# empty recipe used to disable built-in rules for native build
%:%.c
%:%.o

define ENV_ERROR_MESSAGE
ERROR - ENV environment variable is not set.

Review instructions for properly configuring your shell.
https://medium.com/adamedelwiess/computer-systems-experiments-3-configure-experiment-environment-e2acc878a1b1

endef

ifndef ENV
$(error $(ENV_ERROR_MESSAGE))
endif

