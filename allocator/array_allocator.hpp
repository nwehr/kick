#ifndef _kick_array_allocator_h
#define _kick_array_allocator_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Kick
#include "../common.hpp"
#include "../functional.hpp"

#include "./mem_exception.hpp"

kick::size_t default_calc( kick::size_t size, kick::size_t asize );

kick::size_t default_calc( kick::size_t size, kick::size_t asize )
{
	if (size >= asize) {
		return size + 4;
	} else if (size < (asize - 4)){
		return asize - 4;
	}
	
	return asize;
	
}

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator {
	public:
		array_allocator( const function<size_t, size_t, size_t>& calc = &default_calc );
		array_allocator( const array_allocator<T>& ) = default;
		
		size_t asize() const;
		size_t usize() const;
		
		T* malloc	( T* mem, size_t size );
		T* realloc	( T* mem, size_t size );
		T* move		( T* mem, size_t src_index, size_t dest_index );
		T* copy		( T* src, T* dest );
		void free	( T* mem );
		
	protected:
		size_t _asize_;
		size_t _usize_;
		
		function<size_t, size_t, size_t> _calc_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	array_allocator<T>::array_allocator( const function<size_t, size_t, size_t>& calc )
	: _asize_( 0 )
	, _usize_( 0 )
	, _calc_( calc )
	{}
	
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
		mem = nullptr;
		
		_usize_ = size;
		_asize_ = _calc_( size, _asize_ );
		
		if( !(mem = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) )) ){
#if (KICK_EXCEPTION > 0)
			throw malloc_exception();
#else
			
#endif
		}
		
		for( size_t i = 0; i < _asize_; ++i )
			new( &mem[i] ) T();
		
		return mem;
		
	}
	
	template<typename T>
	T* array_allocator<T>::realloc( T* mem, size_t size ){
		T* ptr = nullptr;
		
		size_t asize = _calc_( size, _asize_ );
		
		if( asize > _asize_ ){
			if( !(ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) )) ) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#else
				
#endif
			}
			
			
			for( size_t i = _asize_; i < asize; ++i )
				new( &ptr[i] ) T();
			
			_asize_ = asize;
			_usize_ = size;
			
		} else if( asize < _asize_ ){
			if( !(ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) )) ) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#else
				
#endif
			}
			
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
				new( &mem[i] ) T();
			}
			
		}
		
		if( !::memmove( static_cast<void*>( &mem[dest_index] ), static_cast<void*>( &mem[src_index] ), sizeof( T ) * (_usize_ - src_index) ) ) {
#if (KICK_EXCEPTION > 0)
			throw move_exception( static_cast<void*>( &mem[dest_index] ) );
#else
			
#endif
		}
		
		
		// items at the end of the memory block
		if( dest_index > src_index ){
			for( size_t i = src_index; i < dest_index; ++i ){
				new( &mem[i] ) T();
			}
			
		}
		
		return mem;
		
	}
	
	template<typename T>
	void array_allocator<T>::free( T* mem ){
		for( size_t i = 0; i < _usize_; ++i )
			mem[i].~T();
		
		::free( mem );
		
	}
	
}

#endif // _kick_array_allocator_h
