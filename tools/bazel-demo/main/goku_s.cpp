
#include "my_folly.h"
#include "my_glog.h"
#include <iostream>

int main() {
  std::cout << "test Bazel" << std::endl;
  folly_test();
  glog_test();

  std::cout << "End Program" << std::endl;
  return 0;
}

// bazel build --cxxopt='-std=c++17' //main:hello-goku