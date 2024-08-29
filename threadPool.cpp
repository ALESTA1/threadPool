#include<bits/stdc++.h>
#include<mutex>
#include <vector>
#include <condition_variable>
#include <iostream>
#include <functional>
#include <queue>

using namespace std;

class threadPool{

    public:
    threadPool() = delete;
ThreadPool(int _threads) {


    for (int i = 0; i < _threads; ++i) {
        threads.emplace_back([this] { executeTask(); }); // Create and add thread directly
    }
}


    void addTask(function<void()> task){

        unique_lock<mutex> lock(m);
        functionQueue.push(task);

    }
    void executeTask(){

        while(true){

            {
                unique_lock<mutex> lock(m);
                cv.wait(lock,[]{return functionQueue.size(})


            }
        }
    }

    private:

    vector<std::thread> threads;
    condition_variable cv;
    mutex m;
    std::queue<std::function<void()>> functionQueue;

};
int main(){

    return 0;
}
