cmake_minimum_required(VERSION 3.5)

project(caj2pdf VERSION 0.1.3 LANGUAGES CXX)

file(GLOB_RECURSE QRC_SOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.qrc)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QRC_SOURCE_FILES resource.qrc)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Core5Compat Concurrent REQUIRED)

qt6_add_resources(QRC_FILES ${QRC_SOURCE_FILES})
SOURCE_GROUP("Resource Files" FILES ${QRC_SOURCE_FILES})

IF(WIN32)
    set(RC app.o)
ELSE()
    set(RC)
ENDIF()

set(PROJECT_SOURCES
        main.cpp
        #caj2pdf.cpp
        #caj2pdf.h
        #caj2pdf.ui
        convert.cpp
        #page1.cpp
        #page2.cpp
        #page3.cpp
        framelessWindow.h
        framelessWindow.cpp
        mainwindow.h
        mainwindow.cpp
        mainwindow.ui
        qssreader.h
        qssreader.cpp
        ${RC}
        ${QRC_FILES}
)

qt_add_executable(caj2pdf WIN32 MACOSX_BUNDLE
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(caj2pdf PRIVATE Qt6::Widgets)
target_link_libraries(caj2pdf PRIVATE Qt6::Core5Compat)

set_target_properties(caj2pdf PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER dev.sainnhe.caj2pdf-qt
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_ICON_FILE convert
)

qt_finalize_executable(caj2pdf)
