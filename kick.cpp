#include <iostream>
#include "kick.h"

int _strlen_( const char* cstr ){
	int size = 0;
	
	while( true ){
		if( cstr[size] ) ++size;
		else break;
		
	}
	
	return size; 
	
}

int main( int argc, char* argv[] ){
	kick::string Str1( "Hello World!" );
	kick::string Str2( "What?" );
	
	Str2 = Str1;

//	std::cout << "kick" << std::endl;
//	std::cout << myString.size() << std::endl;
	
	std::cout << Str2.c_str() << std::endl;
	
	return 0;

}
