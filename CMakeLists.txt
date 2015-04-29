cmake_minimum_required (VERSION 2.8)
#set(CMAKE_BUILD_TYPE Release)


project (climgRL)

SET(Boost_USE_STATIC_LIBS   ON)
SET(Boost_USE_MULTITHREADED ON)
SET(Boost_USE_STATIC_RUNTIME OFF)
SET(Boost_FOUND FALSE)
FIND_PACKAGE(Boost 1.46.0 REQUIRED COMPONENTS program_options)
if ( Boost_FOUND )
  message(STATUS "Boost and boost_program_options found.")
  include_directories( ${Boost_INCLUDE_DIRS} )
 endif( Boost_FOUND )

 
FIND_PACKAGE(DGtal REQUIRED)
INCLUDE_DIRECTORIES(${DGTAL_INCLUDE_DIRS})
LINK_DIRECTORIES(${DGTAL_LIBRARY_DIRS})


file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(climgRL ${source_files})
target_link_libraries (climgRL ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
 
 
 
project (centralmotor)

file(GLOB_RECURSE central_source_files ${PROJECT_SOURCE_DIR}/centralmotor/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(centralmotor ${central_source_files} ${PROJECT_SOURCE_DIR}/centralmotor/sqlite3.c)

target_link_libraries(centralmotor dl pthread)



project (ftestim)

file(GLOB_RECURSE ftestim_source_files ${PROJECT_SOURCE_DIR}/ftestim/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_library(ftestim MODULE ${ftestim_source_files})


project (basicestim)

file(GLOB_RECURSE basicestim_source_files ${PROJECT_SOURCE_DIR}/basicestim/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_library(basicestim MODULE ${basicestim_source_files})



project (solidestim)


file(GLOB_RECURSE solidestim_source_files ${PROJECT_SOURCE_DIR}/estimsolidity/*.cpp)

set(CMAKE_CXX_FLAGS "-std=c++11")

add_library(solidestim MODULE ${solidestim_source_files})
target_link_libraries (solidestim ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
 
