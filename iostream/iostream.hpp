#ifndef kick_iostream_hpp
#define kick_iostream_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "./istream.hpp"
#include "./ostream.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_iostream : basic_istream, basic_ostream
	///////////////////////////////////////////////////////////////////////////////
	template <typename CharT>
	class basic_iostream : public basic_istream<CharT>, public basic_ostream<CharT> {
	public:
		
	protected:
		
	};
}

#endif
