#ifndef _kick_iostream_streambuf_h
#define _kick_iostream_streambuf_h

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
#include <string.h>

// Kick
#include <kick/common.h>
#include <kick/iostream/ios.h>

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
		
		// reading
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT getc();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT bumpc();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT nextc();
		
		// writing
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT putc( CharT c );
		
		// get ios::in positions
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* ipos();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* ipos_beg();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* ipos_end();
	
		// get ios::out positions
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* opos();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* opos_beg();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* opos_end();
		
		// get ios::in or ios::out positions
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* pos( typename basic_ios<CharT>::seqmode_t );
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* pos_beg( typename basic_ios<CharT>::seqmode_t );
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* pos_end( typename basic_ios<CharT>::seqmode_t );
		
		
		// set ios::in or ios::out positions
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		pos_type iseekpos( pos_type );
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		pos_type oseekpos( pos_type );
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		pos_type seekpos( pos_type, typename basic_ios<CharT>::seqmode_t );
		
		// buffer direct access
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		CharT* buf();
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
		const CharT* buf() const;

		
#if	(KICK_POLYMORPHIC_STREAMBUF > 0)
		virtual
#endif
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
kick::basic_streambuf<CharT>::basic_streambuf( const kick::basic_streambuf<CharT>& streambuf )
: _ipos_	( streambuf._ipos_ )
, _ipos_beg_( streambuf._ipos_beg_ )
, _ipos_end_( streambuf._ipos_end_ )
, _opos_	( streambuf._opos_ )
, _opos_beg_( streambuf._opos_beg_ )
, _opos_end_( streambuf._opos_end_ )
, _buf_		( new CharT[sizeof(streambuf._buf_) / sizeof(CharT)] )
{
	::memcpy( _buf_, streambuf._buf_, sizeof(streambuf._buf_) / sizeof(CharT) );
}

template<typename CharT>
kick::basic_streambuf<CharT>::~basic_streambuf() {
	delete[] _buf_;
}

template<typename CharT>
CharT* kick::basic_streambuf<CharT>::pos( typename kick::basic_ios<CharT>::seqmode_t seq ) {
	switch( seq ) {
		case kick::basic_ios<CharT>::in:
		{
			return ipos();
		}
		break;
		case kick::basic_ios<CharT>::out:
		{
			return opos();
		}
		break;
	}
	
}

template<typename CharT>
CharT* kick::basic_streambuf<CharT>::pos_beg( typename kick::basic_ios<CharT>::seqmode_t seq ) {
	switch( seq ) {
		case kick::basic_ios<CharT>::in:
		{
			return ipos_beg();
		}
		break;
		case kick::basic_ios<CharT>::out:
		{
			return opos_beg();
		}
		break;
	}
	
}

template<typename CharT>
CharT* kick::basic_streambuf<CharT>::pos_end( typename kick::basic_ios<CharT>::seqmode_t seq ) {
	switch( seq ) {
		case kick::basic_ios<CharT>::in:
		{
			return ipos_end();
		}
		break;
		case kick::basic_ios<CharT>::out:
		{
			return opos_end();
		}
		break;
	}
	
}

template<typename CharT>
kick::pos_type kick::basic_streambuf<CharT>::seekpos( kick::pos_type pos, typename kick::basic_ios<CharT>::seqmode_t seq ) {
	switch( seq ) {
		case kick::basic_ios<CharT>::in:
		{
			return iseekpos( pos );
		}
		break;
		case kick::basic_ios<CharT>::out:
		{
			return oseekpos( pos );
		}
		break;
	}
	
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
	
	::memcpy( _buf_, buf, size );
	
	return this;
	
}

#endif // _kick_iostream_streambuf_h
