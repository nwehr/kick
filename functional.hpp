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
	public:
		function( ReturnT (*)(ArgT...) );
		function<ReturnT, ArgT...>& operator=( const function<ReturnT,ArgT...>& );
		function<ReturnT, ArgT...>& operator=( ReturnT (*)(ArgT...) );
		
		ReturnT operator()( ArgT... );
		
	private:
		ReturnT (*_f_)(ArgT...);
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// mem_fn
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename ReturnT, typename... ArgT>
	class mem_fn {
	public:
		mem_fn( ReturnT (ObjectT::*)(ArgT...) );
		ReturnT operator()( ObjectT&, ArgT... );
		
	private:
		ReturnT (ObjectT::*_f_)(ArgT...);
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// function
///////////////////////////////////////////////////////////////////////////////
template<typename ReturnT, typename... ArgT>
kick::function<ReturnT,ArgT...>::function( ReturnT (*f)(ArgT...) )
: _f_( f )
{}

template<typename ReturnT, typename... ArgT>
kick::function<ReturnT, ArgT...>& kick::function<ReturnT, ArgT...>::operator=( const kick::function<ReturnT,ArgT...>& rhs )
{
	_f_ = rhs._f_;
	return *this;
}

template<typename ReturnT, typename... ArgT>
kick::function<ReturnT, ArgT...>& kick::function<ReturnT, ArgT...>::operator=( ReturnT (*f)(ArgT...) )
{
	_f_ = f;
	return *this;
}

template<typename ReturnT, typename... ArgT>
ReturnT kick::function<ReturnT,ArgT...>::operator()( ArgT... a )
{
	return _f_( a... );
}

///////////////////////////////////////////////////////////////////////////////
// mem_fn
///////////////////////////////////////////////////////////////////////////////
template<typename ObjectT, typename ReturnT, typename... ArgT>
kick::mem_fn<ObjectT,ReturnT,ArgT...>::mem_fn( ReturnT (ObjectT::*f)(ArgT...) )
: _f_( f )
{}

template<typename ObjectT, typename ReturnT, typename... ArgT>
ReturnT kick::mem_fn<ObjectT,ReturnT,ArgT...>::operator()( ObjectT& o, ArgT... a ) {
	return (o.*_f_)( a... );
}

#endif
