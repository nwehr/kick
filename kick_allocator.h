//
//      Copyright 2013 Nathan Wehr. All Rights Reserved.
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

#ifndef _kick_allocator_h
#define _kick_allocator_h

#include <cstdlib>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator {
	public:
		array_allocator()
		: _asize_( 0 )
		, _usize_( 0 )
		{}
		
		virtual ~array_allocator(){}
		
		int asize() const {
			return _asize_;
		}
		
		int usize() const {
			return _usize_;
		}
		
		T* malloc( int size ){
			_usize_ = size;
			_asize_ = size + 2;
			
			T* ptr = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) );
			
			if( ptr )
				return ptr;
			
			exit( -1 );
			
		}
		
		T* realloc( T*& mem, int size ){
			_usize_ = size;

			if( _usize_ > _asize_ || (_asize_ - _usize_) > 3 )
				_asize_ = _usize_ + 2;

			T* ptr = static_cast<T*>( ::realloc( mem, sizeof( T ) * _asize_ ) );

			if( ptr )
				return ptr;
			
			exit( -1 );
			
		}
		
		void free( T*& mem ){
			::free( mem );
		}
		
	private:
		int _asize_;
		int _usize_;
		
	}; 
	
	///////////////////////////////////////////////////////////////////////////////
	// string_allocator
	///////////////////////////////////////////////////////////////////////////////
	class string_allocator {
	public:
		string_allocator()
		: _size_( 0 )
		, _mem_( 0 )
		{}
		
		string_allocator( char** mem )
		: _size_( 0 )
		, _mem_( mem )
		{}
		
		virtual ~string_allocator(){}
		
		char* alloc( int size ){
			_size_ = size; 
			
			char* ptr = static_cast<char*>( realloc( *_mem_, (sizeof( void* ) * _size_) ) );
			
			if( ptr ) return ptr;
			else return *_mem_;
			
		}
		
		void free(){
			::free( *_mem_ );
		}
		
	private:
		int _size_;
		char** _mem_;
		
	};
	
	
}

#endif // _kick_allocator_h
