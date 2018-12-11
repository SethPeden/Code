#pragma once

#include <string>
#include <algorithm>

unsigned p1() {
  unsigned sum = 0;
  for (unsigned i = 0; i < 1000; ++i) if (i % 3 == 0 || i % 5 == 0) sum += i;
  return sum;
}

unsigned p2() {
  unsigned a = 1, b = 2, sum = 0;
  while (a < 4000000) {
    if (a % 2 == 0) sum += a;
    b += a;
    a = b - a;
  }
  return sum;
}

unsigned p3() {
  const unsigned long val = 600851475143;
  unsigned long a = val, b = 0;
  for (unsigned long i = 2; i < a / 2; ++i) while (a % i == 0) a = a / i;
  return a;
}

unsigned p4() {
  unsigned out = 0;
  for (unsigned a = 100; a < 1000; ++a)
    for (unsigned b = 100; b < 1000; ++b) {
      std::string s = std::to_string(a * b);
      std::string c, d;
      if (s.size() % 2) {
        c = s.substr(0, s.size() / 2 + 1);
        d = s.substr(s.size() / 2, s.size() / 2 + 1);
      } else {
        c = s.substr(0, s.size() / 2);
        d = s.substr(s.size() / 2, s.size() / 2);
      }
      std::reverse(d.begin(), d.end());
      if (a * b > out && c == d)
        out = a * b;
    }
  return out;
}

unsigned p5() {
  unsigned i = 2;
  while (true) {
    bool a = true;
    for (unsigned j = 2; j <= 10; ++j) a = a && (i % j == 0);
    if (a) return i;
    ++i;
  }
  return 0;
}

unsigned p6() {
  unsigned summed = 0, squared = 0;
  for (unsigned i = 1; i <= 100; ++i) {
    summed += i * i;
    squared += i;
  }
  squared *= squared;
  return squared - summed;
}

unsigned p7() {
  unsigned p = 3, i = 2;
  unsigned j = 6;
  while (i < 10001) {
    p = j - 1;
    bool prime = true;
    for (unsigned k = 2; k < p / 2; ++k)
      prime = prime && (p % k);
    if (prime) ++i;
    p = j + 1;
    if (i >= 10001) break;
    prime = true;
    for (unsigned k = 2; k < p / 2; ++k)
      prime = prime && (p % k);
    if (prime) ++i;
    j += 6;
  }
  return p;
}
