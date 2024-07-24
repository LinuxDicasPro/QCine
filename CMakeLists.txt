cmake_minimum_required(VERSION 3.27)

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(DEBUG true)
    string(TIMESTAMP VERSION "%Y.%m.%d")
else ()
    if (${CMAKE_BUILD_TYPE} MATCHES "Release")
        set(CMAKE_INSTALL_PREFIX /usr)
    endif ()
    set(DEBUG false)
    file(READ "${CMAKE_SOURCE_DIR}/src/Version.hpp" VERSION_FILE_CONTENT)
    string(REGEX MATCH "define VERSION \"([^\"]+)" VERSION_MATCH "${VERSION_FILE_CONTENT}")
    set(VERSION ${CMAKE_MATCH_1})
endif ()

set(PRG_NAME QCine)
project(${PRG_NAME} VERSION ${VERSION})
set(QT_VERSION 6)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(QAPPLICATION_CLASS QApplication CACHE STRING "Inheritance class for SingleApplication")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

configure_file("${CMAKE_SOURCE_DIR}/src/Version.hpp.in" "${CMAKE_SOURCE_DIR}/src/Version.hpp" @ONLY)

message(STATUS "project source dir: " ${PROJECT_SOURCE_DIR})
message(STATUS "cmake module path: " ${CMAKE_MODULE_PATH})
message(STATUS "cmake install prefix: " ${CMAKE_INSTALL_PREFIX})
message(STATUS "current date: " ${VERSION})
message(STATUS "debug mode: " ${DEBUG})

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

find_package(Qt${QT_VERSION} COMPONENTS
        Concurrent
        Core
        DBus
        Gui
        Multimedia
        MultimediaWidgets
        Widgets
        REQUIRED
)

include(FindFFmpeg)
include(FindVLCQT)
include(FindScreenSaver)

file(GLOB DIRECTORIES CONFIGURE_DEPENDS LIST_DIRECTORIES true utils utils/*/ src src/*/)

foreach(DIR ${DIRECTORIES})
    if(IS_DIRECTORY ${DIR})
        list(APPEND SRC_DIRS ${DIR})
        message(STATUS ${DIR})
    endif ()
endforeach()

include_directories(
        ${SRC_DIRS}
        ${Qt${QT_VERSION}Multimedia_PRIVATE_INCLUDE_DIRS}
        ${FFMPEG_INCLUDE_DIRS}
        ${LIBVLC_INCLUDE_DIR}
        ${VLC_COMMON_INCLUDE_DIR}
)

add_subdirectory(utils/SingleApplication)
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*)

add_executable(${PRG_NAME}
        ${SRC_FILES}
        ${VLCQT_CORE_SRCS}
        ${VLCQT_CORE_HEADERS}
        ${VLCQT_WIDGETS_SRCS}
        ${VLCQT_WIDGETS_HEADERS}
        ${SCREENSAVER_SOURCES}
)

set_property(TARGET ${PRG_NAME} PROPERTY OUTPUT_NAME "qcine")
set_property(TARGET ${PRG_NAME} PROPERTY LINK_FLAGS "-Wl,-s")
set_property(TARGET ${PRG_NAME} PROPERTY COMPILE_FLAGS "-03")
set_property(TARGET ${PRG_NAME} PROPERTY COMPILE_FLAGS "-finline-functions")
set_property(TARGET ${PRG_NAME} PROPERTY COMPILE_FLAGS "-ftree-vectorize")

include(CheckIPOSupported)
check_ipo_supported(RESULT supported OUTPUT error)

if (supported)
    message(STATUS "IPO / LTO enabled")
    set_property(TARGET ${PRG_NAME} PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else ()
    message(STATUS "IPO / LTO not supported: <${error}>")
endif ()

target_link_libraries(${PRG_NAME}
        Qt${QT_VERSION}::Concurrent
        Qt${QT_VERSION}::Core
        Qt${QT_VERSION}::DBus
        Qt${QT_VERSION}::Gui
        Qt${QT_VERSION}::Multimedia
        Qt${QT_VERSION}::MultimediaWidgets
        Qt${QT_VERSION}::Widgets
        SingleApplication::SingleApplication
        Threads::Threads
        ${LIBVLC_LIBRARY}
        ${LIBVLCCORE_LIBRARY}
        ${FFMPEG_LIBRARIES}
)

add_custom_target(appimage
#        COMMAND ${CMAKE_COMMAND} -E echo "Creating AppImage..."
#        COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/create_appimage.sh
        DEPENDS ${PRG_NAME}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
