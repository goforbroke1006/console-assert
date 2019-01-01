cmake_minimum_required(VERSION 3.10)
project(console-assert)

set(CMAKE_CXX_STANDARD 11)

add_executable(console-assert main.cpp strings.h asserts.h)

if (WIN32)
	set(CMAKE_INSTALL_PREFIX "C:\\Program Files\\")
elseif(UNIX)
	set(CMAKE_INSTALL_PREFIX /usr/local/bin/)
endif()

install(TARGETS console-assert
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
