#include <iostream>

#include "../string.hpp"
#include "../map.hpp"

using namespace kick;

int main( int argc, const char* argv[] ){
	map<string, int> myMap; 

	// Adding items using insert
	myMap.insert(pair<string, int>("one", 100)); 
	myMap.insert(pair<string, int>("two", 200)); 

	// Adding items using the subscript operator
	myMap["three"] = 300; 
	myMap["four"]  = 400; 

	// Access individual items, outputs 100
	std::cout << myMap["one"] << std::endl; 

	// Iterate through all items in the map
	for(map<string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it) {
		std::cout << (*it).key() << " = " << (*it).val() << std::endl; 
	}
}