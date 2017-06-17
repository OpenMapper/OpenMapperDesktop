CMAKE_MINIMUM_REQUIRED(VERSION 3.1 FATAL_ERROR)
project(OpenMapperDesktop)

set(CMAKE_CXX_STANDARD 14)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

find_package(OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  )

set ( SOURCES
 main.cpp
 window.cpp
 myglwidget.cpp
)

set ( MOC_HEADERS
 window.h
 myglwidget.h
)

QT5_WRAP_UI(UIS window.ui)

# compile
if(WIN32) # Check if we are on Windows
  # if you using Windows ™ Operating System.
  add_executable( ${PROJECT_NAME} WIN32 ${SOURCES} ${MOC_SRCS} ${UIS} )
else()
  add_executable( ${PROJECT_NAME} ${SOURCES} ${MOC_SRCS} ${UIS} )
endif(WIN32)

# build it (link libraries)
target_link_libraries( ${PROJECT_NAME} ${OPENGL_LIBRARIES}  Qt5::Widgets Qt5::Core Qt5::OpenGL)

# generate proper GUI program on specified platform
if(WIN32) # Check if we are on Windows
	if(MSVC) # Check if we are using the Visual Studio compiler
		set_target_properties(${PROJECT_NAME} PROPERTIES
			WIN32_EXECUTABLE YES
			LINK_FLAGS "/ENTRY:mainCRTStartup"
		)
	elseif(CMAKE_COMPILER_IS_GNUCXX)
			# SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
	else()
		message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
	endif(MSVC)
elseif(APPLE)
	set_target_properties(${PROJECT_NAME} PROPERTIES
			MACOSX_BUNDLE YES
	)
elseif(UNIX)
	# Nothing special required
else()
	message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif(WIN32)
