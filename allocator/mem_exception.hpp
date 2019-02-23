#ifndef kick_mem_exception_hpp
#define kick_mem_exception_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "../exception.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// malloc_exception
	///////////////////////////////////////////////////////////////////////////////
	class malloc_exception : public exception {
	public:
		malloc_exception() : exception() {}
		const char* what() const { return "Unable to allocate new memory."; }
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// move_exception
	///////////////////////////////////////////////////////////////////////////////
	class move_exception : public exception {
	public:
		explicit move_exception( void* adx )
		: exception()
		, _msg( new char[50] )
		{
			sprintf( _msg, "Unable to move memory block to %02lux", reinterpret_cast<unsigned long>( adx ) );
		}

		~move_exception() { delete[] _msg; }
		const char* what() const { return _msg; }
		
	private:
		char* _msg;
	};
}

#endif
