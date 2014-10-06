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

//#include <lib.kick/event.h>
	
namespace kick {
	template<typename... ArgT>
	class abstract_delegate {
	public:
		virtual void execute( const ArgT&... a  ) {}
	};
	
	template<typename ObjectT, typename... ArgT>
	class delegate : public abstract_delegate<ArgT...> {
	public:
		delegate( ObjectT* o, void (ObjectT::*f)(ArgT...) )
		: _o_( o )
		, _f_( f )
		{}
		
		virtual void execute( const ArgT&... a ) {
			(_o_->*_f_)( a... );
		}
		
	private:
		ObjectT* _o_;
		void (ObjectT::*_f_)(ArgT...);
	};
	
	template<typename... ArgT>
	class event {
	public:
		void operator()( const ArgT&... a ) {
			for( typename kick::vector<abstract_delegate<ArgT...>*>::iterator it = _d_.begin(); it != _d_.end(); ++it ) {
				(*it)->execute( a... );
			}
			
		}
		
		void connect( abstract_delegate<ArgT...>* d ) {
			_d_.push_back( d );
		}
		
	private:
		kick::vector<abstract_delegate<ArgT...>*> _d_;
	};
	
}

class A {
public:
	kick::event<>& Event() { return m_Event; }
private:
	kick::event<> m_Event;
};

class B {
public:
	B ()
	: m_Delegate( this, &B::Print )
	{}
	
	void Print() {
		std::cout << "B::Print()" << std::endl;
	}
	
	kick::delegate<B>& Delegate() { return m_Delegate; }
	
private:
	kick::delegate<B> m_Delegate;
};

int main( int argc, char* argv[] ) {
	std::cout << "kick version: " << KICK_VERSION_MAJOR << "." << KICK_VERSION_MINOR << "." << KICK_VERSION_PATCH << std::endl;
	
	A MyA;
	B MyB;
	
	MyA.Event().connect( &MyB.Delegate() );
	
	MyA.Event()();
	
}

#endif // ARDUINO
