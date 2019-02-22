#ifndef _kick_vector_h
#define _kick_vector_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "./common.hpp"

#include "./allocator/array_allocator.hpp"

#include "./iterator.hpp"
#include "./functional.hpp"

#ifndef KICK_POLYMORPHIC_VECTOR
#define KICK_POLYMORPHIC_VECTOR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename AllocT = array_allocator<T> >
	class vector {
	public:
		typedef kick::array_iterator<T> iterator;
		typedef kick::const_array_iterator<T> const_iterator;
		
		vector( kick::size_t size = 0, AllocT alloc = AllocT() );
		vector( const vector<T>& vec );

#if (KICK_POLYMORPHIC_VECTOR > 0)
		virtual
#endif
		~vector();
		
		const vector<T>& operator=( const vector<T>& );
		
		inline void clear();
		inline bool empty() const;
		
		void erase( size_t );
		void erase( array_iterator<T> );
		
		void push_back( const T& );
		void push_front( const T& );
		
		void pop_back();
		void pop_front();

		void for_each(void (*)(const T&)) const;

		template<typename O = T>
		void map_to(vector<O>&, O (*)(const T&)) const;

		template<typename O = T>
		void reduce_to(O&, O (*)(const O&, const T&)) const;

		void filter_to(vector<T>&, bool (*)(const T&)) const;
		
		inline const size_t size() const;
		inline const size_t capacity() const;
		
		inline T& front();
		inline T& back();
		
		inline iterator begin() const;
		inline iterator end() const;
		
		inline T& operator[]( size_t );

		
	private:
		T* _mem;
		AllocT _alloc;
		
	};
		
	
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( kick::size_t size, AllocT alloc )
	: _mem( 0 )
	, _alloc( alloc )
	{
		_mem = _alloc.malloc( _mem, size );
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( const vector<T>& vec )
	: _mem( 0 )
	, _alloc( vec._alloc )
	{
		_mem = _alloc.malloc( _mem, size() );
		
		for( kick::size_t i = 0; i < vec.size(); ++i )
			_mem[i] = vec._mem[i];
		
		
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::~vector() {
		if( _mem )
			_alloc.free( _mem );
		
	}
	
	template<typename T, typename AllocT>
	const vector<T>& vector<T,AllocT>::operator=( const vector<T>& vec ) {
		if( this != &vec ) {
			_alloc.free( _mem );
			
			_mem = _alloc.malloc( _mem, vec.size() );
			
			for( int i = 0; i < size(); ++i )
				_mem[i] = vec._mem[i];
			
			
		}
		
		return *this;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::clear() {
		// _alloc.free( _mem );
		_mem = _alloc.realloc( _mem, 0 );
	}
	
	template<typename T, typename AllocT>
	bool vector<T,AllocT>::empty() const {
		return size();
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase( size_t index ) {
		if( index < size() ){
			_mem = _alloc.move( _mem, index + 1, index );
			_mem = _alloc.realloc( _mem, size() - 1 );
			
		}
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase( array_iterator<T> pos ) {
		_mem = _alloc.move( _mem, pos.index() + 1, pos.index() );
		_mem = _alloc.realloc( _mem, size() - 1 );
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_back( const T& item ) {
		_mem = _alloc.realloc( _mem, size() + 1 );
		
		_mem[size() - 1] = item;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_front( const T& item ) {
		_mem = _alloc.realloc( _mem, size() + 1 );
		_mem = _alloc.move( _mem, 0, 1 );
		
		_mem[0] = item;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::pop_back() {
		if( size() )
			_mem = _alloc.realloc( _mem, size() - 1 );
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::pop_front() {
		if( size() ){
			_mem = _alloc.move( _mem, 1, 0 );
			_mem = _alloc.realloc( _mem, size() - 1 );
			
		}	
	}

	template<typename T, typename AllocT>
	void vector<T, AllocT>::for_each(void (*fn)(const T&)) const {
		for(vector<T, AllocT>::iterator it = begin(); it != end(); ++it) {
			fn(*it);
		}
	}

	template<typename T, typename AllocT>
	template<typename O>
	void vector<T, AllocT>::map_to(vector<O>& out, O (*fn)(const T&)) const {
		for(vector<T, AllocT>::iterator it = begin(); it != end(); ++it) {
			out.push_back(fn(*it));
		}
	}

	template<typename T, typename AllocT>
	template<typename O>
	void vector<T, AllocT>::reduce_to(O& out, O (*fn)(const O&, const T&)) const {
		for(vector<T, AllocT>::iterator it = begin(); it != end(); ++it) {
			out = fn(out, *it);
		}
	}
	
	template<typename T, typename AllocT>
	void vector<T, AllocT>::filter_to(vector<T>& out, bool (*fn)(const T&)) const {
		for(vector<T, AllocT>::iterator it = begin(); it != end(); ++it) {
			if(fn(*it)) {
				out.push_back(*it);
			}
		}
	}
	
	template<typename T, typename AllocT>
	const size_t vector<T,AllocT>::size() const {
		return _alloc.usize();
	}
	
	template<typename T, typename AllocT>
	const size_t vector<T,AllocT>::capacity() const {
		return _alloc.asize();
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::front() {
		return _mem[0];
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::back() {
		return _mem[size() - 1];
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::begin() const {
		return iterator( 0, _mem );
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::end() const {
		return iterator( size(), _mem );
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::operator[]( size_t index ) {
		return _mem[index];
	}

} // namespace kick

#endif // _kick_vector_h
