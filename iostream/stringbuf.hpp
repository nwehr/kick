#ifndef _kick_iostream_stringbuf_h
#define _kick_iostream_stringbuf_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "../string.hpp"
#include "./streambuf.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_stringbuf : basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT, typename StringT = basic_string<CharT> >
	class basic_stringbuf : public basic_streambuf<CharT> {
	public:
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		~basic_stringbuf();

		inline StringT str();
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// stringbuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_stringbuf<char, basic_string<char> > stringbuf;
	
	///////////////////////////////////////////////////////////////////////////////
	// wstringbuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_stringbuf<wchar_t, basic_string<wchar_t> > wstringbuf;
	
} // namespace kick

template<typename CharT, typename StringT>
kick::basic_stringbuf<CharT, StringT>::~basic_stringbuf() {}

template<typename CharT, typename StringT>
StringT kick::basic_stringbuf<CharT, StringT>::str() {
	return StringT( this->_buf_ );
}

#endif // _kick_iostream_stringbuf_h
