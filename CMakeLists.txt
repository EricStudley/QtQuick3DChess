cmake_minimum_required(VERSION 3.16)

project(QtQuick3DChess VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)

qt_add_executable(QtQuick3DChess
    qml.qrc
    res.qrc
    src/main.cpp
    src/ChessModel.h
    src/ChessModel.cpp
    src/ChessSquare.h
    src/ChessSquare.cpp
    src/ChessPiece.h
    src/ChessPiece.cpp
    src/ChessEnums.h
)

set_target_properties(QtQuick3DChess PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(QtQuick3DChess
    PRIVATE Qt6::Quick)

install(TARGETS QtQuick3DChess
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
