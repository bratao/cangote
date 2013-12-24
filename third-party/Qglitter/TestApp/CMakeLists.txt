cmake_minimum_required(VERSION 2.8)
project(QGLITTER_TESTAPP)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Network)
find_package(Qt5Xml)


# Add the include directories for the Qt 5 Widgets module to
# the compile lines.
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})


add_definitions(${QT_DEFINITIONS})

set(SOURCES
	App.cpp)

set(HEADERS
	App.h)

qt5_add_resources(RCC_RESOURCES Resources.qrc)
qt5_wrap_cpp(HEADERS_MOC ${HEADERS})

add_executable(TestApp ${SOURCES} ${RCC_RESOURCES} ${HEADERS_MOC})
target_link_libraries(TestApp qglitter ${QT_LIBRARIES} ${PLATFORM_LIBS})
