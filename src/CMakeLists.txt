set(PROJECT_SOURCES
    player.cpp
    Card.cpp
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
    PeaceSign.cpp
    main.cpp
    Winter.cpp
    Spring.cpp
    Heroine.cpp
    CardDeck.cpp
    GameGuide.cpp
    Spy.cpp
    Turncoat.cpp
    Bishop.cpp
    Storage.cpp
    State.cpp
    Intro.cpp
    MainMenu.cpp
    PlayerSetup.cpp
    StateManager.cpp
    LoadMenu.cpp
    Mirage.cpp
    WhiteSeal.cpp
    Sleipnir.cpp
)

add_executable(${PROJECT_NAME}
    ${PROJECT_SOURCES}
)

# Specify the directories where the headers and libraries are located

include_directories(./include)

link_directories(./lib)

target_link_libraries(${PROJECT_NAME} raylib)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} winmm)
endif()

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()