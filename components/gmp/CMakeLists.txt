idf_component_register()

include(ExternalProject)

set(GMP_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/gmp)

ExternalProject_Add(gmp_proj
  URL https://ftp.gnu.org/gnu/gmp/gmp-6.2.1.tar.xz
  URL_HASH SHA256=fd4829912cddd12f84181c3451cc752be224643e87fac497b69edddadc49b4f2
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
  PREFIX ${CMAKE_BINARY_DIR}/gmp_proj
  CONFIGURE_COMMAND <SOURCE_DIR>/configure 
    --host=riscv32-esp-elf 
    --prefix=${GMP_INSTALL_DIR} 
    --enable-static 
    --disable-shared
    --disable-assembly
    "CC=${CMAKE_C_COMPILER}"
    "CXX=${CMAKE_CXX_COMPILER}" 
    "AR=${CMAKE_AR}" 
    "LD=${CMAKE_LINKER}"
    "CFLAGS=${CMAKE_C_FLAGS}"
    "CXXFLAGS=${CMAKE_CXX_FLAGS}"
  BUILD_COMMAND make
  INSTALL_COMMAND make install
  INSTALL_DIR ${GMP_INSTALL_DIR}
  USES_TERMINAL_DOWNLOAD TRUE
  USES_TERMINAL_CONFIGURE TRUE
  USES_TERMINAL_BUILD TRUE
  BUILD_BYPRODUCTS "${GMP_INSTALL_DIR}/lib/libgmp.a"
)

add_prebuilt_library(gmp "${GMP_INSTALL_DIR}/lib/libgmp.a")
target_include_directories(gmp INTERFACE "${GMP_INSTALL_DIR}/include")
add_dependencies(gmp gmp_proj)

target_link_libraries(${COMPONENT_LIB} INTERFACE gmp)
