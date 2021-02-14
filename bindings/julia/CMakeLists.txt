################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/julia/CMakeLists.txt
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

## Project Properties

SET (PROJECT_NAME "OpenSpaceToolkitCoreJl")
SET (PROJECT_DESCRIPTION "Julia bindings for Open Space Toolkit / Core.")
SET (PROJECT_PACKAGE_NAME "OpenSpaceToolkitCoreJl")
SET (PROJECT_GROUP "ostk")
SET (PROJECT_SUBGROUP "core")
SET (PROJECT_PATH "${PROJECT_GROUP}/${PROJECT_SUBGROUP}")
SET (PROJECT_LICENSE "Apache License 2.0")
SET (PROJECT_VENDOR_ID "com.bremond.lucas")
SET (PROJECT_VENDOR_NAME "Lucas Brémond")
SET (PROJECT_VENDOR_CONTACT "lucas.bremond@gmail.com")
SET (PROJECT_VENDOR_URL "lucas.bremond.info")

################################################################################################################################################################

## Project Options

################################################################################################################################################################

## Temporary Julia CMake

# Taken at
# https://github.com/JuliaInterop/libcxxwrap-julia/blob/master/testlib-builder/src/testlib/CMakeLists.txt

# set(CMAKE_MACOSX_RPATH 1)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

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

# Need to find a way to automate that part of data fetching
SET (CMAKE_PREFIX_PATH "/root/.julia/artifacts/2a6fdb6b1893826a3949ec0b4857a8277daa2eb9")

### Julia CxxWrap

FIND_PACKAGE (JlCxx)

GET_TARGET_PROPERTY (JlCxx_location JlCxx::cxxwrap_julia LOCATION)

GET_FILENAME_COMPONENT (JlCxx_location ${JlCxx_location} DIRECTORY)

SET (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib;${JlCxx_location}")

MESSAGE (STATUS "Found JlCxx at ${JlCxx_location}")

### Julia

################################################################################################################################################################

## Target

SET (LIBRARY_NAME ${PROJECT_PACKAGE_NAME})
SET (LIBRARY_TARGET "${LIBRARY_NAME}.so")

FILE (GLOB_RECURSE PROJECT_SRCS "${PROJECT_SOURCE_DIR}/src/*.cxx")

ADD_LIBRARY (${LIBRARY_TARGET} SHARED ${PROJECT_SRCS})

ADD_DEPENDENCIES (${LIBRARY_TARGET} ${SHARED_LIBRARY_TARGET})

TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${CMAKE_SOURCE_DIR}/src")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/include")
TARGET_INCLUDE_DIRECTORIES (${LIBRARY_TARGET} PUBLIC "${PROJECT_SOURCE_DIR}/src")

TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} JlCxx::cxxwrap_julia)
TARGET_LINK_LIBRARIES (${LIBRARY_TARGET} ${SHARED_LIBRARY_TARGET})

SET_TARGET_PROPERTIES ( ${LIBRARY_TARGET} PROPERTIES
                        VERSION ${PROJECT_VERSION_STRING}
                        SOVERSION ${PROJECT_VERSION_MAJOR}
                        OUTPUT_NAME ${PROJECT_PACKAGE_NAME}
                        CLEAN_DIRECT_OUTPUT 1
                        PREFIX ""
                        BUILD_WITH_INSTALL_RPATH TRUE
                        INSTALL_RPATH "$ORIGIN/../lib:$ORIGIN/")

INSTALL (TARGETS ${LIBRARY_TARGET} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib RUNTIME DESTINATION lib)

# Move files to binary build directory
# SET (OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build/build_timestamp")

# ADD_CUSTOM_COMMAND (OUTPUT ${OUTPUT}
#     COMMAND cp "${CMAKE_SOURCE_DIR}/${PROJECT_PACKAGE_NAME}.jl" "${CMAKE_BINARY_DIR}/${PROJECT_PACKAGE_NAME}.jl"
#     COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT})

# INSTALL (TARGETS ${LIBRARY_TARGET} DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")
# INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/${PROJECT_GROUP}/__init__.py" DESTINATION "${INSTALL_LIB}/${PROJECT_GROUP}" COMPONENT "python")
# INSTALL (FILES "${PROJECT_SOURCE_DIR}/tools/python/${PROJECT_PATH}/__init__.py" DESTINATION "${INSTALL_LIB}/${PROJECT_PATH}" COMPONENT "python")

################################################################################################################################################################

# FIND_PROGRAM (PYTHON "python3")

# IF (NOT PYTHON)

#     MESSAGE (FATAL_ERROR "Unable to find [python3] program.")

# ENDIF (NOT PYTHON)

# SET (PACKAGE_NAME ${PROJECT_PACKAGE_NAME})
# SET (PACKAGE_TARGET "${PACKAGE_NAME}-python-package")

SET (MODULE_JL_IN "${CMAKE_CURRENT_SOURCE_DIR}/tools/julia/ostk.jl.in")
SET (MODULE_JL "${CMAKE_CURRENT_BINARY_DIR}/ostk.jl")
SET (OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/build/timestamp")

CONFIGURE_FILE (${MODULE_JL_IN} ${MODULE_JL})

ADD_CUSTOM_COMMAND (OUTPUT ${OUTPUT}
                    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tools/julia/ostk.jl" "${CMAKE_CURRENT_BINARY_DIR}/ostk/src/ostk.jl"
                    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tools/julia/Project.toml" "${CMAKE_CURRENT_BINARY_DIR}/ostk/Project.toml"
                    COMMAND cp "${CMAKE_CURRENT_SOURCE_DIR}/tools/julia/Manifest.toml" "${CMAKE_CURRENT_BINARY_DIR}/ostk/Manifest.toml"
                    COMMAND cp "${CMAKE_SOURCE_DIR}/lib/${SHARED_LIBRARY_TARGET}" "${CMAKE_CURRENT_BINARY_DIR}/core/libopen-space-toolkit-core.so.0"
                    COMMAND cp "${CMAKE_SOURCE_DIR}/lib/${LIBRARY_TARGET}" "${CMAKE_CURRENT_BINARY_DIR}/lib/${LIBRARY_TARGET}"
                    COMMAND ${CMAKE_COMMAND} -E touch ${OUTPUT}
                    DEPENDS ${DEPS})

# ADD_CUSTOM_TARGET (${PACKAGE_TARGET} ALL DEPENDS ${OUTPUT})

# ADD_DEPENDENCIES (${PACKAGE_TARGET} ${LIBRARY_TARGET})

# INSTALL (CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install)")

################################################################################################################################################################

# ADD_CUSTOM_TARGET ("publish" COMMAND python3 -m twine upload "${CMAKE_CURRENT_BINARY_DIR}/dist/*" DEPENDS ${OUTPUT})

################################################################################################################################################################
