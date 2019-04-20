#include "mbed.h"

Serial pc(USBTX, USBRX);

int main() {
    while (true)
      pc.putc(pc.getc());
}
