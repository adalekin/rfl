# <Copyright Holder>. Copyright (C) <Copyright Year(s)>. <License>.

#
# Project Properties
#
CMAKE_MINIMUM_REQUIRED (VERSION 2.6.2)
PROJECT(rfl)


#
# Project Options
#
OPTION( BUILD_SHARED_LIBS "Set to OFF to build static libraries" OFF )
OPTION( INSTALL_DOC "Set to OFF to skip build/install Documentation" ON )

#
# Debugging Options
#
SET (CMAKE_VERBOSE_MAKEFILE 0) # Use 1 for debugging, 0 for release

#
# Project Output Paths
#
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

#
# Project Search Paths
#
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/tools")
LIST (APPEND CMAKE_PREFIX_PATH "${MAINFOLDER}/thirdparty")
SET (CMAKE_MODULE_PATH "${MAINFOLDER}/tools/share/cmake")
INCLUDE_DIRECTORIES("${MAINFOLDER}/include")

#
# Locate Project Prerequisites 
#

#
# Special hack for switching to 32-bit mode on Snow
# Leopard if Qt has been compiled for 32-bit, only.
#
IF (APPLE)
   IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
      EXECUTE_PROCESS(
		COMMAND file "${QT_QTCORE_LIBRARY}"
		COMMAND grep "x86_64" -c
		OUTPUT_VARIABLE QT4_SUPPORTS_X86_64_OUTPUT
      )
      IF (NOT QT4_SUPPORTS_X86_64_OUTPUT MATCHES "0")
          SET(QT4_SUPPORTS_X86_64 1)
      ELSE (NOT QT4_SUPPORTS_X86_64_OUTPUT MATCHES "0")
          SET(QT4_SUPPORTS_X86_64 0)
      ENDIF (NOT QT4_SUPPORTS_X86_64_OUTPUT MATCHES "0")

      IF (QT4_SUPPORTS_X86_64)
          SET(CMAKE_OSX_ARCHITECTURES x86_64)
      ELSE (QT4_SUPPORTS_X86_64)
          SET(CMAKE_OSX_ARCHITECTURES i386)
      ENDIF (QT4_SUPPORTS_X86_64)
   ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ENDIF (APPLE)


#
# Add Build Targets
#
SET( BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS}" CACHE BOOL
   "Set to OFF to build static libraries" FORCE )
SET( CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
   "Where to install ${PROJECT_NAME}" FORCE )
SET( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
   "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE )
SET( CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" CACHE PATH
   "Path to custom CMake Modules" FORCE )
SET( INSTALL_DOC "${INSTALL_DOC}" CACHE BOOL
   "Set to OFF to skip build/install Documentation" FORCE )

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(test)

#
# Add Install Targets
#
IF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")
    INSTALL(DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}" DESTINATION "include")
ENDIF (EXISTS "${MAINFOLDER}/include/${PROJECT_NAME}" AND IS_DIRECTORY "${MAINFOLDER}/include/${PROJECT_NAME}")

#
# Add Documentation Targets
#
INCLUDE (DocumentationTargets)

