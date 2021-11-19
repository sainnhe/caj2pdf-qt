cmake_minimum_required(VERSION 3.5)

project(caj2pdf VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Core5Compat REQUIRED)

IF (WIN32)
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

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(caj2pdf WIN32 MACOSX_BUNDLE
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET caj2pdf APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(caj2pdf SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(caj2pdf WIN32 MACOSX_BUNDLE
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(caj2pdf PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(caj2pdf PRIVATE Qt6::Core5Compat)

set_target_properties(caj2pdf PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(caj2pdf)
endif()
