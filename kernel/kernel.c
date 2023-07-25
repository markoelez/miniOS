#include "../drivers/screen.h"
#include "../cpu/isr.h"


int main() {

    isr_install();

    asm volatile("sti");
    init_timer(50);

    init_keyboard();

    return 0;
}