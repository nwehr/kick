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
		
		vector<T>& operator=(const vector<T>&);
		
		inline void clear();
		inline bool empty() const;
		
		void erase( size_t );
		void erase( array_iterator<T> );
		
		void push_back( const T& );
		void push_front( const T& );
		
		void pop_back();
		void pop_front();

		vector<T, AllocT> filter(bool (*)(const T&)) const;

		template<typename O = T>
		vector<O, AllocT> transform(O (*)(const T&)) const;

		template<typename O = T>
		O reduce(O (*)(const O&, const T&)) const;
		
		inline size_t size() const;
		inline size_t capacity() const;
		
		inline T& front();
		inline T& back();
		
		inline iterator begin() const;
		inline iterator end() const;
		
		inline T& operator[]( size_t );

	private:
		AllocT _alloc;
	};
		
	
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( kick::size_t size, AllocT alloc )
	: _alloc( alloc )
	{
		if(_alloc.malloc(size)) {
			// error
		}
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( const vector<T>& vec )
	: _alloc(vec._alloc)
	{
		if(!_alloc.malloc(size())) {
			for(auto const& it : vec) {
				push_back(it);
			}
		}
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::~vector() {
		_alloc.free();
	}
	
	template<typename T, typename AllocT>
	vector<T>& vector<T,AllocT>::operator=( const vector<T>& vec ) {
		if(this != &vec) {
			_alloc.free();

			if(!_alloc.malloc(vec.size())) {
				for(auto const& it : vec) {
					push_back(it);
				}
			}
		}
		
		return *this;		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::clear() {
		_alloc.realloc(0);
	}
	
	template<typename T, typename AllocT>
	bool vector<T,AllocT>::empty() const {
		return size();
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase( size_t index ) {
		if(index < size()) {
			_alloc.move(index + 1, index);
			_alloc.realloc(size() - 1);
		}
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase(array_iterator<T> pos) {
		_alloc.move(pos.index() + 1, pos.index());
		_alloc.realloc(size() - 1);
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_back(const T& item) {
		_alloc.realloc(size() + 1);
		_alloc[size() - 1] = item;
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_front(const T& item) {
		_alloc.realloc(size() + 1);
		_alloc.move(0, 1);
		
		*this[0] = item;
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::pop_back() {
		if(size()) {
			_alloc.realloc(size() - 1);
		}
	}
	
	template<typename T, typename AllocT>
	void vector<T, AllocT>::pop_front() {
		if(size()) {
			_alloc.move(1, 0);
			_alloc.realloc(size() - 1);
		}	
	}

	template<typename T, typename AllocT>
	vector<T, AllocT> vector<T, AllocT>::filter(bool (*fn)(const T&)) const {
		vector<T, AllocT> filtered;

		for(auto const& it : *this) {
			if(fn(it)) {
				filtered.push_back(it);
			}
		}

		return filtered;
	}

	template<typename T, typename AllocT>
	template<typename O>
	vector<O, AllocT> vector<T, AllocT>::transform(O (*fn)(const T&)) const {
		vector<O, AllocT> mapped;

		for(auto const& it : *this) {
			mapped.push_back(fn(it));
		}

		return mapped;
	}

	template<typename T, typename AllocT>
	template<typename O>
	O vector<T, AllocT>::reduce(O (*fn)(const O&, const T&)) const {
		O reduced = O();

		for(auto const& it : *this) {
			reduced = fn(reduced, it);
		}

		return reduced;
	}
	
	template<typename T, typename AllocT>
	size_t vector<T,AllocT>::size() const {
		return _alloc.size();
	}
	
	template<typename T, typename AllocT>
	size_t vector<T,AllocT>::capacity() const {
		return _alloc.capacity();
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::front() {
		return _alloc[0];
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::back() {
		return _alloc[size() - 1];
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::begin() const {
		return iterator(0, _alloc.mem());
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::end() const {
		return iterator(size(), _alloc.mem());
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::operator[]( size_t index ) {
		return _alloc[index];
	}

} // namespace kick

#endif // _kick_vector_h
