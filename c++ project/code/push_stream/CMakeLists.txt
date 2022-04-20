cmake_minimum_required( VERSION 3.21 )

project( push_stream 
         VERSION 0.1.0
         DESCRIPTION "Description of project"
         HOMEPAGE_URL "http://www.abc.com"
         LANGUAGES CXX )
         
#execute_process(COMMAND g++ -std=c++20 -x c++-header -fmodules-ts
#         /usr/include/c++/11.1.0/iostream
#         /usr/include/c++/11.1.0/string
#)
         
add_executable( push_stream )

target_sources( push_stream PRIVATE 
                main.cpp
                pch.h)
                
target_compile_features( push_stream PRIVATE cxx_std_20 )
#target_compile_options( push_stream PRIVATE -fmodules-ts )

#target_include_directories( push_stream PRIVATE /usr/include )

#target_link_directories( push_stream PRIVATE /usr/lib )

#target_link_libraries( push_stream PRIVATE m )

#set_target_properties( push_stream PROPERTIES
            #CXX_STANDARD 20
            #CXX_EXTENSIONS OFF
            #etc..
            #)
# 设置指定的C++编译器版本是必须的，如果不设置，或者为OFF，则指定版本不可用时，会使用上一版本。
#set_target_properties(push_stream PROPERTIES  CXX_STANDARD_REQUIRED on)


## --------------------------------------------------------------------------
## Adding build-requirements
## 源文件列表
#target_sources( <target> PRIVATE <source-file>... )
#
#target_precompile_headers( <target> PRIVATE <header-file>... )
#
## 预处理头文件搜索路径列表，等价参数：-I
#target_include_directories( <target> PRIVATE <include-search-dir>... )  
#
## 预编译宏 自动在指定的宏前添加，等价参数：-D
#target_compile_definitions( <target> PRIVATE <macro-definitions>... )  
#
## 编译选项和特性
#target_compile_options( <target> PRIVATE <compiler-option>... )
#target_compile_features( <target> PRIVATE <feature>... )
#
## 链接库
#target_link_libraries( <target> PRIVATE <dependency>... )
#
## 链接选项
#target_link_options( <target> PRIVATE <linker-option>... )
#
## 链接库搜索路径，等价参数：-L
#target_link_directories( <target> PRIVATE <linker-search-dir>... )

#execute_process(COMMAND ln -s /opt/gcc/gcm.cache  ./)

## Modern Cmake建议围绕Target和Property进行项目配置，竭力避免出现下面变量variable的set定义。
## Variable横行是典型CMake2.8时期的风格, Modern CMake则遵循了OO方法。其中，target表示待构建的对象，
## target相关的语句用于定义来约束link、compile等相关属性的scope。
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#find_package(OpenCV REQUIRED)
#include_directories(${OpenCV_INCLUDE_DIRS})
#target_link_libraries(push_stream ${OpenCV_LIBRARIES})

set(FFMPEG_ROOT "/usr")
target_link_libraries(push_stream
    "${FFMPEG_ROOT}/lib/libavutil.so"
    "${FFMPEG_ROOT}/lib/libpostproc.so"
    "${FFMPEG_ROOT}/lib/libswresample.so"
    "${FFMPEG_ROOT}/lib/libswscale.so"
    "${FFMPEG_ROOT}/lib/libavfilter.so"
    "${FFMPEG_ROOT}/lib/libavdevice.so"
    "${FFMPEG_ROOT}/lib/libavformat.so"
    "${FFMPEG_ROOT}/lib/libavcodec.so"
    "${FFMPEG_ROOT}/lib/libasound.so"
    "${FFMPEG_ROOT}/lib/libpthread.so"
    "${FFMPEG_ROOT}/lib/libmysqlpp.so.3.3.0"
)
find_package(Boost REQUIRED COMPONENTS thread)

include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(push_stream ${Boost_LIBRARIES})

target_link_libraries(push_stream "/usr/lib/libasound.so.2")

