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
#include <kick/config.h>

#include <kick/allocator.h>
#include <kick/iterator.h>

#include <kick/pair.h>

/// enable or disable virtual methods to support polymorphism
#ifndef KICK_POLYMORPHIC_MAP
	#define KICK_POLYMORPHIC_MAP KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// map
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V, typename A = array_allocator< pair<K,V> > >
	class map {
	public:
		typedef array_iterator< pair<K,V> > iterator;
		
		map( kick::size_t size = 0 )
		: _items_( 0 )
		, _alloc_( A() )
		{
			_alloc_.malloc( _items_, size );
		}
		
		map( const map<K,V>& map )
		: _items_( 0 )
		, _alloc_( map._alloc_ )
		{
			_alloc_.malloc( _items_, size() );
			
			for( kick::size_t i = 0; i < map.size(); ++i )
				_items_[i] = map._items_[i];
			
			//_items_ = _alloc_.copy( map._items_, _items_ );
			
		}
		
#if (KICK_POLYMORPHIC_MAP > 0)
		virtual
#endif
		~map(){
			if( _items_ )
				_alloc_.free( _items_ );
			
		}
		
		bool find( const K& key, unsigned int& index ){
			kick::size_t min = 0;
			kick::size_t mid = 0;
			kick::size_t max = size();
			
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
		
		void insert( const pair<K,V>& pair ){
			unsigned int index( 0 );
			
			if( !find( pair.key(), index ) ){
				_alloc_.realloc( _items_, size() + 1 );
				
				if( index < size() - 1 )
					_alloc_.move( _items_, index, index + 1 );
								
				_items_[index] = pair;
				
			}
			
		}
		
		const kick::size_t size() const {
			return _alloc_.usize();
		}
		
		const kick::size_t capacity() const {
			return _alloc_.asize();
		}
		
		V& operator[]( const K& key ){
			unsigned int index( 0 );
			
			if( !find( key, index ) ){
				_alloc_.realloc( _items_, size() + 1 );
				
				if( index < size() - 1 )
					_alloc_.move( _items_, index, index + 1 );
				
				_items_[index] = pair<K,V>();
				
			}
			
			return _items_[index].val();
			
		}
		
		iterator begin(){
			return iterator( 0, _items_ );
		}
		
		iterator end(){
			return iterator( size(), _items_ );
		}
		
	private:
		kick::pair<K,V>* _items_;
		A _alloc_;
		
	};
	
}

#endif // _kick_map_h
