# Install script for directory: E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/QGLITTER")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QGlitter" TYPE FILE FILES
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitter"
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitterAppcast.h"
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitterAppcastItem.h"
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitterConfig.h"
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitterObject.h"
    "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter/QGlitterUpdater.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter-build/lib/libqglitter.dll.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libqglitter.dll.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libqglitter.dll.a")
    IF(CMAKE_INSTALL_DO_STRIP)
      EXECUTE_PROCESS(COMMAND "C:/sbuild/mingw/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libqglitter.dll.a")
    ENDIF(CMAKE_INSTALL_DO_STRIP)
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter-build/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "E:/Projetos/Meus Projetos/Cangote/Software/Qt Cangote/cangote/third-party/Qglitter/QGlitter-build/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
