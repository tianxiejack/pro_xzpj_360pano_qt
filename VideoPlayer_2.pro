#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui opengl network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer_2
TEMPLATE = app

CONFIG += console
SOURCES += src/main.cpp \
    src/videoplayer/videoplayer.cpp \
    src/mainwindowgl.cpp \
    src/videowidget.cpp \
    src/netcom.cpp \
    src/protocol.cpp \
    src/init.cpp \
    src/qcustomcalendarwidget.cpp \
    src/widget.cpp \
    src/widgetinit.cpp \
    src/panorama_hand_widget.cpp \
    src/turntable_widget.cpp \
    src/locationcollectwidget.cpp \
    src/CGlobalDate.cpp \
    src/listwidget.cpp \
    src/vediosliderwidget.cpp \
    src/mytablewidget.cpp \
    src/closeeventwidget.cpp \
    mvconfigwidget.cpp
DESTDIR =$$PWD/ffmpeg/bin
HEADERS  += \
    src/videoplayer/videoplayer.h \
    src/mainwindowgl.h \
    src/videowidget.h \
    src/netcom.h \
    src/protocol.h \
    src/qcustomcalendarwidget.h \
    src/widget.h \
    src/panorama_hand_widget.h \
    src/turntable_widget.h \
    src/locationcollectwidget.h \
    src/CGlobalDate.h \
    src/listwidget.h \
    src/vediosliderwidget.h \
    src/mytablewidget.h \
    src/closeeventwidget.h \
    mvconfigwidget.h

FORMS    += \
    src/mainwindowgl.ui \
    src/widget.ui

INCLUDEPATH += $$PWD/ffmpeg/include \
                $$PWD/src

LIBS += $$PWD/ffmpeg/lib/avcodec.lib \
        $$PWD/ffmpeg/lib/avdevice.lib \
        $$PWD/ffmpeg/lib/avfilter.lib \
        $$PWD/ffmpeg/lib/avformat.lib \
        $$PWD/ffmpeg/lib/avutil.lib \
        $$PWD/ffmpeg/lib/postproc.lib \
        $$PWD/ffmpeg/lib/swresample.lib \
        $$PWD/ffmpeg/lib/swscale.lib

RESOURCES += \
    calendar.qrc
