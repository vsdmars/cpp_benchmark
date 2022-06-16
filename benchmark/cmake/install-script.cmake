file(
    RELATIVE_PATH relative_path
    "/${benchmark_INSTALL_CMAKEDIR}"
    "/${CMAKE_INSTALL_BINDIR}/${benchmark_NAME}"
)

get_filename_component(prefix "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)
set(config_dir "${prefix}/${benchmark_INSTALL_CMAKEDIR}")
set(config_file "${config_dir}/benchmarkConfig.cmake")

message(STATUS "Installing: ${config_file}")
file(WRITE "${config_file}" "\
get_filename_component(
    _benchmark_executable
    \"\${CMAKE_CURRENT_LIST_DIR}/${relative_path}\"
    ABSOLUTE
)
set(
    BENCHMARK_EXECUTABLE \"\${_benchmark_executable}\"
    CACHE FILEPATH \"Path to the benchmark executable\"
)
")
list(APPEND CMAKE_INSTALL_MANIFEST_FILES "${config_file}")
