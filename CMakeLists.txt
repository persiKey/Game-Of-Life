cmake_minimum_required(VERSION 3.16)
project(GameOfLife LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set (SRC_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/GameOfLife/GameOfLife.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GameOfLife/public/GameOfLife.hpp
)

set(PUBLIC_HEADERS_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GameOfLife/public/
)

set(PRIVATE_HEADERS_DIR 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/GameOfLife/private/  
)

add_library(${PROJECT_NAME} ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${PRIVATE_HEADERS_DIR})

set(DEMO ${PROJECT_NAME}_DEMO)
add_executable(${DEMO} src/GOF_demo.cpp)
target_link_libraries(${DEMO} PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS_DIR})


include(FetchContent)
FetchContent_Declare(SFML
GIT_REPOSITORY https://github.com/SFML/SFML.git
GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(GRAPHIC_DEMO ${PROJECT_NAME}_GRAPHIC_DEMO)
add_executable(${GRAPHIC_DEMO} src/GOF_graphic_demo.cpp)
target_link_libraries(${GRAPHIC_DEMO} PRIVATE ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PUBLIC_HEADERS_DIR})
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
