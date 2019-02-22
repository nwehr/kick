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
		deque<int> odds;

		numbers.filter_to(odds, [](const int& val) -> bool {
			return val % 2 != 0;
		});

		std::cout << "odds:" << std::endl;

		odds.for_each([](const int& val) {
			std::cout << val << std::endl;
		});
	}

	{
		deque<int> squares;

		numbers.map_to<int>(squares, [](const int& val) -> int {
			return val * val;
		});

		std::cout << "squares:" << std::endl;

		squares.for_each([](const int& val){
			std::cout << val << std::endl;
		});
	}

	{
		int sum;

		numbers.reduce_to<int>(sum, [](const int& sum, const int& val) -> int {
			return sum * val;
		});

		std::cout << "sum:" << std::endl << sum << std::endl;
	}
}