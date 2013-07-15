project(bunsan_dcs)

include(${CMAKE_SOURCE_DIR}/system-config.cmake OPTIONAL)

cmake_minimum_required(VERSION 2.8)

include(BunsanCommon)

bunsan_use_bunsan(common network)
bunsan_use_xmlrpc(c++2 libwww-client abyss-server)
bunsan_use_boost(system filesystem serialization program_options thread)

bunsan_add_shared_library(${PROJECT_NAME}
    src/lib/hub.cpp
    src/lib/hub_interface.cpp

    src/lib/hub_interfaces/xmlrpc.cpp
    src/lib/hub_interfaces/xmlrpc.hpp

    src/lib/hubs/xmlrpc_proxy.cpp
    src/lib/hubs/local.hpp
    src/lib/hubs/xmlrpc_proxy.hpp
    src/lib/hubs/local.cpp
)
list(APPEND libraries ${PROJECT_NAME})

bunsan_add_executable(${PROJECT_NAME}_cli src/main.cpp)

bunsan_install_headers()
bunsan_install_targets(${PROJECT_NAME} ${PROJECT_NAME}_cli)

bunsan_include_tests()
