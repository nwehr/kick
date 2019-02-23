#include <iostream>
#include "../deque.hpp"

using namespace kick;

int main( int argc, const char* argv[] ){
	deque<int> numbers; 

	numbers.push_back(1); 
	numbers.push_back(2); 
	numbers.push_back(3); 
	numbers.push_back(4); 
	numbers.push_back(5); 

	{
		int sum = numbers
		.filter([](const int& val) -> bool {
			return val % 2 != 0;
		})
		.transform<int>([](const int& val) -> int {
			return val * val;
		})
		.reduce<int>([](const int& total, const int& val) -> int {
			return total + val;
		});

		// for(auto const& it : odds) {
		// 	std::cout << it << std::endl;
		// }

		std::cout << sum << std::endl;
	}

	// {
	// 	deque<int> odds;

	// 	numbers.filter_to(odds, [](const int& val) -> bool {
	// 		return val % 2 != 0;
	// 	});

	// 	std::cout << "odds:" << std::endl;

	// 	for(auto const& val : odds) {
	// 		std::cout << val << std::endl;
	// 	}
	// }

	// {
	// 	deque<int> squares;

	// 	numbers.map_to<int>(squares, [](const int& val) -> int {
	// 		return val * val;
	// 	});

	// 	std::cout << "squares:" << std::endl;

	// 	for(auto const& val : squares) {
	// 		std::cout << val << std::endl;
	// 	}
	// }

	// {
	// 	int sum;

	// 	numbers.reduce_to<int>(sum, [](const int& sum, const int& val) -> int {
	// 		return sum * val;
	// 	});

	// 	std::cout << "sum:" << std::endl << sum << std::endl;
	// }
}