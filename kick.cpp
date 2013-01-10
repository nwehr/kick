#include <iostream>
#include "kick.h"

int main( int argc, char* argv[] ){
	kick::map<int, int> myMap;
	
	myMap.insert( kick::pair<int, int>( 3, 4 ) );
	
	std::cout << myMap[3] << std::endl;
	
	return 0;

}
