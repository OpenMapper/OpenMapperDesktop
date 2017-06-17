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

include_directories( ${OPENGL_INCLUDE_DIRS}  )

SET(OMD_LIB_SOURCES
 main.cc
 window.cc
 myglwidget.cc
)

SET(OMD_LIB_HEADERS
 window.h
 myglwidget.h
)

SET(OMD_LIB_RESOURCES ${OMD_LIB_SOURCES} ${OMD_LIB_HEADERS} )

QT5_WRAP_UI(UIS window.ui)

# compile
if(WIN32) # Check if we are on Windows
  # if you using Windows ™ Operating System.
  add_executable( ${PROJECT_NAME}_main WIN32 ${OMD_LIB_RESOURCES} ${UIS} )
else()
  add_executable( ${PROJECT_NAME}_main ${OMD_LIB_RESOURCES} ${UIS})
endif(WIN32)

# build it (link libraries)
target_link_libraries( ${PROJECT_NAME}_main ${OPENGL_LIBRARIES}  Qt5::Widgets Qt5::Core Qt5::OpenGL)

# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		SET_TARGET_PROPERTIES(${PROJECT_NAME}_main PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME}_main PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)

SET_TARGET_PROPERTIES(${PROJECT_NAME}_main  PROPERTIES
    DEBUG_POSTFIX "_d"
    RUNTIME_OUTPUT_DIRECTORY ../bin/
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ../bin/
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ../bin/)
