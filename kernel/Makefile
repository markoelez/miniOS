LDFLAGS:=$(LDFLAGS) -T linker.ld
LIBS=-lc

OBJS:=$(patsubst %.c,%.o,$(shell find . -name '*.c'))
OBJS+=$(patsubst %.s,%.o,$(shell find . -name '*.s'))

DEPS=$(LIBDIR)/libc.a

KERNEL=$(ISO)/$(BOOTDIR)/$(OS).kernel

.PHONY: all clean build install-headers install-kernel

$(KERNEL): $(OBJS) $(DEPS) linker.ld
	$(info [kernel] linking)
	@mkdir -p $(ISO)/$(BOOTDIR)
	@$(LD) $(LDFLAGS) -o $(KERNEL) $(OBJS) $(LIBS)

%.o: %.c
	$(info [kernel] $@)
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(info [kernel] $@)
	@$(CC) -c $< -o $@ $(CFLAGS)

build: $(KERNEL)

install-headers:
	$(info [kernel] installing headers)
	@mkdir -p $(INCLUDEDIR)/kernel
	@cp -r $(shell find . -name '*.h') $(INCLUDEDIR)/kernel

clean:
	$(info [kernel] $@)
	@rm -rf $(OS).kernel $(OBJS) $(shell find . -name '*.o')