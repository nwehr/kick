#ifndef ARDUINO

// C
#include <time.h>

// C++
#include <iostream>

#define KICK_POLYMORPHIC_CONTAINERS 0

// Kick
#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::shared_ptr<kick::string> myInt( new kick::string( "Hello, World!" ) );
	kick::shared_ptr<kick::string> myInt2 = myInt;
	
	std::cout << myInt.refs() << std::endl;
	std::cout << myInt->c_str() << std::endl;
	
// 	kick::vector<int> myVec;
// 	
// 	myVec.push_back( 1 );
// 	myVec.push_back( 2 );
// 	myVec.push_back( 3 );
// 	myVec.push_back( 4 );
// 	myVec.push_back( 5 );
// 	myVec.push_back( 6 );
// 	myVec.push_back( 7 );
// 	myVec.push_back( 8 );
// 	
// 	for( kick::vector<int>::iterator it = myVec.begin(); it != myVec.end(); ++it )
// 		std::cout << *it << std::endl;
// 	
// 	kick::vector<kick::string> myVec2;
// 	
// 	myVec2.push_back( "one" );
// 	myVec2.push_back( "two" );
// 	myVec2.push_back( "three" );
// 	myVec2.push_back( "four" );
// 	myVec2.push_back( "five" );
// 	myVec2.push_back( "six" );
// 	myVec2.push_back( "seven" );
// 	myVec2.push_back( "eight" );
// 	
// 	for( kick::vector<kick::string>::iterator it = myVec2.begin(); it != myVec2.end(); ++it )
// 		std::cout << (*it).c_str() << std::endl;
//	
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
//	
//	kick::map<int, int> myMap2;
//	
//	myMap2.insert( kick::pair<int, int>( 16, 16 ) );
//	myMap2.insert( kick::pair<int, int>( 2, 2 ) );
//	myMap2.insert( kick::pair<int, int>( 1, 1 ) );
//	myMap2.insert( kick::pair<int, int>( 7, 7 ) );
//	myMap2.insert( kick::pair<int, int>( 6, 6 ) );
//	myMap2.insert( kick::pair<int, int>( 4, 4 ) );
//	
//	for( kick::map<int, int>::iterator it = myMap2.begin(); it != myMap2.end(); ++it )
//		std::cout << (*it).key() << std::endl;

}

#endif // ARDUINO
