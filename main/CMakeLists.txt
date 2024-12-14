idf_component_register(SRCS "src/app_main.cpp" "src/matter_interface.cpp"
        INCLUDE_DIRS "include"
)

set_property(TARGET ${COMPONENT_LIB} PROPERTY CXX_STANDARD 17)
target_compile_options(${COMPONENT_LIB} PRIVATE "-DCHIP_HAVE_CONFIG_H")