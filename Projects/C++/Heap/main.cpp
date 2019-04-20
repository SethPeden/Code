#include <iostream>
#include <string>
#include "heap.h"
using namespace std;

void usage(string name) {
  cout << "Usage:" << endl;
  cout << "\t" << name << " -<parameter> [value] ..." << endl;
  cout << "\tParameters" << endl;
  cout << "\t\thelp [h]: prints usage" << endl;
  cout << "\t\tsize [s]: sets the size of the heap" << endl;
  cout << "\t\t\ttype: integer" << endl;
}

int main(int argc, char **argv) {
  Heap h;
  if (argc > 1) {
    for (int i = 1; i < argc; ++i) {
      string parameter = string(argv[i]);
      if (parameter == "-h" || parameter == "-help") {
        usage(string(argv[0]));
      } else if ((parameter == "-s" || parameter == "-size") && ++i < argc) {
        h = Heap(atoi(argv[i]));
      }
    }
  } else {
    usage(string(argv[0]));
  }
  cout << h << endl;
  int *p = (int *) h.alloc(15);
  *p = 0xefcdab89;
  cout << h << endl;
  h.dealloc(p);
  cout << h << endl;
  return 0;
}
