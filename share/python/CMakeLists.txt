################################################################################################################################################################

# @project        Library/Core
# @file           LibraryCorePy/CMakeLists.txt
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        TBD

################################################################################################################################################################

## Project Properties

SET (PROJECT_NAME "LibraryCorePy")
SET (PROJECT_DESCRIPTION "Python bindings for Library / Core.")
SET (PROJECT_PACKAGE_NAME "LibraryCorePy")
SET (PROJECT_PATH "Library/Core")
SET (PROJECT_LICENSE "MIT License")
SET (PROJECT_VENDOR_ID "com.bremond.lucas")
SET (PROJECT_VENDOR_NAME "Lucas Brémond")
SET (PROJECT_VENDOR_CONTACT "lucas.bremond@gmail.com")
SET (PROJECT_VENDOR_URL "lucas.bremond.info")

################################################################################################################################################################

## Setup

### Compatibility Check

CMAKE_MINIMUM_REQUIRED (VERSION "2.8.12" FATAL_ERROR)

### Paths

SET (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

### Policies

CMAKE_POLICY (SET "CMP0048" NEW)

################################################################################################################################################################

## Project Configuration

PROJECT (${PROJECT_NAME} VERSION ${PROJECT_VERSION_STRING} LANGUAGES "C" "CXX")

################################################################################################################################################################

## Dependencies

### Boost [1.67.0]

SET (Boost_USE_STATIC_LIBS ON)
SET (Boost_USE_MULTITHREADED ON)

UNSET (Boost_INCLUDE_DIR CACHE)
UNSET (Boost_LIBRARY_DIRS CACHE)

FIND_PACKAGE ("Boost" "1.67" COMPONENTS "python27" REQUIRED)

INCLUDE_DIRECTORIES (${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES (${Boost_LIBRARY_DIRS})

### Python

SET (PYTHON_INCLUDE_DIR "/usr/include/python2.7")
SET (PYTHON_LIBRARIES "/usr/lib64/libpython2.7.so")

################################################################################################################################################################

## Target

SET (LIBRARY_NAME ${PROJECT_PACKAGE_NAME})
SET (LIBRARY_TARGET "${LIBRARY_NAME}.so")

FILE (GLOB_RECURSE PROJECT_SRCS "${PROJECT_SOURCE_DIR}/src/*.cxx")

ADD_LIBRARY (${LIBRARY_TARGET} SHARED ${PROJECT_SRCS})

ADD_DEPENDENCIES (${LIBRARY_TARGET} ${SHARED_LIBRARY_TARGET})

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC ${PYTHON_INCLUDE_DIR})
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/src")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/src")

TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} ${PYTHON_LIBRARIES})
TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} ${Boost_LIBRARIES})
TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} ${SHARED_LIBRARY_TARGET})

SET_TARGET_PROPERTIES (${LIBRARY_TARGET} PROPERTIES VERSION ${PROJECT_VERSION_STRING} SOVERSION ${PROJECT_VERSION_MAJOR} OUTPUT_NAME ${PROJECT_PACKAGE_NAME} CLEAN_DIRECT_OUTPUT 1 PREFIX "")

INSTALL (TARGETS ${LIBRARY_TARGET} DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")
INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/__init__.py" DESTINATION "${INSTALL_LIB}/Library" COMPONENT "python")
INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/Core/__init__.py" DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")

################################################################################################################################################################