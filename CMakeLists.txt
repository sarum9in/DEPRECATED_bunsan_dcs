project(bunsan_dcs)

cmake_minimum_required(VERSION 2.8)

if(${CMAKE_COMPILER_IS_GNUCXX})
    set(gxx_flags "-std=c++0x -Wall -Wextra")
    if(${UNIX})
        set(gxx_flags "-pthread ${gxx_flags}")
    endif()
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${gxx_flags}")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2 ${gxx_flags}")
endif()

include(${CMAKE_SOURCE_DIR}/user-config.cmake OPTIONAL)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: Debug Release" FORCE)
endif()

if(NOT DEFINED ENABLE_TESTS)
    set(ENABLE_TESTS ON CACHE BOOL "Do you want to enable testing?" FORCE)
endif()

find_package(XMLRPC REQUIRED c++2 libwww-client abyss-server)

# BOOST
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost COMPONENTS system filesystem serialization iostreams unit_test_framework program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

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

if(${ENABLE_TESTS})
    enable_testing()
    add_subdirectory(tests ${PROJECT_BINARY_DIR}/tests)
endif()

