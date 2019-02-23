#include <iostream>
#include "../either.hpp"

using namespace kick;

int main( int argc, char* argv[] ){
	left<bool, int>(true)
	.if_left([](bool result) {
		std::cout << "returned left" << std::endl;
	})
	.if_right([](int result) {
		std::cout << "returned right" << std::endl;
	});

	right<bool, int>(10)
	.if_left([](bool result) {
		std::cout << "returned left" << std::endl;
	})
	.if_right([](int result) {
		std::cout << "returned right" << std::endl;
	});

}
