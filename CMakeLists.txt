cmake_minimum_required(VERSION 3.16)
project(ChineseChess LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_RESOURCES
    resources/ChineseChess.qrc
)

if(QT_VERSION VERSION_LESS 6.0)
    qt5_add_resources(QRC_FILES ${PROJECT_RESOURCES})
else()
    qt6_add_resources(QRC_FILES ${PROJECT_RESOURCES})
endif()

set(PROJECT_GUI_SOURCES
    gui/main.cpp
    gui/ChineseChess.ui
    gui/ChineseChess.h
    gui/ChineseChess.cpp
)

set(PROJECT_SRC_SOURCES
    src/ChineseChessUnit.cpp
    src/ChineseChessManager.cpp
)

qt_add_executable(${PROJECT_NAME} 
    ${PROJECT_GUI_SOURCES} 
    ${PROJECT_SRC_SOURCES}
    ${QRC_FILES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Gui
        Qt${QT_VERSION_MAJOR}::Widgets
)

