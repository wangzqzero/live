cmake_minimum_required( VERSION 3.21 )

project( mysqltest 
         VERSION 0.1.0
         DESCRIPTION "Description of project"
         HOMEPAGE_URL "http://www.abc.com"
         LANGUAGES CXX )
         
#execute_process(COMMAND g++ -std=c++20 -x c++-header -fmodules-ts
#         /usr/include/c++/11.1.0/iostream
#         /usr/include/c++/11.1.0/string
#)
         
add_executable( mysqltest )

target_sources( mysqltest PRIVATE 
                main.cpp )
                
target_compile_features( mysqltest PRIVATE cxx_std_20 )
#target_compile_options( mysqltest PRIVATE -fmodules-ts )

#target_include_directories( mysqltest PRIVATE /usr/include )

#target_link_directories( mysqltest PRIVATE /usr/lib )

#target_link_libraries( mysqltest PRIVATE m )

#set_target_properties( mysqltest PROPERTIES
            #CXX_STANDARD 20
            #CXX_EXTENSIONS OFF
            #etc..
            #)
# 设置指定的C++编译器版本是必须的，如果不设置，或者为OFF，则指定版本不可用时，会使用上一版本。
#set_target_properties(mysqltest PROPERTIES  CXX_STANDARD_REQUIRED on)


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

#mysql所需的头文件和库所需的目录和库文件可以用/usr/bin/mysql_config来查看

include_directories("/usr/include/mysql")
link_directories("usr/lib")

set(MYSQL_LIBS
    mysqlclient pthread z m rt atomic ssl crypto dl
    )
target_link_libraries(mysqltest  ${MYSQL_LIBS})
target_link_libraries(mysqltest
    "/usr/lib/libmysqlpp.so"
)
