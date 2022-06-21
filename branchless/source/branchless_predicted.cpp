#include <benchmark/benchmark.h>

#include "common.h"

static void BM_branch_predicted(benchmark::State& state)
{
  Seed<0, 10> seed {};

  const unsigned int N = state.range(0);
  std::vector<unsigned long> v1(N), v2(N);
  std::vector<int> c1(N);

  for (size_t i = 0; i < N; ++i) {
    v1[i] = seed.getVal();
    v2[i] = seed.getVal();
    c1[i] = seed.getVal() >= 0;
  }

  // pointer to continuous heap memory
  unsigned long* p1 = v1.data();
  unsigned long* p2 = v2.data();
  int* b1 = c1.data();

  for (auto _ : state) {
    unsigned long data = 0;

    for (size_t i = 0; i < N; ++i) {
      b1[i] ? branchless_call<true>(data, p1[i] + p2[i])
            : branchless_call<false>(data, p1[i] + p2[i]);
    }

    benchmark::DoNotOptimize(data);
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(N * state.iterations());
}
BENCHMARK(BM_branch_predicted)->Arg(1 << 22);

BENCHMARK_MAIN();
