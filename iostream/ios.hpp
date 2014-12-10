#ifndef _kick_iostream_ios_h
#define _kick_iostream_ios_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdint.h>

// Kick
#include "../common.hpp"
#include "./streambuf.hpp"

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
		
		typedef uint16_t fmt_t;
		
		static const fmt_t boolalpha	= 0x1;
		static const fmt_t showbase		= 0x2;
		static const fmt_t showpoint	= 0x4;
		static const fmt_t showpos		= 0x8;
		static const fmt_t skipws		= 0x10;
		static const fmt_t initbuf		= 0x20;
		static const fmt_t uppercase	= 0x40;
		
		inline fmt_t& fmt();
		inline const fmt_t& fmt() const;
		
		inline basic_streambuf<CharT>* sbuf();
		inline const basic_streambuf<CharT>* sbuf() const;
		
	protected:
		fmt_t _fmt;
		basic_streambuf<CharT>* _sbuf;
		
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
: _fmt( kick::basic_ios<CharT>::boolalpha )
, _sbuf( 0 )
{}

template<typename CharT>
kick::basic_ios<CharT>::basic_ios( kick::basic_streambuf<CharT>* sbuf )
: _fmt( kick::basic_ios<CharT>::boolalpha )
, _sbuf( sbuf )
{}

template<typename  CharT>
kick::basic_ios<CharT>::~basic_ios() {}

template<typename CharT>
typename kick::basic_ios<CharT>::fmt_t& kick::basic_ios<CharT>::fmt() {
	return _fmt;
}

template<typename CharT>
const typename kick::basic_ios<CharT>::fmt_t& kick::basic_ios<CharT>::fmt() const {
	return _fmt;
}

template<typename CharT>
kick::basic_streambuf<CharT>* kick::basic_ios<CharT>::sbuf() {
	return _sbuf;
}

template<typename CharT>
const kick::basic_streambuf<CharT>* kick::basic_ios<CharT>::sbuf() const {
	return _sbuf;
}

#endif // _kick_iostream_ios_h
