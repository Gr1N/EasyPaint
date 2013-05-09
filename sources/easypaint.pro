#-------------------------------------------------
#
# Project created by QtCreator 2012-03-03T14:45:04
#
#-------------------------------------------------

QT       += widgets printsupport

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
    undocommand.cpp \
    widgets/toolbar.cpp \
    widgets/colorchooser.cpp \
    widgets/palettebar.cpp \
    widgets/palettebutton.cpp \
    widgets/shortcutedit.cpp \
    dialogs/resizedialog.cpp \
    dialogs/settingsdialog.cpp \
    dialogs/textdialog.cpp \
    instruments/abstractinstrument.cpp \
    instruments/abstractselection.cpp \
    instruments/pencilinstrument.cpp \
    instruments/lineinstrument.cpp \
    instruments/eraserinstrument.cpp \
    instruments/rectangleinstrument.cpp \
    instruments/ellipseinstrument.cpp \
    instruments/fillinstrument.cpp \
    instruments/sprayinstrument.cpp \
    instruments/magnifierinstrument.cpp \
    instruments/colorpickerinstrument.cpp \
    instruments/selectioninstrument.cpp \
    instruments/curvelineinstrument.cpp \
    instruments/textinstrument.cpp \
    effects/abstracteffect.cpp \
    effects/negativeeffect.cpp \
    effects/grayeffect.cpp \
    effects/binarizationeffect.cpp \
    effects/gammaeffect.cpp \
    dialogs/effectsettingsdialog.cpp \
    widgets/customfiltersettings.cpp \
    effects/effectwithsettings.cpp \
    widgets/sharpenfiltersettings.cpp \
    widgets/imagepreview.cpp \
    widgets/gaussianblurfiltersettings.cpp

HEADERS  += mainwindow.h \
    easypaintenums.h \
    imagearea.h \
    datasingleton.h \
    additionaltools.h \
    undocommand.h \
    widgets/toolbar.h \
    widgets/colorchooser.h \
    widgets/palettebar.h \
    widgets/palettebutton.h \
    widgets/shortcutedit.h \
    dialogs/resizedialog.h \
    dialogs/settingsdialog.h \
    dialogs/textdialog.h \
    instruments/abstractinstrument.h \
    instruments/abstractselection.h \
    instruments/pencilinstrument.h \
    instruments/lineinstrument.h \
    instruments/eraserinstrument.h \
    instruments/rectangleinstrument.h \
    instruments/ellipseinstrument.h \
    instruments/fillinstrument.h \
    instruments/sprayinstrument.h \
    instruments/magnifierinstrument.h \
    instruments/colorpickerinstrument.h \
    instruments/selectioninstrument.h \
    instruments/curvelineinstrument.h \
    instruments/textinstrument.h \
    effects/abstracteffect.h \
    effects/negativeeffect.h \
    effects/grayeffect.h \
    effects/binarizationeffect.h \
    effects/gammaeffect.h \
    effects/gaussianblureffect.h \
    effects/sharpeneffect.h \
    dialogs/effectsettingsdialog.h \
    widgets/customfiltersettings.h \
    widgets/abstracteffectsettings.h \
    effects/effectwithsettings.h \
    effects/customeffect.h \
    widgets/sharpenfiltersettings.h \
    widgets/imagepreview.h \
    widgets/gaussianblurfiltersettings.h

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








