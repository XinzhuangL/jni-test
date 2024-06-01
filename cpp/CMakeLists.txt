cmake_minimum_required(VERSION "3.10")
project(cpp)

set(CMAKE_CXX_STANDARD 11)

set(JAVA_HOME /Library/Java/JavaVirtualMachines/jdk-1.8.jdk/Contents/Home)

message(STATUS "JAVA_HOME is set to ${JAVA_HOME}")


# 包含 JNI 头文件目录
include_directories(${JAVA_HOME}/include)
include_directories(${JAVA_HOME}/include/darwin)

# 链接到 JNI 库
find_library(JVM_LIBRARY jvm PATHS ${JAVA_HOME}/jre/lib/server)
if(NOT JVM_LIBRARY)
    message(FATAL_ERROR "JVM library not found")
endif()

add_executable(main
        jni_main.cpp)
target_include_directories(main PRIVATE
        /Users/lixinzhuang1/IdeaProjects/JNI-demo/src/main/java)
target_link_libraries(main ${JVM_LIBRARY})
