cmake_minimum_required(VERSION 2.8)
CMAKE_POLICY(SET CMP0017 NEW)

set (CMAKE_CXX_FLAGS "-g3 -Wall") 

if(NOT TOMAHAWK_LIBRARIES)
    message(STATUS "BUILDING OUTSIDE TOMAHAWK")
    find_package(Tomahawk REQUIRED)
else()
    message(STATUS "BUILDING INSIDE TOMAHAWK")
    set(TOMAHAWK_USE_FILE "${CMAKE_SOURCE_DIR}/TomahawkUse.cmake")
endif()
include( ${TOMAHAWK_USE_FILE} )

include_directories( ${TOMAHAWK_INCLUDE_DIRS} )

set(QT ${QT} opengl)
set(QT_USE_QTOPENGL TRUE)
find_package(OpenGL REQUIRED)
include_directories( ${QT_QTOPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} )

qt_wrap_ui( EqPlugin_UI equalizer.ui )

tomahawk_add_plugin(equalizer
    TYPE viewpage
    EXPORT_MACRO TOMAHAWK_VIEWPAGE_EXPORT_PRO
    SOURCES
        ${EqPlugin_UI}
        EqPlugin.cpp
        EqWidget.cpp
        GraphicEq.cpp
        fft3.c
        resources.qrc
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
        ${QT_QTOPENGL_LIBRARIES}
        ${OPENGL_LIBRARIES}
        -lfftw3f -g3
)

install(TARGETS tomahawk_viewpage_equalizer DESTINATION /usr/local/lib)
