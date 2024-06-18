set(PROJECT_SOURCES
    player.cpp
    card.cpp
    land.cpp
    sign.cpp
    IO_Interface.cpp
    PlayerSign.cpp
    Soldier.cpp
    Special.cpp
    System.cpp
    Match.cpp
    scarecrow.cpp
    Drummer.cpp
    WarSign.cpp
    main.cpp
    Winter.cpp
    Spring.cpp
    Heroine.cpp
    CardDeck.cpp
    GameGuide.cpp
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
