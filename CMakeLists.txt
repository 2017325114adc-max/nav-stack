cmake_minimum_required(VERSION 3.16)

project(Demo)

set(CMAKE_BUILD_TYPE Debug)

find_package(Eigen3 REQUIRED)

add_executable(wudi src/hello.cpp)
add_executable(meiren src/imu_statistics.cpp)
add_executable(Eigen src/eigen_demo.cpp)
add_executable(buffer src/imu_buffer_demo.cpp)

target_include_directories(buffer PRIVATE ${PROJECT_SOURCE_DIR}/include)
  
target_link_libraries(Eigen PRIVATE Eigen3::Eigen)
target_link_libraries(meiren PRIVATE Eigen3::Eigen)
target_link_libraries(buffer PRIVATE Eigen3::Eigen)
