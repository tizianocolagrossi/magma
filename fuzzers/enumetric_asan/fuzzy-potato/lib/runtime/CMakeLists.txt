add_library( dump_rt MODULE
    dump_rt.cpp
)

set_target_properties(dump_rt PROPERTIES
    COMPILE_FLAGS "-fPIC -c -Wattributes --std=c++17"
)