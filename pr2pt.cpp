#include<iostream>
#include<future>

using namespace std;

int addNums(int a, int b) {
  return a+b;
}

template<typename F, typename ...Args>
class my_packaged_task {};

template<typename F, typename ...Args>
class my_packaged_task<F(Args...)> {
public:
  my_packaged_task(decay_t<F(*)(Args...)> f): func(f){}
  // I discussed why using decay_t<F(*)(Args...)> here with Jiawei.

  future<F> get_future() {
    return move(p.get_future());
  }
  
  void operator()(Args ...args) {
    p.set_value(func(args...));
  }

private:
  function<F(Args...)> func;
  promise<F> p;
};

int main() {
  my_packaged_task<int(int, int)> pt(addNums);

  auto fut = pt.get_future();
  thread t(move(pt), 1, 2);
  t.join();
  cout << fut.get() << endl;

  return 0;
}