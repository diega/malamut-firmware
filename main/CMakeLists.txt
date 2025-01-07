idf_component_register(
  SRCS "main.cpp"
  REQUIRES snark
)

target_compile_definitions(${COMPONENT_LIB} PRIVATE CURVE_ALT_BN128)