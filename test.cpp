#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::deque<int> myDeque;
	
	myDeque.push_back( 100 );
	myDeque.push_back( 200 );
	myDeque.push_back( 300 );
	
	for( kick::deque<int>::iterator it = myDeque.begin(); it != myDeque.end(); ++it )
		std::cout << *it << std::endl; 

	return 0;

}
