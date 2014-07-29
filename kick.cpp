#ifndef ARDUINO

#define KICK_POLYMORPHIC_CONTAINERS 1
#define KICK_POLYMORPHIC_IO 1

// C++
#include <iostream>
#include <string>
#include <vector>

// Kick
#include <lib.kick/string.h>
#include <lib.kick/smart_ptr.h>
#include <lib.kick/vector.h>
#include <lib.kick/deque.h>
#include <lib.kick/version.h>
#include <lib.kick/map.h>

#include <lib.kick/algorithm/sort.h>

#include <lib.kick/iostream/stringbuf.h>
#include <lib.kick/iostream/istream.h>

int main( int argc, char* argv[] ) {
	kick::vector<kick::string> MyVector;
	
	MyVector.push_back( "three" );
	MyVector.push_back( "two" );
	MyVector.push_back( "one" );
	
	for( kick::vector<kick::string>::iterator it = MyVector.begin(); it != MyVector.end(); ++it ) {
		std::cout << *it << std::endl;
	}
	
	
}

#endif // ARDUINO
