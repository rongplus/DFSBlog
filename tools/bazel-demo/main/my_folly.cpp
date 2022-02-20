#include "my_folly.h"

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

#include <iostream>

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

void folly_test() { std::cout << __func__ << std::endl; }