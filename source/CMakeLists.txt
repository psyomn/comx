project(comx_core)

## Extensions
enable_testing()

## Project

set(srcs
  filesystem_walker.cc
  archive.cc
  archive_cbz.cc
  archive_builder.cc
  config.cc
  )

set(headers
  filesystem_walker.h
  archive.h
  archive_cbz.h
  archive_builder.h
  config.h
  )

set(COMX_CORE_LIBS libzippp zip)
set(COMX_CORE_DEPS libzippp-git-download)

add_library(comx_core STATIC ${srcs} ${headers})
target_compile_features(comx_core PUBLIC cxx_std_17)
set_target_properties(comx_core PROPERTIES CXX_EXTENSIONS OFF)
target_link_libraries(comx_core PRIVATE ${COMX_CORE_LIBS})

target_include_directories(comx_core PUBLIC "${LIBZIPPP_HEADER_PATH}")
add_dependencies(comx_core ${COMX_CORE_DEPS})

## TESTING

function(comx_core_test name)
  add_executable(${name} test/${name}.cc)
  target_link_libraries(${name} comx_core)
  target_include_directories(${name} PRIVATE . ${COMX_CORE_LIBS})
  add_test(
    NAME    ${name}_valgrind
    COMMAND valgrind --leak-check=full
                     --error-exitcode=1 $<TARGET_FILE:${name}>)
  add_test(${name} ${name})
endfunction(comx_core_test)

comx_core_test(filesystem_walker_test)
comx_core_test(archive_test)
comx_core_test(config_test)

## FIXTURES

file(COPY "${CMAKE_SOURCE_DIR}/test"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
