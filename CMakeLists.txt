#----------------------------------------------------------------------------
# Setup the project
cmake_minimum_required(VERSION 3.16...3.24)
project(SimCalModule_GS_HCAL)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Find ROOT
#
find_package(ROOT REQUIRED)
message(STATUS "Found ROOT: ${ROOT_DIR}.")
add_definitions(-DWITHROOT)
include_directories(${ROOT_INCLUDE_DIRS})
#----------------------------------------------------------------------------
# Setting pythia8 on LCG
find_package(PkgConfig REQUIRED)

# pythia8-config を使って include と lib を取得
execute_process(COMMAND $ENV{PYTHIA8}/bin/pythia8-config --cxxflags OUTPUT_VARIABLE PYTHIA8_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND $ENV{PYTHIA8}/bin/pythia8-config --libs OUTPUT_VARIABLE PYTHIA8_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

# 変数の設定
set(PYTHIA8_INCLUDE_DIR "$ENV{PYTHIA8}/include")
set(PYTHIA8_LIBRARY "$ENV{PYTHIA8}/lib/libpythia8.so")

include_directories(${PYTHIA8_INCLUDE_DIR})
link_directories("$ENV{PYTHIA8}/lib")

message(STATUS "PYTHIA8 Include Dir: ${PYTHIA8_INCLUDE_DIR}")
message(STATUS "PYTHIA8 Libraries: ${PYTHIA8_LIBRARY}")
#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
add_executable(SimCalModule_GS_HCAL SimCalModule.cc ${sources} ${headers})
target_link_libraries(SimCalModule_GS_HCAL ${Geant4_LIBRARIES} ${ROOT_LIBRARIES} ${PYTHIA8_LIBRARY})

#----------------------------------------------------------------------------
# Copy all scripts to the build directory. This is so that we can
# run the executable directly because itrelies on these scripts being
# in the current working directory.
#
set(SimCalModule_SCRIPTS
  run.mac
  vis.mac
  gui.mac
  )

foreach(_script ${SimCalModule_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(CalorimeterModule DEPENDS SimCalModule_300mmFe)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/)
install(TARGETS SimCalModule_GS_HCAL DESTINATION bin)
