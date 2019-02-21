#include <iostream>
#include "../vector.hpp"
#include "../experimental/hof/hof.hpp"

using namespace kick;

int main( int argc, char* argv[] ){
	vector<int> myVector; 
	
	myVector.push_back(100); 
	myVector.push_back(200); 
	myVector.push_back(300); 

	vector<int> newVector = experimental::hof::map<int, int>(myVector, [] (int num) -> int {
		return num / 2;
	});

	for(auto it = newVector.begin(); it != newVector.end(); ++it) {
		std::cout << *it << std::endl; 
	}
	
	// // Access individual items, outputs 100
	// std::cout << myVector[0] << std::endl; 

	// // Iterate by incrementing an index
	// for(int i = 0; i < myVector.size(); ++i) {
	// 	std::cout << myVector[i] << std::endl; 
	// }

	// // Iterate with the vector iterator
	// for(vector<int>::iterator it = myVector.begin(); it != myVector.end(); ++it) {
	// 	std::cout << *it << std::endl; 
	// }
}
