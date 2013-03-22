#include <time.h>

#include <iostream>
#include <vector>
#include <map>
#include <string>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::map<int, int> myMap; 
	
	myMap.insert( kick::pair<int, int>( 1, 1 ) );
	myMap.insert( kick::pair<int, int>( 5, 5 ) );
	myMap.insert( kick::pair<int, int>( 2, 2 ) );
	myMap.insert( kick::pair<int, int>( 16, 16 ) );
	myMap.insert( kick::pair<int, int>( 6, 6 ) );
	myMap.insert( kick::pair<int, int>( 7, 7 ) );
	
	for( kick::map<int, int>::iterator it = myMap.begin(); it != myMap.end(); ++it )
		std::cout << (*it).val() << std::endl; 

}
