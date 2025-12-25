#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <memory>

#include "Tasks.hpp"

namespace ThreadsPool{
  namespace Exceptions{
    class NumThreads final: public std::exception{
    public:
      const char* what() const noexcept override{return "the number of threads is negative or greater than the maximum allowed";}
    };
  }

  namespace Impl{
    class ThreadSafeQueue{
    public:
      void push(std::unique_ptr<Task> task){
        std::unique_lock<std::mutex> lock(mtx);
        q_tasks.push(std::move(task));
      }

      void pop(){
        std::unique_lock<std::mutex> lock(mtx);
        cv_not_empty.wait(lock, [this] {return !q_tasks.empty();});
        q_tasks.pop();
      }

    private:
      std::queue<std::unique_ptr<Task>> q_tasks{};
      std::mutex mtx{};
      std::condition_variable cv_not_empty{};
    };
  }

  class Pool{
  public:
    Pool() = default;

    void start(size_t num_threads_){
      auto max_threads = std::thread::hardware_concurrency();

      if(num_threads > max_threads){
        throw Exceptions::NumThreads();
      }

      num_threads = num_threads_;
    }

    void SubmitTask(std::unique_ptr<Task> task){
      tasks.push(std::move(task));
    }

  private:
    std::vector<std::thread> workers{};

    size_t num_threads{};
    Impl::ThreadSafeQueue tasks{};
  };
}

