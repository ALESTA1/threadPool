#include <bits/stdc++.h>

#include <mutex>

#include <vector>

#include <condition_variable>

#include <iostream>

#include <functional>

#include <queue>

using namespace std;

class ThreadPool {

  public:

    ThreadPool(int _threads): stop(false) {

      for (int i = 0; i < _threads; ++i) {

        threads.emplace_back([this] {
          executeTask();
        });

      }

    }

    ~ThreadPool() {
      {

        unique_lock < mutex > lock(m);
        stop = true;

      }
      cv.notify_all();
      for (auto & thread: threads) {

        if (thread.joinable()) {

          thread.join();

        }

      }

    }

  void addTask(function < void() > task) {

    {

      unique_lock < mutex > lock(m);

      functionQueue.push(task);

    }

    cv.notify_one();

  }

  private:

    void executeTask() {

      while (true) {

        function < void() > task;

        {

          unique_lock < mutex > lock(m);

          cv.wait(lock, [this] {
            return stop || !functionQueue.empty();
          });

          if (stop && functionQueue.empty()) {

            return;

          }

          task = functionQueue.front();

          functionQueue.pop();

        }

        task();

      }

    }

  vector < thread > threads;

  condition_variable cv;

  mutex m;

  queue < function < void() >> functionQueue;

  bool stop;

};

int main() {

  return 0;

}
