cmake_minimum_required(VERSION 2.8)
project(qt_updater)

if(APPLE)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

	set(CMAKE_OSX_ARCHITECTURES x86_64)
	set(CMAKE_OSX_DEPLOYMENT_TARGET 10.7)

	if(CMAKE_OSX_SYSROOT STREQUAL "")
		execute_process(COMMAND xcodebuild -version -sdk macosx Path OUTPUT_VARIABLE CMAKE_OSX_SYSROOT OUTPUT_STRIP_TRAILING_WHITESPACE)
	endif()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(QGlitter)
add_subdirectory(QGlitterTool)
add_subdirectory(TestApp)
