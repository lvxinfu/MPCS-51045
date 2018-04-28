#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<chrono>
#include<cstdlib>
#include<string>

using namespace std;

mutex mtx;
condition_variable cv;
bool ready = false;

void worker_work(string s) {
  cout << "Worker is working on " << s << ". -- ";
}

void print_id(int id, string s) {
  unique_lock<mutex> lck(mtx);
  while(!ready) cv.wait(lck);
  this_thread::sleep_for(chrono::milliseconds(rand() %200));
  worker_work(s);
  cout << "thread " << id << '\n';
}

void go() {
  unique_lock<mutex> lck(mtx);
  ready = true;
  cv.notify_all();
}

int main() {
  thread threads[10]; // 10 workers

  for(int i=0; i<10; i++) {
    threads[i] = thread(print_id, i, "this step");
  }
  cout << "10 workers are ready to work." << endl;
  go();

  for(auto &th : threads) {
    th.join();
  }
  cout << "This step is finished!" << endl;

  return 0;
}