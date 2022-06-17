#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>


class ThreadPool {
public:
  explicit ThreadPool(size_t threadNum) : stop_(false) {
    for (size_t i = 0; i < threadNum; ++i) {
      workers_.emplace_back([this]() {
        for (;;) {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> ul(mtx_);
            cv_.wait(ul, [this]() { return stop_ || !tasks_.empty(); });
            if (stop_ && tasks_.empty()) {
              return;
            }
            task = std::move(tasks_.front());
            tasks_.pop();
          }
          task();
        }
      });
    }
  }

  ~ThreadPool() {
    {
      std::unique_lock<std::mutex> ul(mtx_);
      stop_ = true;
    }
    cv_.notify_all();
    for (auto &worker : workers_) {
      worker.join();
    }
  }

  template <typename F, typename... Args>
  auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))> {
    auto taskPtr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...));
    {
      std::unique_lock<std::mutex> ul(mtx_);
      if (stop_) {
        throw std::runtime_error("submit on stopped ThreadPool");
      }
      tasks_.emplace([taskPtr]() { (*taskPtr)(); });
    }
    cv_.notify_one();
    return taskPtr->get_future();
  }

private:
  bool stop_;
  std::vector<std::thread> workers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex mtx_;
  std::condition_variable cv_;
};
int Get(int i, int j, int k) {

  std::this_thread::sleep_for(std::chrono::seconds(10));
  std::cout << std::this_thread::get_id() << " First " << i << std::endl;
  std::cout << "Second " << j << std::endl;
  return i * j * k;
}

std::string Print(std::string msg) {
  std::this_thread::sleep_for(std::chrono::seconds(10));
  return msg + msg;
}

int thread_pool_test() {
  ThreadPool pool(4);
  int a = 9;
  int b = 9;
  std::vector<std::future<int>> results;
  for (int i = 0; i < 18; ++i) {
    //  results.emplace_back(pool.submit([]() {
    //         // computing task and return result
    // }));

    results.emplace_back(pool.submit([i] {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << std::this_thread::get_id() << " hello " << i << std::endl;
      std::cout << "world " << i << std::endl;
      return i * i;
    }));

    results.emplace_back(pool.submit(&Get, i, i + 8, 2));
  }

  for (auto &&result : results)
    std::cout << "\n===========" << result.get() << std::endl;

  std::cout << "\n====next loop=======\n";
  std::this_thread::sleep_for(std::chrono::seconds(60));
  std::vector<std::future<std::string>> results22;

  for (int i = 0; i < 18; ++i) {
    //  results.emplace_back(pool.submit([]() {
    //         // computing task and return result
    // }));

    results.emplace_back(pool.submit([i] {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << std::this_thread::get_id() << " *****hello***** " << i
                << std::endl;
      std::cout << "world " << i << std::endl;
      return i * i;
    }));

    results22.emplace_back(pool.submit(&Print, "Pinterest"));
  }

  for (auto &&result : results22)
    std::cout << "\n===========" << result.get() << std::endl;
  // // future from a packaged_task
  // std::packaged_task<int()> task([]{ return 7; }); // wrap the function
  // std::future<int> f1 = task.get_future();  // get a future
  // std::thread t(std::move(task)); // launch on a thread

  // // future from an async()
  // std::future<int> f2 = std::async(std::launch::async, []{ return 8; });

  // // future from a promise
  // std::promise<int> p;
  // std::future<int> f3 = p.get_future();
  // std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();

  // std::cout << "Waiting..." << std::flush;
  // f1.wait();
  // f2.wait();
  // f3.wait();
  // std::cout << "Done!\nResults are: "
  //           << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
  // t.join();

  return 0;
}