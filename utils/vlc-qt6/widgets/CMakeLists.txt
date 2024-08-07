#############################################################################
# VLC-Qt - Qt and libvlc connector library
# Copyright (C) 2016 Tadej Novak <tadej@tano.si>
# 2021 Andry <i@andry.io>
#
# This library is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this library. If not, see <http://www.gnu.org/licenses/>.
#############################################################################
# Configuration #
#################

# Add definition for exporting symbols
ADD_DEFINITIONS(-DVLCQT_WIDGETS_LIBRARY)

# Add definitions for shared or static library
IF(STATIC)
    ADD_DEFINITIONS(-DQT_STATIC -D_REENTRANT)
ELSE()
    ADD_DEFINITIONS(-DQT_SHARED -D_REENTRANT)
ENDIF()


###################
# List of sources #
###################
# Define the C++ source files
SET(VLCQT_WIDGETS_SRCS
    ControlAudio.cpp
    ControlVideo.cpp
    SharedExportWidgets.h
    WidgetSeek.cpp
    WidgetSeekProgress.cpp
    WidgetVideo.cpp
    WidgetVolumeSlider.cpp
)

# Define the Include files
SET(VLCQT_WIDGETS_HEADERS
    ControlAudio.h
    ControlVideo.h
    SharedExportWidgets.h
    WidgetSeek.h
    WidgetSeekProgress.h
    WidgetVideo.h
    WidgetVolumeSlider.h
)


#####################
# Compiler settings #
#####################
INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/widgets
    ${CMAKE_BINARY_DIR}/src
    ${CMAKE_BINARY_DIR}/include
)

IF(MSVC)
    INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/windows/msvc)
ENDIF()

# Additional macros
GENERATE_PKGCONFIG(${VLCQT_WIDGETS_NAME} widgets)
GENERATE_WINDOWS_RC(${VLCQT_WIDGETS_NAME} widgets VLCQT_WIDGETS_SRCS)

# Create the library.
IF(STATIC)
    ADD_LIBRARY(${VLCQT_WIDGETS} STATIC ${VLCQT_WIDGETS_SRCS} ${VLCQT_WIDGETS_HEADERS})
ELSE()
    ADD_LIBRARY(${VLCQT_WIDGETS} SHARED ${VLCQT_WIDGETS_SRCS} ${VLCQT_WIDGETS_HEADERS})
ENDIF()

ADD_DEPENDENCIES(${VLCQT_WIDGETS} ${VLCQT_CORE})

# Linux/Mac: Set framework, version and headers
SET_TARGET_PROPERTIES(${VLCQT_WIDGETS} PROPERTIES FRAMEWORK ON
                                                  OUTPUT_NAME "${VLCQT_WIDGETS_NAME}"
                                                  VERSION ${VLCQT_VERSION}
                                                  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
                                                  PUBLIC_HEADER "${VLCQT_WIDGETS_HEADERS}"
)

SYMLINK_FRAMEWORK_TEST(${VLCQT_WIDGETS} widgets ${VLCQT_WIDGETS_NAME})

# Link the required libraries
IF(QT_VERSION MATCHES 4)

ELSE()
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} PRIVATE ${VLCQT_CORE} Qt${QT_VERSION_MAJOR}::Widgets)
ENDIF()

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux" AND WITH_X11)
    TARGET_LINK_LIBRARIES(${VLCQT_WIDGETS} PRIVATE -lX11)
ENDIF()


################
# Installation #
################
IF(NOT STATIC AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(VLCQtWidgetsIncludesLocation ${CMAKE_INSTALL_LIBDIR}/${VLCQT_WIDGETS_NAME}.framework)
    SET(VLCQtWidgetsPublicHeaderLocation ${CMAKE_INSTALL_LIBDIR}/${VLCQT_WIDGETS_NAME}.framework)
ELSE()
    SET(VLCQtWidgetsIncludesLocation ${CMAKE_INSTALL_INCLUDEDIR})
    SET(VLCQtWidgetsPublicHeaderLocation ${CMAKE_INSTALL_INCLUDEDIR}/${VLCQT_WIDGETS_NAME})
ENDIF()

INSTALL(TARGETS ${VLCQT_WIDGETS} EXPORT VLCQtWidgetsTargets
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${VLCQtWidgetsIncludesLocation}
        PUBLIC_HEADER DESTINATION ${VLCQtWidgetsPublicHeaderLocation}
)
