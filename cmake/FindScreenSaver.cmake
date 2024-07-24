# Find QtAVPlayer

set(PWD ${CMAKE_SOURCE_DIR}/utils/screensaver)
message(STATUS "screensaver dir: " ${PWD})

set(SCREENSAVER_SOURCES
        ${PWD}/screensaver.cpp
        ${PWD}/screensaver.h
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(SCREENSAVER_SOURCES
            ${SCREENSAVER_SOURCES}
            ${PWD}/powersaving.cpp
            ${PWD}/powersaving.h
    )
endif ()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SCREENSAVER_SOURCES
            ${SCREENSAVER_SOURCES}
            ${PWD}/winscreensaver.cpp
            ${PWD}/winscreensaver.h
    )
endif ()
