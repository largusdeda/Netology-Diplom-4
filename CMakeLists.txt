cmake_minimum_required(VERSION 3.22.0)

project("thread_safe_queue" LANGUAGES CXX)

set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

include_directories(include)

add_executable( ${PROJECT_NAME} 
    include/foo1.h 
    include/foo2.h
    include/foo3.h 
    include/foo4.h
    include/thread_pool.h 
    include/safe_queue.h 

    src/main.cpp 
    src/foo1.cpp
    src/foo2.cpp 
    src/foo3.cpp  
    src/foo4.cpp 
    src/thread_pool.cpp )

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)