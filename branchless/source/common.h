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

__attribute__((noinline)) void branch_call(bool stat,
                                           unsigned long& data,
                                           unsigned long long val)
{
  if (stat) {
    data += val;
  } else {
    data *= val;
  }
}

template<bool B>
__attribute__((noinline)) void branchless_call(unsigned long& data,
                                               unsigned long long val)
{
  if constexpr (B) {
    data += val;
  } else {
    data *= val;
  }
}
