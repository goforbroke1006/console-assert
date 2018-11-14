cmake_minimum_required(VERSION 3.10)
project(console-interaction-tester)

set(CMAKE_CXX_STANDARD 11)

add_executable(console-interaction-tester main.cpp)

set(CMAKE_INSTALL_PREFIX /usr/local/bin/)
install(TARGETS console-interaction-tester
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )