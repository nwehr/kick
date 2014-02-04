#ifndef ARDUINO

#define KICK_POLYMORPHIC_CONTAINERS 1
#define KICK_POLYMORPHIC_IO 1

// C++
#include <iostream>
#include <string>
#include <vector>

// Kick
#include <kick/string.h>
#include <kick/smart_ptr.h>
#include <kick/vector.h>
#include <kick/deque.h>
#include <kick/version.h>
#include <kick/map.h>

#include <kick/algorithm/sort.h>

#include <kick/iostream/stringbuf.h>
#include <kick/iostream/istream.h>

int main( int argc, char* argv[] ) {
	char myBuffer[] = "13.4";
//	float myVal = 0.0;
	
	kick::stringbuf myStringBuf1;
	myStringBuf1.setbuf( myBuffer, 4 );
	
	kick::stringbuf myStringBuf2;
	
	kick::istream myIstream( &myStringBuf1 );
	
	myIstream >> myStringBuf2;
	
	std::cout << myStringBuf2.buf() << std::endl;
		
//	kick::map<kick::string, int> myMap;
//	
//	myMap.insert( kick::pair<kick::string, int>( "sixteen", 16 ) );
//	myMap.insert( kick::pair<kick::string, int>( "two", 2 ) );
//	myMap.insert( kick::pair<kick::string, int>( "one", 1 ) );
//	myMap.insert( kick::pair<kick::string, int>( "seven", 7 ) );
//	myMap.insert( kick::pair<kick::string, int>( "six", 6 ) );
//	myMap.insert( kick::pair<kick::string, int>( "four", 4 ) );
//	myMap.insert( kick::pair<kick::string, int>( "four", 4 ) );
//	myMap.insert( kick::pair<kick::string, int>( "four", 4 ) );
//
//	for( kick::map<kick::string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it )
//		std::cout << (*it).key().c_str() << std::endl;
//	
//	kick::map<int, int> myMap2;
//	
//	myMap2.insert( kick::pair<int, int>( 16, 16 ) );
//	myMap2.insert( kick::pair<int, int>( 2, 2 ) );
//	myMap2.insert( kick::pair<int, int>( 2, 2 ) );
//	myMap2.insert( kick::pair<int, int>( 1, 1 ) );
//	myMap2.insert( kick::pair<int, int>( 7, 7 ) );
//	myMap2.insert( kick::pair<int, int>( 6, 6 ) );
//	myMap2.insert( kick::pair<int, int>( 4, 4 ) );
//	
//	for( kick::map<int, int>::iterator it = myMap2.begin(); it != myMap2.end(); ++it )
//		std::cout << (*it).key() << std::endl;
//	
//	std::vector<kick::shared_ptr<int> > myVec1;
//	
//	myVec1.push_back( kick::shared_ptr<int>( new int( 3 ) ) );
//	myVec1.push_back( kick::shared_ptr<int>( new int( 5 ) ) );
//	myVec1.push_back( kick::shared_ptr<int>( new int( 4 ) ) );
//	myVec1.push_back( kick::shared_ptr<int>( new int( 2 ) ) );
//	
////	kick::algorithm::bubble_sort( myVec1 );
//	
//	for( std::vector<kick::shared_ptr<int> >::const_iterator it = myVec1.begin(); it != myVec1.end(); ++it ) {
//		std::cout << **it << std::endl;
//	}
	
}

#endif // ARDUINO
