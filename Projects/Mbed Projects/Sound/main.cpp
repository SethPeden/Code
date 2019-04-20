#include "mbed.h"
#include <vector>
#include <cmath>

DigitalIn toggle(p22, PullUp);
PwmOut speaker(p21);
AnalogIn a(p20);

float volume = 0.15;
float fs = 10000.0;
float freq1 = 440.0;
std::vector<float> channel1;
volatile bool reset = false;

Ticker ticker;

template <class T>
std::vector<T> range(T start, T increment, T end) {
  std::vector<T> r;
  for (T d = start; d <= end; d += increment)
    r.push_back(d);
  return r;
}

template <class T, class U>
std::vector<T> transform(std::vector<T> input, U (*func)(U)) {
  std::vector<T> output;
  for (unsigned int i = 0; i < input.size(); ++i)
    output.push_back(func(input[i]));
  return output;
}

float f1(float t) {
  return 2 * M_PI * freq1 * t;
}

void play() {
  static unsigned int i = 0;
  static float old = 0;
  if (reset) i = 0;
  if (!toggle) {
    speaker = channel1[i] * volume - old / 2.0;
    old = speaker;
    ++i;
    if (i >= channel1.size()) i = 0;
  } else {
    speaker = 0.0;
  }
}

int main() {
  std::vector<float> time = range(0.0f, 1 / fs, 1 / 200.0f);
  channel1 = transform<float, double>(transform<float>(time, &f1), &sin);
  speaker.period(1 / fs);
  ticker.attach(&play, 1 / fs);
  while (true) {
    // printf("a: %f\n", double(a));
    freq1 = int(a * 8) / 8.0 * 1000.0;
    channel1 = transform<float, double>(transform<float>(time, &f1), &sin);
    wait((rand() % 32) / 64.0);
  }
}
