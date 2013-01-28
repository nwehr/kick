#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::vector<int> myVec;
	
	myVec.push_back( 100 );
	myVec.push_back( 200 );
	myVec.push_back( 300 );
	
	for( kick::vector<int>::iterator it = myVec.begin(); it != myVec.end(); ++it )
		std::cout << *it << std::endl;
	

}
