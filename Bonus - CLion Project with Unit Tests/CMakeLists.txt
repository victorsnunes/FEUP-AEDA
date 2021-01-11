cmake_minimum_required(VERSION 3.10)
project(PADARIA_AEDA-FEUP)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(PADARIA_AEDA-FEUP main.cpp Tests/tests.cpp Tests/menu.cpp Tests/date.cpp Tests/product.cpp Tests/order.cpp Tests/employee.cpp Tests/client.cpp Tests/bakery.cpp)

target_link_libraries(PADARIA_AEDA-FEUP gtest gtest_main)