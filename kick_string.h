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
		: _cstr_( 0 )
		, _alloc_()
		{
			_cstr_ = _alloc_.malloc( 1 ); 
		}
		
		string( const char* cstr )
		: _cstr_( 0 )
		, _alloc_()
		{
			int size( 0 );
			
			while( cstr[size] )
				++size;
			
			_cstr_ = _alloc_.malloc( size );
			
			for( int i = 0; i < size; ++i )
				_cstr_[i] = cstr[i];
			
		}
		
		string( const string& str )
		: _cstr_( 0 )
		, _alloc_()
		{
			_cstr_ = _alloc_.malloc( str.size() ); 
			
			for( int i = 0; i < size(); ++i )
				_cstr_[i] = str._cstr_[i];

		}
		
		virtual ~string(){
			_alloc_.free( _cstr_ );
		}
		
		string& operator=( const string& str ){
			_cstr_ = _alloc_.malloc( str.size() );
			
			for( int i = 0; i < size(); ++i )
				_cstr_[i] = str._cstr_[i];
			
			return *this;
			
		}
		
		bool operator==( const string& str ) const {
			if( size() == str.size() ){
				for( int i = 0; i < size(); ++i )
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
			if( i < size() && i >= 0 )
				return _cstr_[i];
			
			exit( -1 ); //TODO: out-of-range, do something!!!
			
		}
		
		int size() const {
			return _alloc_.usize();
		}
		
		char* c_str() const {
			return _cstr_;
		}
		
	private:
		char* _cstr_;
		string_allocator<char> _alloc_;
		
	};
	
}

#endif // _kick_string_h
