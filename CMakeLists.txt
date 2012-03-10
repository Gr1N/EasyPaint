cmake_minimum_required (VERSION 2.6)
 
# set project's name
set (PROJECT easypaint)

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

# add version define
set(EASYPAINT_VERSION "0.0.1")

# ------ install prefix --------------------------
set(CMAKE_INSTALL_PREFIX "/usr")
add_definitions( -DPREFIX="${CMAKE_INSTALL_PREFIX}")
message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})
 
#------- headers --------
set (HEADERS 
    ./sources/additionaltools.h
    ./sources/colorchooser.h
    ./sources/datasingleton.h
    ./sources/easypaintenums.h
    ./sources/effects.h
    ./sources/imagearea.h
    ./sources/mainwindow.h
    ./sources/paintinstruments.h
    ./sources/resizedialog.h
    ./sources/toolbar.h)

#------- sources --------
set (SOURCES 
    ./sources/additionaltools.cpp
    ./sources/colorchooser.cpp
    ./sources/datasingleton.cpp
    ./sources/effects.cpp
    ./sources/imagearea.cpp
    ./sources/main.cpp
    ./sources/mainwindow.cpp
    ./sources/paintinstruments.cpp
    ./sources/resizedialog.cpp
    ./sources/toolbar.cpp)
 
#------- languages -------
#~ set (LANGUAGES
    #~ rus
    #~ eng)

#------- resources -------
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

#-------  build executable from sources ----------
add_executable (${PROJECT} ${HEADERS} ${SOURCES} ${MOC_SOURCES} ${QRC_SOURCES})
 
target_link_libraries (${PROJECT} ${QT_LIBRARIES})

#-------  make src packae and installing ----------
if(UNIX AND NOT APPLE)
    # make src.tar.gz
    ADD_CUSTOM_TARGET (dist @echo create source package )
    set(EASYPAINT_DIST "easypaint-${EASYPAINT_VERSION}")
    add_custom_command(COMMAND cp 
        ARGS -R ${CMAKE_CURRENT_SOURCE_DIR} "/tmp/${EASYPAINT_DIST}" 
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        TARGET  dist
    )

    ADD_CUSTOM_COMMAND(COMMAND tar 
        ARGS cvfz ${CMAKE_CURRENT_BINARY_DIR}/${EASYPAINT_DIST}.tar.gz --exclude=*~ --exclude-vcs --exclude=localize/*qm --exclude=*.kdev4 --exclude=build --exclude=create-src.sh --exclude=win32 -C "/tmp" "${EASYPAINT_DIST}"  
        WORKING_DIRECTORY "/tmp"
        TARGET  dist
    )

    add_custom_command(COMMAND rm 
        ARGS -rf "/tmp/${EASYPAINT_DIST}"
        WORKING_DIRECTORY "/tmp"
        TARGET  dist
    )

    # installing
    INSTALL(TARGETS easypaint RUNTIME DESTINATION bin)

    # install desktop files
    #~ INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/easypaint.desktop" DESTINATION share/applications)

    # install pixmap
    #~ INSTALL(FILES "${CMAKE_CURRENT_SOURCE_DIR}/img/easypaint.png" DESTINATION share/pixmaps)

    #~ INSTALL(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/localize/" DESTINATION share/screengrab/localize FILES_MATCHING PATTERN "*.qm")
endif(UNIX AND NOT APPLE)
