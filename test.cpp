#include <iostream>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	kick::vector<kick::string> myVec;
	
	for( int i = 0; i < 1000; ++i )
		myVec.push_back( "Hello World" );
	
	for( kick::vector<kick::string>::iterator it = myVec.begin(); it != myVec.end(); ++it )
		std::cout << (*it).c_str() << std::endl; 
	

}
