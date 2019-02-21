#ifndef kick_i2cbuf_hpp
#define kick_i2cbuf_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdint.h>

// Internal
#include "./streambuf.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// i2cbuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	class i2cbuf : public basic_streambuf<uint8_t> {
	public:
		
	protected:
		
	};
}

#endif
