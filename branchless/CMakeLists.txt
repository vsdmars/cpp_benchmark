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

# ---- Declare executable ----

SET(targets branch_predicted branch_not_predicted branchless_predicted branchless_not_predicted)

foreach(t ${targets})
    add_executable(${t} source/${t}.cpp)
    add_executable(benchmark::${t} ALIAS ${t})

    set_target_properties(
        ${t} PROPERTIES
        OUTPUT_NAME ${t}
        EXPORT_NAME ${t}
    )

    target_compile_features(${t} PRIVATE cxx_std_20)
    target_link_libraries(${t} PRIVATE benchmark::benchmark)
    target_link_options(${t} PRIVATE -fno-omit-frame-pointer -fsanitize=address)
    target_compile_options(${t} PRIVATE -fno-omit-frame-pointer -fsanitize=address)

# ---- Setup binary location ----
    set_property(TARGET ${t}
        PROPERTY RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

endforeach(t)


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
