#ifndef ARDUINO

//#define KICK_POLYMORPHIC_CONTAINERS 0

// C++
#include <iostream>
#include <string>

// Kick
#include <kick/string.h>
#include <kick/smart_ptr.h>
#include <kick/vector.h>
#include <kick/deque.h>
#include <kick/map.h>

int main( int argc, char* argv[] ){
	kick::map<std::string, int> myMap;
	
	myMap.insert( kick::pair<std::string, int>( "sixteen", 16 ) );
	myMap.insert( kick::pair<std::string, int>( "two", 2 ) );
	myMap.insert( kick::pair<std::string, int>( "one", 1 ) );
	myMap.insert( kick::pair<std::string, int>( "seven", 7 ) );
	myMap.insert( kick::pair<std::string, int>( "six", 6 ) );
	myMap.insert( kick::pair<std::string, int>( "four", 4 ) );
	myMap.insert( kick::pair<std::string, int>( "four", 4 ) );
	myMap.insert( kick::pair<std::string, int>( "four", 4 ) );

	for( kick::map<std::string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it )
		std::cout << (*it).key() << std::endl;
	
	kick::map<int, int> myMap2;
	
	myMap2.insert( kick::pair<int, int>( 16, 16 ) );
	myMap2.insert( kick::pair<int, int>( 2, 2 ) );
	myMap2.insert( kick::pair<int, int>( 2, 2 ) );
	myMap2.insert( kick::pair<int, int>( 1, 1 ) );
	myMap2.insert( kick::pair<int, int>( 7, 7 ) );
	myMap2.insert( kick::pair<int, int>( 6, 6 ) );
	myMap2.insert( kick::pair<int, int>( 4, 4 ) );
	
	for( kick::map<int, int>::iterator it = myMap2.begin(); it != myMap2.end(); ++it )
		std::cout << (*it).key() << std::endl;

}

#endif // ARDUINO
