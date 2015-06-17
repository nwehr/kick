#ifndef _kick_iostream_streambuf_h
#define _kick_iostream_streambuf_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <string.h>

// Kick
#include "../common.hpp"
#include "./ios.hpp"

#ifndef KICK_POLYMORPHIC_STREAMBUF
	#define KICK_POLYMORPHIC_STREAMBUF KICK_POLYMORPHIC_IO
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_streambuf
	///////////////////////////////////////////////////////////////////////////////
	template <typename CharT>
	class basic_streambuf {
	public:
		static const int_type sync_ok		= 0x0;
		static const int_type sync_error	= 0x1;
		static const int_type sync_impl		= 0x2;
		
		static const int_type buf_ok	= 0x0;
		static const int_type buf_eof	= 0x1;
		
	public:
		basic_streambuf();
		basic_streambuf( const basic_streambuf& );
		
#ifdef KICK_POLYMORPHIC_STREAMBUF
		virtual
#endif
		~basic_streambuf();
		
		inline int_type sgetc();
		inline int_type sbumpc();
		inline int_type snextc();
		
		inline int_type sputc( CharT c );
		inline int_type sputn( const CharT* s, size_t n );
		
		inline pos_type ipos();
		inline pos_type ipos_beg();
		inline pos_type ipos_end();
	
		inline pos_type opos();
		inline pos_type opos_beg();
		inline pos_type opos_end();
		
		inline pos_type iseekpos( pos_type );
		inline pos_type oseekpos( pos_type );
		
		inline CharT* buf();
		inline const CharT* buf() const;

		basic_streambuf<CharT>* setbuf( CharT*, size_t );
		
		int pubsync();
		
	protected:
#ifdef KICK_POLYMORPHIC_STREAMBUF
		virtual
#endif
		int sync();

#ifdef KICK_POLYMORPHIC_STREAMBUF
		virtual
#endif
		int overflow();

#ifdef KICK_POLYMORPHIC_STREAMBUF
		virtual
#endif
		int underflow();
		
	protected:
		pos_type _ipos;
		pos_type _ipos_beg;
		pos_type _ipos_end;
		
		pos_type _opos;
		pos_type _opos_beg;
		pos_type _opos_end;
		
		CharT* _buf;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// streambuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_streambuf<char> streambuf;
	
	///////////////////////////////////////////////////////////////////////////////
	// wstreambuf
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_streambuf<wchar_t> wstreambuf;
	
} // namespace kick

template<typename CharT>
kick::basic_streambuf<CharT>::basic_streambuf()
: _ipos		( 0 )
, _ipos_beg	( 0 )
, _ipos_end	( 0 )
, _opos		( 0 )
, _opos_beg	( 0 )
, _opos_end	( 0 )
, _buf		( 0 )
{}

template<typename CharT>
kick::basic_streambuf<CharT>::basic_streambuf( const kick::basic_streambuf<CharT>& sbuf )
: _ipos		( sbuf._ipos )
, _ipos_beg	( sbuf._ipos_beg )
, _ipos_end	( sbuf._ipos_end )
, _opos		( sbuf._opos )
, _opos_beg	( sbuf._opos_beg )
, _opos_end	( sbuf._opos_end )
, _buf		( sbuf._buf )
{}

template<typename CharT>
kick::basic_streambuf<CharT>::~basic_streambuf() {}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::sgetc() {
	if( !_buf[_ipos] ) {
		return underflow();
	}
	
	return static_cast<int>(_buf[_ipos]);
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::sbumpc() {
	if( !_buf[++_ipos] ) {
		return overflow();
	}
	
	return static_cast<int>(_buf[_ipos]);
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::snextc() {
	return static_cast<int>(_buf[++_ipos]);
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::sputc( CharT c ) {
	if( _opos > _opos_end ) {
		return overflow();
	}
	
	_buf[_opos] = c;
	
	++_opos;
	
	return buf_ok;
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::sputn( const CharT* s, kick::size_t n ) {
	for( size_t i = 0; i < n; ++i ) {
		if( sputc(s[i]) == buf_eof ) {
			return overflow();
		}
	}
	
	return buf_ok;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos() {
	return _ipos;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos_beg() {
	return _ipos_beg;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos_end() {
	return _ipos_end;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos() {
	return _opos;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos_beg() {
	return _opos_beg;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos_end() {
	return _opos_end;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::iseekpos( kick::pos_type pos ) {
	_ipos = pos;
	return _ipos;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::oseekpos( kick::pos_type pos ) {
	_opos = pos;
	return _opos;
}

template<typename CharT>
CharT* kick::basic_streambuf<CharT>::buf() {
	return _buf;
}

template<typename CharT>
const CharT* kick::basic_streambuf<CharT>::buf() const {
	return _buf;
}

template<typename CharT>
kick::basic_streambuf<CharT>* kick::basic_streambuf<CharT>::setbuf( CharT* buf, kick::size_t size ) {
	_buf = buf;
	
	_ipos = 0;
	_opos = 0;
	
	_ipos_end = (size - 1);
	_opos_end = (size - 1);
	
	return this;
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::pubsync() {
	return sync();
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::sync() {
	return sync_impl;
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::overflow() {
	return buf_eof;
}

template<typename CharT>
kick::int_type kick::basic_streambuf<CharT>::underflow() {
	return buf_eof;
}

#endif // _kick_iostream_streambuf_h
