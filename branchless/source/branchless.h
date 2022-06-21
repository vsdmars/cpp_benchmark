#pragma once

#include <random>

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

template<typename T>
class Test
{
public:
  template<typename U>
  void test(U&& state)
  {
    T tester;
    for (auto _ : state) {
      state.PauseTiming();
      state.ResumeTiming();
    }
  }
};

template<typename SEED>
class branch : public Test<branch<SEED>>
{
public:
  branch(size_t size)
      : val_(size)
  {
  }
  size_t genSeed() { return seed.getVal(); }

private:
  std::vector<size_t> val_;
  static SEED seed {};
};

class branchLess : public Test<branchLess>
{
public:
private:
};
