project(bunsan_dcs)

cmake_minimum_required(VERSION 2.8)

find_package(XMLRPC REQUIRED c++2 libwww-client abyss-server)

# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system filesystem serialization iostreams unit_test_framework program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

message(AUTHOR_WARNING "We have to check pthread library on win* platform")
message(AUTHOR_WARNING "We have to provide support for different compilers")

add_definitions(-std=c++0x -pthread -g -D_GLIBCXX_USE_NANOSLEEP -Wall -Wextra)

include_directories(include ${XMLRPC_INCLUDE_DIRS})

aux_source_directory(src/lib lib_srcs)
aux_source_directory(src/lib/hubs hubs_srcs)
aux_source_directory(src/lib/hub_interfaces hub_interfaces_srcs)

add_library(${PROJECT_NAME} SHARED ${lib_srcs} ${hubs_srcs} ${hub_interfaces_srcs})
target_link_libraries(${PROJECT_NAME} bunsan_common ${Boost_LIBRARIES} ${XMLRPC_LIBRARIES})

add_executable(dcs src/main.cpp)
target_link_libraries(dcs ${PROJECT_NAME})

# install

install(DIRECTORY include DESTINATION .)
install(TARGETS
	dcs
	${PROJECT_NAME}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib)

# testing

enable_testing()
add_subdirectory(tests ${PROJECT_BINARY_DIR}/tests)

