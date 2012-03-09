cmake_minimum_required (VERSION 2.6)
 
set (PROJECT 
    easypaint)
 
set (HEADERS 
    ./sources/additionaltools.h
    ./sources/colorchooser.h
    ./sources/datasingleton.h
    ./sources/easypaintenums.h
    ./sources/effects.h
    ./sources/imagearea.h
    ./sources/mainwindow.h
    ./sources/paintinstruments.h
    ./sources/resizeimagedialog.h
    ./sources/toolbar.h)
 
set (SOURCES 
    ./sources/additionaltools.cpp
    ./sources/colorchooser.cpp
    ./sources/datasingleton.cpp
    ./sources/effects.cpp
    ./sources/imagearea.cpp
    ./sources/main.cpp
    ./sources/mainwindow.cpp
    ./sources/paintinstruments.cpp
    ./sources/resizeimagedialog.cpp
    ./sources/toolbar.cpp)
 
#~ set (LANGUAGES
    #~ rus
    #~ eng)
 
set (RESOURCE_PATH 
    ./sources)
 
set (RESOURCES 
    ${RESOURCE_PATH}/media.qrc)
 
#~ set (TRANSLATIONS_PATH 
    #~ ../resources/translations)
 
project (${PROJECT})
 
include_directories (./)
 
find_package (Qt4 REQUIRED)
include (${QT_USE_FILE})
qt4_add_resources (QRC_SOURCES ${RESOURCES})
qt4_wrap_cpp (MOC_SOURCES ${HEADERS})
#~ foreach (LANGUAGE ${LANGUAGES})
    #~ set (TS ${TRANSLATIONS_PATH}/${LANGUAGE}.ts)
    #~ set (QM ${TRANSLATIONS_PATH}/${LANGUAGE}.qm)
    #~ set (TRANSLATIONS ${TRANSLATIONS} ${TS})
    #~ set (TRANSLATIONS_BINARY ${TRANSLATIONS_BINARY} ${QM})
    #~ add_custom_command (
        #~ OUTPUT ${QM}
        #~ COMMAND ${QT_LRELEASE_EXECUTABLE} ${TS}
        #~ MAIN_DEPENDENCY ${TS})
#~ endforeach()
#~ add_custom_target (
    #~ translations 
    #~ COMMAND ${QT_LUPDATE_EXECUTABLE} ${HEADERS} ${SOURCES} -ts ${TRANSLATIONS})
#~ add_custom_command (
    #~ TARGET translations
    #~ COMMAND ${QT_LRELEASE_EXECUTABLE} ${TRANSLATIONS})
 
add_definitions (-Wall)
 
source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})
source_group ("Generated Files" FILES ${MOC_SOURCES})
source_group ("Resource Files" FILES ${QRC_SOURCES})
 
add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
 
target_link_libraries (${PROJECT} ${QT_LIBRARIES})
