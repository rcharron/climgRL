cmake_minimum_required (VERSION 2.8)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
# -Wextra -pedantic-errors -Werror  -Wcast-qual -Wcast-align -Wconversion -Wdouble-promotion -Wfloat-equal -Wshadow -Wpointer-arith -Woverloaded-virtual -Wstrict-aliasing -Wstrict-overflow -Wunsafe-loop-optimizations -Wconversion -Wlogical-op -Wdisabled-optimization -Wunused")

project (ClimgRL)

#Dépendances

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

#Copie des ressources

file(COPY ${PROJECT_SOURCE_DIR}/ClimgRL/ressources/estimatormodels.db DESTINATION ${EXECUTABLE_OUTPUT_PATH}.)
file(COPY ${PROJECT_SOURCE_DIR}/ClimgRL/ressources/signature.sgn DESTINATION ${EXECUTABLE_OUTPUT_PATH}.)

#Programme principal
file(GLOB_RECURSE central_source_files ${PROJECT_SOURCE_DIR}/ClimgRL/coordinateur/*.cpp)
add_executable(ClimgRL ${central_source_files} ${PROJECT_SOURCE_DIR}/ClimgRL/coordinateur/sqlite3.c)
target_link_libraries(ClimgRL dl pthread)


#estimateurs

project (basicestim)

file(GLOB_RECURSE basicestim_source_files ${PROJECT_SOURCE_DIR}/ClimgRL/estimateurs/estimbasic/*.cpp)
add_library(basicestim MODULE ${basicestim_source_files})


project (solidestim)

file(GLOB_RECURSE solidestim_source_files ${PROJECT_SOURCE_DIR}/ClimgRL/estimateurs/estimsolidity/*.cpp)
add_library(solidestim MODULE ${solidestim_source_files})
target_link_libraries (solidestim ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})


project (spineestim)

file(GLOB_RECURSE spineestim_source_files ${PROJECT_SOURCE_DIR}/ClimgRL/estimateurs/estimskelton/*.cpp)
add_library(spineestim MODULE ${spineestim_source_files})
target_link_libraries (spineestim ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})


project (exentricitestim)

file(GLOB_RECURSE exentricitestim_source_files ${PROJECT_SOURCE_DIR}/ClimgRL/estimateurs/estimeccentricity/*.cpp)
add_library(exentricitestim MODULE ${exentricitestim_source_files})
target_link_libraries (exentricitestim ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})
 
 
#Pour les tests 
project (testnewfeatures)
file(GLOB_RECURSE source_files ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(testnewfeatures ${source_files})
target_link_libraries (testnewfeatures ${DGTAL_LIBRARIES}  ${Boost_LIBRAIRIES}  ${Boost_PROGRAM_OPTIONS_LIBRARY})


#project (ftestim)

#file(GLOB_RECURSE ftestim_source_files ${PROJECT_SOURCE_DIR}/ftestim/*.cpp)
#add_library(ftestim MODULE ${ftestim_source_files})
#add_executable(ftestim ${ftestim_source_files})
