#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::vector<int> myVec;
	
	myVec.push_back( 1 );
	myVec.push_back( 2 );
	myVec.push_back( 3 );
	
	for( kick::vector<int>::iterator it = myVec.begin(); it != myVec.end(); ++it ){
		std::cout << *it << std::endl;
	}
	
	kick::map<kick::string, kick::string> myMap;
	
	myMap.insert( kick::pair<kick::string, kick::string>( "one", "One" ) );
	myMap.insert( kick::pair<kick::string, kick::string>( "two", "Two" ) );
	myMap.insert( kick::pair<kick::string, kick::string>( "three", "Three" ) );
	
	for( kick::map<kick::string, kick::string>::iterator it = myMap.begin(); it != myMap.end(); ++it ){
		std::cout << (*it).val().c_str() << std::endl;
		
	}

	kick::string myString = "Hello World";
	
	std::cout << myString.size() << std::endl;

	return 0;

}
