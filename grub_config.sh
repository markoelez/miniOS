#!/usr/bin/bash

echo "insmod efi_gop" > "$GRUBCFG"
echo "menuentry \"miniOS\" {" >> "$GRUBCFG"
echo "    multiboot2 /boot/miniOS.kernel" >> "$GRUBCFG"
echo "}" >> "$GRUBCFG"