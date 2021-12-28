#include <folly/Benchmark.h>
#include <folly/container/Foreach.h>
#include <vector>
using namespace std;
using namespace folly;
BENCHMARK(insertFrontVector, n) {
  vector<int> v;
  FOR_EACH_RANGE(i, 0, n) { v.insert(v.begin(), i); }
}
BENCHMARK(insertBackVector, n) {
  vector<int> v;
  FOR_EACH_RANGE(i, 0, n) { v.insert(v.end(), i); }
}
int main() { runBenchmarks(); }