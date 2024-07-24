# Find vlc-qt6

function(to_hex DECIMAL OUTHEX)
    set(HEX_DIGITS "0123456789ABCDEF")
    set(REMAINDER 0)
    set(HEX "")

    foreach (x in 0)
        math(EXPR REMAINDER "${DECIMAL} % 16")
        string(SUBSTRING ${HEX_DIGITS} ${REMAINDER} 1 HEX_DIGIT)
        set(HEX "${HEX_DIGIT}${HEX}")
        math(EXPR DECIMAL "${DECIMAL} / 16")
    endforeach ()

    set(${OUTHEX} ${HEX} PARENT_SCOPE)
endfunction()

function(convert_version_to_hex input_version output_hex)
    string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)" _ ${input_version})
    set(MAJOR_VERSION ${CMAKE_MATCH_1})
    set(MINOR_VERSION ${CMAKE_MATCH_2})
    set(PATCH_VERSION ${CMAKE_MATCH_3})

    to_hex(${CMAKE_MATCH_1} MAJOR_HEX)
    to_hex(${CMAKE_MATCH_2} MINOR_HEX)
    to_hex(${CMAKE_MATCH_3} PATCH_HEX)

    # Concatenar valores hexadecimais
    set(${output_hex} "0x${MAJOR_HEX}${MINOR_HEX}${PATCH_HEX}" PARENT_SCOPE)
endfunction()

include(FindLIBVLC)

set(PWD ${CMAKE_SOURCE_DIR}/utils/vlc-qt6)
set(PWDC ${PWD}/core)
set(PWDW ${PWD}/widgets)
message(STATUS "vlc-qt6 dir: " ${PWD})

set(VLCQT_CORE_SRCS
        ${PWDC}/AbstractVideoFrame.cpp
        ${PWDC}/AbstractVideoStream.cpp
        ${PWDC}/Audio.cpp
        ${PWDC}/Common.cpp
        ${PWDC}/Enums.cpp
        ${PWDC}/Error.cpp
        ${PWDC}/Instance.cpp
        ${PWDC}/Media.cpp
        ${PWDC}/MediaList.cpp
        ${PWDC}/MediaListPlayer.cpp
        ${PWDC}/MediaPlayer.cpp
        ${PWDC}/MetaManager.cpp
        ${PWDC}/ModuleDescription.cpp
        ${PWDC}/TrackModel.cpp
        ${PWDC}/Video.cpp
        ${PWDC}/VideoStream.cpp
        ${PWDC}/YUVVideoFrame.cpp
)

set(VLCQT_CORE_HEADERS
        ${PWDC}/AbstractVideoFrame.h
        ${PWDC}/AbstractVideoStream.h
        ${PWDC}/Audio.h
        ${PWDC}/Common.h
        ${PWDC}/Config.h
        ${PWDC}/Enums.h
        ${PWDC}/Error.h
        ${PWDC}/Instance.h
        ${PWDC}/Media.h
        ${PWDC}/MediaList.h
        ${PWDC}/MediaListPlayer.h
        ${PWDC}/MediaPlayer.h
        ${PWDC}/MetaManager.h
        ${PWDC}/ModuleDescription.h
        ${PWDC}/SharedExportCore.h
        ${PWDC}/Stats.h
        ${PWDC}/TrackModel.h
        ${PWDC}/Video.h
        ${PWDC}/VideoDelegate.h
        ${PWDC}/VideoStream.h
        ${PWDC}/YUVVideoFrame.h
)

convert_version_to_hex(${LIBVLC_VERSION} LIBVLC_VERSION)
message(STATUS "LibVLC version to hex: " ${LIBVLC_VERSION})
configure_file(${PWD}/Config.h.in ${PWDC}/Config.h @ONLY)

if (${LIBVLC_VERSION} EQUAL 0x020200 OR ${LIBVLC_VERSION} GREATER 0x020200)
    set(VLCQT_CORE_SRCS ${VLCQT_CORE_SRCS}
            ${PWDC}/Equalizer.cpp
            ${PWDC}/AudioDevice.cpp
    )

    set(VLCQT_CORE_HEADERS  ${VLCQT_CORE_HEADERS}
            ${PWDC}/Equalizer.h
            ${PWDC}/AudioDevice.h
    )
endif ()

set(VLCQT_WIDGETS_SRCS
        ${PWDW}/ControlAudio.cpp
        ${PWDW}/ControlVideo.cpp
        ${PWDW}/WidgetSeek.cpp
        ${PWDW}/WidgetSeekProgress.cpp
        ${PWDW}/WidgetVideo.cpp
        ${PWDW}/WidgetVolumeSlider.cpp
)

set(VLCQT_WIDGETS_HEADERS
        ${PWDW}/ControlAudio.h
        ${PWDW}/ControlVideo.h
        ${PWDW}/SharedExportWidgets.h
        ${PWDW}/WidgetSeek.h
        ${PWDW}/WidgetSeekProgress.h
        ${PWDW}/WidgetVideo.h
        ${PWDW}/WidgetVolumeSlider.h
)
