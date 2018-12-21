#pragma once

#include <string>
#include <algorithm>
#include <iostream>

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

unsigned p8(char **s) {
  // static char **s = { "73167176531330624919225119674426574742355349194934",
  //                     "96983520312774506326239578318016984801869478851843",
  //                     "85861560789112949495459501737958331952853208805511",
  //                     "12540698747158523863050715693290963295227443043557",
  //                     "66896648950445244523161731856403098711121722383113",
  //                     "62229893423380308135336276614282806444486645238749",
  //                     "30358907296290491560440772390713810515859307960866",
  //                     "70172427121883998797908792274921901699720888093776",
  //                     "65727333001053367881220235421809751254540594752243",
  //                     "52584907711670556013604839586446706324415722155397",
  //                     "53697817977846174064955149290862569321978468622482",
  //                     "83972241375657056057490261407972968652414535100474",
  //                     "82166370484403199890008895243450658541227588666881",
  //                     "16427171479924442928230863465674813919123162824586",
  //                     "17866458359124566529476545682848912883142607690042",
  //                     "24219022671055626321111109370544217506941658960408",
  //                     "07198403850962455444362981230987879927244284909188",
  //                     "84580156166097919133875499200524063689912560717606",
  //                     "05886116467109405077541002256983155200055935729725",
  //                     "71636269561882670428252483600823257530420752963450" };
  unsigned n = 13;
  unsigned max = 0;
  for (unsigned i = n - 1; i < 51 - n; ++i) {
    for (unsigned j = n - 1; j < 21 - n; ++j) {
      for (unsigned d = 0; d < 4; ++d) {
        unsigned product = 1;
        for (unsigned k = 0; k < n; ++k) {
          unsigned val;
          switch (d) {
            case 0:
              val = (s[i][j - k] - '0');
              break;
            case 1:
              val = (s[i][j + k] - '0');
              break;
            case 2:
              val = (s[i - k][j] - '0');
              break;
            case 3:
              val = (s[i + k][j] - '0');
              break;
          }
          std::cout << val << std::endl;
          product *= val;
        }
        if (product > max)
          max = product;
      }
    }
  }
  return max;
  return 0;
}
