cmake_minimum_required(VERSION 3.16)
project(WayCptr LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets WaylandClient Network)
find_package(LayerShellQt REQUIRED)
find_package(Threads REQUIRED)

set(LUA_INCLUDE_DIR "/usr/include/lua5.4")
set(LUA_LIBRARIES "/usr/lib/liblua5.4.so")

find_package(sol2 REQUIRED)

add_executable(waycptr 
    main.cpp

    #---------------------- 
    # --- panel/include ---
    #---------------------- 
    panel/include/panel-conf.hpp
    panel/include/panel.hpp
    
    #--------------------- 
    # --- panel/source ---
    #--------------------- 
    panel/source/panel.cpp 
)

target_include_directories(waycptr PUBLIC
    ${CMAKE_SOURCE_DIR}/panel/include
    ${CMAKE_SOURCE_DIR}/widgets/include
    ${CMAKE_SOURCE_DIR}/lua-engine/include

    ${LUA_INCLUDE_DIR}
)

target_link_libraries(waycptr PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    sol2::sol2
    LayerShellQt::Interface
    Threads::Threads
    ${LUA_LIBRARIES}
)
