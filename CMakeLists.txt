#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.8)
#Name your project here
project(ricalc)

#set the module directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

#find BOOST
set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package( Boost 1.54.0 COMPONENTS program_options )

#set up CUDA
find_package(CUDA)
if(CUDA_FOUND)
    link_libraries(${CUDA_cufft_LIBRARY})
    add_definitions(-DCUDA_AVAILABLE)
endif(CUDA_FOUND)

#set up the FFTW package (fast Fourier transform)
find_package(FFTW)
if(FFTW_FOUND)
    include_directories(${FFTW_INCLUDE_DIR})
    link_libraries(${FFTW_LIBRARY})
    add_definitions(-DFFTW_AVAILABLE)
endif(FFTW_FOUND)

#ask the user for the RTS location
set(RTS_ROOT_PATH $ENV{RTS_ROOT_PATH})
find_package(RTS REQUIRED)

#set the include directories
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
	${RTS_INCLUDE_DIR}
    ${Boost_INCLUDE_DIR}
)

#enable warnings
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	add_definitions(-Wall -lfftw3 -lm)
endif()

#Assign source files to the appropriate variables
file(GLOB SRC_CPP "*.cpp")
file(GLOB SRC_H "*.h")
file(GLOB SRC_CU "*.cu")

#copy example material files
configure_file(etaPolyethylene.txt ${CMAKE_CURRENT_BINARY_DIR}/etaPolyethylene.txt COPYONLY)
configure_file(etaTeflon.txt ${CMAKE_CURRENT_BINARY_DIR}/etaTeflon.txt COPYONLY)
configure_file(etaToluene.txt ${CMAKE_CURRENT_BINARY_DIR}/etaToluene.txt COPYONLY)


#create an executable
cuda_add_executable(ricalc ${SRC_CPP} ${SRC_H} ${SRC_CU})

#set the link libraries
target_link_libraries(ricalc ${Boost_LIBRARIES})



