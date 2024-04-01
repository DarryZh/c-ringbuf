cmake_minimum_required(VERSION 3.22)

project(ringbuf_test)

# 设置编译选项
set(CMAKE_C_STANDARD 99) # 设置C语言标准
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra") # 添加警告

# 添加可执行文件生成规则
add_executable(ringbuf_test
    ../../fd/ringbuf.c
    main.c
)

# 指定包含目录
target_include_directories(ringbuf_test PUBLIC ../../fd)

