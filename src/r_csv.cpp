#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>

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

   std::string line;
   uint64_t row_count = 0;
   uint64_t count = 0;
   uint64_t first_ts = 0;
   uint64_t last_ts = 0;
   std::vector<std::string> first_three_lines;

   bool is_first_valid = false;

   while(std::getline(file, line)){
	   if(line.empty()) continue;

	   row_count++;

	   size_t comma_pos = line.find(',');
	   if(comma_pos == std::string::npos) continue;

	   std::string ts_str = line.substr(0, comma_pos);

	   try{
		   uint64_t current_ts = std::stoull(ts_str);

		   if(!is_first_valid){
			   first_ts = current_ts;
			   is_first_valid = true;
		   }

		   last_ts = current_ts;
	   }catch (const std::exception& e){
		
	   }


	   if(is_first_valid == true && count < 3 ){
		   first_three_lines.push_back(line);
		   count++;
	   }

   }
  
   file.close();

   std::cout << "--- IMU Data Statistics ---" << std::endl;
   std::cout << "rows: " << row_count << std::endl;

   std::cout << "first 3 lines: " << std::endl;
   for(const auto& l : first_three_lines){
	   std::cout << " " << l << std::endl;
   }

   if(row_count > 0){
	   double duration = static_cast<double>(last_ts - first_ts) / 1e9;

	   std::cout << "duration: " << std::fixed << std::setprecision(1) << duration << " s" << std::endl;
   }

   return 0;

}
