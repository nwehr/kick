#ifndef _kick_allocator_h
#define _kick_allocator_h

//
//      Copyright 2013 Nathan Wehr. All Rights Reserved.
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
#include <stdlib.h>
#include <string.h>

// Kick
#include <kick/config.h>

#ifdef ARDUINO
	// missing operator placement new on Arduino
	void* operator new( size_t size, void* ptr ) { return ptr; }
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator {
	public:
		array_allocator( const size_t alloc_ext = 4 );
		array_allocator( const array_allocator& alloc );
		
		~array_allocator(); 
		
		size_t asize() const;
		size_t usize() const;
		
		T* malloc( T* mem, size_t size );

		T* realloc( T* mem, size_t size );
		
		T* move( T* mem, unsigned int src_index, unsigned int dest_index );
		
		void free( T* mem );
		
	protected:
		size_t _asize_;
		size_t _usize_;
		size_t _stpos_;
		
		const size_t _alloc_ext_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	array_allocator<T>::array_allocator( const size_t alloc_ext )
	: _asize_( 0 )
	, _usize_( 0 )
	, _alloc_ext_( alloc_ext )
	{}
	
	template<typename T>
	array_allocator<T>::array_allocator( const array_allocator& alloc )
	: _asize_( alloc._asize_ )
	, _usize_( alloc._usize_ )
	, _alloc_ext_( alloc._alloc_ext_ )
	{}
	
	template<typename T>
	array_allocator<T>::~array_allocator(){}
	
	template<typename T>
	size_t array_allocator<T>::asize() const {
		return _asize_;
	}
	
	template<typename T>
	size_t array_allocator<T>::usize() const {
		return _usize_;
	}
	
	template<typename T>
	T* array_allocator<T>::malloc( T* mem, size_t size ){
		_usize_ = size;
		_asize_ = size + _alloc_ext_;
		
		mem = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) );
		
		for( size_t i = 0; i < _usize_; ++i )
			new( &mem[i] ) T();
		
		return mem;
		
	}
	
	template<typename T>
	T* array_allocator<T>::realloc( T* mem, size_t size ){
		bool reallocate( false );
		
		// call destructors if shrinking
		if( size < _usize_ ) {
			for( size_t i = size; i < _usize_; ++i )
				mem[i].~T();
			
			
		} else {
			if( size >= _asize_ ){
				_asize_ = size + _alloc_ext_;
				reallocate = true;
				
			} else if( (_asize_ - size) > _alloc_ext_ ){
				_asize_ = size;
				reallocate = true;
				
			}
			
		}
		
		if( reallocate )
			mem = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * _asize_ ) );
		
		if( size > _usize_ ){
			for( size_t i = _usize_; i < size; ++i )
				new( &mem[i] ) T();
			
			
		}
		
		_usize_ = size;
		
		return mem;
		
	}
	
	template<typename T>
	T* array_allocator<T>::move( T* mem, unsigned int src_index, unsigned int dest_index ){
		// Call destructors on items if we're overwriting them...
		if( dest_index < src_index ){
			for( unsigned int i = dest_index; i < src_index + 1; ++i )
				mem[i].~T();
			
			
		}
		
		// Call destructors at the end of the memory block
		if( dest_index > src_index ){
			for( unsigned int i = dest_index; i < dest_index + 1; ++i )
				mem[i].~T();
			
		}
		
		::memmove( static_cast<void*>( &mem[dest_index] )
				  , static_cast<void*>( &mem[src_index] )
				  , sizeof( T ) * (_usize_ - src_index) );
		
		// This was the old method of shifting the array... much, much slower...
		// 			for( int i = (_usize_ - (dest_index - src_index)); i > src_index; --i )
		// 				mem[i] = mem[i - (dest_index - src_index)];
		
		return mem;
		
	}
	
	template<typename T>
	void array_allocator<T>::free( T* mem ){
		for( size_t i = 0; i < _usize_; ++i )
			mem[i].~T();
		
		::free( mem );
		
	}
	
}

#endif // _kick_allocator_h
