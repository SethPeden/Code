#include "mbed.h"
#include <ctime>
#include <cstdlib>

Serial pc(USBTX, USBRX);

DigitalIn clk(p19);
DigitalIn data(p20);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
BusOut bus(LED1, LED2, LED3, LED4);

int value = 0;
int count = 0;

int main() {
  bool c = false;
  while(count < 32) {
    if (!c && clk) {
      led1 = 1;
      led2 = data;
      value <<= 1;
      value |= (data & 0b1);
      ++count;
      c = true;
    } else if (c && !clk) {
      led1 = 0;
      c = false;
    }
    wait(0.05);
  }
  long long int seed = (long long int) value;
  seed = (seed << 32) | ~(seed);
  pc.printf("Seed: 0x%llX\n\n", seed);
  srand(time(&seed));
  while (true) {
    bus = rand() % 16;
    wait(0.5);
  }
}
