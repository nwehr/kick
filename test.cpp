// C++
#include <iostream>

// Kick
#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::map<kick::string, int> myMap; 
	
	myMap.insert( kick::pair<kick::string, int>( "one", 1 ) );
	myMap.insert( kick::pair<kick::string, int>( "five", 5 ) );
	myMap.insert( kick::pair<kick::string, int>( "two", 2 ) );
	myMap.insert( kick::pair<kick::string, int>( "sixteen", 16 ) );
	myMap.insert( kick::pair<kick::string, int>( "six", 6 ) );
	myMap.insert( kick::pair<kick::string, int>( "seven", 7 ) );
	
	for( kick::map<kick::string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it )
		std::cout << (*it).val() << std::endl; 

}
