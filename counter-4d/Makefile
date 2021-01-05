NAME = multiple
CFLAGS = -Og -Wall -std=c99 -ffreestanding
LDFLAGS = -nostdlib -e main

.PRECIOUS: %.elf %.o

all : $(NAME).bin

%.bin: %.elf
	 arm-none-eabi-objcopy $< -O binary $@

%.elf: %.o
	 arm-none-eabi-ld $(LDFLAGS) $< -o $@

%.o: %.c
	 arm-none-eabi-gcc $(CFLAGS) -c $< -o $@

install: $(NAME).bin
	rpi-install.py $<

clean:
	rm -f *.o *.elf *.bin