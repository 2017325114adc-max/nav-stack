#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <Eigen/Dense>

	struct ImuSample{

		std::int64_t timestamp_ns;

		Eigen::Vector3d gyro;
		Eigen::Vector3d accel;

	};

int main(int argc, char* argv[]){

   std::string file_path = "data/machine_hall/MH_01_easy/mav0/imu0/data.csv";

   if(argc > 1){
	   file_path = argv[1];
   }

   std::ifstream file(file_path);

   if(!file.is_open()){
	   std::cerr << "Error : 无法打开文件 " << file_path << std::endl;
	   return 1; 
   }

   std::vector<ImuSample> imu_data;
   std::vector<double> dt_values;

   std::string line;

   Eigen::Vector3d gyro_mean = Eigen::Vector3d::Zero();
   Eigen::Vector3d accel_mean = Eigen::Vector3d::Zero();

   Eigen::Vector3d gyro_variance = Eigen::Vector3d::Zero();
   Eigen::Vector3d accel_variance = Eigen::Vector3d::Zero();

   double dt_mean = 0.0;
   double dt_variance = 0.0;

   size_t invalid_dt_count = 0;

   while(std::getline(file, line)){
	   if(line.empty()) continue;

	   std::stringstream ss(line);

	   ImuSample sample;

	   char comma;

	   if(!(ss >> sample.timestamp_ns >> comma
		   >> sample.gyro[0] >> comma
		   >> sample.gyro[1] >> comma
		   >> sample.gyro[2] >> comma

		   >> sample.accel[0] >> comma
		   >> sample.accel[1] >> comma
		   >> sample.accel[2]))  continue;

	   imu_data.push_back(sample);

   }

   file.close();

   if(imu_data.empty()){

	   std::cerr << "没有有效的 IMU 数据! " << std::endl;
	   
	   return 1;

   }

   for(const auto& sample : imu_data){

           gyro_mean += sample.gyro;
           accel_mean += sample.accel;

   }

   const double count = static_cast<double>(imu_data.size());

   gyro_mean /=  count;
   accel_mean /= count;

   for(const auto& sample : imu_data){

	   gyro_variance += (sample.gyro - gyro_mean).cwiseAbs2();
	   accel_variance += (sample.accel - accel_mean).cwiseAbs2();

   }

   gyro_variance /= count;
   accel_variance /= count;

   for(size_t i = 1; i < imu_data.size(); i++){

	   const auto current = imu_data[i].timestamp_ns;
	   const auto previous = imu_data[i - 1].timestamp_ns;

	   if(current <= previous){

		   invalid_dt_count++;

		   continue;

	   }

	   const double dt = static_cast<double>(current - previous) / 1e9;

	   dt_values.push_back(dt);

   }

   if(dt_values.empty()){

	   std::cerr << "没有有效采样间隔! " << std::endl;

	   return 1;

   }



   for(size_t i = 0; i < dt_values.size(); i++) dt_mean += dt_values[i];

   dt_mean /= dt_values.size();

   for(size_t i = 0; i < dt_values.size(); i++) dt_variance += (dt_values[i] - dt_mean)*(dt_values[i] - dt_mean);

   dt_variance /= dt_values.size();


   std::cout << "数据量: " << static_cast<int>(count) << std::endl;

   for(size_t i = 0; i < std::min(imu_data.size(), size_t(3)); i++){
	   const auto& sample = imu_data[i];

	   std::cout << "\n第 " << i + 1 << " 条数据\n";

	   std::cout << "timestamp: " << sample.timestamp_ns << std::endl;

	   std::cout << "gyro " << sample.gyro.transpose() << std::endl;

	   std::cout << "accel " << sample.accel.transpose() << std::endl;

	   if(i == 0 ){

		   double gyro_norm = sample.gyro.norm();
		   double accel_norm = sample.accel.norm();

	   	   std::cout << "gyro_norm: " << gyro_norm << std::endl;
		   std::cout << "accel_norm: " << accel_norm << std::endl;
	   }
   }


   std::cout << "\n========== IMU Statistics ==========\n";

   std::cout << "\ngyro_mean: " << gyro_mean.transpose() << std::endl;
   std::cout << "accel_mean: " << accel_mean.transpose() << std::endl;

   std::cout << "\ngyro_variance: " << gyro_variance.transpose() << std::endl;
   std::cout << "accel_variance: " << accel_variance.transpose() << std::endl;

   if(dt_mean <= 0.0){
	   std::cerr << "采样间隔均值异常!" << std::endl;
	   return 1;
   }

   std::cout << "\ndt_mean: " << dt_mean << std::endl;
   std::cout << "frequency: " << 1.0 / dt_mean << "Hz" << std::endl;
   std::cout << "dt_variance: " << dt_variance << std::endl; 
   
   std::cout << "有效采样间隔数量: " << dt_values.size() << std::endl;
   std::cout << "异常采样间隔数量: " << invalid_dt_count << std::endl;

   double duration = static_cast<double>(imu_data.back().timestamp_ns -imu_data.front().timestamp_ns) / 1e9;

   std::cout << "\n数据持续时间: "
	     << std::fixed
	     << std::setprecision(3)
	     << duration << " s" << std::endl;

   std::cout << "\n========== Statistics Finished ==========" << std::endl;

   return 0;

}
