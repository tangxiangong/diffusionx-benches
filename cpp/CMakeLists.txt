cmake_minimum_required(VERSION 3.31)
project(cpp-bench)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# 添加 lib 目录到链接目录
link_directories(${PROJECT_SOURCE_DIR}/lib)

file(GLOB_RECURSE ALL_SRC_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# 为 src/ 下的每个 .cpp 文件生成一个可执行程序
foreach(src_file ${ALL_SRC_FILES})
    # 获取不带扩展名的文件名作为可执行文件名
    get_filename_component(executable_name ${src_file} NAME_WE)
    add_executable(${executable_name} ${src_file})
    # 链接第三方库
    target_link_libraries(${executable_name} PRIVATE diffusionx)
    target_include_directories(${executable_name} PRIVATE ${PROJECT_SOURCE_DIR}/include)
endforeach()
