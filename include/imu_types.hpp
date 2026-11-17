#pragma once 

#include <cstdint>
#include <Eigen/Dense>

struct ImuSample{

	std::int64_t timestamp_ns{0};

	Eigen::Vector3d gyro = Eigen::Vector3d::Zero();

	Eigen::Vector3d accel = Eigen::Vector3d::Zero();

};



