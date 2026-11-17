#include <iostream>
#include "imu_buffer.hpp"

int main(){

	ImuBuffer buffer(3);
	ImuBuffer buffer1(4);
	ImuBuffer b(4);

	ImuSample sample1{
	       	1000000000,
       	        {0.01, 0.02, 0.03},
       		{0.1, 0.2, 0.3}
        };

        ImuSample sample2{
		2000000000,
       		{0.02, 0.04, 0.06},
       		{0.2, 0.4, 0.6}
   	};

   	ImuSample sample3{
	       	4000000000,
        	{0.04, 0.08, 0.12},
        	{0.4, 0.8, 1.2}
    	};

    	ImuSample sample4{
        	8000000000,
        	{0.08, 0.16, 0.24},
        	{0.8, 1.6, 2.4}
    	};

	std::cout << "Capacity: " << buffer.capacity() << std::endl;
        std::cout << "Size: " << buffer.size() << std::endl;

	buffer.pushBack(sample1);
	buffer.pushBack(sample2);
        buffer.pushBack(sample3);

	buffer1.pushBack(sample1);
        buffer1.pushBack(sample2);
        buffer1.pushBack(sample3);
	buffer1.pushBack(sample4);


	ImuBuffer a = std::move(buffer1);

	std::cout << "buffer1 size: "
          	  << buffer1.size() << std::endl;

	std::cout << "a size: "
         	  << a.size() << std::endl;

	b = std::move(a);

	std::cout << "\nb size: " << b.size() << std::endl;
	std::cout << "a size: " << a.size() << std::endl;


	try{
		buffer.at(100);
	} catch(const std::out_of_range& e){
		std::cout << e.what() << std::endl;
	}

	std::cout << "Capacity: " << buffer.capacity() << std::endl;
	std::cout << "Size: " << buffer.size() << std::endl;

	bool success = buffer.pushBack(sample4);

	std::cout << "Push fourth sample: "
	          << (success ? "success" : "failed") << std::endl;

	const ImuSample& first = buffer.at(0);

	std::cout << "\nFirst IMU sample:" << std::endl;

        std::cout << "Timestamp: " << first.timestamp_ns << std::endl;

	std::cout << "Gyroscope: "
                  << first.gyro[0] << ", "
                  << first.gyro[1] << ", "
                  << first.gyro[2] << std::endl;

        std::cout << "Accelerometer: "
                  << first.accel[0] << ", "
                  << first.accel[1] << ", "
                  << first.accel[2] << std::endl;

	return 0;

}

