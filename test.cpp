#include <time.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <kick/kick.h>


class c {
public:
	c( const std::string& s ) {

	}

	~c() {
	
	}
};

int main( int argc, char* argv[] ){
	kick::map<kick::string, int> myMap;

	char t[100];
	c O( static_cast<std::string>( t ) );
	
	myMap.insert( kick::pair<kick::string, int>( "one", 100 ) );
	myMap.insert( kick::pair<kick::string, int>( "two", 200 ) );
	myMap.insert( kick::pair<kick::string, int>( "three", 300 ) );
	myMap.insert( kick::pair<kick::string, int>( "four", 400 ) );
	
	myMap.insert( kick::pair<kick::string, int>( "two", 500 ) );
	
	for( kick::map<kick::string, int>::iterator it = myMap.begin(); it != myMap.end(); ++it )
		std::cout<< (*it).key().c_str() << " - " << (*it).val() << std::endl;
	
	
}
