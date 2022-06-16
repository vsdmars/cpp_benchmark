include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# find_package(<package>) call for consumers to find this project
set(package benchmark)

install(
    TARGETS benchmark_exe
    RUNTIME COMPONENT benchmark_Runtime
)

write_basic_package_version_file(
    "${package}ConfigVersion.cmake"
    COMPATIBILITY SameMajorVersion
)

# Allow package maintainers to freely override the path for the configs
set(
    benchmark_INSTALL_CMAKEDIR "${CMAKE_INSTALL_DATADIR}/${package}"
    CACHE PATH "CMake package config location relative to the install prefix"
)
mark_as_advanced(benchmark_INSTALL_CMAKEDIR)

install(
    FILES "${PROJECT_BINARY_DIR}/${package}ConfigVersion.cmake"
    DESTINATION "${benchmark_INSTALL_CMAKEDIR}"
    COMPONENT benchmark_Development
)

# Export variables for the install script to use
install(CODE "
set(benchmark_NAME [[$<TARGET_FILE_NAME:benchmark_exe>]])
set(benchmark_INSTALL_CMAKEDIR [[${benchmark_INSTALL_CMAKEDIR}]])
set(CMAKE_INSTALL_BINDIR [[${CMAKE_INSTALL_BINDIR}]])
" COMPONENT benchmark_Development)

install(
    SCRIPT cmake/install-script.cmake
    COMPONENT benchmark_Development
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
