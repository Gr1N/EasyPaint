#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T14:45:04
#
#-------------------------------------------------

QT       += core gui

TARGET = EasyPaint
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    toolbar.cpp \
    colorchooser.cpp \
    imagearea.cpp \
    paintinstruments.cpp \
    datasingleton.cpp \
    additionaltools.cpp \
    effects.cpp \
    resizeimagedialog.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    easypaintenums.h \
    colorchooser.h \
    imagearea.h \
    paintinstruments.h \
    datasingleton.h \
    additionaltools.h \
    effects.h \
    resizeimagedialog.h

RESOURCES += \
    media.qrc
