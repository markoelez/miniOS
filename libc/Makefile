CFLAGS+=-Wno-format

OBJS+=$(patsubst %.c,%.o,$(shell find . -name '*.c'))
OBJS+=$(patsubst %.s,%.o,$(shell find . -name '*.s'))

LIBC=$(LIBDIR)/libc.a

.PHONY: all clean build install-headers

$(LIBC): $(OBJS)
	$(info [libc] linking $(notdir $@))
	@$(AR) rcs $@ $(OBJS)

%.o: %.c
	$(info [libc] $@)
	@$(CC) -c $< -o $@ $(CFLAGS)

%.o: %.S
	$(info [libc] $@)
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	$(info [libc] $@)
	@rm -f $(OBJS) *.o */*.o */*/*.o

build: $(LIBC)

install-headers:
	$(info [libc] installing headers)
	@mkdir -p $(INCLUDEDIR)/libc
	@cp -r $(shell find . -name '*.h') $(INCLUDEDIR)/libc