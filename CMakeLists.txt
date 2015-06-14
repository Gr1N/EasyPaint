cmake_minimum_required (VERSION 2.8.11)

# set project's name
set (PROJECT easypaint)
project (${PROJECT})

if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE Release)
endif ()

# add version define
set (MAJOR_VERSION 0)
set (MINOR_VERSION 1)
set (PATCH_VERSION 1)
set (EASYPAINT_VERSION_STRING ${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION})
add_definitions (-DEASYPAINT_VERSION="${EASYPAINT_VERSION_STRING}")

# C++11 support
include (CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG ("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG ("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if (COMPILER_SUPPORTS_CXX11)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else ()
    message (FATAL "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. C++11 support is required")
endif ()

add_definitions (-Wall)

include (GNUInstallDirs)

set (CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_AUTOMOC ON)

message(STATUS "System: " ${CMAKE_HOST_SYSTEM_NAME} " " ${CMAKE_HOST_SYSTEM_VERSION})
message(STATUS "Processor: " ${CMAKE_HOST_SYSTEM_PROCESSOR})

find_package (Qt5 REQUIRED COMPONENTS Widgets PrintSupport)

add_subdirectory (sources)

# building tarball with CPack
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR ${MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${PATCH_VERSION})
set(CPACK_GENERATOR TBZ2)
set(CPACK_SOURCE_GENERATOR TBZ2)
set(CPACK_SOURCE_IGNORE_FILES /build/;.gitignore;.*~;.git;.kdev4;temp)
include(CPack)
