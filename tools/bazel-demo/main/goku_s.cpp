
#include "my_boost.h"
#include "my_folly.h"
#include "my_glog.h"
#include "my_stl.h"
#include <iostream>

int main() {
  std::cout << "test Bazel" << std::endl;
  folly_test();
  glog_test();
   boost_test();

  std::cout << "End Program" << std::endl;
  return 0;
}

// bazel build --cxxopt='-std=c++17' //main:hello-goku