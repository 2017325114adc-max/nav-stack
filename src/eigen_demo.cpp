#include <iostream>
#include <Eigen/Dense>

int main(){

	Eigen::Vector3d gyro;

	Eigen::Vector3d a(1,2,3);
	Eigen::Vector3d b(4,5,6);


	Eigen::Matrix3d rotation;


	gyro << 0.1,0.2,0.3;

	rotation << 1,0,0,
		    0,1,0,
		    0,0,1;


	std::cout << "Gyroscope:\n";
	std::cout << gyro << std::endl;

	std::cout << "x: " << gyro[0] << std::endl;
	std::cout << "y: " << gyro[1] << std::endl;
	std::cout << "z: " << gyro[2] << std::endl;

	std::cout << "Rotation matrix:\n";
	std::cout << rotation << std::endl;

	std::cout << "Addition:\n"
		  << a + b << std::endl;

	std::cout << "Subtraction:\n"
		  << a - b << std::endl;

	std::cout << "Dot product:\n"
		  << a.dot(b) << std::endl;

	std::cout << "Norm:\n"
		  << a.norm() << std::endl;

	return 0;

}
