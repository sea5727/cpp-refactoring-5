cmake_minimum_required(VERSION 3.0.0)
project(cpp-refactoring-4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CTest)
enable_testing()

list(APPEND CMAKE_MODULE_PATH "/usr/local/boost-1.73.0/lib/cmake/")
find_package(Boost 1.73 REQUIRED COMPONENTS program_options thread)
if(Boost_FOUND)
    message(Boost Found! ${Boost_LIBRARIES})
    include_directories(/usr/local/include)
    link_directories(/usr/local/lib)
endif()

add_executable(cpp-refactoring-5 main.cpp ApplicationTcpSession.cpp Handler.cpp)
target_link_libraries(cpp-refactoring-5 ${Boost_LIBRARIES} pthread)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
