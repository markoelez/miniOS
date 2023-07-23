CC := i386-elf-gcc
LD := i386-elf-ld
CFLAGS := -m32 -ffreestanding
NASM := nasm
LDFLAGS := -m elf_i386
BOOTLOADER := bootloader/
KERNEL := kernel/
DRIVERS := $(patsubst %.c, %.o, $(wildcard $(KERNEL)drivers/*.c))

all: run

run: $(BOOTLOADER)os-image.bin
	qemu-system-i386 -drive format=raw,file=$<

$(BOOTLOADER)os-image.bin: $(BOOTLOADER)mbr.bin $(BOOTLOADER)kernel.bin
	cat $^ > $@

$(BOOTLOADER)kernel.bin: $(BOOTLOADER)kernel-entry.o $(KERNEL)kernel.o $(DRIVERS)
	$(LD) $(LDFLAGS) -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BOOTLOADER)kernel-entry.o: $(BOOTLOADER)kernel-entry.asm
	$(NASM) $< -I$(BOOTLOADER) -f elf -o $@

$(BOOTLOADER)mbr.bin: $(BOOTLOADER)mbr.asm
	$(NASM) $< -I$(BOOTLOADER) -f bin -o $@

clean:
	$(RM) $(BOOTLOADER)*.bin $(KERNEL)*.o $(BOOTLOADER)*.o $(KERNEL)drivers/*.o
