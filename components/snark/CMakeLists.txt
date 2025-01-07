idf_component_register(REQUIRES ff fqfft gmp)

include(ExternalProject)

set(SNARK_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/snark)
set(FF_INCLUDE_DIR ${CMAKE_BINARY_DIR}/esp-idf/ff/ff/include)
set(FQFFT_INCLUDE_DIR ${CMAKE_BINARY_DIR}/esp-idf/fqfft/fqfft/include)
set(GMP_INCLUDE_DIR ${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/include)

ExternalProject_Add(snark_proj
  GIT_REPOSITORY https://github.com/scipr-lab/libsnark.git
  GIT_TAG 6c705e3135f585c222813654caedc86520fda1f6
  GIT_SUBMODULES_RECURSE FALSE
  GIT_PROGRESS TRUE
  PATCH_COMMAND git checkout -- CMakeLists.txt && sed -i.bak "153,155d" CMakeLists.txt
  CMAKE_ARGS
    "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}"
    "-DGMP_LIBRARIES=${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/lib/libgmp.a"
    "-DGMPXX_LIBRARIES=${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/lib/libgmp.a"
    "-DLIBFF_LIBRARIES=${CMAKE_BINARY_DIR}/esp-idf/ff/ff/lib/libff.a"
    "-DCMAKE_AR=${CMAKE_AR}"
    "-DCMAKE_RANLIB=${CMAKE_RANLIB}"
    "-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}"
    "-DCMAKE_CXX_FLAGS=-I${FF_INCLUDE_DIR} -I${FQFFT_INCLUDE_DIR} -I${GMP_INCLUDE_DIR} -I<SOURCE_DIR>"
    "-DCURVE=ALT_BN128"
    "-DLOWMEM=ON"
    "-DWITH_PROCPS=OFF"
    "-DWITH_SUPERCOP=OFF"
    "-DMULTICORE=OFF"
    "-DUSE_PT_COMPRESSION=OFF"
    "-DPROFILE_OP_COUNTS=OFF"
    "-DUSE_ASM=OFF"
    "-DPERFORMANCE=OFF"
    "-DUSE_LINKED_LIBRARIES=ON"
    "-DCMAKE_INSTALL_PREFIX=${SNARK_INSTALL_DIR}"
    "-DLIBFF_INCLUDE_DIR=${FF_INCLUDE_DIR}"
    "-DLIBFQFFT_INCLUDE_DIR=${FQFFT_INCLUDE_DIR}"
    "-DOPT_FLAGS=-ggdb3 -O2 -march=rv32imc_zicsr_zifencei"
  USES_TERMINAL_DOWNLOAD TRUE
  USES_TERMINAL_CONFIGURE TRUE
  USES_TERMINAL_BUILD TRUE
  BUILD_BYPRODUCTS "${SNARK_INSTALL_DIR}/lib/libsnark.a"
)

ExternalProject_Add_StepDependencies(snark_proj configure ff_proj)

add_prebuilt_library(snark "${SNARK_INSTALL_DIR}/lib/libsnark.a")
target_include_directories(snark INTERFACE "${SNARK_INSTALL_DIR}/include")
add_dependencies(snark snark_proj)

target_compile_definitions(snark INTERFACE CURVE_ALT_BN128)
target_compile_options(${COMPONENT_LIB} INTERFACE -std=gnu++11 -fexceptions)
target_link_libraries(${COMPONENT_LIB} INTERFACE snark)
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_BINARY_DIR}/esp-idf/ff/ff/lib/libff.a")
target_link_libraries(${COMPONENT_LIB} INTERFACE "${CMAKE_BINARY_DIR}/esp-idf/gmp/gmp/lib/libgmp.a")