cmake_minimum_required(VERSION 3.2)
project(Battle_Tanks)


set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/Build)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

INCLUDE(FindX11)
INCLUDE(FindPNG)
INCLUDE(CPack)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set (EZWIN_LIB_DIR
    EzWindows/include)

set(SOURCE_FILES
    "Program Files/BitmapDeclaration.h"
    "Program Files/BmpMove.h"
    "Program Files/ClearScreen.h"
    "Program Files/Fire.h"
    "Program Files/Functions.h"
    "Program Files/GamePlayFunctions.h"
    "Program Files/GamePlayScreen.h"
  #  "Program Files/HighScoreGenerator.cpp"
    "Program Files/MouseClickEvent.h"
    "Program Files/PocketTanks.cpp"
    "Program Files/ScoreManagement.h"
    "Program Files/Screens.h"
    "Program Files/VariablesDeclaration.h"
    "Program Files/WeaponShop.h")

set(EZWIN_SOURCE_FILES
    EzWindows/lib/Alert.cc
    EzWindows/lib/bitmap.cc
    EzWindows/lib/ButtonGraphic.cc
    EzWindows/lib/circle.cc
 #   EzWindows/lib/dstring.cc
    EzWindows/lib/ellipse.cc
    EzWindows/lib/EllipseGraphic.cc
    EzWindows/lib/End.cc
    EzWindows/lib/Graphic.cc
    EzWindows/lib/GraphicManager.cc
    EzWindows/lib/GraphicPosition.cc
    EzWindows/lib/label.cc
    EzWindows/lib/lellipse.cc
    EzWindows/lib/Makefile.CC
    EzWindows/lib/MessageGraphic.cc
    EzWindows/lib/Miscellaneous.cc
   # EzWindows/lib/numextra.cc
   # EzWindows/lib/PolygonGraphic.cc
    EzWindows/lib/position.cc
    EzWindows/lib/randint.cc
    EzWindows/lib/random.cc
    EzWindows/lib/ray.cc
    EzWindows/lib/rect.cc
   # EzWindows/lib/RectangleGraphic.cc
    EzWindows/lib/shape.cc
    EzWindows/lib/square.cc
    EzWindows/lib/triangle.cc
    EzWindows/lib/uniform.cc
   # EzWindows/lib/uniform.cpp
    EzWindows/lib/WindowManager.cc
    EzWindows/lib/wobject.cc
    EzWindows/lib/X11BitmapGraphic.cc
   # EzWindows/lib/XpmGraphic.cc
   )

set(EZWIN_LIB_FILES
    EzWindows/include/Alert.h
    EzWindows/include/bitmap.h
    EzWindows/include/ButtonGraphic.h
    EzWindows/include/circle.h
    EzWindows/include/Constants.h
    EzWindows/include/cstring.h
 #   EzWindows/include/dstring.h
    EzWindows/include/ellipse.h
    EzWindows/include/EllipseGraphic.h
    EzWindows/include/EventNames.h
    EzWindows/include/ezwin.h
    EzWindows/include/Graphic.h
    EzWindows/include/GraphicManager.h
    EzWindows/include/GraphicPosition.h
    EzWindows/include/label.h
    EzWindows/include/lellipse.h
    EzWindows/include/MessageGraphic.h
    EzWindows/include/Miscellaneous.h
    EzWindows/include/position.h
    EzWindows/include/randint.h
    EzWindows/include/random.h
    EzWindows/include/ray.h
    EzWindows/include/rect.h
    EzWindows/include/shape.h
    EzWindows/include/SimpleWindow.h
    EzWindows/include/square.h
    EzWindows/include/triangle.h
    EzWindows/include/uniform.h
    EzWindows/include/UsingCC.h
    EzWindows/include/UsingG++.h
    EzWindows/include/WindowManager.h
    EzWindows/include/wobject.h
    EzWindows/include/X11BitmapGraphic.h
   # EzWindows/include/xpm.h
   )

include_directories(${X11_INCLUDE_DIR})
include_directories(${EZWIN_LIB_DIR})
include_directories(${XPM_INCLUDE_DIR})
include_directories(${PNG_INCLUDE_DIRS})

MESSAGE(STATUS "Found XPM: ${XPM_LIBRARY} \n")
MESSAGE(STATUS "Found XPM: ${XPM_INCLUDE_DIR} \n")
MESSAGE(STATUS "Found XPM: ${PNG_LIBRARIES} \n")
MESSAGE(STATUS "Found XPM: ${XPM_INCLUDE_DIRS} \n")


set(SOURCES ${EZWIN_SOURCE_FILES} ${EZWIN_LIB_FILES})
add_library(EzWindows SHARED ${SOURCES})

target_link_libraries(EzWindows PUBLIC ${X11_LIBRARIES} ${XPM_LIBRARY} ${PNG_LIBRARIES})

#include_directories ("${PROJECT_SOURCE_DIR}/EzWindows")
#add_subdirectory (EzWindows)

# add the executable
add_executable (Battle_Tanks ${SOURCE_FILES})
target_link_libraries (Battle_Tanks EzWindows )
#file(COPY ${PROJECT_SOURCE_DIR}/Program\ Files/Images DESTINATION ${PROJECT_SOURCE_DIR}/Images)


#[[
# This tells CMake to build a library with other.c and file.c and name it mylib
# (biicode automatically creates a library for each block)
add_library(mylib other.c file.c)

# Sends the -std=c99 flag to the gcc compiler
add_definitions(-std=c99)

# This tells CMake to build an executable with fib.c and name it fibonacci
# (biicode automatically adds detected targets in your source code)
add_executable(fibonacci fib.c)

# Links mylib to the fibonacci executable
# (biicode automatically links block's library to each executable)
target_link_libraries(fibonacci PUBLIC mylib)

add_executable(Battle_Tanks ${SOURCE_FILES})]]
INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "a Graphical game similar to Pocket Tanks.")
#SET(CPACK_PACKAGE_VENDOR "Me, myself, and I")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
#SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_GENERATOR "DEB")

SET(CPACK_PACKAGE_EXECUTABLES "Battle_Tanks" "Battle Tanks")

