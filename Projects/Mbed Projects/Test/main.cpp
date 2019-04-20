#include "mbed.h"

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

int main() {
  static int i = 1;
  static bool dir = true;
  while (true) {
    led1 = i & 0b0001;
    led2 = i & 0b0010;
    led3 = i & 0b0100;
    led4 = i & 0b1000;
    if (dir && i < 0b1000) {
      i = i << 1;
      dir = true;
    } else if (i > 0b0001) {
      i = i >> 1;
      dir = false;
    } else {
      i = i << 1;
      dir = true;
    }
    // i = i << 1;
    // if (i > 8) i = 1;
    wait(0.05);
  }

}
