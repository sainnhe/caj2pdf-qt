cmake_minimum_required(VERSION 3.5)

project(caj2pdf VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Core5Compat REQUIRED)

IF(WIN32)
    set(RC app.o)
ELSE()
    set(RC)
ENDIF()

set(PROJECT_SOURCES
        main.cpp
        caj2pdf.cpp
        caj2pdf.h
        caj2pdf.ui
        convert.cpp
        page1.cpp
        page2.cpp
        page3.cpp
        ${RC}
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
