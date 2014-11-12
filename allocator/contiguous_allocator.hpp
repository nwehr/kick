#ifndef _kick_contiguous_allocator_h
#define _kick_contiguous_allocator_h

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
#if (KICK_EXCEPTION > 0)
	///////////////////////////////////////////////////////////////////////////////
	// malloc_exception
	///////////////////////////////////////////////////////////////////////////////
	class malloc_exception : public exception {
	public:
		malloc_exception() : exception() {}
		const char* what() const { return "Unable to allocate new memory."; }
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// move_exception
	///////////////////////////////////////////////////////////////////////////////
	class move_exception : public exception {
	public:
		explicit move_exception( void* adx )
		: exception()
		, _msg( new char[50] )
		{
			sprintf( _msg, "Unable to move memory block to %02lux", reinterpret_cast<unsigned long>( adx ) );
		}

		~move_exception() { delete[] _msg; }
		
		const char* what() const { return _msg; }
		
	private:
		char* _msg;
		
	};
	
#endif // KICK_EXCEPTION
	
	///////////////////////////////////////////////////////////////////////////////
	// contiguous_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class contiguous_allocator {
	public:
		contiguous_allocator( const function<size_t, size_t, size_t>& calc = &default_calc );
		~contiguous_allocator();
		
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
	// contiguous_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	contiguous_allocator<T>::contiguous_allocator( const function<size_t, size_t, size_t>& calc )
	: _asize_( 0 )
	, _usize_( 0 )
	, _calc_( calc )
	{}
	
	template<typename T>
	contiguous_allocator<T>::~contiguous_allocator(){}
	
	template<typename T>
	size_t contiguous_allocator<T>::asize() const {
		return _asize_;
	}
	
	template<typename T>
	size_t contiguous_allocator<T>::usize() const {
		return _usize_;
	}
	
	template<typename T>
	T* contiguous_allocator<T>::malloc( T* mem, size_t size ){
		T* ptr = 0;
		
		_usize_ = size;
		_asize_ = _calc_( size, _asize_ );
		
		if( !(ptr = static_cast<T*>( ::malloc( sizeof( T ) * _asize_ ) )) ){
#if (KICK_EXCEPTION > 0)
			throw malloc_exception();
#else
			
#endif
		}
		
		for( size_t i = 0; i < _asize_; ++i )
			new( &ptr[i] ) T();
		
		return ptr;
		
	}
	
	template<typename T>
	T* contiguous_allocator<T>::realloc( T* mem, size_t size ){
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
	T* contiguous_allocator<T>::move( T* mem, size_t src_index, size_t dest_index ){
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
	void contiguous_allocator<T>::free( T* mem ){
		for( size_t i = 0; i < _usize_; ++i )
			mem[i].~T();
		
		::free( mem );
		
	}
	
}

#endif // _kick_contiguous_allocator_h