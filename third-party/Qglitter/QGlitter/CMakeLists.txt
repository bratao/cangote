cmake_minimum_required(VERSION 2.8.11)
project(QGLITTER)

set(QGLITTER_VERSION "0.1.0")

if(NOT QGLITTER_BUILD_SHARED AND NOT QGLITTER_BUILD_STATIC)
	set(QGLITTER_BUILD_SHARED ON)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenSSL REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Xml)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})

include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${QGLITTER_BINARY_DIR})

if(UNIX)
	add_definitions(-fvisibility=hidden)
endif()

if(APPLE)
	set(PLATFORM_SOURCES
		Platform/Mac/Mac.cpp)

	set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

if(WIN32)
	set(PLATFORM_SOURCES
		Platform/Win32/Win32.cpp)

	add_definitions(-DQGLITTER_EXPORT_SYMBOLS)
endif()

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    SET(LINUX ON CACHE BOOL "Linux system" FORCE)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

if(LINUX)
	set(PLATFORM_SOURCES
		Platform/Linux/Linux.cpp)
endif()




set(SOURCES
	QGlitterAppcast.cpp
	QGlitterAppcastItem.cpp
	QGlitterAutomaticUpdateAlert.cpp
	QGlitterDefaultVersionComparator.cpp
	QGlitterDownloader.cpp
	QGlitterUpdateAlert.cpp
	QGlitterUpdateCheckStatus.cpp
	QGlitterUpdater.cpp
	QGlitterUpdateStatus.cpp
	Crypto/OpenSSLCrypto.cpp
	${PLATFORM_SOURCES})

set(HEADERS
	QGlitterAutomaticUpdateAlert.h
	QGlitterDownloader.h
	QGlitterUpdateAlert.h
	QGlitterUpdateCheckStatus.h
	QGlitterUpdater.h
	QGlitterUpdateStatus.h)

set(PUBLIC_HEADERS
	QGlitter
	QGlitterAppcast.h
	QGlitterAppcastItem.h
	QGlitterConfig.h
	QGlitterObject.h
	QGlitterUpdater.h)

set(UI_FILES
	Designer/QGlitterAutomaticUpdateAlert.ui
	Designer/QGlitterUpdateAlert.ui
	Designer/QGlitterUpdateStatus.ui)

qt5_wrap_ui(UI_SOURCES ${UI_FILES})

install(FILES ${PUBLIC_HEADERS} DESTINATION include/QGlitter)

if(QGLITTER_BUILD_SHARED)
	add_library(qglitter SHARED ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES})
	target_link_libraries(qglitter Qt5::Widgets Qt5::Core Qt5::Network ${OPENSSL_LIBRARIES} ${PLATFORM_LIBS})
	set_target_properties(qglitter PROPERTIES VERSION ${QGLITTER_VERSION} SOVERSION ${QGLITTER_VERSION} INSTALL_NAME_DIR "${CMAKE_INSTALL_PREFIX}/lib")

	if(WIN32)
		install(TARGETS qglitter LIBRARY DESTINATION bin ARCHIVE DESTINATION bin)
	else()
		install(TARGETS qglitter LIBRARY DESTINATION lib)
	endif()
endif()

if(QGLITTER_BUILD_STATIC)
	add_library(qglitter_static STATIC ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES})
	target_link_libraries(qglitter_static Qt5::Widgets Qt5::Core Qt5::Network ${OPENSSL_LIBRARIES} ${PLATFORM_LIBS})
	set_target_properties(qglitter_static PROPERTIES OUTPUT_NAME "qglitter")

	install(TARGETS qglitter_static ARCHIVE DESTINATION lib)
endif()
