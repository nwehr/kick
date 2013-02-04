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

#ifndef _kick_allocator_h
#define _kick_allocator_h

#include <cstdlib>

#include <kick/kick_typdef.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class allocator {
	public:
		virtual ~allocator(){}
		
		virtual int asize() const = 0;
		virtual int usize() const = 0; 
		
		virtual T* malloc( int size ) = 0;
		virtual T* realloc( T*& mem, int size ) = 0;
		
		virtual void free( T*& ) = 0; 
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator : public allocator<T> {
	public:
		array_allocator( const int alloc_ext = 4 )
		: _asize_( 0 )
		, _usize_( 0 )
		, _alloc_ext_( alloc_ext )
		{}
		
		array_allocator( const array_allocator& alloc )
		: _asize_( alloc._asize_ )
		, _usize_( alloc._usize_ )
		, _alloc_ext_( alloc._alloc_ext_ )
		{}
		
		array_allocator( T*& mem, int size = 0, const int alloc_ext = 4 )
		: _asize_( 0 )
		, _usize_( 0 )
		, _alloc_ext_( alloc_ext )
		{
			mem = malloc( size );
		}
		
		virtual ~array_allocator(){}
		
		virtual int asize() const {
			return _asize_;
		}
		
		virtual int usize() const {
			return _usize_;
		}
		
		virtual T* malloc( int size ){
			_usize_ = size;
			_asize_ = size + _alloc_ext_;

			//TODO: memory should be properly aligned for these objects
			T* ptr = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) );

			for( int i = 0; i < _usize_; ++i )
				new( &ptr[i] ) T();

			return ptr;

		}
		
		virtual T* realloc( T*& mem, int size ){
			// call destructors if shrinking
			if( size < _usize_ ) {
				for( int i = size; i < _usize_; ++i )
					mem[i].~T();
				
				
			}

			if( size > _asize_ )
				_asize_ = size + _alloc_ext_;
			else if( (_asize_ - size) > _alloc_ext_ )
				_asize_ = size; 

			//TODO: memory should be properly aligned for these objects
			T* ptr = static_cast<T*>( ::realloc( mem, sizeof( T ) * _asize_ ) );

			if( size > _usize_ ){
				for( int i = _usize_; i < size; ++i )
					new( &ptr[i] ) T();	
				
				
			}

			_usize_ = size;

			return ptr;

		}
		
		T* move( T*& mem, int src_index, int dest_index ){
			// Call destructors on items if we're overwriting them...
			if( dest_index < src_index ){
				for( int i = dest_index; i < src_index + 1; ++i )
					mem[i].~T();
				
				
			}
			
			if( dest_index > src_index ){
				for( int i = src_index; i < dest_index; ++i )
					new( &mem[i] ) T();
				
			}
			
			return static_cast<T*>( memmove( &mem[dest_index], &mem[src_index], sizeof( T ) * (_usize_ - (dest_index - src_index)) ) );
			
			// This was the old method of shifting the array... much, much slower...
//			for( int i = (_usize_ - (dest_index - src_index)); i > src_index; --i )
//				mem[i] = mem[i - (dest_index - src_index)];
			
		}
		
		T* copy( T*& src, T*& dest ){
			return static_cast<T*>( memcpy( dest, src, sizeof( T ) * _usize_ ) );
		}
		
		virtual void free( T*& mem ){
			for( int i = 0; i < _usize_; ++i )
				mem[i].~T();
			
			::free( mem );
			
		}
		
	protected:
		int _asize_;
		int _usize_;
		
		const int _alloc_ext_;
		
	};
	
}

#endif // _kick_allocator_h
