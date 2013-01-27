#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::map<kick::string, kick::string> myMap;
	
	myMap.insert( kick::pair<kick::string, kick::string>( "one", "One" ) );
	myMap.insert( kick::pair<kick::string, kick::string>( "two", "Two" ) );
	myMap.insert( kick::pair<kick::string, kick::string>( "three", "Three" ) );
	
	for( kick::map<kick::string, kick::string>::iterator it = myMap.begin(); it != myMap.end(); ++it ){
		kick::pair<kick::string, kick::string> myPair = *it;
		
		std::cout << (*it).val().c_str() << std::endl;
		
	}
	
	return 0;

}
