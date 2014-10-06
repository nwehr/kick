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
		function( ReturnT (*f)(ArgT...) );
		ReturnT operator()( ArgT... a );
		
	private:
		ReturnT (*_f_)(ArgT...);
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// mem_fn
	///////////////////////////////////////////////////////////////////////////////
	template<typename ObjectT, typename ReturnT, typename... ArgT>
	class mem_fn {
	public:
		mem_fn( ReturnT (ObjectT::*f)(ArgT...) );
		ReturnT operator()( ObjectT& o, ArgT... a );
		
	private:
		ReturnT (ObjectT::*_f_)(ArgT...);
		
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// function
///////////////////////////////////////////////////////////////////////////////
kick::function<ReturnT,ArgT...>::function( ReturnT (*f)(ArgT...) )
: _f_( f )
{}

ReturnT kick::function<ReturnT,ArgT...>::operator()( ArgT... a ) {
	return _f_( a... );
}

///////////////////////////////////////////////////////////////////////////////
// mem_fn
///////////////////////////////////////////////////////////////////////////////
kick::mem_fn<ObjectT,ReturnT,ArgT...>::mem_fn( ReturnT (ObjectT::*f)(ArgT...) )
: _f_( f )
{}

ReturnT kick::mem_fn<ObjectT,ReturnT,ArgT...>::operator()( ObjectT& o, ArgT... a ) {
	return (o.*_f_)( a... );
}

#endif
