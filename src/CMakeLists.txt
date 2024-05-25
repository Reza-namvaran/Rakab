set(PROJECT_SOURCES
    main.cpp
    player.cpp
)

add_executable(Rakab
    ${PROJECT_SOURCES}
)

target_include_directories(Rakab PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(Rakab PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
