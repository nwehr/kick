#ifndef kick_event_h
#define kick_event_h

//
// Copyright 2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "vector.h"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// abstract_delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class abstract_delegate {
	public:
		virtual void execute( const ArgT&... a  );
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename... ArgT>
	class delegate : public abstract_delegate<ArgT...> {
	public:
		delegate( ObjectT* o, void (ObjectT::*f)(ArgT...) );
		virtual void execute( const ArgT&... a );
		
	private:
		ObjectT* _o_;
		void (ObjectT::*_f_)(ArgT...);
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// event
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class event {
	public:
		void operator()( const ArgT&... a );
		void connect( abstract_delegate<ArgT...>* d );
		
	private:
		kick::vector<abstract_delegate<ArgT...>*> _d_;
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// abstract_delegate
///////////////////////////////////////////////////////////////////////////////
template<typename... ArgT>
void kick::abstract_delegate<ArgT...>::execute( const ArgT&... a  ) {}

///////////////////////////////////////////////////////////////////////////////
// delegate
///////////////////////////////////////////////////////////////////////////////
template<typename ObjectT, typename... ArgT>
kick::delegate<ObjectT,ArgT...>::delegate( ObjectT* o, void (ObjectT::*f)(ArgT...) )
: _o_( o )
, _f_( f )
{}

template<typename ObjectT, typename... ArgT>
void kick::delegate<ObjectT,ArgT...>::execute( const ArgT&... a ) {
	(_o_->*_f_)( a... );
}

///////////////////////////////////////////////////////////////////////////////
// event
///////////////////////////////////////////////////////////////////////////////
template<typename... ArgT>
void kick::event<ArgT...>::operator()( const ArgT&... a ) {
	for( typename kick::vector<abstract_delegate<ArgT...>*>::iterator it = _d_.begin(); it != _d_.end(); ++it ) {
		(*it)->execute( a... );
	}
	
}

template<typename... ArgT>
void kick::event<ArgT...>::connect( abstract_delegate<ArgT...>* d ) {
	_d_.push_back( d );
}

#endif
