#ifndef _kick_iostream_ostream_h
#define _kick_iostream_ostream_h

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
#include <kick/iostream/ios.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_ostream : basic_ios
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_ostream : public virtual basic_ios<CharT> {
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// ostream
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_ostream<char> ostream;
	
	///////////////////////////////////////////////////////////////////////////////
	// wostream
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_ostream<wchar_t> wostream; 
	
} // namespace kick

#endif // _kick_iostream_ostream_h
