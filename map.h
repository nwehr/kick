#ifndef _kick_map_h
#define _kick_map_h

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

// Kick
#include <kick/common.h>

#include <kick/allocator.h>
#include <kick/iterator.h>

#include <kick/pair.h>

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
		
		map( size_t size = 0 );
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
		
		inline iterator begin();
		inline iterator end();
		
	private:
		pair<KeyT,ValT>* _items_;
		AllocT _alloc_;
		
	};
	
} // namespace kick

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( size_t size )
: _items_( 0 )
, _alloc_( AllocT() )
{
	_items_ = _alloc_.malloc( _items_, size );
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::map( const map<KeyT,ValT,AllocT>& map )
: _items_( 0 )
, _alloc_( map._alloc_ )
{
	_items_ = _alloc_.malloc( _items_, size() );
	
	for( size_t i = 0; i < map.size(); ++i )
		_items_[i] = map._items_[i];
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>::~map(){
	if( _items_ )
		_alloc_.free( _items_ );
	
}

template<typename KeyT, typename ValT, typename AllocT>
kick::map<KeyT,ValT,AllocT>& kick::map<KeyT,ValT,AllocT>::operator=( const map<KeyT,ValT,AllocT>& map ) {
	if( this != &map ){
		_items_ = _alloc_.malloc( _items_, size() );
		
		for( size_t i = 0; i < map.size(); ++i )
			_items_[i] = map._items_[i];
		
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
		
		if( _items_[mid].key() > key ) max = mid;
		else min = mid;
		
	}
	
	if( max ){
		if( _items_[min].key() == key ){
			index = min;
			return true;
			
		} else {
			index = _items_[min].key() > key ? (min == 0 ? min : min - 1) : min + 1;
			return false;
			
		}
		
	}
	
	index = 0;
	return false;
	
}

template<typename KeyT, typename ValT, typename AllocT>
void kick::map<KeyT,ValT,AllocT>::insert( const pair<KeyT,ValT>& pair ) {
	size_t index( 0 );
	
	if( !find( pair.key(), index ) ){
		_items_ = _alloc_.realloc( _items_, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_items_ = _alloc_.move( _items_, index, index + 1 );
		
		_items_[index] = pair;
		
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
const size_t kick::map<KeyT,ValT,AllocT>::capacity() const {
	return _alloc_.asize();
}

template<typename KeyT, typename ValT, typename AllocT>
ValT& kick::map<KeyT,ValT,AllocT>::operator[]( const KeyT& key ) {
	size_t index( 0 );
	
	if( !find( key, index ) ){
		_items_ = _alloc_.realloc( _items_, size() + 1 );
		
		if( index < (size() > 0 ? size() : 1) - 1 )
			_items_ = _alloc_.move( _items_, index, index + 1 );
		
	}
	
	return _items_[index].val();
	
}

template<typename KeyT, typename ValT, typename AllocT>
typename map<KeyT,ValT,AllocT>::iterator map<KeyT,ValT,AllocT>::begin() {
	return iterator( 0, _items_ );
}

template<typename KeyT, typename ValT, typename AllocT>
typename kick::map<KeyT,ValT,AllocT>::iterator kick::map<KeyT,ValT,AllocT>::end() {
	return iterator( size(), _items_ );
}

#endif // _kick_map_h
