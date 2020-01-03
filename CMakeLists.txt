cmake_minimum_required(VERSION 3.3)
project(Minecraft-Block-Viewer)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O2")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

include_directories(include)
include_directories(include/glhelper)
include_directories(include/Block)

# Custom Library
file(GLOB glhelper_SRC "src/glhelper/*.cpp")
add_library(glhelper ${glhelper_SRC})

# Executables
add_executable(minecraft_block_viewer src/minecraft_block_viewer.cpp src/Block/Block.cpp)

include_directories(
	${CMAKE_CURRENT_BINARY_DIR} 
	${OPENGL_INCLUDE_DIRS} 
	${GLUT_INCLUDE_DIRS} 
	${GLEW_INCLUDE_DIRS}
	${GLFW_INCLUDE_DIRS}
)

target_link_libraries(
	minecraft_block_viewer
	${OPENGL_INCLUDE_LIBRARIES}
	${OPENGL_gl_LIBRARY} 			# GL
	${GLUT_INCLUDE_LIBRARIES} 		# glut
	${GLEW_LIBRARIES}				# GLEW
	glfw							# GLFW
	GLU								# GLU
	glhelper						# Custom Library
	jsoncpp
)
