#include <stdio.h>
#include <string>

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

int main(int argc, char **argv) {
  char buffer[2048];
  for (int i = 1; i < argc; ++i) {
    strcpy(buffer, argv[i]);
    char *str = argv[i];
    for (char *c = str; *c; ++c) {
      *c = reverse(*c);
    }
    printf("%s ", str);
  }
  printf("\n");
}
