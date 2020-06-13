project(psycom_core)

enable_testing()

## Project

set(srcs utils.cc filesystem_walker.cc archive.cc)
set(headers utils.h filesystem_walker.h archive.h)

add_library(psycom_core STATIC ${srcs} ${headers})
target_compile_features(psycom_core PUBLIC cxx_std_17)
set_target_properties(psycom_core PROPERTIES CXX_EXTENSIONS OFF)

## Dependencies

find_package(ZLIB REQUIRED)
if (ZLIB_FOUND)
  include_directories(${ZLIB_INCLUDE_DIRS})
  target_link_libraries(psycom_core ${ZLIB_LIBRARIES})
else ()
  error("couldn't find zlib")
endif(ZLIB_FOUND)

## TESTING

function(psycom_core_test name)
  add_executable(${name} test/${name}.cc)
  target_link_libraries(${name} psycom_core)
  target_include_directories(${name} PRIVATE .)
  add_test(
    NAME    ${name}_valgrind
    COMMAND valgrind --leak-check=full
                     --error-exitcode=1 $<TARGET_FILE:${name}>)
  add_test(${name} ${name})
endfunction(psycom_core_test)

psycom_core_test(filesystem_walker_test)
psycom_core_test(archive_test)

## FIXTURES

file(COPY "${CMAKE_SOURCE_DIR}/test"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
