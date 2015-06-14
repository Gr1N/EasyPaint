
#------- headers --------
set (HEADERS
    mainwindow.h
    easypaintenums.h
    imagearea.h
    datasingleton.h
    additionaltools.h
    effects/abstracteffect.h
    effects/negativeeffect.h
    effects/grayeffect.h
    effects/binarizationeffect.h
    effects/customeffect.h
    effects/effectwithsettings.h
    effects/gammaeffect.h
    effects/gaussianblureffect.h
    effects/sharpeneffect.h
    undocommand.h
    widgets/toolbar.h
    widgets/colorchooser.h
    widgets/palettebar.h
    widgets/palettebutton.h
    widgets/shortcutedit.h
    widgets/abstracteffectsettings.h
    widgets/customfiltersettings.h
    widgets/sharpenfiltersettings.h
    widgets/gaussianblurfiltersettings.h
    widgets/imagepreview.h
    dialogs/resizedialog.h
    dialogs/settingsdialog.h
    dialogs/textdialog.h
    dialogs/effectsettingsdialog.h
    instruments/abstractinstrument.h
    instruments/abstractselection.h
    instruments/selectioninstrument.h
    instruments/pencilinstrument.h
    instruments/lineinstrument.h
    instruments/eraserinstrument.h
    instruments/rectangleinstrument.h
    instruments/ellipseinstrument.h
    instruments/fillinstrument.h
    instruments/sprayinstrument.h
    instruments/magnifierinstrument.h
    instruments/colorpickerinstrument.h
    instruments/curvelineinstrument.h
    instruments/textinstrument.h
)

#------- sources --------
set (SOURCES
    main.cpp
    mainwindow.cpp
    imagearea.cpp
    datasingleton.cpp
    additionaltools.cpp
    effects/abstracteffect.cpp
    effects/negativeeffect.cpp
    effects/grayeffect.cpp
    effects/binarizationeffect.cpp
    effects/effectwithsettings.cpp
    effects/gammaeffect.cpp
    undocommand.cpp
    widgets/toolbar.cpp
    widgets/colorchooser.cpp
    widgets/palettebar.cpp
    widgets/palettebutton.cpp
    widgets/shortcutedit.cpp
    widgets/customfiltersettings.cpp
    widgets/sharpenfiltersettings.cpp
    widgets/gaussianblurfiltersettings.cpp
    widgets/imagepreview.cpp
    dialogs/resizedialog.cpp
    dialogs/settingsdialog.cpp
    dialogs/textdialog.cpp
    dialogs/effectsettingsdialog.cpp
    instruments/abstractinstrument.cpp
    instruments/abstractselection.cpp
    instruments/selectioninstrument.cpp
    instruments/pencilinstrument.cpp
    instruments/lineinstrument.cpp
    instruments/eraserinstrument.cpp
    instruments/rectangleinstrument.cpp
    instruments/ellipseinstrument.cpp
    instruments/fillinstrument.cpp
    instruments/sprayinstrument.cpp
    instruments/magnifierinstrument.cpp
    instruments/colorpickerinstrument.cpp
    instruments/curvelineinstrument.cpp
    instruments/textinstrument.cpp
)

#------- resources -------
set (RESOURCES
    resources.qrc
)

#------- languages -------
if(NOT NO_TRANSLATIONS)
    set (TRANSLATIONS
        translations/easypaint_ru_RU.ts
        translations/easypaint_cs_CZ.ts
        translations/easypaint_fr_FR.ts
    )

    find_package (Qt5LinguistTools)
    qt5_add_translation (TRANSLATIONS_QM ${TRANSLATIONS})
endif(NOT NO_TRANSLATIONS)

qt5_add_resources (QRC_SOURCES ${RESOURCES})

#-------  build executable from sources ----------
add_executable (${PROJECT}
    ${HEADERS}
    ${SOURCES}
    ${QRC_SOURCES}
    ${TRANSLATIONS_QM}
)

target_link_libraries (${PROJECT}
    Qt5::Widgets
    Qt5::PrintSupport
)

#-------  installing ----------
if (UNIX AND NOT APPLE)
    # installing
    install(TARGETS ${PROJECT} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    # install desktop files
    install(FILES "media/easypaint.desktop" DESTINATION ${CMAKE_INSTALL_DATADIR}/applications)

    # install pixmap
    install(FILES "media/logo/easypaint_64.png" DESTINATION ${CMAKE_INSTALL_DATADIR}/pixmaps)

    # install translations
    install(FILES ${TRANSLATIONS_QM} DESTINATION ${CMAKE_INSTALL_DATADIR}/easypaint/translations)
endif()
