cmake_minimum_required(VERSION 3.0.0)
project(simulation VERSION 0.1.0)

include(CTest)
enable_testing()

# 添加宏定义
add_definitions(-DUSE_SDL -DUSE_WIN32DRV)

# 添加头文件目录
include_directories(src)
include_directories(lvgl)

# 添加cmake子库编译
add_subdirectory("lvgl")
add_subdirectory("lvgl_drivers")

# 添加源文件(递归包含)
FILE(GLOB_RECURSE src_source ./src/*.c)

# 编译可执行文件
add_executable(${PROJECT_NAME} ${src_source})

# 链接库
target_link_libraries(${PROJECT_NAME} lvgl)
target_link_libraries(${PROJECT_NAME} lvgl_demos)
target_link_libraries(${PROJECT_NAME} lvgl_examples)
target_link_libraries(${PROJECT_NAME} lvgl_drivers)
target_link_libraries(${PROJECT_NAME} mingw32)
target_link_libraries(${PROJECT_NAME} SDL2main)
target_link_libraries(${PROJECT_NAME} SDL2)
target_link_libraries(${PROJECT_NAME} avfilter avformat avcodec avutil swresample swscale)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
