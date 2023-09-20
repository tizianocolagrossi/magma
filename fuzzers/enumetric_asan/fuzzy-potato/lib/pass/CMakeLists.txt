
add_library( fuzzy-pass MODULE
    main.cpp
    fuzzy_pass.cpp
    instnamer_module.cpp
    dump_instrumenter.cpp
    dbg_type_info.cpp
    dbg_value_info.cpp
)

#target_link_libraries(fuzzy-pass ${CLANG_LIBS})

target_compile_features(fuzzy-pass PRIVATE cxx_range_for cxx_auto_type )

set_target_properties(fuzzy-pass PROPERTIES
COMPILE_FLAGS "-fno-rtti -std=c++17"
)
