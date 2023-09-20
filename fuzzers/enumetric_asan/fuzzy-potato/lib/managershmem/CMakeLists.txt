add_executable( manager_sh_stats 
    manager.cpp
)

add_executable( test_shmem 
    tester.cpp
)

set_target_properties(manager_sh_stats PROPERTIES
    COMPILE_FLAGS "-c -Wattributes --std=c++17"
)