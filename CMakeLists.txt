cmake_minimum_required(VERSION 3.13)
project(TecelaSQL)

find_package (Threads)
find_package(Boost REQUIRED COMPONENTS system filesystem thread)

set(CMAKE_CXX_STANDARD 14)

add_executable(TecelaSQL main.cpp Server/Server.cpp Server/Server.h SocketHandler/SocketHandler.cpp SocketHandler/SocketHandler.h QueryProvider/QueryProvider.cpp QueryProvider/QueryProvider.h CacheManger/CacheManager.cpp CacheManger/CacheManager.h client/main.cpp Server/test.cpp Socket/Socket.cpp Socket/Socket.h HashTable/HashTable.h)

target_link_libraries (TecelaSQL
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES})
