cmake_minimum_required(VERSION 3.0.0)
project(DietTracker VERSION 0.1.0)

include(CTest)
enable_testing()

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost COMPONENTS) 

#add_subdirectory("/DietTracker/")

AUX_SOURCE_DIRECTORY(DietTracker SOURCEDIR)

add_executable(DietTracker 
    ${SOURCEDIR}
)

if(Boost_FOUND)
    target_link_libraries(DietTracker )
endif()

target_link_libraries(DietTracker PRIVATE ${Boost_LIBRARIES})
target_include_directories(DietTracker PRIVATE ${Boost_INCLUDE_DIRS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
