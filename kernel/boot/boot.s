.set MAGIC,            0xE85250D6
.set ARCH,             0
.set HEADER_LEN,       (multiboot_end - multiboot_start)
.set CHECKSUM,         -(MAGIC + ARCH + HEADER_LEN)

# Multiboot header
.section .multiboot
multiboot_start:
    # Magic
    .align 8
    .long MAGIC
    .long ARCH
    .long HEADER_LEN
    .long CHECKSUM

    # End tag
    .align 8
    .short 0
    .short 0
    .long 8
multiboot_end:

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
    .skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
    movl $stack_top, %esp
    mov $0, %ebp # stop stacktraces here

    # Transfer control to the main kernel.
    pushl %eax
    pushl %ebx

    cli # disable until we setup handlers
    call kernel_main
    add $8, %esp # cleanup the stack

    # Hang if kernel_main unexpectedly returns.
    cli
.hang:
    hlt
    jmp .hang
