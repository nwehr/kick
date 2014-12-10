#ifndef _kick_config_h
#define _kick_config_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	typedef int size_type;
	typedef int pos_type;
	
	typedef unsigned int size_t;
}

#ifndef KICK_EXCEPTION
#define KICK_EXCEPTION 1
#endif

#ifndef KICK_POLYMORPHIC
#define KICK_POLYMORPHIC 1
#endif

#ifndef KICK_POLYMORPHIC_CONTAINERS
#define KICK_POLYMORPHIC_CONTAINERS KICK_POLYMORPHIC
#endif

#ifndef KICK_POLYMORPHIC_IO
#define KICK_POLYMORPHIC_IO KICK_POLYMORPHIC
#endif

#ifndef KICK_OPERATOR_NEW
#define KICK_OPERATOR_NEW 0
#endif

#if (KICK_OPERATOR_NEW > 0)
#include <stdlib.h>
#include "./allocator/mem_exception.hpp"

///////////////////////////////////////////////////////////////////////////////
// new
///////////////////////////////////////////////////////////////////////////////
void* operator new( kick::size_t size ) {
	void* ptr = malloc( size );
	
	if( ptr ) {
		return ptr;
	}
	
#if (KICK_EXCEPTION > 0)
	throw kick::malloc_exception();
#endif
	
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// placement new
///////////////////////////////////////////////////////////////////////////////
void* operator new( kick::size_t size, void* p ) {
	if( p ) {
		void* ptr = realloc( p, size );
		
		if( ptr ) {
			return ptr;
		}
	}
	
#if (KICK_EXCEPTION > 0)
	throw kick::malloc_exception();
#endif
	
	return NULL;
}

///////////////////////////////////////////////////////////////////////////////
// delete
///////////////////////////////////////////////////////////////////////////////
void operator delete( void* p ) {
	if( p ) {
		free( p );
	}
}

#endif

#endif // _kick_config_h
