#include <iostream>
#include <string>
#include "../experimental/either.hpp"
#include "../optional.hpp"
#include "../string.hpp"

using namespace kick;

int main( int argc, char* argv[] ) {
	optional<std::string> message("Hello, World!");
	
	message.get_safe()
	.map_left([](const std::string& msg) {
		std::cout << msg << std::endl;
	})
	.map_right([](const optional_error& err) {
		std::cout << err.what << std::endl;
	});
}
