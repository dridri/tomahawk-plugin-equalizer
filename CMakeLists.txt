cmake_minimum_required(VERSION 2.8)
CMAKE_POLICY(SET CMP0017 NEW)

if(NOT TOMAHAWK_LIBRARIES)
    message(STATUS "BUILDING OUTSIDE TOMAHAWK")
    find_package(Tomahawk REQUIRED)
else()
    message(STATUS "BUILDING INSIDE TOMAHAWK")
    set(TOMAHAWK_USE_FILE "${CMAKE_SOURCE_DIR}/TomahawkUse.cmake")
endif()
include( ${TOMAHAWK_USE_FILE} )

include_directories( ${TOMAHAWK_INCLUDE_DIRS} )

qt_wrap_ui( EqPlugin_UI equalizer.ui )

tomahawk_add_plugin(equalizer
    TYPE infoplugin
    EXPORT_MACRO INFOPLUGINDLLEXPORT_PRO
    SOURCES
        ${EqPlugin_UI}
        EqPlugin.cpp
        EqWidget.cpp
        EqEffect.cpp
    LINK_LIBRARIES
        ${TOMAHAWK_LIBRARIES}
)
