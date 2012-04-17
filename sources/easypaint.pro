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
    imagearea.cpp \
    datasingleton.cpp \
    additionaltools.cpp \
    effects.cpp \
    undocommand.cpp \
    widgets/toolbar.cpp \
    widgets/colorchooser.cpp \
    widgets/palettebar.cpp \
    widgets/palettebutton.cpp \
    widgets/shortcutedit.cpp \
    dialogs/resizedialog.cpp \
    dialogs/settingsdialog.cpp \
    instruments/abstractinstrument.cpp \
    instruments/pencilinstrument.cpp \
    instruments/lineinstrument.cpp \
    instruments/eraserinstrument.cpp \
    instruments/rectangleinstrument.cpp \
    instruments/ellipseinstrument.cpp \
    instruments/fillinstrument.cpp \
    instruments/sprayinstrument.cpp \
    instruments/magnifierinstrument.cpp \
    instruments/colorpickerinstrument.cpp \
    instruments/selectioninstrument.cpp

HEADERS  += mainwindow.h \
    easypaintenums.h \
    imagearea.h \
    datasingleton.h \
    additionaltools.h \
    effects.h \
    undocommand.h \
    widgets/toolbar.h \
    widgets/colorchooser.h \
    widgets/palettebar.h \
    widgets/palettebutton.h \
    widgets/shortcutedit.h \
    dialogs/resizedialog.h \
    dialogs/settingsdialog.h \
    instruments/abstractinstrument.h \
    instruments/pencilinstrument.h \
    instruments/lineinstrument.h \
    instruments/eraserinstrument.h \
    instruments/rectangleinstrument.h \
    instruments/ellipseinstrument.h \
    instruments/fillinstrument.h \
    instruments/sprayinstrument.h \
    instruments/magnifierinstrument.h \
    instruments/colorpickerinstrument.h \
    instruments/selectioninstrument.h

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
desktop.files = media/easypaint.desktop
icon.path = /usr/share/pixmaps
icon.files = media/logo/easypaint_64.png
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
INSTALLS += target translations desktop icon








