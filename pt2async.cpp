#include<iostream>
#include<future>

using namespace std;

int addNums(int a, int b) {
  return a+b;
}

template<typename F, typename ...Args>
auto my_async(F &f, Args &&...args) {
  packaged_task<F> pt(f);
  auto fut = pt.get_future();
  thread t(move(pt), args...);
  t.join();
  return fut;
}

int main() {
/*
  auto fut = async(addNums, 1, 2);
  cout << fut.get() << endl;
*/

  auto fut = my_async(addNums, 2, 3);
  cout << fut.get() << endl;
  
  return 0;  
}