################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/CMakeLists.txt
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

## Project Properties

SET (PROJECT_NAME "OpenSpaceToolkitCorePy")
SET (PROJECT_DESCRIPTION "Python bindings for Open Space Toolkit / Core.")
SET (PROJECT_PACKAGE_NAME "OpenSpaceToolkitCorePy")
SET (PROJECT_GROUP "ostk")
SET (PROJECT_SUBGROUP "core")
SET (PROJECT_PATH "${PROJECT_GROUP}/${PROJECT_SUBGROUP}")
SET (PROJECT_LICENSE "Apache License 2.0")
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

# SET (PYBIND11_FINDPYTHON ON)
# find_package(Python3 COMPONENTS Interpreter Development)

# SET (PYBIND11_PYTHON_VERSION 3.8 CACHE STRING "")

FIND_PACKAGE(pybind11 REQUIRED)

#unset(PYTHONINTERP_FOUND CACHE)
#unset(PYTHON_EXECUTABLE CACHE)
#unset(PYTHON_VERSION_STRING CACHE)
#unset(PYTHON_VERSION_MAJOR CACHE)
#unset(PYTHON_VERSION_MINOR CACHE)
#unset(PYTHON_VERSION_PATCH CACHE)

#unset(PYBIND11_INCLUDE_DIR CACHE)
#unset(PYTHON_INCLUDE_DIRS CACHE)
#unset(PYTHON_LIBRARIES CACHE)
#unset(PYTHON_MODULE_PREFIX CACHE)
#unset(PYTHON_MODULE_EXTENSION CACHE)
#unset(PYTHON_LIBRARY CACHE)

#SET (PYBIND11_PYTHON_VERSION 3.8)
#find_package(PythonInterp "/usr/local/bin/python3.8")
#find_package(PythonLibs "/usr/local/lib/libpython3.8.so")
#SET (PYTHON_LIBRARY "/usr/local/lib/libpython3.8.so")

#MESSAGE (WARNING ${PythonInterp})
#MESSAGE (WARNING ${PythonLibs})

################################################################################################################################################################

## Target

SET (LIBRARY_NAME ${PROJECT_PACKAGE_NAME})
SET (LIBRARY_TARGET "${LIBRARY_NAME}")

FILE (GLOB_RECURSE PROJECT_SRCS "${PROJECT_SOURCE_DIR}/src/*.cxx")

PYBIND11_ADD_MODULE (${LIBRARY_TARGET} ${PROJECT_SRCS})

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/src")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/src")

TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} PRIVATE ${SHARED_LIBRARY_TARGET})

SET_TARGET_PROPERTIES (${LIBRARY_TARGET} PROPERTIES
                        VERSION ${PROJECT_VERSION_STRING}
                        SOVERSION ${PROJECT_VERSION_MAJOR}
                        OUTPUT_NAME ${PROJECT_PACKAGE_NAME}
                        CLEAN_DIRECT_OUTPUT 1
                        PREFIX ""
                        BUILD_WITH_INSTALL_RPATH TRUE
                        INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")

INSTALL (TARGETS ${LIBRARY_TARGET} DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")
INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/${PROJECT_GROUP}/__init__.py" DESTINATION "${INSTALL_LIB}/${PROJECT_GROUP}" COMPONENT "python")
INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/${PROJECT_PATH}/__init__.py" DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")

###############################################################################################################################################################

FIND_PROGRAM (PYTHON "python3")

IF (NOT PYTHON)

    MESSAGE (FATAL_ERROR "Unable to find [python3] program.")

ENDIF (NOT PYTHON)

SET (PACKAGE_NAME ${PROJECT_PACKAGE_NAME})
SET (PACKAGE_TARGET "${PACKAGE_NAME}-python-package")

SET (SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/tools/python/setup.py.in")
SET (SETUP_PY "${CMAKE_CURRENT_BINARY_DIR}/setup.py")
SET (DEPS "${CMAKE_CURRENT_SOURCE_DIR}/tools/python/${PROJECT_PATH}/__init__.py")
SET (OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

CONFIGURE_FILE (${SETUP_PY_IN} ${SETUP_PY})

ADD_CUSTOM_COMMAND (OUTPUT ${OUTPUT}
                    COMMAND mkdir -p "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_PATH}"
                    COMMAND cp -r "${CMAKE_CURRENT_SOURCE_DIR}/test" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_PATH}/test"
                    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tools/python/${PROJECT_GROUP}/__init__.py" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_GROUP}/__init__.py"
                    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tools/python/${PROJECT_PATH}/__init__.py" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_PATH}/__init__.py"
                    COMMAND cp "${CMAKE_SOURCE_DIR}/lib/${SHARED_LIBRARY_TARGET}" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_PATH}/libopen-space-toolkit-core.so.0"
                    COMMAND cp "${CMAKE_SOURCE_DIR}/lib/${LIBRARY_TARGET}.*.so" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_PATH}/"
                    COMMAND ${PYTHON} ${SETUP_PY} bdist_wheel
                    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                    DEPENDS ${DEPS})

ADD_CUSTOM_TARGET (${PACKAGE_TARGET} ALL DEPENDS ${OUTPUT})

ADD_DEPENDENCIES (${PACKAGE_TARGET} ${LIBRARY_TARGET})

INSTALL (CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")

################################################################################################################################################################
