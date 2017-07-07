CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
project(OpenMapperDesktop)

SET(CMAKE_CXX_STANDARD 14)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

INCLUDE_DIRECTORIES(
  ${OPENGL_INCLUDE_DIRS}
  # ${CMAKE_CURRENT_LIST_DIR}/../OpenMapper/include
)

SET(OMD_LIB_SOURCES
 main.cc
 window.cc
 myglwidget.cc
)

SET(OMD_LIB_HEADERS
 window.h
 myglwidget.h
)

SET(OMD_LIB_RESOURCES
  ${OMD_LIB_SOURCES}
  ${OMD_LIB_HEADERS}
)

QT5_WRAP_UI(UIS window.ui)

# compile
add_executable(${PROJECT_NAME}_main
  ${OMD_LIB_RESOURCES}
  ${UIS}
)

# Build it (link libraries)
target_link_libraries(${PROJECT_NAME}_main
  ${OPENGL_LIBRARIES}
  Qt5::Widgets
  Qt5::Core
  Qt5::OpenGL
  # ${PROJECT_SOURCE_DIR}/OpenMapper/lib/libOpenMapper.a
)

# generate proper GUI program on specified platform.
if(APPLE)
	SET_TARGET_PROPERTIES(${PROJECT_NAME}_main PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Windows not supported yet)")
endif(APPLE)

SET_TARGET_PROPERTIES(${PROJECT_NAME}_main  PROPERTIES
    DEBUG_POSTFIX "_d"
    RUNTIME_OUTPUT_DIRECTORY ../bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ../bin/)
