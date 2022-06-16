# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(benchmarkTests LANGUAGES CXX)

# ---- Tests ----

add_executable(benchmark_test source/benchmark_test.cpp)
target_link_libraries(benchmark_test PRIVATE benchmark_lib)
target_compile_features(benchmark_test PRIVATE cxx_std_20)

add_test(NAME benchmark_test COMMAND benchmark_test)

# ---- End-of-file commands ----

add_folders(Test)
