cmake_minimum_required(VERSION 3.16)

project(Demo)

find_package(Eigen3 REQUIRED)

add_executable(wudi src/hello.cpp)
add_executable(meiren src/imu_statistics.cpp)
add_executable(Eigen src/eigen_demo.cpp)

target_link_libraries(Eigen PRIVATE Eigen3::Eigen)
target_link_libraries(meiren PRIVATE Eigen3::Eigen)	

