#include <benchmark/benchmark.h>

#include "branchless.h"

template<bool IS_BRANCH, typename SEED>
std::vector<size_t> branch<IS_BRANCH, SEED>::seedVal {};

template<bool IS_BRANCH, typename SEED>
SEED branch<IS_BRANCH, SEED>::seed {};

constexpr size_t cnt = 1000;

/**
 * Benchmark for runtime branch
 */
static void BM_BranchTest(benchmark::State& state)
{
  branch<true, Seed<0, cnt>> br {};

  std::vector<size_t> data(cnt);

  br.test(state, data);
}
BENCHMARK(BM_BranchTest)->Arg(cnt);

/**
 * Benchmark for branchless
 */
static void BM_BranchLessTest(benchmark::State& state)
{
  branch<false, Seed<0, cnt>> br {};

  std::vector<size_t> data(cnt);

  br.test(state, data);
}
BENCHMARK(BM_BranchLessTest)->Arg(cnt);

BENCHMARK_MAIN();
