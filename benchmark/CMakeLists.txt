cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    benchmark
    VERSION 0.1.0
    DESCRIPTION "benchmark for testing code"
    HOMEPAGE_URL "https://github.com/vsdmars/cpp_benchmark/"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    benchmark_lib OBJECT
    source/lib.cpp
)

target_include_directories(
    benchmark_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(benchmark_lib PUBLIC cxx_std_20)

# ---- Declare executable ----

add_executable(benchmark_exe source/main.cpp)
add_executable(benchmark::exe ALIAS benchmark_exe)

set_target_properties(
    benchmark_exe PROPERTIES
    OUTPUT_NAME benchmark
    EXPORT_NAME exe
)

target_compile_features(benchmark_exe PRIVATE cxx_std_20)

target_link_libraries(benchmark_exe PRIVATE benchmark_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

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
