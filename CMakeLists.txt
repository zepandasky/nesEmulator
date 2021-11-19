cmake_minimum_required(VERSION 3.3)
project(nes_emulator)

set (SRC_FILES 	${PROJECT_SOURCE_DIR}/source_files/Bus.cpp
		${PROJECT_SOURCE_DIR}/source_files/CPU6502.cpp
                ${PROJECT_SOURCE_DIR}/source_files/main.cpp)
set (HDR_FILES  ${PROJECT_SOURCE_DIR}/header_files/Bus.h 
                ${PROJECT_SOURCE_DIR}/header_files/CPU6502.h 
                ${PROJECT_SOURCE_DIR}/header_files/olcPixelGameEngine.h 
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
set(OpenGL_GL_PREFERENCE LEGACY)

find_package(X11 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${X11_INCLUDE_DIR})
include_directories(${PNG_INCLUDE_DIR})

set(CORELIBS ${OPENGL_LIBRARY} ${X11_LIBRARIES} ${PNG_LIBRARY})

add_definitions(-DCMAKE_HAS_X)
add_executable(nes_emulator ${SRC_FILES} ${HDR_FILES})
target_link_libraries(nes_emulator ${CORELIBS} Threads::Threads stdc++fs)