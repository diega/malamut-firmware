idf_component_register(REQUIRES gmp)

include(ExternalProject)

set(FF_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/ff)

ExternalProject_Add(ff_proj
  GIT_REPOSITORY https://github.com/scipr-lab/libff.git
  GIT_TAG 176f3f42fdef791f12b24417a400c4b6d386863c
  GIT_SUBMODULES_RECURSE FALSE
  GIT_PROGRESS TRUE
  PATCH_COMMAND git checkout -- CMakeLists.txt && sed -i.bak "115,116d" CMakeLists.txt
  CMAKE_ARGS 
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DCMAKE_AR=${CMAKE_AR}"
    "-DCMAKE_RANLIB=${CMAKE_RANLIB}"
    "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}"
    "-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS} -DCLOCK_PROCESS_CPUTIME_ID=0"
    "-DCMAKE_INSTALL_PREFIX=${FF_INSTALL_DIR}"
    "-DCURVE=ALT_BN128"
    "-DLOWMEM=ON"
    "-DWITH_PROCPS=OFF"
    "-DMULTICORE=OFF"
    "-DUSE_PT_COMPRESSION=OFF"
    "-DPROFILE_OP_COUNTS=OFF"
    "-DUSE_ASM=OFF"
    "-DPERFORMANCE=OFF"
    "-DIS_LIBFF_PARENT=OFF"
    "-DGMP_INCLUDE_DIR=${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/include"
    "-DGMP_LIBRARY=${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/lib/libgmp.a"
  USES_TERMINAL_DOWNLOAD TRUE
  USES_TERMINAL_CONFIGURE TRUE
  USES_TERMINAL_BUILD TRUE
  BUILD_BYPRODUCTS "${FF_INSTALL_DIR}/lib/libff.a"
)

ExternalProject_Add_StepDependencies(ff_proj configure gmp_proj)

add_prebuilt_library(ff "${FF_INSTALL_DIR}/lib/libff.a")
target_include_directories(ff INTERFACE "${FF_INSTALL_DIR}/include")
add_dependencies(ff ff_proj)

target_link_libraries(${COMPONENT_LIB} INTERFACE ff)