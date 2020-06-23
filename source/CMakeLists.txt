project(comx_core)

## Extensions
enable_testing()

## Project

set(srcs utils.cc filesystem_walker.cc archive.cc)
set(headers utils.h filesystem_walker.h archive.h)

add_library(psycom_core STATIC ${srcs} ${headers})
target_compile_features(psycom_core PUBLIC cxx_std_17)
set_target_properties(psycom_core PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(psycom_core PRIVATE libzippp)
target_include_directories(psycom_core PUBLIC "${LIBZIPPP_HEADER_PATH}")
add_dependencies(psycom_core libzippp-git-download)

## TESTING

function(psycom_core_test name)
  add_executable(${name} test/${name}.cc)
  target_link_libraries(${name} psycom_core)
  target_include_directories(${name} PRIVATE . libzippp)
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
