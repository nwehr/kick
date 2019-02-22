#ifndef _kick_map_h
#define _kick_map_h

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

#include "./pair.hpp"

#ifndef KICK_POLYMORPHIC_MAP
#define KICK_POLYMORPHIC_MAP KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// map
	///////////////////////////////////////////////////////////////////////////////
	template<typename KeyT, typename ValT, typename AllocT = array_allocator< pair<KeyT,ValT> > >
	class map {
	public:
		typedef array_iterator< pair<KeyT,ValT> > iterator;
		typedef const_array_iterator< pair<KeyT,ValT> > const_iterator;
		
		map( size_t size = 0, AllocT alloc = AllocT() );
		map( const map<KeyT,ValT,AllocT>& );
		
#if (KICK_POLYMORPHIC_MAP > 0)
		virtual
#endif
		~map();
		
		map<KeyT,ValT,AllocT>& operator=( const map<KeyT,ValT,AllocT>& );
		
		bool find( const KeyT&, size_t& );
		
		void insert( const pair<KeyT,ValT>& );
		inline void insert( const KeyT&, const ValT& );
		
		inline const size_t size() const;
		inline const size_t capacity() const;
		
		ValT& operator[]( const KeyT& );

		void for_each(void (*fn)(const KeyT&, const ValT&)) const;

		template<typename O = ValT>
		void map_to(map<KeyT, O>&, O (*)(const KeyT&, const ValT&)) const;

		template<typename O = ValT>
		void reduce_to(O&, O (*)(const O&, const KeyT&, const ValT&)) const;

		void filter_to(map<KeyT, ValT>&, bool (*)(const KeyT&, const ValT&)) const;
		
		inline iterator begin() const;
		inline iterator end() const;
		
	private:
		pair<KeyT,ValT>* _mem_;
		AllocT _alloc_;
		
	};
	
} // namespace kick

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( size_t size, AllocT alloc )
: _mem_( 0 )
, _alloc_( alloc )
{
	_mem_ = _alloc_.malloc( _mem_, size );
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( const map<KeyT,ValT,AllocT>& map )
: _mem_( 0 )
, _alloc_( map._alloc_ )
{
	_mem_ = _alloc_.malloc( _mem_, size() );
	
	for( size_t i = 0; i < map.size(); ++i )
		_mem_[i] = map._mem_[i];
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::~map(){
	if( _mem_ )
		_alloc_.free( _mem_ );
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>& kick::map<KeyT,ValT,AllocT>::operator=( const map<KeyT,ValT,AllocT>& map ) {
	if( this != &map ){
		_mem_ = _alloc_.malloc( _mem_, size() );
		
		for( size_t i = 0; i < map.size(); ++i )
			_mem_[i] = map._mem_[i];
		
	}
	
	return *this;
	
}

template<typename KeyT, typename ValT, typename AllocT>
bool kick::map<KeyT,ValT,AllocT>::find( const KeyT& key, size_t& index ) {
	size_t min = 0;
	size_t mid = 0;
	size_t max = size();
	
	while( min + 1 < max ){
		mid = (min + max) / 2;
		
		if( _mem_[mid].key() > key ) max = mid;
		else min = mid;
		
	}
	
	if( max ){
		if( _mem_[min].key() == key ){
			index = min;
			return true;
			
		} else {
			index = _mem_[min].key() > key ? (min == 0 ? min : min - 1) : min + 1;
			return false;
			
		}
		
	}
	
	index = 0;
	return false;
	
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT,ValT,AllocT>::insert( const pair<KeyT,ValT>& pair ) {
	size_t index = 0;
	
	if( !find( pair.key(), index ) ){
		_mem_ = _alloc_.realloc( _mem_, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_mem_ = _alloc_.move( _mem_, index, index + 1 );
		
		_mem_[index] = pair;
		
	}
	
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT,ValT,AllocT>::insert( const KeyT& key, const ValT& val ) {
	insert( pair<KeyT,ValT>( key, val ) );
}

template<typename KeyT, typename ValT, typename AllocT>
const kick::size_t kick::map<KeyT,ValT,AllocT>::size() const {
	return _alloc_.usize();
}

template<typename KeyT, typename ValT, typename AllocT>
const kick::size_t kick::map<KeyT,ValT,AllocT>::capacity() const {
	return _alloc_.asize();
}

template<typename KeyT, typename ValT, typename AllocT>
ValT& kick::map<KeyT,ValT,AllocT>::operator[]( const KeyT& key ) {
	size_t index = 0;
	
	if( !find( key, index ) ){
		_mem_ = _alloc_.realloc( _mem_, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_mem_ = _alloc_.move( _mem_, index, index + 1 );
		
		_mem_[index] = pair<KeyT, ValT>( key, ValT() );
		
	}
	
	return _mem_[index].val();
	
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT, ValT, AllocT>::for_each(void (*fn)(const KeyT&, const ValT&)) const {
	for(kick::map<KeyT, ValT, AllocT>::iterator it = begin(); it != end(); ++it) {
		fn((*it).key(), (*it).val());
	}
}

template<typename KeyT, typename ValT, typename AllocT>
template<typename O>
void kick::map<KeyT, ValT, AllocT>::map_to(kick::map<KeyT, O>& out, O (*fn)(const KeyT&, const ValT&)) const {
	for(kick::map<KeyT, ValT, AllocT>::iterator it = begin(); it != end(); ++it) {
		out.insert(kick::pair<KeyT, O>((*it).key(), fn((*it).key(), (*it).val())));
	}
}

template<typename KeyT, typename ValT, typename AllocT>
template<typename O>
void kick::map<KeyT, ValT, AllocT>::reduce_to(O& out, O (*fn)(const O&, const KeyT&, const ValT&)) const {
	for(kick::map<KeyT, ValT, AllocT>::iterator it = begin(); it != end(); ++it) {
		out = fn(out, (*it).key(), (*it).val());
	}
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT, ValT, AllocT>::filter_to(kick::map<KeyT, ValT>& out, bool (*fn)(const KeyT&, const ValT&)) const {
	for(kick::map<KeyT, ValT, AllocT>::iterator it = begin(); it != end(); ++it) {
		if(fn((*it).key(), (*it).val())) {
			out.insert(kick::pair<KeyT, ValT>((*it).key(), (*it).val()));
		}
	}
}

template<typename KeyT, typename ValT, typename AllocT>
typename kick::map<KeyT,ValT,AllocT>::iterator kick::map<KeyT,ValT,AllocT>::begin() const {
	return iterator( 0, _mem_ );
}

template<typename KeyT, typename ValT, typename AllocT>
typename kick::map<KeyT,ValT,AllocT>::iterator kick::map<KeyT,ValT,AllocT>::end() const {
	return iterator( size(), _mem_ );
}

#endif // _kick_map_h
