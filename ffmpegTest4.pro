QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiothread.cpp \
    main.cpp \
    playthread.cpp \
    widget.cpp

HEADERS += \
    audiothread.h \
    playthread.h \
    widget.h

FORMS += \
    widget.ui

FFMPEG_PATH += E:\chd\ffmpeg\ffmpeg-n4.4.3-3-gb48951bd29-win64-gpl-shared-4.4
INCLUDEPATH += $$FFMPEG_PATH/include
LIBS += $$FFMPEG_PATH/lib/lib*.dll.a

SDL2_PATH += E:\chd\ffmpeg\SDL2-2.30.5\x86_64-w64-mingw32
INCLUDEPATH += $$SDL2_PATH/include
LIBS += $$SDL2_PATH/bin/SDL2.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Style.qrc \
    image.qrc
