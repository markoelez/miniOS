export

OS=miniOS
HOST=i386-elf
PREFIX=usr
BOOTDIR=boot
ISODIR=out
ISO=$(PWD)/$(ISODIR)
SYSROOTDIR=sysroot
SYSROOT=$(PWD)/$(SYSROOTDIR)

GRUBCFG=$(ISODIR)/boot/grub/grub.cfg

INCLUDEDIR=$(SYSROOT)/$(PREFIX)/include
LIBDIR=$(SYSROOT)/$(PREFIX)/lib

PATH:=$(PATH):/sbin:$(PWD)/toolchain/compiler/bin

MAKE:=$(MAKE) -s
LD=$(HOST)-ld
AR=$(HOST)-ar
AS=$(HOST)-as
CC=$(HOST)-gcc

CFLAGS=-O1 -std=gnu11 -ffreestanding -Wall -Wextra
ASFLAGS=--32
LDFLAGS=-nostdlib -L$(SYSROOT)/usr/lib -m elf_i386

CC+=--sysroot=$(SYSROOT) -isystem=/$(PREFIX)/include

PROJECTS=libc kernel
# Generate project sub-targets
PROJECT_HEADERS=$(PROJECTS:=.headers) # appends .headers to every project name
PROJECT_CLEAN=$(PROJECTS:=.clean)

all: clean build $(OS).iso qemu

build: $(PROJECTS)

# Copy headers before building anything
$(PROJECTS): $(PROJECT_HEADERS) | $(LIBDIR)
	@$(MAKE) -C $@ build

clean: $(PROJECT_CLEAN)
	@rm -rf $(SYSROOTDIR)
	@rm -rf $(ISODIR)
	@rm -rf $(OS).iso
	@rm -rf grub.cfg

$(GRUBCFG):
	$(info [all] generating grub config)
	@mkdir -p $(ISODIR)/boot/grub
	@bash ./grub_config.sh

$(OS).iso: $(PROJECTS) $(GRUBCFG)
	$(info [all] writing $@)
	@grub-mkrescue -o $(OS).iso $(ISODIR) 2> /dev/null

qemu: $(OS).iso
	qemu-system-x86_64 -cdrom $(OS).iso -monitor stdio -s -no-reboot -no-shutdown -serial file:serial.log
	cat serial.log

$(INCLUDEDIR):
	@mkdir -p $(INCLUDEDIR)

$(LIBDIR):
	@mkdir -p $(LIBDIR)

# Automatic rules for our generated sub-targets
%.headers: %/ | $(INCLUDEDIR)
	@$(MAKE) -C $< install-headers

%.clean: %/
	@$(MAKE) -C $< clean
