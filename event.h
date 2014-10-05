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
	// base_delegate
	///////////////////////////////////////////////////////////////////////////////
	class base_delegate {
	public:
		virtual ~base_delegate() {}
		
	};
	
	template<typename... ArgT> class event;
	
	///////////////////////////////////////////////////////////////////////////////
	// abstract_delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class abstract_delegate : public base_delegate {
	public:
		virtual void execute( ArgT... arg ) = 0;
		
	protected:
		kick::vector<event<ArgT...>*> _e_;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// concrete_delegate
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename... ArgT>
	class concrete_delegate : public abstract_delegate<ArgT...> {
	public:
		concrete_delegate( ObjectT* o, void (ObjectT::*f)(ArgT...), event<ArgT...>* e )
		: _o_( o )
		, _f_( f )
		{
			e->connect( this );
			this->_e_.push_back( e );
		}
		
		virtual void execute( ArgT... a ) {
			return (_o_->*_f_)( a... );
		}
		
	protected:
		ObjectT* _o_;
		void (ObjectT::*_f_)(ArgT...);
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// delegate
	///////////////////////////////////////////////////////////////////////////////
	class delegate {
	public:
		template<typename ObjectT, typename... ArgT>
		void connect( ObjectT* o, void (ObjectT::*f)(ArgT...), event<ArgT...>* e ) {
			_d_.push_back( new concrete_delegate<ObjectT, ArgT...>( o, f, e ) );
		}
		
	protected:
		kick::vector<base_delegate*> _d_;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// event
	///////////////////////////////////////////////////////////////////////////////
	template<typename... ArgT>
	class event {
	public:
		virtual void operator()( ArgT... arg ) {
			for( typename kick::vector<abstract_delegate<ArgT...>*>::iterator it = _d_.begin(); it != _d_.end(); ++it ) {
				(*it)->execute( arg... );
			}
		};
		
		void connect( abstract_delegate<ArgT...>* d ) {
			_d_.push_back( d );
		}
		
		void disconnect( abstract_delegate<ArgT...>& d ) {
			for( typename kick::vector<abstract_delegate<ArgT...> >::iterator it = _d_.begin(); it != _d_.end(); ++it ) {
				if( d == *it ) {
					_d_.erase( it ); break;
				}
			}
		}
		
	private:
		kick::vector<abstract_delegate<ArgT...>*> _d_;
		
	};
	
}

#endif
