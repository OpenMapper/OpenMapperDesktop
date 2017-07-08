CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
PROJECT(OpenMapperDesktop)

SET(CMAKE_CXX_STANDARD 14)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)  

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

INCLUDE_DIRECTORIES(
  ${OPENGL_INCLUDE_DIRS}
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_CURRENT_LIST_DIR}/include/openmapper_desktop
  ${CMAKE_CURRENT_LIST_DIR}/gui
  # ${CMAKE_CURRENT_LIST_DIR}/../OpenMapper/include
)

SET(OMD_LIB_HEADER_DIR
 ${CMAKE_CURRENT_LIST_DIR}/include
)

SET(OMD_LIB_SRC_DIR
 ${CMAKE_CURRENT_LIST_DIR}/src
)

SET(OMD_LIB_GUI_DIR
 ${CMAKE_CURRENT_LIST_DIR}/gui
)

FILE(GLOB_RECURSE OMD_LIB_HEADERS "${OMD_LIB_HEADER_DIR}/*.h")
FILE(GLOB_RECURSE OMD_LIB_SOURCES "${OMD_LIB_SRC_DIR}/*.cc")

SET(OMD_LIB_RESOURCES
  ${OMD_LIB_SOURCES}
  ${OMD_LIB_HEADERS}
)

# QT5_WRAP_CPP(OMD_GUI_HEADERS ${CMAKE_CURRENT_LIST_DIR}/include/openmapper_desktop/window.h)
# QT5_WRAP_UI(OMD_GUI ${OMD_LIB_GUI_DIR}/window.ui)

# compile
add_executable(${PROJECT_NAME}_main
  ${OMD_LIB_RESOURCES}
)

# Build it (link libraries)
target_link_libraries(${PROJECT_NAME}_main
  ${OPENGL_LIBRARIES}
  Qt5::Widgets
  Qt5::Core
  Qt5::OpenGL
    ${OMD_GUI}

  # ${PROJECT_SOURCE_DIR}/OpenMapper/lib/libOpenMapper.a
)

# generate proper GUI program on specified platform.
IF(APPLE)
	SET_TARGET_PROPERTIES(${PROJECT_NAME}_main PROPERTIES
			MACOSX_BUNDLE YES
	)
ELSEIF(UNIX)
	# Nothing special required
ELSE()
	message(SEND_ERROR "You are on an unsupported platform! (Windows not supported yet)")
ENDIF(APPLE)

SET_TARGET_PROPERTIES(${PROJECT_NAME}_main  PROPERTIES
    DEBUG_POSTFIX "_d"
    RUNTIME_OUTPUT_DIRECTORY ../bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ../bin/)
