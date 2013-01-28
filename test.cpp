#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::vector<int> myVec;
	
	myVec.push_back( 1 );
	myVec.push_back( 2 );
	myVec.push_back( 3 );
	myVec.push_front( 4 );
	myVec.pop_front(); 
	
	for( int i = 0; i < myVec.size(); ++i ){
		std::cout << myVec[i] << std::endl; 
		
	}
	
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
