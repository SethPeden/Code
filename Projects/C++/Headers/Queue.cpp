#include <iostream>
#include <vector>
#include <thread>
#include <functional>
using namespace std;

struct Queue {
  ~Queue() {
    this->self.join();
  }
  void add(function<void (void)> task) {
    this->tasks.push_back(task);
    if (this->stopped)
      this->resume();
  }
  void run() {
    this->self = thread( [=] { 
      while (!this->stopped && this->tasks.size() > 0) {
        this->tasks.at(0)();
        this->tasks.erase(this->tasks.begin());
      }
    } );
  }
  void resume() {
    this->stopped = false;
    this->run();
  }
  void stop() {
    this->stopped = true;
    this->self.join();
  }
private:
  thread self;
  bool stopped = false;
  vector<function<void (void)>> tasks;
};

int main() {
  Queue urgent, background;

  for (int i = 1; i < 25; ++i) {
    urgent.add( [=] {
      cout << "AAAAAAAAAA: " << i << endl;
    });
    background.add( [=] {
      cout << "BBBBBBBBBB: " << i << endl;
    } );
  }

  urgent.run();
  background.run();

  return 0;
}