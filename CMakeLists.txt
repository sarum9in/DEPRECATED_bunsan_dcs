project(bunsan)

cmake_minimum_required(VERSION 2.8)

set(
	xmlrpc_link_lib
	xmlrpc++
	xmlrpc_client++
	xmlrpc_cpp
	xmlrpc_server++
	xmlrpc_server_abyss++
	xmlrpc_server_cgi++
	xmlrpc_server_pstream++
	xmlrpc_util
)

# BOOST
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
find_package (Boost COMPONENTS system filesystem serialization iostreams unit_test_framework program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
#set(Boost_LIBRARIES boost_system boost_filesystem boost_serialization boost_iostreams boost_unit_test_framework boost_program_options)
#include_directories(/usr/local/include)
#link_directories(/usr/local/lib)
message("We have to check pthread library on win* platform")
#find_package (Threads)
#target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
#target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} pthread)

add_definitions(-std=c++0x -pthread -g)

include_directories(.)

aux_source_directory(. srcs)
aux_source_directory(hubs hubs_srcs)
aux_source_directory(hub_interfaces hub_interfaces_srcs)

add_executable(${PROJECT_NAME} ${srcs} ${hubs_srcs} ${hub_interfaces_srcs})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${xmlrpc_link_lib})

## vim:nocindent
