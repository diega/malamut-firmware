idf_component_register(REQUIRES gmp)

include(ExternalProject)

set(FQFFT_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/fqfft)

ExternalProject_Add(fqfft_proj
  GIT_REPOSITORY https://github.com/scipr-lab/libfqfft.git
  GIT_TAG 7e1e957d0e84accadcf92e88162510c0ad886709
  GIT_SUBMODULES_RECURSE FALSE
  GIT_PROGRESS TRUE
  CMAKE_ARGS "-DCURVE=ALT_BN128" "-DWITH_PROCPS=OFF" "-DMULTICORE=OFF" "-DIS_LIBFQFFT_PARENT=OFF"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_directory <SOURCE_DIR>/libfqfft ${FQFFT_INSTALL_DIR}/include/libfqfft
  USES_TERMINAL_DOWNLOAD TRUE
  USES_TERMINAL_CONFIGURE TRUE
  USES_TERMINAL_BUILD TRUE
)

add_library(fqfft INTERFACE)
target_include_directories(fqfft INTERFACE "${FQFFT_INSTALL_DIR}/include")
add_dependencies(fqfft fqfft_proj)

target_link_libraries(${COMPONENT_LIB} INTERFACE fqfft)