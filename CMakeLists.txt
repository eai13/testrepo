cmake_minimum_required(VERSION 3.5)

project(testrepo VERSION 0.1 LANGUAGES CXX)

include(versioning.cmake)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

configure_file(
    ${CMAKE_SOURCE_DIR}/version.h.in
    ${CMAKE_BINARY_DIR}/generated/version.h
)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

add_executable(testrepo
    ${PROJECT_SOURCES}
)

target_link_libraries(testrepo PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(testrepo PRIVATE
    ${CMAKE_BINARY_DIR}/generated
)
