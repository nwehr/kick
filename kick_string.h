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
	class string {
	public:
		typedef kick::size_type size_type;

		static const size_type npos = -1;
		
		string()
		: _cstr_( 0 )
		, _alloc_( array_allocator<char>( 1 ) )
		{
			_cstr_ = _alloc_.malloc( 0 );
			_cstr_[0] = 0;
		}
		
		string( const char* cstr )
		: _cstr_( 0 )
		, _alloc_( array_allocator<char>( 1 ) )
		{
			int size( 0 );
			
			while( cstr[size] )
				++size;
			
			_cstr_ = _alloc_.malloc( ++size );
			
			for( int i = 0; i < size; ++i )
				_cstr_[i] = cstr[i];
			
		}

		string( const char* cstr, int size )
		: _cstr_( 0 )
		, _alloc_( array_allocator<char>( 1 ) )
		{
			_cstr_ = _alloc_.malloc( size + 1 );

			for( int i = 0; i < size; ++i )
				_cstr_[i] = cstr[i];

			_cstr_[size] = 0;

		}
		
		string( const string& str )
		: _cstr_( 0 )
		, _alloc_( str._alloc_ )
		{
			int size( str.size() + 1 );
			_cstr_ = _alloc_.malloc( size );
			
			for( int i = 0; i < size; ++i )
				_cstr_[i] = str._cstr_[i];

		}
		
		virtual ~string(){
			if( size() )
				_alloc_.free( _cstr_ );
			
		}
		
		string& operator=( const string& str ){
			_alloc_.free( _cstr_ );

			int size( str.size() + 1 );
			_cstr_ = _alloc_.malloc( size );
			
			for( int i = 0; i < size; ++i )
				_cstr_[i] = str._cstr_[i];
			
			return *this;
			
		}
		
		bool operator==( const string& str ) const {
			if( size() == str.size() ){
				int size( str.size() + 1 );
				for( int i = 0; i < size; ++i )
					if( _cstr_[i] != str._cstr_[i] )
						return false;
				
				return true;
				
			}
			
			return false;
			
		}
		
		bool operator!=( const string& str ) const {
			return !(*this == str);
		}
		
		bool operator<( const string& str ) const {
			for( int i = 0; i < size(); ++i )
				if( _cstr_[i] > str._cstr_[i] )
					return false;
			
			return true;
			
		}
		
		bool operator>( const string& str ) const {
			for( int i = 0; i < size(); ++i )
				if( _cstr_[i] < str._cstr_[i] )
					return false;
			
			return true;
			
		}
		
		inline char& operator[]( int index ){
			if( index < size() && index >= 0 )
				return _cstr_[index];
			
			exit( -1 ); //TODO: out-of-range, do something!!!
			
		}

		inline const char& operator[]( int index ) const {
			if( index < size() && index >= 0 )
				return _cstr_[index];

			exit( -1 ); //TODO: out-of-range, do something!!!

		}
		
		inline int size() const {
			if( _alloc_.usize() )
				return _alloc_.usize() - 1;
			
			return 0;
			
		}
		
		inline char* c_str() const {
			return _cstr_;
		}

		string substr( int pos, int len ) const {
			if( pos < 0 || len <= 0 || pos >= size() )
				return string();
			
			if( pos + len > size() )
				len = size() - pos;
			
			return string( &_cstr_[pos], len );
			
		}

		int find( const string& nstr, int spos = 0 ) const {
			const int nsize = nstr.size();
			const int hsize = size();
			
			if( nsize > hsize ) return npos;

			if( spos < 0 ) spos = 0;

			const int smax = hsize - nsize;
			while( spos <= smax ) {
				while( spos < smax && _cstr_[spos] != nstr._cstr_[0] )
					++spos;

				int hpos = spos + 1;
				int epos = 1;
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
		inline int find( const char* buf, int spos = 0 ) const {
			string n( buf );
			return find( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int find( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return find( n, spos );
		}

		//TODO: Optimized search for single char
		inline int find( char c, int spos = 0 ) const {
			string n( &c, 1 );
			return find( n );
		}

		int rfind( const string& nstr, int spos = npos ) const {
			const int nsize = nstr.size();
			const int hsize = size();

			if( nsize > hsize ) return npos;

			if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;

			const int smin = nsize - 1;
			while( spos >= smin ) {
				while( spos >= smin && _cstr_[spos] != nstr._cstr_[nsize - 1] )
					--spos;

				int hpos = spos - 1;
				int epos = nsize - 2;
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
		inline int rfind( const char* buf, int spos = npos ) const {
			string n( buf );
			return rfind( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int rfind( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return rfind( n, spos );
		}

		//TODO: Optimized search for single char
		inline int rfind( char c, int spos = npos ) const {
			string n( &c, 1 );
			return rfind( n );
		}

		int find_first_of( const string& nstr, int spos = 0 ) const {
			const int nsize = nstr.size();
			const int hsize = size();

			if( nsize < 1 ) return npos;

			if( spos < 0 ) spos = 0;
			while( spos < hsize ) {
				int npos = 0;
				while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
					++npos;

				if( npos < nsize ) return spos;
				
				++spos;
			}

			return npos;
		}

		//TODO: Optimized search for C string
		inline int find_first_of( const char* buf, int spos = 0 ) const {
			string n( buf );
			return find_first_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int find_first_of( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return find_first_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline int find_first_of( char c, int spos = 0 ) const {
			string n( &c, 1 );
			return find_first_of( n );
		}

		int find_last_of( const string& nstr, int spos = npos ) const {
			const int nsize = nstr.size();
			const int hsize = size();

			if( nsize < 1 ) return npos;

			if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
			while( spos >= 0 ) {
				int npos = 0;
				while( _cstr_[spos] != nstr._cstr_[npos] && npos < nsize )
					++npos;

				if( npos < nsize ) return spos;

				--spos;
			}

			return npos;
		}

		//TODO: Optimized search for C string
		inline int find_last_of( const char* buf, int spos = npos ) const {
			string n( buf );
			return find_last_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int find_last_of( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return find_last_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline int find_last_of( char c, int spos = npos ) const {
			string n( &c, 1 );
			return find_last_of( n );
		}

		int find_first_not_of( const string& nstr, int spos = 0 ) const {
			const int nsize = nstr.size();
			const int hsize = size();

			if( nsize < 1 ) return npos;

			if( spos < 0 ) spos = 0;
			while( spos < hsize ) {
				int npos = 0;
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
		inline int find_first_not_of( const char* buf, int spos = 0 ) const {
			string n( buf );
			return find_first_not_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int find_first_not_of( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return find_first_not_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline int find_first_not_of( char c, int spos = 0 ) const {
			string n( &c, 1 );
			return find_first_not_of( n );
		}

		int find_last_not_of( const string& nstr, int spos = npos ) const {
			const int nsize = nstr.size();
			const int hsize = size();

			if( nsize < 1 ) return npos;

			if( spos == npos || spos > hsize - 1 ) spos = hsize - 1;
			while( spos >= 0 ) {
				int npos = 0;
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
		inline int find_last_not_of( const char* buf, int spos = npos ) const {
			string n( buf );
			return find_last_not_of( n, spos );
		}

		//TODO: Optimized search for char buffer
		inline int find_last_not_of( const char* buf, int spos, int len ) const {
			string n( buf, len );
			return find_last_not_of( n, spos );
		}

		//TODO: Optimized search for single char
		inline int find_last_not_of( char c, int spos = npos ) const {
			string n( &c, 1 );
			return find_last_not_of( n );
		}
		
	private:
		char* _cstr_;
		array_allocator<char> _alloc_;
		
	};
	
}

#endif // _kick_string_h
