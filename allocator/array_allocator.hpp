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
#include "../optional.hpp"
#include "../error.hpp"

#include "./mem_exception.hpp"

kick::size_t default_next_capacity(kick::size_t size, kick::size_t capacity);
kick::size_t default_next_capacity(kick::size_t size, kick::size_t capacity) {
	if(size >= capacity) {
		return size + 8;
	} else if(size < (capacity - 8)) {
		return capacity - 8;
	} else {
		return capacity;
	}
}

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// malloc_error
	///////////////////////////////////////////////////////////////////////////////
	struct malloc_error : public error {
		malloc_error(size_t size) : error() {
			code = 0;
			what = "could not malloc";
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	// realloc_error
	///////////////////////////////////////////////////////////////////////////////
	struct realloc_error : public error {
		realloc_error(size_t size) : error() {
			code = 1;
			what = "could not realloc";
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	// move_error
	///////////////////////////////////////////////////////////////////////////////
	struct move_error : public error {
		move_error(size_t source_index, size_t dest_index) : error() {
			code = 2;
			what = "could not move"; 
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_allocator {
	public:
		array_allocator(size_t (*next_capacity)(size_t, size_t) = &default_next_capacity);
		array_allocator(const array_allocator<T>&) = default;
		
		[[deprecated]] inline size_t asize() const;
		[[deprecated]] inline size_t usize() const;
		
		inline size_t size() const;
		inline size_t capacity() const;

		inline T* mem() const;
		
		[[deprecated]] T* malloc	( T* mem, size_t size );
		[[deprecated]] T* realloc	( T* mem, size_t size );
		[[deprecated]] T* move		( T* mem, size_t source_index, size_t dest_index );
		[[deprecated]] void free	( T* mem );

		optional<malloc_error> 	malloc(size_t);
		optional<realloc_error> realloc(size_t);
		optional<move_error> 	move(size_t source_index, size_t dest_index);
		void free();

		T& operator[](size_t);
		
	protected:
		size_t _size;
		size_t _capacity;

		T* _mem;
		
		size_t (*_next_capacity)(size_t, size_t);
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// array_allocator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	array_allocator<T>::array_allocator(size_t (*next_capacity)(size_t, size_t))
	: _size(0)
	, _capacity(0)
	, _mem(nullptr)
	, _next_capacity(next_capacity)
	{}
	
	template<typename T>
	size_t array_allocator<T>::asize() const {
		return _capacity;
	}
	
	template<typename T>
	size_t array_allocator<T>::usize() const {
		return _size;
	}

	template<typename T>
	size_t array_allocator<T>::capacity() const {
		return _capacity;
	}
	
	template<typename T>
	size_t array_allocator<T>::size() const {
		return _size;
	}

	template<typename T>
	T* array_allocator<T>::mem() const {
		return _mem;
	}
	
	template<typename T>
	T* array_allocator<T>::malloc( T* mem, size_t size ){
		mem = nullptr;
		
		_size = size;
		_capacity = _next_capacity( size, _capacity );
		
		if( !(mem = static_cast<T*>( ::malloc( sizeof( T ) * _capacity ) )) ){
#if (KICK_EXCEPTION > 0)
			throw malloc_exception();
#else
			
#endif
		}
		
		for( size_t i = 0; i < _capacity; ++i )
			new( &mem[i] ) T();
		
		return mem;
	}

	template<typename T>
	optional<malloc_error> array_allocator<T>::malloc(size_t size ){
		if(_mem) {
			free();
		}
		
		_size = size;
		_capacity = _next_capacity(size, _capacity);
		
		if(!(_mem = static_cast<T*>(::malloc(sizeof(T) * _capacity)))){
			return optional<malloc_error>(malloc_error(size));
		}
		
		for(size_t i = 0; i < _capacity; ++i) {
			new(&_mem[i]) T();
		}

		return optional<malloc_error>();
	}
	
	template<typename T>
	T* array_allocator<T>::realloc( T* mem, size_t size ){
		T* ptr = nullptr;
		
		size_t asize = _next_capacity( size, _capacity );
		
		if( asize > _capacity ){
			if( !(ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) )) ) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#else
				
#endif
			}
			
			
			for( size_t i = _capacity; i < asize; ++i )
				new( &ptr[i] ) T();
			
			_capacity = asize;
			_size = size;
			
		} else if( asize < _capacity ){
			if( !(ptr = static_cast<T*>( ::realloc( static_cast<void*>( mem ), sizeof( T ) * asize ) )) ) {
#if (KICK_EXCEPTION > 0)
				throw malloc_exception();
#else
				
#endif
			}
			
			for( size_t i = _capacity; i >= asize; --i )
				mem[i].~T();
			
			_capacity = asize;
			_size = size;
			
		} else {
			ptr = mem;
			_size = size;
		}
		
		return ptr;
		
	}

	template<typename T>
	optional<realloc_error> array_allocator<T>::realloc(size_t next_size ){
		size_t next_capacity = _next_capacity(next_size, _capacity);
		
		if(next_capacity > _capacity) {
			if(!(_mem = static_cast<T*>(::realloc(static_cast<void*>(_mem), sizeof(T) * next_capacity)))) {
				return optional<realloc_error>(realloc_error(next_size));
			}
			
			for(size_t i = _capacity; i < next_capacity; ++i) {
				new(&_mem[i]) T();
			}
			
			_capacity = next_capacity;
			_size = next_size;
		} else if(next_capacity < _capacity) {
			if(!(_mem = static_cast<T*>(::realloc(static_cast<void*>(_mem), sizeof(T) * next_capacity)))) {
				return optional<realloc_error>(realloc_error(next_size));
			}
			
			for(size_t i = _capacity; i >= next_capacity; --i) {
				_mem[i].~T();
			}
			
			_capacity = next_capacity;
			_size = next_size;
		} else {
			_size = next_size;
		}

		return optional<realloc_error>();
	}
	
	template<typename T>
	T* array_allocator<T>::move( T* mem, size_t source_index, size_t dest_index ){
		// overwritten items
		if( dest_index < source_index ){
			for( size_t i = dest_index; i < source_index; ++i ){
				mem[i].~T();
				new( &mem[i] ) T();
			}
			
		}
		
		if( !::memmove( static_cast<void*>( &mem[dest_index] ), static_cast<void*>( &mem[source_index] ), sizeof( T ) * (_size - source_index) ) ) {
#if (KICK_EXCEPTION > 0)
			throw move_exception( static_cast<void*>( &mem[dest_index] ) );
#else
			
#endif
		}
		
		
		// items at the end of the memory block
		if( dest_index > source_index ){
			for( size_t i = source_index; i < dest_index; ++i ){
				new( &mem[i] ) T();
			}
			
		}
		
		return mem;
		
	}

	template<typename T>
	optional<move_error> array_allocator<T>::move(size_t source_index, size_t dest_index ){
		// overwritten items
		if(dest_index < source_index) {
			for(size_t i = dest_index; i < source_index; ++i) {
				_mem[i].~T();
				new(&_mem[i]) T();
			}
		}
		
		if(!::memmove(static_cast<void*>(&_mem[dest_index]), static_cast<void*>(&_mem[source_index]), sizeof(T) * (_size - source_index))) {
			return optional<move_error>(move_error(source_index, dest_index));
		}
		
		// items at the end of the memory block
		if(dest_index > source_index) {
			for(size_t i = source_index; i < dest_index; ++i) {
				new(&_mem[i]) T();
			}
			
		}

		return optional<move_error>();
	}
	
	template<typename T>
	void array_allocator<T>::free( T* mem ){
		for( size_t i = 0; i < _size; ++i )
			mem[i].~T();
		
		::free( mem );
	}

	template<typename T>
	void array_allocator<T>::free(){
		for(size_t i = 0; i < _size; ++i) {
			_mem[i].~T();
		}
		
		::free(_mem);
	}

	template<typename T>
	T& array_allocator<T>::operator[](size_t index) {
		return _mem[index];
	}
}

#endif // _kick_array_allocator_h
