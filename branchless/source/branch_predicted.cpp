#include <benchmark/benchmark.h>

#include "common.h"

constexpr int sample_cnt = 1000;

static void BM_branch_predicted(benchmark::State& state)
{
  Seed<0, 1000> seed {};

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
    // triggers data being used instead of compiler opt-out result.
    unsigned long a1 = 0, a2 = 0;

    for (size_t i = 0; i < N; ++i) {
      if (b1[i]) {
        // always hit
        a1 += p1[i];
      } else {
        a1 *= p2[i];
      }
    }

    benchmark::DoNotOptimize(a1);
    benchmark::DoNotOptimize(a2);
    benchmark::ClobberMemory();
  }

  state.SetItemsProcessed(N * state.iterations());
}
BENCHMARK(BM_branch_predicted)->Arg(sample_cnt);

BENCHMARK_MAIN();
