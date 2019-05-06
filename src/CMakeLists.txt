cmake_minimum_required(VERSION 3.13)

find_package (Threads)
find_package(Boost REQUIRED COMPONENTS system filesystem  )

add_executable(TecelaSQL
        Server/Server.cpp
        Server/Server.h
        Socket/Socket.cpp
        Socket/Socket.h
        HashTable/HashTable.h
        Application/Application.cpp
        Application/Application.h
        Query/Query.cpp
        Query/Query.h
        Command/Command.cpp
        Command/Command.h
        Command/AddCommand/AddCommand.cpp
        Command/AddCommand/AddCommand.h
        Command/DecrCommand/DecrCommand.cpp
        Command/DecrCommand/DecrCommand.h
        Command/DeleteCommand/DeleteCommand.cpp
        Command/DeleteCommand/DeleteCommand.h
        Command/DisconnectCommand/DisconnetCommand.cpp
        Command/DisconnectCommand/DisconnetCommand.h
        Command/FlushAllCommand/FlushAllCommand.cpp
        Command/FlushAllCommand/FlushAllCommand.h
        Command/GetCommand/GetCommand.cpp
        Command/GetCommand/GetCommand.h
        Command/IncrCommand/IncrCommand.cpp
        Command/IncrCommand/IncrCommand.h
        Command/SetCommand/SetCommand.cpp
        Command/SetCommand/SetCommand.h
        CacheManager/CacheManager.cpp CacheManager/CacheManager.h HashTable/test/testing.cpp HashTable/HashTable.cpp HashTable/HashNode.h utils.h Command/TouchCommand/TouchCommand.cpp Command/TouchCommand/TouchCommand.h)

target_link_libraries (TecelaSQL
        ${CMAKE_THREAD_LIBS_INIT}
        ${Boost_LIBRARIES})
