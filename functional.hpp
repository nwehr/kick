#ifndef kick_functional_h
#define kick_functional_h

//
// Copyright 2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// function
	///////////////////////////////////////////////////////////////////////////////
	template<typename ReturnT, typename... ArgT>
	class function {
		function();
		
	public:
		function( ReturnT (*)(ArgT...) );
		function( const function<ReturnT, ArgT...>& );
		
		function<ReturnT, ArgT...>& operator=( ReturnT (*)(ArgT...) );
		function<ReturnT, ArgT...>& operator=( const function<ReturnT,ArgT...>& );
		
		ReturnT operator()( ArgT... );
		
	protected:
		ReturnT (*_f)(ArgT...);
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// mem_fn
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename ReturnT, typename... ArgT>
	class mem_fn {
		mem_fn();
		
	public:
		mem_fn( ReturnT (ObjectT::*)(ArgT...) );
		mem_fn( const mem_fn<ObjectT, ReturnT, ArgT...>& );
		
		mem_fn<ObjectT, ReturnT, ArgT...>& operator=( ReturnT (ObjectT::*)(ArgT...) );
		mem_fn<ObjectT, ReturnT, ArgT...>& operator=( const mem_fn<ObjectT, ReturnT, ArgT...>& );
		
		ReturnT operator()( ObjectT&, ArgT... );
		
	protected:
		ReturnT (ObjectT::*_f)(ArgT...);
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// function
///////////////////////////////////////////////////////////////////////////////
template<typename ReturnT, typename... ArgT>
kick::function<ReturnT,ArgT...>::function( ReturnT (*f)(ArgT...) )
: _f( f )
{}

template<typename ReturnT, typename... ArgT>
kick::function<ReturnT,ArgT...>::function( const kick::function<ReturnT, ArgT...>& f )
: _f( f._f )
{}

template<typename ReturnT, typename... ArgT>
kick::function<ReturnT, ArgT...>& kick::function<ReturnT, ArgT...>::operator=( ReturnT (*f)(ArgT...) )
{
	_f = f;
	return *this;
}

template<typename ReturnT, typename... ArgT>
kick::function<ReturnT, ArgT...>& kick::function<ReturnT, ArgT...>::operator=( const kick::function<ReturnT,ArgT...>& rhs )
{
	_f = rhs._f;
	return *this;
}

template<typename ReturnT, typename... ArgT>
ReturnT kick::function<ReturnT,ArgT...>::operator()( ArgT... a )
{
	return _f( a... );
}

///////////////////////////////////////////////////////////////////////////////
// mem_fn
///////////////////////////////////////////////////////////////////////////////
template<typename ObjectT, typename ReturnT, typename... ArgT>
kick::mem_fn<ObjectT,ReturnT,ArgT...>::mem_fn( ReturnT (ObjectT::*f)(ArgT...) )
: _f( f )
{}

template<typename ObjectT, typename ReturnT, typename... ArgT>
kick::mem_fn<ObjectT,ReturnT,ArgT...>::mem_fn( const mem_fn<ObjectT, ReturnT, ArgT...>& f )
: _f( f._f )
{}

template<typename ObjectT, typename ReturnT, typename... ArgT>
ReturnT kick::mem_fn<ObjectT,ReturnT,ArgT...>::operator()( ObjectT& o, ArgT... a ) {
	return (o.*_f)( a... );
}

template<typename ObjectT, typename ReturnT, typename... ArgT>
kick::mem_fn<ObjectT, ReturnT, ArgT...>& kick::mem_fn<ObjectT, ReturnT, ArgT...>::operator=( ReturnT (ObjectT::*f)(ArgT...) ) {
	_f = f;
	return *this;
}

template<typename ObjectT, typename ReturnT, typename... ArgT>
kick::mem_fn<ObjectT, ReturnT, ArgT...>& kick::mem_fn<ObjectT, ReturnT, ArgT...>::operator=( const mem_fn<ObjectT, ReturnT, ArgT...>& f ) {
	_f = f._f;
	return *this;
}

#endif
