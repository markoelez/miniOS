CC := i386-elf-gcc
LD := i386-elf-ld

CFLAGS := -g -m32 -ffreestanding -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror
LDFLAGS := -m elf_i386

SOURCE = $(wildcard kernel/*.c drivers/*.c cpu/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h libc/*.h)
OBJ = ${SOURCE:.c=.o cpu/interrupt.o}

all: clean run

run: image.bin
	qemu-system-i386 -drive file=image.bin,format=raw,index=0,if=floppy

image.bin: boot/bootsect.bin kernel.bin
	cat $^ > $@

kernel.bin: boot/kernel_entry.o ${OBJ}
	${LD} ${LDFLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	find . -name "*.o" -type f -delete
	find . -name "*.bin" -type f -delete
