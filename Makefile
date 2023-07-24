CC := i386-elf-gcc
LD := i386-elf-ld

CFLAGS := -m32 -ffreestanding
LDFLAGS := -m elf_i386

SOURCE = $(wildcard kernel/*.c drivers/*.c common/*.c, cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h common/*.h cpu/*.h)
OBJ = ${SOURCE:.c=.o cpu/interrupt.o}

all: clean run

run: os-image.bin
	qemu-system-i386 -drive file=os-image.bin,format=raw,index=0,if=floppy

os-image.bin: boot/bootsect.bin kernel.bin
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
