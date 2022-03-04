cmake_minimum_required(VERSION 3.0.0)

project(demo VERSION 0.1.0)

include(CTest)
enable_testing()

INCLUDE(FindPkgConfig)

FIND_PACKAGE(OpenGL REQUIRED)
INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIRS})

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

file(
	GLOB_RECURSE
	source_files
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(GLAD_C ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/glad.c)

add_executable(demo ${source_files} ${GLAD_C})

target_link_libraries (
  demo
  ${OPENGL_LIBRARIES}
  glfw3 GL m Xrandr Xi X11 Xxf86vm pthread dl Xinerama Xcursor
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)