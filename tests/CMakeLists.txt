project(bunsan_dcs_tests)

cmake_minimum_required(VERSION 2.8)

message("tests was included")

file(GLOB test_srcs "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach(src ${test_srcs})
	string(REGEX REPLACE "^.*/([^/]+)$" "\\1" trgt ${src})
	add_executable(${trgt} ${src})
	target_link_libraries(${trgt} bunsan_dcs)
	add_test(${trgt} ${trgt})
endforeach()

