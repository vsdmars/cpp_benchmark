# For build directory
SET(BIN_DIR "${PROJECT_BINARY_DIR}/bin")
SET(BIN_TEST_DIR "${PROJECT_BINARY_DIR}/tests")

SET(BUILD_DIRS ${BIN_DIR} ${BIN_TEST_DIR})

foreach(d ${LRUC_DIRS})
   file(MAKE_DIRECTORY "${d}")
endforeach(d)
