#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T14:45:04
#
#-------------------------------------------------

QT       += core gui

TARGET = easypaint
VERSION = 0.0.1
TEMPLATE = app

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build

SOURCES += main.cpp\
        mainwindow.cpp \
    toolbar.cpp \
    colorchooser.cpp \
    imagearea.cpp \
    paintinstruments.cpp \
    datasingleton.cpp \
    additionaltools.cpp \
    effects.cpp \
    resizedialog.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    toolbar.h \
    easypaintenums.h \
    colorchooser.h \
    imagearea.h \
    paintinstruments.h \
    datasingleton.h \
    additionaltools.h \
    effects.h \
    resizedialog.h \
    settingsdialog.h

TRANSLATIONS += \
    translations/easypaint_cs_CZ.ts \
    translations/easypaint_fr_FR.ts \
    translations/easypaint_ru_RU.ts

RESOURCES += \
    resources.qrc

target.path = /usr/bin
translations.path = /usr/share/easypaint/translations
translations.files = translations/*.qm
desktop.path = /usr/share/applications
desktop.files = media/EasyPaint.desktop
;icon.path = /usr/share/pixmaps
;icon.files = contrib/easypaint.png
isEmpty(QMAKE_LRELEASE) {
 win32 {
  QMAKE_LRELEASE =   $$[QT_INSTALL_BINS]\\lrelease.exe
}
else:QMAKE_LRELEASE =  $$[QT_INSTALL_BINS]/lrelease-qt4
}
isEmpty(TS_DIR) {
 TS_DIR =  translations
}
;TSQM.name = $$QMAKE_LRELEASE
;TSQM.input = TRANSLATIONS
;TSQM.output = $$TS_DIR/${QMAKE_FILE_BASE}.qm
;TSQM.commands = $$QMAKE_LRELEASE
;TSQM.CONFIG = no_link
;QMAKE_EXTRA_COMPILERS += TSQM
;PRE_TARGETDEPS += compiler_TSQM_make_all
;INSTALLS += target translations desktop icon
INSTALLS += target translations desktop
