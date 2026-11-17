#include <iostream>
#include <string>
#include <memory>
#include <utility>

class ScopeProbe{

	public:
		explicit ScopeProbe(std::string name):name_(name){

			std::cout << name_ << " constructed\n";

		}

		~ScopeProbe(){
			std::cout << name_ << " destroyed\n";
		}

	
	private:
		std::string name_;

};

int main(){
	
	ScopeProbe object1("object1");
	ScopeProbe object2("object2");

	std::unique_ptr<int> p = std::make_unique<int>(100);

	auto p1 = std::make_unique<int>(100);
	auto p2 = std::move(p1);

	std::cout << *p << std::endl;

	std::cout << *p2 << std::endl;

	if(p1 == nullptr) std::cout << "p1 is empty\n";

	return 0;

}


