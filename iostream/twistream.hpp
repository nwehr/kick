#ifndef kick_i2cstream_hpp
#define kick_i2cstream_hpp

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
#include "./iostream.hpp"
#include "./i2cbuf.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// otwistream : basic_ostream
	///////////////////////////////////////////////////////////////////////////////
	class otwistream : public basic_ostream<uint8_t> {
	public:
		otwistream()
		: basic_ostream()
		{
//			_buf->setbuf( new )
		}
		
		~oi2cstream() {}
		
	private:
		
	};
}

#endif
