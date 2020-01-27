CONFIG -= qt

TEMPLATE = lib
DEFINES += JACFFMPEGLIB_LIBRARY

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

*g++ {
   #message("Adding -Werror for G++")
   QMAKE_CXXFLAGS += -Werror -Wall
}

win32-msvc* {
   #message("Adding /WX for MSVC")
   QMAKE_CXXFLAGS += /W3 /WX
}

PRECOMPILED_HEADER += pch.hpp

SOURCES += \
    demuxer.cpp \
    packet.cpp \
    stream.cpp \
    utilities.cpp

HEADERS += \
    demuxer.hpp \
    packet.hpp \
    pch.hpp \
    stream.hpp \
    utilities.hpp

# On Linux rely on finding in standard paths. Install FFmpeg devel packages
# Copy over FFmpeg DLLs on Windows. Not sure if there is a nicer way to do this
# On Linux FFmpeg binaries should be in standard paths
win32 {
    LIBS += -L$$PWD/../FFmpeg_libs/lib/
    INCLUDEPATH += $$PWD/../FFmpeg_libs/include
    DEPENDPATH += $$PWD/../FFmpeg_libs/include
    #QMAKE_POST_LINK += xcopy /Y $$shell_quote($$shell_path($$PWD/FFmpeg_libs/bin/*.dll)) $$shell_quote($$shell_path($$OUT_PWD))
    target.path = $$PWD/install
}

LIBS += -lavcodec -lavformat -lavfilter -lavutil -lswscale -lswresample

unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
