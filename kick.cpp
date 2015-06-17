#ifndef ARDUINO

// #define KICK_POLYMORPHIC 1

#include <iostream>

// C++
#include "iostream/ostream.hpp"
#include "iostream/stringbuf.hpp"

int main (int argc, char* argv[]) {
	char* s = new char[16]();
	
	
	kick::streambuf buf;
	
	buf.setbuf(s, 16);
	
	std::cout << (buf.sputn("a\nb\nc", 6) == kick::stringbuf::buf_eof) << std::endl;
	
	std::cout << s << std::endl;
	
	delete[] s;
	
	return 0;
	
}

#endif // ARDUINO
