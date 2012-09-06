cmake_minimum_required (VERSION 2.6)
 
# set project's name
set (PROJECT easypaint)

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

# add version define
set(EASYPAINT_VERSION 0.1.0)

#------- headers --------
set (HEADERS 
    sources/mainwindow.h
    sources/easypaintenums.h
    sources/imagearea.h
    sources/datasingleton.h
    sources/additionaltools.h
    sources/effects.h
    sources/undocommand.h
    sources/widgets/toolbar.h
    sources/widgets/colorchooser.h
    sources/widgets/palettebar.h
    sources/widgets/palettebutton.h
    sources/widgets/shortcutedit.h
    sources/dialogs/resizedialog.h
    sources/dialogs/settingsdialog.h
    sources/instruments/abstractinstrument.h
    sources/instruments/abstractselection.h
    sources/instruments/selectioninstrument.h
    sources/instruments/pencilinstrument.h
    sources/instruments/lineinstrument.h
    sources/instruments/eraserinstrument.h
    sources/instruments/rectangleinstrument.h
    sources/instruments/ellipseinstrument.h
    sources/instruments/fillinstrument.h
    sources/instruments/sprayinstrument.h
    sources/instruments/magnifierinstrument.h
    sources/instruments/colorpickerinstrument.h
    sources/instruments/curvelineinstrument.h
    sources/instruments/textinstrument.h)

#------- sources --------
set (SOURCES 
    sources/main.cpp
    sources/mainwindow.cpp
    sources/imagearea.cpp
    sources/datasingleton.cpp
    sources/additionaltools.cpp
    sources/effects.cpp
    sources/undocommand.cpp
    sources/widgets/toolbar.cpp
    sources/widgets/colorchooser.cpp
    sources/widgets/palettebar.cpp
    sources/widgets/palettebutton.cpp
    sources/widgets/shortcutedit.cpp
    sources/dialogs/resizedialog.cpp
    sources/dialogs/settingsdialog.cpp
    sources/instruments/abstractinstrument.cpp
    sources/instruments/abstractselection.cpp
    sources/instruments/selectioninstrument.cpp
    sources/instruments/pencilinstrument.cpp
    sources/instruments/lineinstrument.cpp
    sources/instruments/eraserinstrument.cpp
    sources/instruments/rectangleinstrument.cpp
    sources/instruments/ellipseinstrument.cpp
    sources/instruments/fillinstrument.cpp
    sources/instruments/sprayinstrument.cpp
    sources/instruments/magnifierinstrument.cpp
    sources/instruments/colorpickerinstrument.cpp
    sources/instruments/curvelineinstrument.cpp
    sources/instruments/textinstrument.cpp)
 
#------- resources -------
set (RESOURCE_PATH 
    sources)
 
set (RESOURCES 
    ${RESOURCE_PATH}/resources.qrc)
 
#------- languages -------
if(NOT NO_TRANSLATIONS)
    set (TRANSLATIONS
        sources/translations/easypaint_ru_RU.ts
        sources/translations/easypaint_cs_CZ.ts
        sources/translations/easypaint_fr_FR.ts)
endif(NOT NO_TRANSLATIONS)

project (${PROJECT})
 
include_directories (./)
 
find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
qt4_add_resources (QRC_SOURCES ${RESOURCES})
qt4_wrap_cpp (MOC_SOURCES ${HEADERS})
qt4_add_translation( TRANSLATIONS_QM ${TRANSLATIONS} )
 
add_definitions (-Wall)
 
source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})
source_group ("Generated Files" FILES ${MOC_SOURCES})
source_group ("Resource Files" FILES ${QRC_SOURCES})

#-------  build executable from sources ----------
add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES} ${TRANSLATIONS_QM})
 
target_link_libraries (${PROJECT} ${QT_LIBRARIES})

#-------  installing ----------
if(UNIX AND NOT APPLE)
    # installing
    INSTALL(TARGETS easypaint RUNTIME DESTINATION bin)

    # install desktop files
    INSTALL(FILES "sources/media/easypaint.desktop" DESTINATION share/applications)

    # install pixmap
    INSTALL(FILES "sources/media/logo/easypaint_64.png" DESTINATION share/pixmaps)

    INSTALL(FILES ${TRANSLATIONS_QM} DESTINATION share/easypaint/translations)
endif(UNIX AND NOT APPLE)
