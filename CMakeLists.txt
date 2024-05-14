cmake_minimum_required(VERSION 3.16)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GOF_SOURCE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOfLife/
)

set(GOF_HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GameOfLife/
)

set (SRC_FILES 
    ${GOF_HEADERS_DIR}/GameOfLife.hpp

    ${GOF_HEADERS_DIR}/GOFTypes.hpp
    ${GOF_HEADERS_DIR}/IGOF.hpp
    ${GOF_HEADERS_DIR}/ICheckBoard.hpp
    ${GOF_HEADERS_DIR}/ICheckBoardFiller.hpp

    ${GOF_HEADERS_DIR}/IGOFAlgorithm.hpp
    ${GOF_SOURCE_DIR}/IGOFAlgorithm.cpp

    ${GOF_HEADERS_DIR}/VectorBorderCheckBoard.hpp
    ${GOF_SOURCE_DIR}/VectorBorderCheckBoard.cpp

    ${GOF_HEADERS_DIR}/MatrixBorderCheckBoard.hpp
    ${GOF_SOURCE_DIR}/MatrixBorderCheckBoard.cpp

    ${GOF_HEADERS_DIR}/SequentialTorusGOFAlgorithm.hpp
    ${GOF_SOURCE_DIR}/SequentialTorusGOFAlgorithm.cpp

    ${GOF_HEADERS_DIR}/SequentialVectorTorusGOFAlgorithm.hpp
    ${GOF_SOURCE_DIR}/SequentialVectorTorusGOFAlgorithm.cpp

    ${GOF_SOURCE_DIR}/RandomFiller.cpp
    ${GOF_HEADERS_DIR}/RandomFiller.hpp

    ${GOF_SOURCE_DIR}/FromFileFiller.cpp
    ${GOF_HEADERS_DIR}/FromFileFiller.hpp

    ${GOF_SOURCE_DIR}ParallelTorusAlgorithm.cpp
    ${GOF_HEADERS_DIR}ParallelTorusAlgorithm.hpp
)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GOF_HEADERS_DIR})

set(DEMO ${PROJECT_NAME}_DEMO)
add_executable(${DEMO} ${CMAKE_CURRENT_SOURCE_DIR}/src/GOF_demo.cpp)
target_link_libraries(${DEMO} PRIVATE ${PROJECT_NAME})

set(BENCHMARK ${PROJECT_NAME}_BENCHMARK)
add_executable(${BENCHMARK} ${CMAKE_CURRENT_SOURCE_DIR}/src/GOF_benchmark.cpp)
target_link_libraries(${BENCHMARK} PRIVATE ${PROJECT_NAME})

#[===[
include(FetchContent)
FetchContent_Declare(SFML
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
set(GRAPHIC_DEMO ${PROJECT_NAME}_GRAPHIC_DEMO)
add_executable(${GRAPHIC_DEMO} ${CMAKE_CURRENT_SOURCE_DIR}/src/GOF_graphic_demo.cpp)
target_link_libraries(${GRAPHIC_DEMO} PRIVATE ${PROJECT_NAME})
target_link_libraries(${GRAPHIC_DEMO} PRIVATE sfml-graphics)

if(WIN32)
    add_custom_command(
        TARGET ${GRAPHIC_DEMO}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy 
            ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll 
            $<TARGET_FILE_DIR:${GRAPHIC_DEMO}>
        VERBATIM)
endif()

install(TARGETS ${GRAPHIC_DEMO})
]===]
