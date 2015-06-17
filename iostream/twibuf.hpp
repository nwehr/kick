#ifndef kick_twibuf_hpp
#define kick_twibuf_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdint.h>

// C++
#include <iostream> // for debugging

// Internal
#include "./streambuf.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_twibuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	
	
	///////////////////////////////////////////////////////////////////////////////
	// basic_twibuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_twibuf : public basic_streambuf<CharT> {
	public:
		
		
	protected:
		int write( const CharT* data ) {
			
		}
		
#ifdef KICK_POLYMORPHIC_STREAMBUF
		virtual
#endif
		int sync() {
			if( !_buf ) {
				return sync_ok;
			}
			
			return write( _buf );
			
		}
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// twibuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_twibuf<unsigned char> twibuf;
	
}

#endif
