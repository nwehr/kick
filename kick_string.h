//
//      Copyright 2012-2013 Nathan Wehr. All Rights Reserved.
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

#ifndef kick_string_h
#define kick_string_h

#include <cstdlib>
#include <kick/kick_allocator.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// string
	///////////////////////////////////////////////////////////////////////////////
	class string {
	public:
		string()
		: _size_( 1 )
		, _cstr_( static_cast<char*>( malloc( sizeof( char ) * 1 ) ) )
		{
			_cstr_[0] = 0;	// terminating null for c_str() support
		}
		
		string( const char* cstr )
		: _size_( 0 )
		, _cstr_( 0 )
		{
			while( cstr[_size_] )
				++_size_;
			
			_cstr_ = static_cast<char*>( malloc( sizeof( char ) * ++_size_ ) );	// include the trailing null char
			
			for( int i = 0; i < _size_; ++i )
				_cstr_[i] = cstr[i];
			
		}
		
		string( const string& str )
		: _size_( str._size_ )
		, _cstr_( static_cast<char*>( malloc( sizeof( char ) * str._size_ ) ) )
		{
			for( int i = 0; i < _size_; ++i )
				_cstr_[i] = str._cstr_[i];

		}
		
		virtual ~string(){
			free( _cstr_ ); 
			//_alloc_.free();
		}
		
		string& operator=( const string& str ){
			_size_ = str._size_;
			
			_cstr_ = static_cast<char*>( realloc( _cstr_, sizeof( char ) * _size_ ) );
			
			for( int i = 0; i < _size_; ++i )
				_cstr_[i] = str._cstr_[i];
			
			return *this;
			
		}
/*
		string& operator=( const char* cstr ){
			_size_ = 0;
			
			while( cstr[_size_] )
				++_size_;
			
			_cstr_ = static_cast<char*>( realloc( _cstr_, sizeof( char ) * ++_size_ ) );	// include the trailing null char
			
			for( int i = 0; i < _size_; ++i )
				_cstr_[i] = cstr[i];
			
			return *this;
			
		}
*/		
		bool operator==( const string& str ) const {
			if( _size_ == str._size_ ){
				for( int i = 0; i < _size_; ++i )
					if( _cstr_[i] != str._cstr_[i] )
						return false;
				
				return true;
				
			}
			
			return false;
			
		}
		
		bool operator!=( const string& str ) const {
			return !(*this == str);
		}
		
		char& operator[]( int i ){
			if( i < _size_ && i >= 0 )
				return _cstr_[i];
			
			exit( -1 ); //TODO: out-of-range, do something!!!
			
		}
		
		int size() const {
			return _size_ - 1;
		}
		
		char* c_str() const {
			return _cstr_;
		}
		
	private:
		int _size_;
		char* _cstr_;
		
//		string_allocator _alloc_;
		
	};
	
}

#endif // _kick_string_h
