#ifndef _kick_iostream_ios_h
#define _kick_iostream_ios_h

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

// C
#include <stdint.h>

// Kick
#include <kick/common.h>
#include <kick/iostream/streambuf.h>

#ifndef KICK_POLYMORPHIC_STREAM
	#define KICK_POLYMORPHIC_STREAM KICK_POLYMORPHIC_IO
#endif

namespace kick {
	typedef int pos_type;
	typedef	int off_type;
	
	///////////////////////////////////////////////////////////////////////////////
	// basic_streambuf (forward declaration)
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_streambuf;
	
	///////////////////////////////////////////////////////////////////////////////
	// basic_ios
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_ios {
	protected:
		basic_ios();
		basic_ios( basic_streambuf<CharT>* );
		
	public:
#if	(KICK_POLYMORPHIC_STREAM > 0)
		virtual
#endif
		~basic_ios(); 
		
		typedef uint16_t	format_t;
		typedef uint8_t		seqmode_t;
		
		static const format_t boolalpha	= 0x1;
		static const format_t showbase	= 0x2;
		static const format_t showpoint	= 0x4;
		static const format_t showpos	= 0x8;
		static const format_t skipws	= 0x10;
		static const format_t initbuf	= 0x20;
		static const format_t uppercase	= 0x40;
		
		static const seqmode_t in	= 0x0;
		static const seqmode_t out	= 0x1;
		
		format_t& fmt();
		const format_t& fmt() const;
		
		basic_streambuf<CharT>* sbuf();
		const basic_streambuf<CharT>* sbuf() const;
		
	protected:
		format_t _fmt_;
		basic_streambuf<CharT>* _sbuf_;
		
	};

	///////////////////////////////////////////////////////////////////////////////
	// ios
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_ios<char> ios;
	
	///////////////////////////////////////////////////////////////////////////////
	// wios
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_ios<wchar_t> wios;

} // namespace kick

template<typename CharT>
kick::basic_ios<CharT>::basic_ios()
: _fmt_( kick::basic_ios<CharT>::boolalpha )
, _sbuf_( 0 )
{}

template<typename CharT>
kick::basic_ios<CharT>::basic_ios( kick::basic_streambuf<CharT>* sbuf )
: _fmt_( kick::basic_ios<CharT>::boolalpha )
, _sbuf_( sbuf )
{}

template<typename  CharT>
kick::basic_ios<CharT>::~basic_ios() {}

template<typename CharT>
typename kick::basic_ios<CharT>::format_t& kick::basic_ios<CharT>::fmt() {
	return _fmt_;
}

template<typename CharT>
const typename kick::basic_ios<CharT>::format_t& kick::basic_ios<CharT>::fmt() const {
	return _fmt_;
}

template<typename CharT>
kick::basic_streambuf<CharT>* kick::basic_ios<CharT>::sbuf() {
	return _sbuf_;
}

template<typename CharT>
const kick::basic_streambuf<CharT>* kick::basic_ios<CharT>::sbuf() const {
	return _sbuf_;
}

#endif // _kick_iostream_ios_h
