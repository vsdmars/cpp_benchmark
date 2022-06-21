cmake_minimum_required(VERSION 3.23)

include(cmake/prelude.cmake)

project(
    benchmark
    VERSION 0.1.0
    DESCRIPTION "benchmark for testing code"
    HOMEPAGE_URL "https://github.com/vsdmars/cpp_benchmark/"
    LANGUAGES CXX
)

# ---- Enable Google Benchmark ----
find_package(benchmark REQUIRED) # benchmark::benchmark

# ---- Enable unit test ----
# https://stackoverflow.com/a/30264765
enable_testing()

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

# add_library(
    # branchless OBJECT
    # source/branchless.cpp
# )

# target_compile_features(branchless PUBLIC cxx_std_20)
# target_link_options(branchless PRIVATE -fno-omit-frame-pointer -fsanitize=address)
# target_compile_options(branchless PRIVATE -fno-omit-frame-pointer -fsanitize=address)

# ---- Declare executable ----

add_executable(branch_predicted source/branch_predicted.cpp)
add_executable(benchmark::branch_predicted ALIAS branch_predicted)

set_target_properties(
    branch_predicted PROPERTIES
    OUTPUT_NAME branch_predicted
    EXPORT_NAME branch_predicted
)

target_compile_features(branch_predicted PRIVATE cxx_std_20)
target_link_libraries(branch_predicted PRIVATE benchmark::benchmark)
target_link_options(branch_predicted PRIVATE -fno-omit-frame-pointer -fsanitize=address)
target_compile_options(branch_predicted PRIVATE -fno-omit-frame-pointer -fsanitize=address)

# ---- Setup binary location ----
set_property(TARGET branch_predicted
    PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

# ---- Create build directories ----
include(cmake/create_dir.cmake)

# ---- Developer mode ----

if(NOT benchmark_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of benchmark"
  )
endif()

include(cmake/dev-mode.cmake)
