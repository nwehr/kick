#ifndef _kick_string_h
#define _kick_string_h

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
#include "./common.hpp"
#include "./allocator/array_allocator.hpp"

/// enable or disable virtual methods to support polymorphism
#ifndef KICK_POLYMORPHIC_STRING
#define KICK_POLYMORPHIC_STRING KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_string
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT, typename AllocT = array_allocator<CharT> >
	class basic_string {
	public:
		static const size_type npos = -1;
		
		basic_string( AllocT alloc = AllocT() );
		basic_string( const CharT*, AllocT alloc = AllocT() );
		basic_string( const CharT*, size_type, AllocT alloc = AllocT() );
		basic_string( size_type, AllocT alloc = AllocT() );
		basic_string( const basic_string<CharT, AllocT>& );
		
#if (KICK_POLYMORPHIC_STRING > 0)
		virtual
#endif
		~basic_string();
		
		basic_string& operator=( const basic_string<CharT, AllocT>& str );
		
		bool operator==( const basic_string<CharT, AllocT>& ) const;
		bool operator!=( const basic_string<CharT, AllocT>& ) const;
		bool operator<( const basic_string<CharT, AllocT>& ) const;
		bool operator>( const basic_string<CharT, AllocT>& ) const;
		
		inline CharT& operator[]( size_type );
		
		inline size_type size() const;
		inline size_type length() const;
		inline size_type capacity() const;
		inline bool empty() const;
		
		
		inline CharT* c_str() const;
		inline CharT* data() const;
		
		size_type copy( CharT*, size_type, size_type pos = 0 ) const;
		
		size_type find( const basic_string<CharT, AllocT>&, size_type spos = 0 ) const;
		inline size_type find( const CharT*, size_type spos = 0 ) const;
		inline size_type find( const CharT*, size_type, size_type ) const;
		inline size_type find( CharT, size_type spos = 0 ) const;

		size_type rfind( const basic_string<CharT, AllocT>&, size_type spos = npos ) const;
		inline size_type rfind( const CharT*, size_type spos = npos ) const;
		inline size_type rfind( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type rfind( CharT c, size_type spos = npos ) const;
		
		size_type find_first_of( const basic_string<CharT, AllocT>& nstr, size_type spos = 0 ) const;
		inline size_type find_first_of( const CharT* buf, size_type spos = 0 ) const;
		inline size_type find_first_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_first_of( CharT c, size_type spos = 0 ) const;
		
		size_type find_last_of( const basic_string<CharT, AllocT>& nstr, size_type spos = npos ) const;
		inline size_type find_last_of( const CharT* buf, size_type spos = npos ) const;
		inline size_type find_last_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_last_of( CharT c, size_type spos = npos ) const;

		size_type find_first_not_of( const basic_string<CharT, AllocT>& nstr, size_type spos = 0 ) const;
		inline size_type find_first_not_of( const CharT* buf, size_type spos = 0 ) const;
		inline size_type find_first_not_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_first_not_of( CharT c, size_type spos = 0 ) const;
		
//		size_type find_last_not_of( const basic_string<CharT>& nstr, size_type spos = npos ) const;
//		inline size_type find_last_not_of( const CharT* buf, size_type spos = npos ) const;
//		inline size_type find_last_not_of( const CharT* buf, size_type spos, size_type len ) const;
//		inline size_type find_last_not_of( CharT c, size_type spos = npos ) const;
		
		size_type find_first_less_than( CharT c, size_type spos = 0 ) const;
		size_type find_first_greater_than( CharT c, size_type spos = 0 ) const;

		basic_string<CharT, AllocT> substr( size_type pos, size_type len = npos ) const;
		
	protected:
		CharT* _mem;
		AllocT _alloc;
		
	};

	///////////////////////////////////////////////////////////////////////////////
	// string
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_string<char> string;
	
	///////////////////////////////////////////////////////////////////////////////
	// wstring
	///////////////////////////////////////////////////////////////////////////////
	typedef basic_string<wchar_t> wstring;
	
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::basic_string( AllocT alloc )
: _mem( nullptr )
, _alloc( alloc )
{
	_mem = _alloc.malloc( _mem, 0 );
	_mem[0] = 0;
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::basic_string( const CharT* cstr, AllocT alloc )
: _mem( nullptr )
, _alloc( alloc )
{
	size_type size( 0 );
	
	while( cstr[size] )
		++size;
	
	_mem = _alloc.malloc( _mem, ++size );
	
	for( size_type i = 0; i < size; ++i )
		_mem[i] = cstr[i];
	
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::basic_string( const CharT* cstr, kick::size_type size, AllocT alloc )
: _mem( nullptr )
, _alloc( alloc )
{
	_mem = _alloc.malloc( _mem, size + 1 );
	
	for( size_type i = 0; i < size; ++i )
		_mem[i] = cstr[i];
	
	_mem[size] = 0;
	
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::basic_string( kick::size_type size, AllocT alloc )
: _mem( nullptr )
, _alloc( alloc )
{
	_mem = _alloc.malloc( _mem, size + 1 );
	_mem[0] = 0;
	_mem[size] = 0;
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::basic_string( const kick::basic_string<CharT, AllocT>& str )
: _mem( nullptr )
, _alloc( str._alloc )
{
	size_type size( str.size() + 1 );
	
	_mem = _alloc.malloc( _mem, size );
	
	for( size_type i = 0; i < size; ++i )
		_mem[i] = str._mem[i];
	
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>::~basic_string() {
	if( _mem )
		_alloc.free( _mem );
	
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT>& kick::basic_string<CharT, AllocT>::operator=( const kick::basic_string<CharT, AllocT>& str ) {
	_mem = _alloc.malloc( _mem, (str.size() + 1) );
	
	for( size_type i = 0; i < (str.size() + 1); ++i )
		_mem[i] = str._mem[i];
	
	return *this;
	
}

template<typename CharT, typename AllocT>
bool kick::basic_string<CharT, AllocT>::operator==( const kick::basic_string<CharT, AllocT>& str ) const {
	return (strcmp( _mem, str._mem ) == 0 ? true : false);
}

template<typename CharT, typename AllocT>
bool kick::basic_string<CharT, AllocT>::operator!=( const kick::basic_string<CharT, AllocT>& str ) const {
	return !(*this == str);
}

template<typename CharT, typename AllocT>
bool kick::basic_string<CharT, AllocT>::operator<( const kick::basic_string<CharT, AllocT>& str ) const {
	return (strcmp( _mem, str._mem ) < 0 ? true : false);
}

template<typename CharT, typename AllocT>
bool kick::basic_string<CharT, AllocT>::operator>( const kick::basic_string<CharT, AllocT>& str ) const {
	return (strcmp( _mem, str._mem ) > 0 ? true : false);
}

template<typename CharT, typename AllocT>
CharT& kick::basic_string<CharT, AllocT>::operator[]( kick::size_type index ) {
	return _mem[index];
	
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::size() const {
	if( _alloc.usize() )
		return _alloc.usize() - 1;
	
	return 0;
	
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::length() const {
	return size();
}

template<typename CharT, typename AllocT>
bool kick::basic_string<CharT, AllocT>::empty() const {
	return size() > 0;
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::capacity() const {
	return _alloc.asize();
}

template<typename CharT, typename AllocT>
CharT* kick::basic_string<CharT, AllocT>::c_str() const {
	return _mem;
}

template<typename CharT, typename AllocT>
CharT* kick::basic_string<CharT, AllocT>::data() const {
	return c_str();
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::copy( CharT* str, kick::size_type len, kick::size_type pos ) const {
	const size_type ssize = size();
	
	if( pos > ssize - 1 ) return 0;
	if( pos + len > ssize ) len = ssize - pos;
	
	size_type di = 0;
	for( size_type i = pos; i < ssize; ++i ) {
		str[di] = _mem[i];
		++di;
	}
	
	return di;
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize > hsize ) return npos;
	
	if( spos < 0 ) spos = 0;
	
	const size_type smax = hsize - nsize;
	while( spos <= smax ) {
		while( spos < smax && _mem[spos] != nstr._mem[0] )
			++spos;
		
		size_type hpos = spos + 1;
		size_type epos = 1;
		while( hpos < hsize && epos < nsize && _mem[hpos] == nstr._mem[epos] ) {
			++hpos;
			++epos;
		}
		
		if( epos == nsize )
			return spos;
		else
			++spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find( n );
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::rfind( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize > hsize ) return npos;
	
	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
	
	const size_type smin = nsize - 1;
	while( spos >= smin ) {
		while( spos >= smin && _mem[spos] != nstr._mem[nsize - 1] )
			--spos;
		
		size_type hpos = spos - 1;
		size_type epos = nsize - 2;
		while( hpos >= 0 && epos >= 0 && _mem[hpos] == nstr._mem[epos] ) {
			--hpos;
			--epos;
		}
		
		if( epos == -1 )
			return hpos + 1;
		else
			--spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::rfind( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return rfind( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::rfind( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return rfind( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::rfind( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return rfind( n );
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_of( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos < 0 ) spos = 0;
	while( spos < hsize ) {
		size_type npos = 0;
		while( _mem[spos] != nstr._mem[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize ) return spos;
		
		++spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_of( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find_first_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_first_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_of( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_first_of( n );
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_last_of( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
	while( spos >= 0 ) {
		size_type npos = 0;
		while( _mem[spos] != nstr._mem[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize ) return spos;
		
		--spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_last_of( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find_last_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_last_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_last_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_last_of( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_last_of( n );
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_not_of( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos < 0 ) spos = 0;
	while( spos < hsize ) {
		size_type npos = 0;
		while( _mem[spos] != nstr._mem[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize )
			++spos;
		else
			return spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_not_of( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find_first_not_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_not_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_first_not_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_not_of( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_first_not_of( n );
}

//template<typename CharT>
//kick::size_type kick::basic_string<CharT, AllocT>::find_last_not_of( const kick::basic_string<CharT, AllocT>& nstr, kick::size_type spos ) const {
//	const size_type nsize = nstr.size();
//	const size_type hsize = size();
//	
//	if( nsize < 1 ) return npos;
//	
//	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
//	while( spos >= 0 ) {
//		size_type npos = 0;
//		while( _mem[spos] != nstr._mem[npos] && npos < nsize )
//			++npos;
//		
//		if( npos < nsize )
//			--spos;
//		else
//			return spos;
//	}
//	
//	return npos;
//}
//
////TODO: Optimized search for C string
//template<typename CharT>
//kick::size_type kick::basic_string<CharT, AllocT>::find_last_not_of( const CharT* buf, kick::size_type spos ) const {
//	basic_string<CharT> n( buf );
//	return find_last_not_of( n, spos );
//}
//
////TODO: Optimized search for char buffer
//template<typename CharT>
//kick::size_type kick::basic_string<CharT, AllocT>::find_last_not_of( const CharT* buf, size_type spos, size_type len ) const {
//	basic_string<CharT> n( buf, len );
//	return find_last_not_of( n, spos );
//}
//
////TODO: Optimized search for single char
//template<typename CharT>
//kick::size_type find_last_not_of( CharT c, kick::size_type spos ) const {
//	basic_string<CharT> n( &c, 1 );
//	return find_last_not_of( n, spos );
//}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_less_than( CharT c, kick::size_type spos ) const {
	const size_type hsize = size();
	for( ; spos < hsize; ++spos )
		if( _mem[spos] < c ) return spos;
	
	return npos;
}

template<typename CharT, typename AllocT>
kick::size_type kick::basic_string<CharT, AllocT>::find_first_greater_than( CharT c, kick::size_type spos ) const {
	const size_type hsize = size();
	for( ; spos < hsize; ++spos )
		if( _mem[spos] > c ) return spos;
	
	return npos;
}

template<typename CharT, typename AllocT>
kick::basic_string<CharT, AllocT> kick::basic_string<CharT, AllocT>::substr( kick::size_type pos, kick::size_type len ) const {
	if( len == npos ) len = size();
	if( pos < 0 || len <= 0 || pos >= size() )
		return basic_string<CharT>();
	
	if( pos + len > size() )
		len = size() - pos;
	
	return basic_string<CharT>( &_mem[pos], len );
	
}

// Non-member overload for outputting kick strings to stream objects...
template<typename StreamT, typename CharT = char, typename AllocT = kick::array_allocator<CharT> >
StreamT& operator<<( StreamT& os, const kick::basic_string<CharT, AllocT>& str ) {
	os << str.c_str();
	return os;
}

#endif // _kick_string_h
