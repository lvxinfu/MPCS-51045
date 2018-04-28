#include<iostream>
#include<future>

using namespace std;

template<typename T>
class my_promise {
public:
  my_promise() {}
  future<T> get_future() {
    unique_lock<mutex> lck(mtx);
    while(!ready) cv.wait(lck);
    return move(fut);
  }
  
  void set_value(T &v) {
    ready = true;
    val = v;
  }

  private:
  future<T> fut;
  T val;
  mutex mtx;
  condition_variable cv;
  bool ready = false;
};
// this implementation of std::promise is partially created.

int main() {
  return 0;
}