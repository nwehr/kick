#ifndef _kick_iostream_stringbuf_h
#define _kick_iostream_stringbuf_h

//
//      Copyright 2014 Nathan Wehr. All Rights Reserved.
//
//      Redistribution and use in source and binary forms, with or without modification, are
//      permitted provided that the following conditions are met:
//
//              1. Redistributions of source code must retain the above copyright notice, this list of
//              conditions and the following disclaimer.
//
//              2. Redistributions in binary form must reproduce the above copyright notice, this list
//              of conditions and the following disclaimer in the documentation and/or other materials
//              provided with the distribution.
//
//      THIS SOFTWARE IS PROVIDED BY NATHAN WEHR ''AS IS'' AND ANY EXPRESS OR IMPLIED
//      WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//      FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NATHAN WEHR OR
//      CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//      CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//      SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//      ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//      NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//      ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//      The views and conclusions contained in the software and documentation are those of the
//      authors and should not be interpreted as representing official policies, either expressed
//      or implied, of Nathan Wehr.
//

// Kick
#include <kick/iostream/streambuf.h>
#include <kick/string.h>

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

#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		StringT str();
		
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
