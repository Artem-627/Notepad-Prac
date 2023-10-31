cmake_minimum_required(VERSION 3.20)


project(Notepad VERSION 1.0.0 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(Notepad
    Source/main.cpp
    Source/Front.h
    Source/Front.cpp
    Source/Back.h
    Source/Back.cpp
)

set_target_properties(Notepad PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

target_link_libraries(Notepad PRIVATE Qt6::Widgets)
