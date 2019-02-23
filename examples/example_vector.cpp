#include <iostream>
#include "../vector.hpp"

using namespace kick;

int main( int argc, char* argv[] ){
	vector<int> numbers; 
	
	numbers.push_back(1); 
	numbers.push_back(2); 
	numbers.push_back(3); 
	numbers.push_back(4); 
	numbers.push_back(5); 

	{
		int sum = numbers.filter([](const int& val) -> bool {
			return val % 2 != 0;
		}).map<int>([](const int& val) -> int {
			return val * val;
		}).reduce<int>([](const int& total, const int& val) -> int {
			return total + val;
		});

		std::cout << "sum: " << sum << std::endl;
		// numbers.filter_to(odds, [](const int& val) -> bool {
		// 	return val % 2 != 0;
		// });

		// std::cout << "odds:" << std::endl; 

		// for(auto const& val : squared_odds) {
		// 	std::cout << val << std::endl;
		// }
	}
}
