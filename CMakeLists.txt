cmake_minimum_required (VERSION 2.6)
 
# set project's name
set (PROJECT easypaint)

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

# add version define
set(EASYPAINT_VERSION "0.0.1")

#------- headers --------
set (HEADERS 
    sources/additionaltools.h
    sources/colorchooser.h
    sources/datasingleton.h
    sources/easypaintenums.h
    sources/effects.h
    sources/imagearea.h
    sources/mainwindow.h
    sources/paintinstruments.h
    sources/resizedialog.h
    sources/toolbar.h
    sources/settingsdialog.h)

#------- sources --------
set (SOURCES 
    sources/additionaltools.cpp
    sources/colorchooser.cpp
    sources/datasingleton.cpp
    sources/effects.cpp
    sources/imagearea.cpp
    sources/main.cpp
    sources/mainwindow.cpp
    sources/paintinstruments.cpp
    sources/resizedialog.cpp
    sources/toolbar.cpp
    sources/settingsdialog.cpp)
 
#------- resources -------
set (RESOURCE_PATH 
    sources)
 
set (RESOURCES 
    ${RESOURCE_PATH}/resources.qrc)
 
#------- languages -------
set (TRANSLATIONS
    sources/translations/easypaint_ru_RU.ts
    sources/translations/easypaint_cs_CZ.ts)

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
    INSTALL(FILES "sources/media/EasyPaint.desktop" DESTINATION share/applications)

    # install pixmap
    #~ INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/img/easypaint.png" DESTINATION share/pixmaps)

    INSTALL(FILES ${TRANSLATIONS_QM} DESTINATION share/easypaint/translations)
endif(UNIX AND NOT APPLE)
