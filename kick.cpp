#ifndef ARDUINO

// #define KICK_POLYMORPHIC 1

// C++
#include <iostream>
#include <string>
#include <vector>

// Kick
//#include <lib.kick/string.h>
//#include <lib.kick/smart_ptr.h>
//#include <lib.kick/vector.h>
//#include <lib.kick/deque.h>
//#include <lib.kick/version.h>
//#include <lib.kick/map.h>

//#include <lib.kick/algorithm/sort.h>
//
//#include <lib.kick/iostream/stringbuf.h>
//#include <lib.kick/iostream/istream.h>
//
//#include <lib.kick/optional.h>

#include <lib.kick/event.hpp>
#include <lib.kick/vector.hpp>
#include <lib.kick/map.hpp>
#include <lib.kick/string.hpp>


// #include <lib.kick/bitset.h>

//class A {
//public:
//	void Trigger() {
//		Event();
//	}
//	
//	void Trigger2() {
//		Event2();
//	}
//	
//	kick::event<> Event;
//	kick::event<> Event2;
//};
//
//class B {
//public:
//	void Print() { std::cout << "Hello, World!" << std::endl; }
//	void Print2() { std::cout << "Hello, World! (2)" << std::endl; }
//	
//	kick::delegate Delegate;
//};

int main( int argc, char* argv[] ) {
//	A MyA;
//	B MyB;
//	
//	MyB.Delegate.connect( &MyB, &B::Print, &MyA.Event );
//	MyB.Delegate.connect( &MyB, &B::Print2, &MyA.Event );
//	
//	MyA.Trigger();
	
	kick::vector<int> V;
	
	V.push_back( 1 );
	V.push_back( 2 );
	V.push_back( 3 );
	V.push_back( 4 );
	V.push_back( 5 );
	V.push_back( 6 );
	
	for( int i = 0; i < V.size(); ++i ) {
		std::cout << V[i] << std::endl; 
	}
	
	kick::map<kick::string, int> M;
	
	M["one"] = 1;
	M["two"] = 2;
	M["three"] = 3;
	
	for( kick::map<kick::string, int>::iterator it = M.begin(); it != M.end(); ++it ) {
		std::cout << (*it).key() << " = " << (*it).val() << std::endl;
	}
	
}

#endif // ARDUINO
