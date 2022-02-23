#include <folly/FBString.h>
#include <folly/Format.h>
#include <folly/ProducerConsumerQueue.h>
#include <folly/Uri.h>
#include <folly/executors/ThreadedExecutor.h>
#include <folly/futures/Future.h>
#include <iostream>
#include <utility>
//#include <folly/Benchmark.h>
#include <folly/small_vector.h>
#include <thread>
// g++ follyTest.cpp -std=c++14 -lfolly -lgflags -lglog -o fl
template <class T> void doNotOptimizeAway(T &&datum) {
  // asm volatile("" : "+r" (datum));
  // asm volatile ("" : "+r" datum);
  // asm volatile("" : "+r" (datum));
}

static void print_uri(const folly::fbstring &address) {
  const folly::Uri uri(address);
  const auto authority = folly::format("The authority from {} is {}",
                                       uri.fbstr(), uri.authority());
  std::cout << authority << std::endl;
}

/// Users/ronghuang/code/cosmos/goku/storage/hotkey_logger_manager.cpp
//
// BENCHMARK(stdVector, n) {
//   FOR_EACH_RANGE(i, 0, n) {
//     std::vector<int> vec;
//     vec.reserve(4);

//     for (int i = 0; i < 4; i++) {
//       vec.push_back(1);
//     }

//     doNotOptimizeAway(vec);
//   }
// }

// BENCHMARK_DRAW_LINE();

// BENCHMARK_RELATIVE(smallVector, n) {
//   FOR_EACH_RANGE(i, 0, n) {
//     folly::small_vector<int, 4> vec;

//     for (int i = 0; i < 4; i++) {
//       vec.push_back(1);
//     }

//     doNotOptimizeAway(vec);
//   }
// }

int main() {
  folly::ThreadedExecutor executor;
  folly::Promise<folly::fbstring> promise;
  folly::Future<folly::fbstring> future =
      promise.getSemiFuture().via(&executor);
  folly::Future<folly::Unit> unit = std::move(future).thenValue(print_uri);
  promise.setValue("https://conan.io/");
  // std::move(unit).get();

  folly::ProducerConsumerQueue<folly::fbstring> queue{10};

  std::thread reader([&queue] {
    for (;;) {
      folly::fbstring str;
      while (!queue.read(str)) {
        // spin until we get a value

        continue;
      }
      std::cout << str << std::endl;

      // sink(str);
    }
  });

  // producer thread:
  for (int n = 0; n < 10; ++n) {
    folly::fbstring str = "aaaa";
    while (!queue.write(str)) {
      // spin until the queue has room
      continue;
    }
  }
  reader.join();

  return 0;
}