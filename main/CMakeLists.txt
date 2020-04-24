set(NAME main)

add_executable(${NAME})

target_sources(${NAME}
    PRIVATE
        src/main.cpp
)

target_include_directories(${NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_options(${NAME}
    PUBLIC
        -Os
        -nostdlib
        -mlongcalls
        -mtext-section-literals
        -Wl,-Map=${CMAKE_CURRENT_BINARY_DIR}/${NAME}.map
)

target_link_libraries(${NAME}
    PUBLIC
        sdk
)

target_generate_binary(${NAME})

add_dependencies(${NAME} install_deps)

add_partition(nvs data nvs 0x9000 24K)
add_partition(phy_init data phy 0xf000 4K)
target_add_flash(${NAME} factory app factory 0x10000 660K)
