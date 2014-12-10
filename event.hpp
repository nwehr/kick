#ifndef kick_event_h
#define kick_event_h

//
// Copyright 2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "./functional.hpp"
#include "./vector.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// base_delegate
	///////////////////////////////////////////////////////////////////////////////
	class base_delegate {
	public:
		virtual ~base_delegate();
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// abstract_delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class abstract_delegate : public base_delegate {
	public:
		virtual ~abstract_delegate();
		virtual void execute( const ArgT&... a  );
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// concrete_delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename... ArgT>
	class concrete_delegate : public abstract_delegate<ArgT...> {
	public:
		concrete_delegate( ObjectT* o, const mem_fn<ObjectT, void, ArgT...>& f );
		virtual ~concrete_delegate();
		
		virtual void execute( const ArgT&... a );
		
	private:
		ObjectT* _o;
		mem_fn<ObjectT, void, ArgT...> _f;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// event
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class event {
	public:
		void operator()( const ArgT&... a );
		
		void connect( abstract_delegate<ArgT...>* d );
		void disconnect( abstract_delegate<ArgT...>* d );
		
	private:
		vector<abstract_delegate<ArgT...>*> _d;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// delegate
	///////////////////////////////////////////////////////////////////////////////
	class delegate {
	public:
		~delegate();
		
		template<typename ObjectT, typename... ArgT>
		void connect( ObjectT* o, void (ObjectT::*f)(ArgT...), event<ArgT...>* e );
		
	private:
		vector<base_delegate*> _d;
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// base_delegate
///////////////////////////////////////////////////////////////////////////////
kick::base_delegate::~base_delegate() {}

///////////////////////////////////////////////////////////////////////////////
// abstract_delegate
///////////////////////////////////////////////////////////////////////////////
template<typename... ArgT>
kick::abstract_delegate<ArgT...>::~abstract_delegate() {}

template<typename... ArgT>
void kick::abstract_delegate<ArgT...>::execute( const ArgT&... a  ) {}

///////////////////////////////////////////////////////////////////////////////
// concrete_delegate
///////////////////////////////////////////////////////////////////////////////
template<typename ObjectT, typename... ArgT>
kick::concrete_delegate<ObjectT,ArgT...>::concrete_delegate( ObjectT* o, const mem_fn<ObjectT, void, ArgT...>& f )
: _o( o )
, _f( f )
{}

template<typename ObjectT, typename... ArgT>
kick::concrete_delegate<ObjectT,ArgT...>::~concrete_delegate() {}

template<typename ObjectT, typename... ArgT>
void kick::concrete_delegate<ObjectT,ArgT...>::execute( const ArgT&... a ) {
	_f( *_o, a... );
}

///////////////////////////////////////////////////////////////////////////////
// event
///////////////////////////////////////////////////////////////////////////////
template<typename... ArgT>
void kick::event<ArgT...>::operator()( const ArgT&... a ) {
	for( typename vector<abstract_delegate<ArgT...>*>::iterator it = _d.begin(); it != _d.end(); ++it ) {
		(*it)->execute( a... );
	}
}

template<typename... ArgT>
void kick::event<ArgT...>::connect( abstract_delegate<ArgT...>* d ) {
	_d.push_back( d );
}

template<typename... ArgT>
void kick::event<ArgT...>::disconnect( abstract_delegate<ArgT...>* d ) {
	for( typename vector<abstract_delegate<ArgT...>*>::iterator it = _d.begin(); it != _d.end(); ++it ) {
		if( d == (*it) ) {
			_d.erase( it ); break;
		}
	}
}

///////////////////////////////////////////////////////////////////////////////
// delegate
///////////////////////////////////////////////////////////////////////////////
kick::delegate::~delegate() {
	for( vector<base_delegate*>::iterator it = _d.end(); it != _d.begin(); --it ) {
		delete (*it);
	}
}

template<typename ObjectT, typename... ArgT>
void kick::delegate::connect( ObjectT* o, void (ObjectT::*f)(ArgT...), event<ArgT...>* e ) {
	concrete_delegate<ObjectT, ArgT...>* d = new concrete_delegate<ObjectT, ArgT...>( o, mem_fn<ObjectT, void, ArgT...>( f ) );
	
	e->connect( d );
	
	_d.push_back( d );
	
}

#endif
