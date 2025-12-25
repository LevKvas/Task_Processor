#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>

// T - different Tasks
template<typename T>
class ThreadSafeQueue{
  public:
    void push(T task){
        std::lock_guard<std::mutex> lock(mtx);
        q_tasks.push_back(task);
    }

    void pop(){
      std::lock_guard<std::mutex> lock(mtx);
      cv_not_empty.wait(lock, [this] {return !q_tasks.empty();});
      q_tasks.pop_front();
    }

private:
    std::queue<T> q_tasks{};
    std::mutex mtx{};
    std::condition_variable cv_not_empty{};
};