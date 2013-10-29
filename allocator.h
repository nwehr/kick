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
#include <kick/common.h>
#include <kick/exception.h>

#ifdef ARDUINO
	// missing operator placement new on Arduino
	void* operator new( size_t size, void* ptr ) { return ptr; }
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// allocator_malloc_exception
	///////////////////////////////////////////////////////////////////////////////
	class allocator_malloc_exception : public exception {
	public:
		allocator_malloc_exception()
		: exception()
		{}
		
		virtual const char* what() const { return "Unable to allocate new memory."; }
		
	};
	
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
		
		T* move( T* mem, size_t src_index, size_t dest_index );
		
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
		T* ptr = 0;
		
		_usize_ = size;
		_asize_ = size + _alloc_ext_;
		
		ptr = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) );
		
		if( !ptr )
			throw allocator_malloc_exception();
		
		for( size_t i = 0; i < _asize_; ++i )
			new( &ptr[i] ) T();
		
		return ptr;
		
	}
	
//	template<typename T>
//	T* array_allocator<T>::realloc( T* mem, size_t size ){
//		bool reallocate( false );
//		size_t prev_size( _asize_ ); 
//		
//		// call destructors if shrinking
//		if( size < _usize_ ){
//			for( size_t i = size; i < _usize_; ++i )
//				mem[i].~T();
//			
//			for( size_t i = size; i < _usize_; ++i )
//				new( &mem[i] ) T(); 
//			
//		} else {
//			if( size >= _asize_ ){
//				_asize_ = size + _alloc_ext_;
//				reallocate = true;
//				
//			} else if( (_asize_ - size) > _alloc_ext_ ){
//				_asize_ = size;
//				reallocate = true;
//				
//			}
//			
//		}
//		
//		if( reallocate )
//			mem = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * _asize_ ) );
//		
//		if( prev_size != _asize_ ){
//			if( prev_size < _asize_ ){
//				for( size_t i = prev_size; i < _asize_; ++i ){
//					new( &mem[i] ) T();
//					
//				}
//				
//			}
//			
//		}
//		
//		_usize_ = size;
//		
//		return mem;
//		
//	}

	template<typename T>
	T* array_allocator<T>::realloc( T* mem, size_t size ){
		T* ptr = 0;
		
		if( size >= _asize_ ){
			size_t asize = size + _alloc_ext_; 
			
			ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) );
			
			if( !ptr )
				throw allocator_malloc_exception();
			
			for( size_t i = _asize_; i < asize; ++i )
				new( &ptr[i] ) T();
			
			_asize_ = asize;
			_usize_ = size;
			
		} else if( size < (_asize_ - _alloc_ext_) ){
			size_t asize = (_asize_ - _alloc_ext_);
						
			ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) );
			
			
			if( !ptr )
				throw allocator_malloc_exception();
			
			for( size_t i = _asize_; i >= asize; --i )
				mem[i].~T();
			
			_asize_ = asize;
			_usize_ = size;
			
		} else {
			ptr = mem;
			
			_usize_ = size;
			
		}
				
		return ptr;
		
	}
	
	template<typename T>
	T* array_allocator<T>::move( T* mem, size_t src_index, size_t dest_index ){
		// overwritten items
		if( dest_index < src_index ){
			for( size_t i = dest_index; i < src_index; ++i ){
				mem[i].~T();
				//new( &mem[i] ) T();
				
			}
			
		}
		
		::memmove( static_cast<void*>( &mem[dest_index] ), static_cast<void*>( &mem[src_index] ), sizeof( T ) * (_usize_ - src_index) );
		
		// items at the end of the memory block
		if( dest_index > src_index ){
			for( size_t i = src_index; i < dest_index; ++i ){
				new( &mem[i] ) T();
			}
			
		}
		
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
