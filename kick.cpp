#ifndef ARDUINO

// #define KICK_POLYMORPHIC 1

// C++
#include <iostream>
#include <string>
#include <vector>

// Kick
#include <lib.kick/string.h>
#include <lib.kick/smart_ptr.h>
#include <lib.kick/vector.h>
#include <lib.kick/deque.h>
#include <lib.kick/version.h>
#include <lib.kick/map.h>

#include <lib.kick/algorithm/sort.h>

#include <lib.kick/iostream/stringbuf.h>
#include <lib.kick/iostream/istream.h>

#include <lib.kick/optional.h>

#include <lib.kick/event.h>
	
class A {
public:
	void Trigger() {
		m_Event();
	}
	
	kick::event<>& Event() {
		return m_Event;
	}
	
private:
	kick::event<> m_Event;
	
};

class B {
public:
	B() {}
	
	void Print() {
		std::cout << "B::Print()" << std::endl;
	}
	
	kick::delegate& Delegate() {
		return m_Delegate;
	}
	
private:
	kick::delegate m_Delegate;
	
};

int main( int argc, char* argv[] ) {
	std::cout << "kick version: " << KICK_VERSION_MAJOR << "." << KICK_VERSION_MINOR << "." << KICK_VERSION_PATCH << std::endl;
	
	A MyA;
	B MyB;

	MyB.Delegate().connect( &MyB, &B::Print, &MyA.Event() );
	
	MyA.Trigger();
	
}

#endif // ARDUINO
