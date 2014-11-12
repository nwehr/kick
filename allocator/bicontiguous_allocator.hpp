#ifndef kick_allocator_bicontiguous_allocator_h
#define kick_allocator_bicontiguous_allocator_h

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
#include "../exception.hpp"
#include "../functional.hpp"

#include "./memory_block.hpp"

kick::size_t default_pre_calc( kick::size_t size, kick::size_t asize )
{
	if (size >= asize) {
		return size + 4;
	} else if (size < (asize - 4)){
		return asize - 4;
	}
	
	return asize;
}

kick::size_t default_app_calc( kick::size_t size, kick::size_t asize ) {
	if (size >= asize) {
		return size + 4;
	} else if (size < (asize - 4)){
		return asize - 4;
	}
	
	return asize;
}

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// bicontiguous_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class bicontiguous_allocator {
	public:
		bicontiguous_allocator( const function<size_t, size_t, size_t>& pre_calc = &default_pre_calc
							   , const function<size_t, size_t, size_t>& app_calc = &default_app_calc );
		
		~bicontiguous_allocator();
		
		size_t asize() const;
		size_t usize() const;
		
		T* malloc	( T* mem, size_t size );
		T* realloc	( T* mem, size_t size );
		T* move		( T* mem, size_t src_index, size_t dest_index );
		T* copy		( T* src, T* dest );
		void free	( T* mem );
		
		T* item( size_t i ) {
			if (i >= _pre_.psize) {
				return _append_b.mem[i - _prepend_b.psize];
			}
			
			return _prepend_b.mem[_prepend_b.psize - (i + 1)];
		}
		
	protected:
		memory_block<T> _prepend_b;
		memory_block<T> _append_b;
		
		function<size_t, size_t, size_t> _prepend_calc;
		function<size_t, size_t, size_t> _append_calc;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// bicontiguous_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	bicontiguous_allocator<T>::bicontiguous_allocator( const function<size_t, size_t, size_t>& prepend_calc = &default_prepend_calc
													  , const function<size_t, size_t, size_t>& append_calc = &default_append_calc )
	: _prepend_calc	( prepend_calc )
	, _append_calc	( append_calc )
	{}
	
	template<typename T>
	bicontiguous_allocator<T>::~bicontiguous_allocator(){}
	
	template<typename T>
	size_t bicontiguous_allocator<T>::asize() const {
		return _prepend_b.asize + _append_b.asize;
	}
	
	template<typename T>
	size_t bicontiguous_allocator<T>::psize() const {
		return _prepend_b.psize + _append_b.psize;
	}
	
	template<typename T>
	int bicontiguous_allocator<T>::malloc( size_t size ){
		// check prepend memory_block
		{
			_prepend_b.mem = 0;
			
			_prepend_b.psize = 0;
			_prepend_b.asize = _prepend_calc( size, _prepend_b.asize );
			
			if (!(ptr = static_cast<T*>( ::malloc( sizeof( T ) * _prepend_b.asize ) ))) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#endif
				return 1;
				
			}
			
			for (size_t i = 0; i < _prepend_b.asize; ++i) {
				new( (&_prepend_b.mem)[i] ) T();
			}
			
		}
		
		// check append memory_block
		{
			_append_b.mem = 0;
			
			_append_b.psize = 0;
			_append_b.asize = _append_calc( size, _append_b.asize );
			
			if (!(ptr = static_cast<T*>( ::malloc( sizeof( T ) * _append_b.asize ) ))) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#endif
				return 1;
				
			}
			
			for (size_t i = 0; i < _append_b.asize; ++i) {
				new( (&_append_b.mem)[i] ) T();
			}
			
		}
		
		return 0;
		
	}
	
	template<typename T>
	T* bicontiguous_allocator<T>::realloc( T* mem, size_t size ){
		T* ptr = 0;
		
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
	T* bicontiguous_allocator<T>::move( T* mem, size_t src_index, size_t dest_index ){
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
	void bicontiguous_allocator<T>::free( T* mem ){
		for( size_t i = 0; i < _usize_; ++i )
			mem[i].~T();
		
		::free( mem );
		
	}
	
}

#endif
