#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "benchmark" ? 0 : 1;
}
