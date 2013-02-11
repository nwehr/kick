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

#ifndef _kick_string_h
#define _kick_string_h

#include <cstdlib>

#include <iostream>

#include <kick/kick_typdef.h>
#include <kick/kick_allocator.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// string
	///////////////////////////////////////////////////////////////////////////////
	template<class T>
	class basic_string {
	public:
		typedef kick::size_type size_type;

		static const size_type npos = -1;
		
		basic_string()
		: _cstr_( 0 )
		, _alloc_( array_allocator<T>( 1 ) )
		{
			_cstr_ = _alloc_.malloc( 0 );
			_cstr_[0] = 0;
		}
		
		basic_string( const T* cstr )
		: _cstr_( 0 )
		, _alloc_( array_allocator<T>( 1 ) )
		{
			size_type size( 0 );
			
			while( cstr[size] )
				++size;
			
			_cstr_ = _alloc_.malloc( ++size );
			
			for( size_type i = 0; i < size; ++i )
				_cstr_[i] = cstr[i];
			
		}

		basic_string( const T* cstr, size_type size )
		: _cstr_( 0 )
		, _alloc_( array_allocator<T>( 1 ) )
		{
			_cstr_ = _alloc_.malloc( size + 1 );

			for( size_type i = 0; i < size; ++i )
				_cstr_[i] = cstr[i];

			_cstr_[size] = 0;

		}
		
		basic_string( const basic_string<T>& str )
		: _cstr_( 0 )
		, _alloc_( str._alloc_ )
		{
			size_type size( str.size() + 1 );
			_cstr_ = _alloc_.malloc( size );
			
			for( size_type i = 0; i < size; ++i )
				_cstr_[i] = str._cstr_[i];

		}
		
		virtual ~basic_string(){
			if( size() )
				_alloc_.free( _cstr_ );
			
		}
		
		basic_string& operator=( const basic_string<T>& str ){
			_alloc_.free( _cstr_ );

			size_type size( str.size() + 1 );
			_cstr_ = _alloc_.malloc( size );
			
			for( size_type i = 0; i < size; ++i )
				_cstr_[i] = str._cstr_[i];
			
			return *this;
			
		}
		
		bool operator==( const basic_string<T>& str ) const {
			if( size() == str.size() ){
				size_type size( str.size() + 1 );
				for( size_type i = 0; i < size; ++i )
					if( _cstr_[i] != str._cstr_[i] )
						return false;
				
				return true;
				
			}
			
			return false;
			
		}
		
		bool operator!=( const basic_string<T>& str ) const {
			return !(*this == str);
		}
		
		bool operator<( const basic_string<T>& str ) const {
			for( size_type i = 0; i < size(); ++i )
				if( _cstr_[i] > str._cstr_[i] )
					return false;
			
			return true;
			
		}
		
		bool operator>( const basic_string<T>& str ) const {
			for( size_type i = 0; i < size(); ++i )
				if( _cstr_[i] < str._cstr_[i] )
					return false;
			
			return true;
			
		}
		
		inline T& operator[]( size_type index ){
			return _cstr_[index];

		}

		inline const T& operator[]( size_type index ) const {
			return _cstr_[index];

		}
		
		inline size_type size() const {
			if( _alloc_.usize() )
				return _alloc_.usize() - 1;
			
			return 0;
			
		}

		inline size_type length() const {
			return size();
		}

		inline bool empty() const {
			return size() > 0;
		}

		inline size_type capacity() const {
			if( _alloc_.asize() )
				return _alloc_.asize() - 1;

			return 0;

		}
		
		inline T* c_str() const {
			return _cstr_;
		}

		inline T* data() const {
			return c_str();
		}

		size_type copy( T* str, size_type len, size_type pos = 0 ) const {
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

		size_type find( const basic_string<T>& nstr, size_type spos = 0 ) const {
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
		inline size_type find( const T* buf, size_type spos = 0 ) const {
			basic_string<T> n( buf );
			return find( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type find( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return find( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type find( T c, size_type spos = 0 ) const {
			basic_string<T> n( &c, 1 );
			return find( n );
		}

		size_type rfind( const basic_string<T>& nstr, size_type spos = npos ) const {
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
		inline size_type rfind( const T* buf, size_type spos = npos ) const {
			basic_string<T> n( buf );
			return rfind( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type rfind( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return rfind( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type rfind( T c, size_type spos = npos ) const {
			basic_string<T> n( &c, 1 );
			return rfind( n );
		}

		size_type find_first_of( const basic_string<T>& nstr, size_type spos = 0 ) const {
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
		inline size_type find_first_of( const T* buf, size_type spos = 0 ) const {
			basic_string<T> n( buf );
			return find_first_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type find_first_of( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return find_first_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type find_first_of( T c, size_type spos = 0 ) const {
			basic_string<T> n( &c, 1 );
			return find_first_of( n );
		}

		size_type find_last_of( const basic_string<T>& nstr, size_type spos = npos ) const {
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
		inline size_type find_last_of( const T* buf, size_type spos = npos ) const {
			basic_string<T> n( buf );
			return find_last_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type find_last_of( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return find_last_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type find_last_of( T c, size_type spos = npos ) const {
			basic_string<T> n( &c, 1 );
			return find_last_of( n );
		}

		size_type find_first_not_of( const basic_string<T>& nstr, size_type spos = 0 ) const {
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
		inline size_type find_first_not_of( const T* buf, size_type spos = 0 ) const {
			basic_string<T> n( buf );
			return find_first_not_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type find_first_not_of( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return find_first_not_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type find_first_not_of( T c, size_type spos = 0 ) const {
			basic_string<T> n( &c, 1 );
			return find_first_not_of( n );
		}

		size_type find_last_not_of( const basic_string<T>& nstr, size_type spos = npos ) const {
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
		inline size_type find_last_not_of( const T* buf, size_type spos = npos ) const {
			basic_string<T> n( buf );
			return find_last_not_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline size_type find_last_not_of( const T* buf, size_type spos, size_type len ) const {
			basic_string<T> n( buf, len );
			return find_last_not_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline size_type find_last_not_of( T c, size_type spos = npos ) const {
			basic_string<T> n( &c, 1 );
			return find_last_not_of( n );
		}

		basic_string<T> substr( size_type pos, size_type len ) const {
			if( pos < 0 || len <= 0 || pos >= size() )
				return basic_string<T>();

			if( pos + len > size() )
				len = size() - pos;

			return basic_string<T>( &_cstr_[pos], len );

		}
/*
// Not finished yet
		int compare( size_type pos, size_type len, const basic_string<T>& str, size_type subpos, size_type sublen ) const {
			const size_type ssize = size();
			size_type max = pos + len;
			if( max > ssize ) max = ssize;

			const size_type subsize = str.size();
			size_type submax = subpos + sublen;
			if( submax > subsize ) submax = subsize;
			
			size_type si = pos;
			size_type di = subpos;

			int comp = 0;
			while( si < max && di < submax ) {
				
			}
		}
*/
	private:
		T* _cstr_;
		array_allocator<T> _alloc_;
		
	};


	typedef basic_string<char> string;
	
}

#endif // _kick_string_h
