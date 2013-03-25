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

// C
#include <stdlib.h>
#include <string.h>

// Kick
#include <kick/kick_config.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator {
	public:
		array_allocator( const unsigned int alloc_ext = 4 )
		: _asize_( 0 )
		, _usize_( 0 )
		, _alloc_ext_( alloc_ext )
		{}
		
		array_allocator( const array_allocator& alloc )
		: _asize_( alloc._asize_ )
		, _usize_( alloc._usize_ )
		, _alloc_ext_( alloc._alloc_ext_ )
		{}
		
		array_allocator( T*& mem, kick::size_t size = 0, const int alloc_ext = 4 )
		: _asize_( 0 )
		, _usize_( 0 )
		, _alloc_ext_( alloc_ext )
		{
			mem = array_allocator::malloc( size );
		}
		
		~array_allocator(){}
		
		kick::size_t asize() const {
			return _asize_;
		}
		
		kick::size_t usize() const {
			return _usize_;
		}
		
		void malloc( T*& mem, kick::size_t size ){
			_usize_ = size;
			_asize_ = size + _alloc_ext_;
			
			//TODO: memory should be properly aligned for these objects
			mem = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) );
			
			for( int i = 0; i < _usize_; ++i )
				new( &mem[i] ) T();
			
			
		}
		
		void realloc( T*& mem, kick::size_t size ){
			// call destructors if shrinking
			if( size < _usize_ ) {
				for( int i = size; i < _usize_; ++i )
					mem[i].~T();
				
				
			}

			bool reallocate( false );
			
			if( size > _asize_ ){
				_asize_ = size + _alloc_ext_;
				reallocate = true;
				
			} else if( (_asize_ - size) > _alloc_ext_ ){
				_asize_ = size;
				reallocate = true;
				
			}
				
			//TODO: memory should be properly aligned for these objects
			if( reallocate )
				mem = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * _asize_ ) );
			
			if( size > _usize_ ){
				for( int i = _usize_; i < size; ++i )
					new( &mem[i] ) T();
				
				
			}

			_usize_ = size;

		}
		
		void move( T*& mem, int src_index, int dest_index ){
			// Call destructors on items if we're overwriting them...
			if( dest_index < src_index ){
				for( int i = dest_index; i < src_index + 1; ++i )
					mem[i].~T();
				
				
			}
			
			if( dest_index > src_index ){
				for( int i = dest_index; i < dest_index + 1; ++i )
					mem[i].~T();
				
			}
			
			::memmove( static_cast<void*>( &mem[dest_index] )
					, static_cast<void*>( &mem[src_index] )
					, sizeof( T ) * (_usize_ - src_index) );
			
			// This was the old method of shifting the array... much, much slower...
// 			for( int i = (_usize_ - (dest_index - src_index)); i > src_index; --i )
// 				mem[i] = mem[i - (dest_index - src_index)];
			
		}
		
//		void copy( T*& src, T*& dest ){
//			return static_cast<T*>( ::memcpy( dest, src, sizeof( T ) * _usize_ ) );
//		}
		
		void free( T*& mem ){
			for( int i = 0; i < _usize_; ++i )
				mem[i].~T();
			
			::free( mem );
			
		}
		
	protected:
		kick::size_t _asize_;
		kick::size_t _usize_;
		
		// start position
		int _stpos_;
		
		const unsigned int _alloc_ext_;
		
	};
	
}

#endif // _kick_allocator_h
