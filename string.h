#ifndef _kick_string_h
#define _kick_string_h

//
//      Copyright 2012-2013 Nathan Wehr. All Rights Reserved.
//      Copyright 2013 Kevin H. Patterson. All Rights Reserved.
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
#include <kick/allocator.h>

/// enable or disable virtual methods to support polymorphism
#ifndef KICK_POLYMORPHIC_STRING
	#define KICK_POLYMORPHIC_STRING KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// basic_string
	///////////////////////////////////////////////////////////////////////////////
	template<typename CharT>
	class basic_string {
	public:
		static const size_type npos = -1;
		
		basic_string();
		basic_string( const CharT* );
		basic_string( const CharT*, size_type );
		basic_string( size_type );
		basic_string( const basic_string<CharT>& );
		
#if (KICK_POLYMORPHIC_STRING > 0)
		virtual
#endif
		~basic_string();
		
		basic_string& operator=( const basic_string<CharT>& str );
		
		bool operator==( const basic_string<CharT>& ) const;
		bool operator!=( const basic_string<CharT>& ) const;
		bool operator<( const basic_string<CharT>& ) const;
		bool operator>( const basic_string<CharT>& ) const;
		
		inline CharT& operator[]( size_type );
		
		inline size_type size() const;
		inline size_type length() const;
		inline size_type capacity() const;
		inline bool empty() const;
		
		
		inline CharT* c_str() const;
		inline CharT* data() const;
		
		size_type copy( CharT*, size_type, size_type pos = 0 ) const;
		
		size_type find( const basic_string<CharT>&, size_type spos = 0 ) const;
		inline size_type find( const CharT*, size_type spos = 0 ) const;
		inline size_type find( const CharT*, size_type, size_type ) const;
		inline size_type find( CharT, size_type spos = 0 ) const;

		size_type rfind( const basic_string<CharT>&, size_type spos = npos ) const;
		inline size_type rfind( const CharT*, size_type spos = npos ) const;
		inline size_type rfind( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type rfind( CharT c, size_type spos = npos ) const;
		
		size_type find_first_of( const basic_string<CharT>& nstr, size_type spos = 0 ) const;
		inline size_type find_first_of( const CharT* buf, size_type spos = 0 ) const;
		inline size_type find_first_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_first_of( CharT c, size_type spos = 0 ) const;
		
		size_type find_last_of( const basic_string<CharT>& nstr, size_type spos = npos ) const;
		inline size_type find_last_of( const CharT* buf, size_type spos = npos ) const;
		inline size_type find_last_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_last_of( CharT c, size_type spos = npos ) const;

		size_type find_first_not_of( const basic_string<CharT>& nstr, size_type spos = 0 ) const;
		inline size_type find_first_not_of( const CharT* buf, size_type spos = 0 ) const;
		inline size_type find_first_not_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_first_not_of( CharT c, size_type spos = 0 ) const;
		
		size_type find_last_not_of( const basic_string<CharT>& nstr, size_type spos = npos ) const;
		inline size_type find_last_not_of( const CharT* buf, size_type spos = npos ) const;
		inline size_type find_last_not_of( const CharT* buf, size_type spos, size_type len ) const;
		inline size_type find_last_not_of( CharT c, size_type spos = npos ) const;
		
		size_type find_first_less_than( CharT c, size_type spos = 0 ) const;
		size_type find_first_greater_than( CharT c, size_type spos = 0 ) const;

		basic_string<CharT> substr( size_type pos, size_type len = npos ) const;
		
	protected:
		CharT* _cstr_;
		array_allocator<CharT> _alloc_;
		
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

template<typename CharT>
kick::basic_string<CharT>::basic_string()
: _cstr_( 0 )
, _alloc_( kick::array_allocator<CharT>( 1 ) )
{
	_cstr_ = _alloc_.malloc( _cstr_, 0 );
	_cstr_[0] = 0;
}

template<typename CharT>
kick::basic_string<CharT>::basic_string( const CharT* cstr )
: _cstr_( 0 )
, _alloc_( kick::array_allocator<CharT>( 1 ) )
{
	size_type size( 0 );
	
	while( cstr[size] )
		++size;
	
	_cstr_ = _alloc_.malloc( _cstr_, ++size );
	
	for( size_type i = 0; i < size; ++i )
		_cstr_[i] = cstr[i];
	
}

template<typename CharT>
kick::basic_string<CharT>::basic_string( const CharT* cstr, kick::size_type size )
: _cstr_( 0 )
, _alloc_( kick::array_allocator<CharT>( 1 ) )
{
	_cstr_ = _alloc_.malloc( _cstr_, size + 1 );
	
	for( size_type i = 0; i < size; ++i )
		_cstr_[i] = cstr[i];
	
	_cstr_[size] = 0;
	
}

template<typename CharT>
kick::basic_string<CharT>::basic_string( kick::size_type size )
: _cstr_( 0 )
, _alloc_( kick::array_allocator<CharT>( 1 ) )
{
	_cstr_ = _alloc_.malloc( _cstr_, size + 1 );
	_cstr_[0] = 0;
	_cstr_[size] = 0;
}

template<typename CharT>
kick::basic_string<CharT>::basic_string( const kick::basic_string<CharT>& str )
: _cstr_( 0 )
, _alloc_( str._alloc_ )
{
	size_type size( str.size() + 1 );
	
	_cstr_ = _alloc_.malloc( _cstr_, size );
	
	for( size_type i = 0; i < size; ++i )
		_cstr_[i] = str._cstr_[i];
	
}

template<typename CharT>
kick::basic_string<CharT>::~basic_string() {
	if( _cstr_ )
		_alloc_.free( _cstr_ );
	
}

template<typename CharT>
kick::basic_string<CharT>& kick::basic_string<CharT>::operator=( const kick::basic_string<CharT>& str ) {
	_cstr_ = _alloc_.malloc( _cstr_, (str.size() + 1) );
	
	for( size_type i = 0; i < (str.size() + 1); ++i )
		_cstr_[i] = str._cstr_[i];
	
	return *this;
	
}

template<typename CharT>
bool kick::basic_string<CharT>::operator==( const kick::basic_string<CharT>& str ) const {
	return (strcmp( _cstr_, str._cstr_ ) == 0 ? true : false);
}

template<typename CharT>
bool kick::basic_string<CharT>::operator!=( const kick::basic_string<CharT>& str ) const {
	return !(*this == str);
}

template<typename CharT>
bool kick::basic_string<CharT>::operator<( const kick::basic_string<CharT>& str ) const {
	return (strcmp( _cstr_, str._cstr_ ) < 0 ? true : false);
}

template<typename CharT>
bool kick::basic_string<CharT>::operator>( const kick::basic_string<CharT>& str ) const {
	return (strcmp( _cstr_, str._cstr_ ) > 0 ? true : false);
}

template<typename CharT>
CharT& kick::basic_string<CharT>::operator[]( kick::size_type index ) {
	return _cstr_[index];
	
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::size() const {
	if( _alloc_.usize() )
		return _alloc_.usize() - 1;
	
	return 0;
	
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::length() const {
	return size();
}

template<typename CharT>
bool kick::basic_string<CharT>::empty() const {
	return size() > 0;
}

template<typename CharT>
size_type kick::basic_string<CharT>::capacity() const {
	return _alloc_.asize();
}

template<typename CharT>
CharT* kick::basic_string<CharT>::c_str() const {
	return _cstr_;
}

template<typename CharT>
CharT* kick::basic_string<CharT>::data() const {
	return c_str();
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::copy( CharT* str, kick::size_type len, kick::size_type pos ) const {
	const size_type ssize = size();
	
	if( pos > ssize - 1 ) return 0;
	if( pos + len > ssize ) len = ssize - pos;
	
	size_type di = 0;
	for( size_type i = pos; i < ssize; ++i ) {
		str[di] = _cstr_[i];
		++di;
	}
	
	return di;
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find( const kick::basic_string<CharT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize > hsize ) return npos;
	
	if( spos < 0 ) spos = 0;
	
	const size_type smax = hsize - nsize;
	while( spos <= smax ) {
		while( spos < smax && _cstr_[spos] != nstr._cstr_[0] )
			++spos;
		
		size_type hpos = spos + 1;
		size_type epos = 1;
		while( hpos < hsize && epos < nsize && _cstr_[hpos] == nstr._cstr_[epos] ) {
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
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find( n );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::rfind( const kick::basic_string<CharT>& nstr, kick::size_type spos = npos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize > hsize ) return npos;
	
	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
	
	const size_type smin = nsize - 1;
	while( spos >= smin ) {
		while( spos >= smin && _cstr_[spos] != nstr._cstr_[nsize - 1] )
			--spos;
		
		size_type hpos = spos - 1;
		size_type epos = nsize - 2;
		while( hpos >= 0 && epos >= 0 && _cstr_[hpos] == nstr._cstr_[epos] ) {
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
template<typename CharT>
kick::size_type kick::basic_string<CharT>::rfind( const CharT* buf, kick::size_type spos = npos ) const {
	basic_string<CharT> n( buf );
	return rfind( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::rfind( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return rfind( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
kick::size_type kick::basic_string<CharT>::rfind( CharT c, kick::size_type spos = npos ) const {
	basic_string<CharT> n( &c, 1 );
	return rfind( n );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_of( const kick::basic_string<CharT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos < 0 ) spos = 0;
	while( spos < hsize ) {
		size_type npos = 0;
		while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize ) return spos;
		
		++spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_of( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find_first_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_first_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_of( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_first_of( n );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_of( const kick::basic_string<CharT>& nstr, kick::size_type spos = npos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
	while( spos >= 0 ) {
		size_type npos = 0;
		while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize ) return spos;
		
		--spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_of( const CharT* buf, kick::size_type spos = npos ) const {
	basic_string<CharT> n( buf );
	return find_last_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_last_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_of( CharT c, kick::size_type spos = npos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_last_of( n );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_not_of( const kick::basic_string<CharT>& nstr, kick::size_type spos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos < 0 ) spos = 0;
	while( spos < hsize ) {
		size_type npos = 0;
		while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize )
			++spos;
		else
			return spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_not_of( const CharT* buf, kick::size_type spos ) const {
	basic_string<CharT> n( buf );
	return find_first_not_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_not_of( const CharT* buf, kick::size_type spos, kick::size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_first_not_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_not_of( CharT c, kick::size_type spos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_first_not_of( n );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_not_of( const kick::basic_string<CharT>& nstr, kick::size_type spos = npos ) const {
	const size_type nsize = nstr.size();
	const size_type hsize = size();
	
	if( nsize < 1 ) return npos;
	
	if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
	while( spos >= 0 ) {
		size_type npos = 0;
		while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
			++npos;
		
		if( npos < nsize )
			--spos;
		else
			return spos;
	}
	
	return npos;
}

//TODO: Optimized search for C string
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_not_of( const CharT* buf, kick::size_type spos = npos ) const {
	basic_string<CharT> n( buf );
	return find_last_not_of( n, spos );
}

//TODO: Optimized search for char buffer
template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_last_not_of( const CharT* buf, size_type spos, size_type len ) const {
	basic_string<CharT> n( buf, len );
	return find_last_not_of( n, spos );
}

//TODO: Optimized search for single char
template<typename CharT>
inline size_type find_last_not_of( CharT c, kick::size_type spos = npos ) const {
	basic_string<CharT> n( &c, 1 );
	return find_last_not_of( n, spos );
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_less_than( CharT c, kick::size_type spos ) const {
	const size_type hsize = size();
	for( ; spos < hsize; ++spos )
		if( _cstr_[spos] < c ) return spos;
	
	return npos;
}

template<typename CharT>
kick::size_type kick::basic_string<CharT>::find_first_greater_than( CharT c, kick::size_type spos ) const {
	const size_type hsize = size();
	for( ; spos < hsize; ++spos )
		if( _cstr_[spos] > c ) return spos;
	
	return npos;
}

template<typename CharT>
kick::basic_string<CharT> kick::basic_string<CharT>::substr( kick::size_type pos, kick::size_type len = npos ) const {
	if( len == npos ) len = size();
	if( pos < 0 || len <= 0 || pos >= size() )
		return basic_string<CharT>();
	
	if( pos + len > size() )
		len = size() - pos;
	
	return basic_string<CharT>( &_cstr_[pos], len );
	
}

// Non-member overload for outputting kick strings to stream objects...
template<typename StreamT, typename CharT = char>
StreamT& operator<<( StreamT& os, const kick::basic_string<CharT>& str ) {
	os << str.c_str();
	return os;
}

#endif // _kick_string_h
