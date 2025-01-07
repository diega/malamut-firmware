set(CIRCUIT_FILE_NAME_WE add)
set(CIRCUIT_FILE ${COMPONENT_DIR}/circuits/${CIRCUIT_FILE_NAME_WE}.circom)
set(GENERATED_OUTPUT_DIR ${CMAKE_BINARY_DIR}/generated)
set(GENERATED_OUTPUT_CPP ${GENERATED_OUTPUT_DIR}/${CIRCUIT_FILE_NAME_WE}_cpp)
set(GENERATED_SOURCES
  ${GENERATED_OUTPUT_CPP}/calcwit.cpp
  ${GENERATED_OUTPUT_CPP}/calcwit.hpp
  ${GENERATED_OUTPUT_CPP}/circom.hpp
  ${GENERATED_OUTPUT_CPP}/${CIRCUIT_FILE_NAME_WE}.cpp
  ${GENERATED_OUTPUT_CPP}/${CIRCUIT_FILE_NAME_WE}.hpp
)
file(MAKE_DIRECTORY ${GENERATED_OUTPUT_CPP})

idf_component_register(
  SRCS
    ${COMPONENT_DIR}/extra/fr.cpp
    ${COMPONENT_DIR}/extra/fr.hpp
    ${COMPONENT_DIR}/extra/fr_element.hpp
    ${COMPONENT_DIR}/extra/fr_generic.cpp
    ${COMPONENT_DIR}/extra/fr_raw_generic.cpp
  INCLUDE_DIRS ${GENERATED_OUTPUT_CPP}
  PRIV_REQUIRES gmp
)

add_custom_command(
  OUTPUT ${GENERATED_SOURCES}
  COMMAND circom ${CIRCUIT_FILE} --c --output ${GENERATED_OUTPUT_DIR}
  DEPENDS ${CIRCUIT_FILE}
)

add_custom_target(generate_circom DEPENDS ${GENERATED_SOURCES})
add_dependencies(${COMPONENT_LIB} generate_circom)
set_property(DIRECTORY "${COMPONENT_DIR}" APPEND PROPERTY
     ADDITIONAL_CLEAN_FILES ${GENERATED_SOURCES})

target_compile_options(${COMPONENT_LIB} PRIVATE -fpermissive -Wno-address-of-packed-member -Wno-format)