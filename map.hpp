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

		map<KeyT, ValT> filter(bool (*fn)(const KeyT&, const ValT&)) const {
			map<KeyT, ValT, AllocT> filtered;

			for(auto const& it: *this) {
				if(fn(it.key(), it.val())) {
					filtered[it.key()] = it.val();
				}
			}

			return filtered;
		}

		template<typename O = ValT>
		map<KeyT, O> transform(O (*fn)(const KeyT&, const ValT&)) const {
			map<KeyT, O, AllocT> mapped;

			for(auto const& it : *this) {
				mapped[it.key()] = fn(it.key(), it.val());
			}

			return mapped;
		}

		template<typename O = ValT>
		O reduce(O (*fn)(const O&, const KeyT&, const ValT&)) const {
			O reduced = O();

			for(auto const& it : *this) {
				reduced = fn(reduced, it.key(), it.val());
			}

			return reduced;
		}
		
		inline iterator begin() const;
		inline iterator end() const;
		
	private:
		pair<KeyT,ValT>* _mem;
		AllocT _alloc;
		
	};
	
} // namespace kick

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( size_t size, AllocT alloc )
: _mem( nullptr )
, _alloc( alloc )
{
	_mem = _alloc.malloc( _mem, size );
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( const map<KeyT,ValT,AllocT>& map )
: _mem( nullptr )
, _alloc( map._alloc )
{
	_mem = _alloc.malloc( _mem, size() );
	
	for( size_t i = 0; i < map.size(); ++i )
		_mem[i] = map._mem[i];
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::~map(){
	if( _mem )
		_alloc.free( _mem );
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>& kick::map<KeyT,ValT,AllocT>::operator=( const map<KeyT,ValT,AllocT>& map ) {
	if( this != &map ){
		_mem = _alloc.malloc( _mem, size() );
		
		for( size_t i = 0; i < map.size(); ++i )
			_mem[i] = map._mem[i];
		
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
		
		if( _mem[mid].key() > key ) max = mid;
		else min = mid;
		
	}
	
	if( max ){
		if( _mem[min].key() == key ){
			index = min;
			return true;
			
		} else {
			index = _mem[min].key() > key ? (min == 0 ? min : min - 1) : min + 1;
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
		_mem = _alloc.realloc( _mem, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_mem = _alloc.move( _mem, index, index + 1 );
		
		_mem[index] = pair;
		
	}
	
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT,ValT,AllocT>::insert( const KeyT& key, const ValT& val ) {
	insert( pair<KeyT,ValT>( key, val ) );
}

template<typename KeyT, typename ValT, typename AllocT>
const kick::size_t kick::map<KeyT,ValT,AllocT>::size() const {
	return _alloc.usize();
}

template<typename KeyT, typename ValT, typename AllocT>
const kick::size_t kick::map<KeyT,ValT,AllocT>::capacity() const {
	return _alloc.asize();
}

template<typename KeyT, typename ValT, typename AllocT>
ValT& kick::map<KeyT,ValT,AllocT>::operator[]( const KeyT& key ) {
	size_t index = 0;
	
	if( !find( key, index ) ){
		_mem = _alloc.realloc( _mem, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_mem = _alloc.move( _mem, index, index + 1 );
		
		_mem[index] = pair<KeyT, ValT>( key, ValT() );
		
	}
	
	return _mem[index].val();
	
}

template<typename KeyT, typename ValT, typename AllocT>
typename kick::map<KeyT,ValT,AllocT>::iterator kick::map<KeyT,ValT,AllocT>::begin() const {
	return iterator( 0, _mem );
}

template<typename KeyT, typename ValT, typename AllocT>
typename kick::map<KeyT,ValT,AllocT>::iterator kick::map<KeyT,ValT,AllocT>::end() const {
	return iterator( size(), _mem );
}

#endif // _kick_map_h
