cmake_minimum_required(VERSION 3.16)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(GOF_SOURCE_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOfLife/
)

set(GOF_HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GameOfLife/
)


set (SRC_FILES 
    ${GOF_SOURCE_DIR}/GameOfLife.cpp
    ${GOF_HEADERS_DIR}/GameOfLife.hpp

    ${GOF_HEADERS_DIR}/GOFTypes.hpp
    ${GOF_HEADERS_DIR}/IGOFAlgorithm.hpp
    ${GOF_HEADERS_DIR}/ICheckBoard.hpp
    
    ${GOF_HEADERS_DIR}/ArrayBorderCheckBoard.hpp
    ${GOF_SOURCE_DIR}/ArrayBorderCheckBoard.cpp
    
    ${GOF_HEADERS_DIR}/SequentialTorusGOFAlgorithm.hpp
    ${GOF_SOURCE_DIR}/SequentialTorusGOFAlgorithm.cpp
    
)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${GOF_HEADERS_DIR})

set(DEMO ${PROJECT_NAME}_DEMO)
add_executable(${DEMO} ${CMAKE_CURRENT_SOURCE_DIR}/src/GOF_demo.cpp)
target_link_libraries(${DEMO} PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${GOF_PUBLIC_HEADERS_DIR})


include(FetchContent)
FetchContent_Declare(SFML
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(GRAPHIC_DEMO ${PROJECT_NAME}_GRAPHIC_DEMO)
add_executable(${GRAPHIC_DEMO} ${CMAKE_CURRENT_SOURCE_DIR}/src/GOF_graphic_demo.cpp)
target_link_libraries(${GRAPHIC_DEMO} PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${GOF_PUBLIC_HEADERS_DIR})
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