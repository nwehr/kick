#ifndef _kick_exception_h
#define _kick_exception_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Kick
#include "./common.hpp"

#ifndef KICK_POLYMORPHIC_EXCEPTION
#define KICK_POLYMORPHIC_EXCEPTION KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// exception
	///////////////////////////////////////////////////////////////////////////////
	class exception {
	protected:
		exception() {}
		
	public:
#if	(KICK_POLYMORPHIC_EXCEPTION > 0)
		virtual
#endif
		~exception() {}

#if	(KICK_POLYMORPHIC_EXCEPTION > 0)
		virtual
#endif
		const char* what() const;
		
	};
	
} // namespace kick

#endif // _kick_exception_h
