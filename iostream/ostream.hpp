#ifndef _kick_iostream_ostream_h
#define _kick_iostream_ostream_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdio.h>

// Kick
#include "./ios.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_ostream : basic_ios
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_ostream : public virtual basic_ios<CharT> {
		basic_ostream();
		
	public:
		basic_ostream( basic_streambuf<CharT>* );
		
		inline basic_ostream& operator<<( CharT );
		inline basic_ostream& operator<<( CharT* );
		inline basic_ostream& operator<<( const CharT* );
		
		inline basic_ostream& operator<<( short );
		inline basic_ostream& operator<<( unsigned short );
		inline basic_ostream& operator<<( int );
		inline basic_ostream& operator<<( unsigned int );
		inline basic_ostream& operator<<( long );
		inline basic_ostream& operator<<( unsigned long );
		inline basic_ostream& operator<<( float );
		inline basic_ostream& operator<<( double );
		inline basic_ostream& operator<<( long double );
		inline basic_ostream& operator<<( void* );
		
	protected:
		
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

template<typename CharT>
kick::basic_ostream<CharT>::basic_ostream( kick::basic_streambuf<CharT>* sbuf )
: kick::basic_ios<CharT>( sbuf )
{}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( CharT val ) {
	this->_sbuf->putc( val );
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( CharT* val ) {
	size_t i = 0;
	
	do {
		this->_sbuf->putc( val[i++] );
	} while( val[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( const CharT* val ) {
	size_t i = 0;
	
	do {
		this->_sbuf->putc( val[i++] );
	} while( val[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( short val ) {
	char buf[8];
	
	sprintf( buf, "%i", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( unsigned short val ) {
	char buf[8];
	
	sprintf( buf, "%u", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( int val ) {
	char buf[12];
	
	sprintf( buf, "%i", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( unsigned int val ) {
	char buf[12];
	
	sprintf( buf, "%u", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( long val ) {
	char buf[24];
	
	sprintf( buf, "%l", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( unsigned long val ) {
	char buf[24];
	
	sprintf( buf, "%ll", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( float val ) {
	char buf[12];
	
	sprintf( buf, "%f", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( double val ) {
	char buf[24];
	
	sprintf( buf, "%f", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( long double val ) {
	char buf[24];
	
	sprintf( buf, "%f", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

template<typename CharT>
kick::basic_ostream<CharT>& kick::basic_ostream<CharT>::operator<<( void* val ) {
	char buf[24];
	
	sprintf( buf, "%p", val );
	
	size_t i = 0;
	
	do {
		this->_sbuf->putc( buf[i++] );
	} while( buf[i] );
	
	return *this;
}

#endif // _kick_iostream_ostream_h
