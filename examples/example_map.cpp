#include <iostream>

#include "../string.hpp"
#include "../map.hpp"

using namespace kick;

int main( int argc, const char* argv[] ){
	map<string, int> numbers; 

	numbers.insert(pair<string, int>("one", 1)); 
	numbers.insert(pair<string, int>("two", 2)); 
	numbers["three"] = 3; 
	numbers["four"]  = 4; 
	numbers["five"]  = 5; 

	{
		map<string, int> squared_odds = numbers.filter([](const string& key, const int& val) -> bool {
			return val % 2 != 0;
		}).transform<int>([](const string& key, const int& val){
			return val * val;
		});

		for(auto const& it : squared_odds) {
			std::cout << it.val() << std::endl;
		}
	}

	// {
	// 	map<string, int> odds;

	// 	numbers.filter_to(odds, [](const string& key, const int& val) -> bool {
	// 		return val % 2 != 0;
	// 	});

	// 	std::cout << "odds:" << std::endl;

	// 	odds.for_each([](const string& key, const int& val) {
	// 		std::cout << key << ": " << val << std::endl;
	// 	});
	// }

	// {
	// 	map<string, int> squares;

	// 	numbers.map_to<int>(squares, [](const string& key, const int& val) -> int {
	// 		return val * val;
	// 	});

	// 	std::cout << "squares:" << std::endl;

	// 	squares.for_each([](const string& key, const int& val) {
	// 		std::cout << key << ": " << val << std::endl;
	// 	});
	// }

	// {
	// 	int sum;

	// 	numbers.reduce_to<int>(sum, [](const int& sum, const string& key, const int& val) -> int {
	// 		return sum + val;
	// 	});

	// 	std::cout << "sum:" << std::endl << sum << std::endl;
	// }
}