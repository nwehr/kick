#include <iostream>
#include "kick.h"

int main( int argc, char* argv[] ){
	kick::string Str1( "Hello World!" );
	kick::string Str2( "What?" );
	
	Str2 = Str1;

//	std::cout << "kick" << std::endl;
//	std::cout << myString.size() << std::endl;
	
	std::cout << Str2.c_str() << std::endl;
	
	return 0;

}
