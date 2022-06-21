#pragma once

#include <algorithm>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

namespace ranges = std::ranges;

// Seed class
template<int BEGIN, int END>
class Seed
{
public:
  size_t getVal() { return pick(gen); }

private:
  std::random_device rd {};
  std::mt19937 gen {rd()};
  std::uniform_int_distribution<size_t> pick {BEGIN, END};
};

// Test class
template<typename T>
class Test
{
public:
  template<typename U>
  void test(U&& state, std::vector<size_t>& data)
  {
    T tester {};

    if (state.thread_index() == 0) {
      tester.prepare(size_t(state.range(0)));
    }

    for (auto _ : state) {
      state.PauseTiming();
      data.clear();
      state.ResumeTiming();

      tester.run(data);
    }

    if (state.thread_index() == 0) {
      int c1 = 0, c2 = 0;

      for (auto& d : data) {
        if (d == 42) {
          c1 += 1;
        } else {
          c2 += 1;
        }
      }

      std::cout << "True: " << c1 << std::endl;
      std::cout << "False: " << c2 << std::endl;
    }
  }
};

template<bool IS_BRANCH, typename SEED>
class branch : public Test<branch<IS_BRANCH, SEED>>
{
  using value_type = void (*)(std::vector<size_t>&);

private:
  static void branch_call(bool is_branch, std::vector<size_t>& data)
  {
    if (is_branch) {
      data.emplace_back(42);
    } else {
      data.emplace_back(43);
    }
  }

  template<bool B>
  static void branchless_call(std::vector<size_t>& data)
  {
    if constexpr (B) {
      data.emplace_back(42);
    } else {
      data.emplace_back(43);
    }
  }

  void call(bool is_branch, auto&& data)
  {
    if constexpr (IS_BRANCH) {
      branch_call(is_branch, data);
    } else {
      is_branch ? branchless_call<true>(data) : branchless_call<false>(data);
    }
  }

public:
  void run(auto&& data)
  {
    for (auto& v : seedVal) {
      if (v == 0) {
        call(false, data);
      } else {
        call(true, data);
      }
    }
  }

public:
  static void prepare(size_t size)
  {
    seedVal.resize(size);
    ranges::generate(
        seedVal.begin(), seedVal.end(), [] { return seed.getVal() % 2; });
  }

private:
  static std::vector<size_t> seedVal;
  static SEED seed;
};
