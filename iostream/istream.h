#ifndef _kick_iostream_istream_h
#define _kick_iostream_istream_h

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
#include <stdlib.h>

// Kick
#include <kick/iostream/ios.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_istream : basic_ios
	///////////////////////////////////////////////////////////////////////////////
	template <typename CharT>
	class basic_istream : public virtual basic_ios<CharT> {
		basic_istream();
		
	public:
		basic_istream( basic_streambuf<CharT>* );
		basic_istream( const basic_istream<CharT>& );
		
#if	(KICK_POLYMORPHIC_STREAM > 0)
		virtual
#endif
		~basic_istream();
		
		inline basic_istream& operator>>( bool& );
		inline basic_istream& operator>>( short& );
		inline basic_istream& operator>>( unsigned short& );
		inline basic_istream& operator>>( int& );
		inline basic_istream& operator>>( unsigned int& );
		inline basic_istream& operator>>( long& );
		inline basic_istream& operator>>( unsigned long& );
		inline basic_istream& operator>>( float& );
		inline basic_istream& operator>>( double& );
		inline basic_istream& operator>>( long double& );
		inline basic_istream& operator>>( void*& );
		
		basic_istream& operator>> ( basic_streambuf<CharT>& );
		
	protected:
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// basic_istream : basic_ios
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_istream<char> istream;
	
	///////////////////////////////////////////////////////////////////////////////
	// basic_istream : basic_ios
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_istream<wchar_t> wistream;
	
} // namespace kick

template<typename CharT>
kick::basic_istream<CharT>::basic_istream( kick::basic_streambuf<CharT>* sbuf )
: kick::basic_ios<CharT>( sbuf )
{}

template<typename CharT>
kick::basic_istream<CharT>::basic_istream( const kick::basic_istream<CharT>& stream )
: kick::basic_ios<CharT>( stream.sbuf() )
{}

template<typename CharT>
kick::basic_istream<CharT>::~basic_istream() {}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( bool& val ) {
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( short& val ) {
	val = atoi( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( unsigned short& val ) {
	val = atoi( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( int& val ) {
	val = atoi( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( unsigned int& val ) {
	val = atoi( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( long& val ) {
	val = atol( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( unsigned long& val ) {
	val = atol( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( float& val ) {
	val = atof( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( double& val ) {
	val = atof( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( long double& val ) {
	val = atof( this->_sbuf_->buf() );
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( void*& val ) {
	val = this->_sbuf_->buf();
	return *this;
}

template<typename CharT>
kick::basic_istream<CharT>& kick::basic_istream<CharT>::operator>>( basic_streambuf<CharT>& sbuf ) {
	this->_sbuf_->iseekpos( 0 );
	sbuf.oseekpos( sbuf.opos_end() );
	
	CharT c;
	while( (c = this->_sbuf_->bumpc()) ) {
		sbuf.putc( c );
	}
	
	return *this;
	
}

#endif // _kick_iostream_istream_h
