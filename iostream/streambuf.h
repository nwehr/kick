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
#include "../common.h"
#include "ios.h"

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
		basic_streambuf();
		basic_streambuf( const basic_streambuf& );
		
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		~basic_streambuf();
		
		inline CharT getc();
		inline CharT bumpc();
		inline CharT nextc();
		
		inline CharT putc( CharT c );
		
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
		
	protected:
		pos_type _ipos_;
		pos_type _ipos_beg_;
		pos_type _ipos_end_;
		
		pos_type _opos_;
		pos_type _opos_beg_;
		pos_type _opos_end_;
		
		CharT* _buf_;
		
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
: _ipos_	( 0 )
, _ipos_beg_( 0 )
, _ipos_end_( 0 )
, _opos_	( 0 )
, _opos_beg_( 0 )
, _opos_end_( 0 )
, _buf_		( new CharT[0] )
{}

template<typename CharT>
kick::basic_streambuf<CharT>::basic_streambuf( const kick::basic_streambuf<CharT>& sbuf )
: _ipos_	( sbuf._ipos_ )
, _ipos_beg_( sbuf._ipos_beg_ )
, _ipos_end_( sbuf._ipos_end_ )
, _opos_	( sbuf._opos_ )
, _opos_beg_( sbuf._opos_beg_ )
, _opos_end_( sbuf._opos_end_ )
, _buf_		( new CharT[sizeof(sbuf._buf_) / sizeof(CharT)] )
{
	::memcpy( _buf_, sbuf._buf_, sizeof(sbuf._buf_) / sizeof(CharT) );
}

template<typename CharT>
kick::basic_streambuf<CharT>::~basic_streambuf() {
	delete[] _buf_;
}

template<typename CharT>
CharT kick::basic_streambuf<CharT>::getc() {
	return _buf_[_ipos_];
}

template<typename CharT>
CharT kick::basic_streambuf<CharT>::bumpc() {
	return _buf_[_ipos_++];
}

template<typename CharT>
CharT kick::basic_streambuf<CharT>::nextc() {
	return _buf_[++_ipos_];
}

template<typename CharT>
CharT kick::basic_streambuf<CharT>::putc( CharT c ) {
	return _buf_[_opos_++] = c;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos() {
	return _ipos_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos_beg() {
	return _ipos_beg_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::ipos_end() {
	return _ipos_end_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos() {
	return _opos_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos_beg() {
	return _opos_beg_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::opos_end() {
	return _opos_end_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::iseekpos( kick::pos_type pos ) {
	_ipos_ = pos;
	return _ipos_;
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::oseekpos( kick::pos_type pos ) {
	_opos_ = pos;
	return _opos_; 
}

template<typename CharT>
CharT* kick::basic_streambuf<CharT>::buf() {
	return _buf_;
}

template<typename CharT>
const CharT* kick::basic_streambuf<CharT>::buf() const {
	return _buf_;
}

template<typename CharT>
kick::basic_streambuf<CharT>* kick::basic_streambuf<CharT>::setbuf( CharT* buf, kick::size_t size ) {
	if( _buf_ )
		delete[] _buf_;
	
	_buf_ = new CharT[size];
	
	_ipos_ = 0;
	_opos_ = 0;
	
	_ipos_end_ = (size - 1);
	_opos_end_ = (size - 1);
	
	::memcpy( _buf_, buf, size );
	
	return this;
	
}

#endif // _kick_iostream_streambuf_h
