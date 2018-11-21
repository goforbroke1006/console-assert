cmake_minimum_required(VERSION 3.10)
project(console-assert)

set(CMAKE_CXX_STANDARD 11)

<<<<<<< HEAD
add_executable(console-interaction-tester main_win32.cpp)

#if (WIN32)
	#set(CMAKE_INSTALL_PREFIX C:/Program\ Files)
#elseif(UNIX)
	#set(CMAKE_INSTALL_PREFIX /usr/local/bin/)
#endif()
#
install(TARGETS console-interaction-tester
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
=======
add_executable(console-assert main.cpp strings.h)

if (WIN32)
	set(CMAKE_INSTALL_PREFIX "C:\\Program Files\\")
elseif(UNIX)
	set(CMAKE_INSTALL_PREFIX /usr/local/bin/)
endif()

install(TARGETS console-assert
        DESTINATION ${CMAKE_INSTALL_PREFIX}
        )
>>>>>>> 6f5374a0b63705e57f6b5217747f5780e25fb96e
