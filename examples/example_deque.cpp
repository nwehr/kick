#include <iostream>
#include "../deque.hpp"

using namespace kick;

int main( int argc, const char* argv[] ){
	deque<int> myDeque; 

	myDeque.push_back(100); 
	myDeque.push_back(200); 
	myDeque.push_back(300); 

	// Iterate through the deque
	for(deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); ++it) {
		std::cout << *it << std::endl; 
	}
}