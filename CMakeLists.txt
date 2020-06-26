cmake_minimum_required(VERSION 3.16)

project(comx)

## Extensions
enable_testing()
include(ExternalProject)

## Dependencies

set(VENDOR_INSTALL_BASE "${CMAKE_CURRENT_BINARY_DIR}/vendor/install")

### LIBZIPPP
ExternalProject_Add(
  libzippp-git-download
  PREFIX "vendor/projects"

  GIT_REPOSITORY "https://www.github.com/ctabin/libzippp"
  GIT_TAG "libzippp-v3.1-1.6.1"

  INSTALL_COMMAND make DESTDIR=${VENDOR_INSTALL_BASE} install
)

set(LIBZIPPP_STATIC_PATH "${VENDOR_INSTALL_BASE}/usr/local/lib/libzippp_static.a")
set(LIBZIPPP_HEADER_PATH "${VENDOR_INSTALL_BASE}/usr/local/include/libzippp/")
add_library(libzippp SHARED IMPORTED)
set_target_properties(libzippp PROPERTIES IMPORTED_LOCATION ${LIBZIPPP_STATIC_PATH})

## project

add_subdirectory(source)
