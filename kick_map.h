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

#ifndef _kick_map_h
#define _kick_map_h

#include <kick/kick_typdef.h>

#include <kick/kick_allocator.h>
#include <kick/kick_iterator.h>

#include <kick/kick_pair.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// map
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V, typename A = array_allocator< pair<K,V> > >
	class map {
	public:
		typedef kick::array_iterator< pair<K,V> > iterator;
		
		map( int size = 0 )
		: _items_( 0 )
		, _alloc_( A() )
		{
			_items_ = _alloc_.malloc( size );
		}
		
		map( const kick::map<K,V>& map )
		: _items_( 0 )
		, _alloc_( map._alloc_ )
		{
			_items_ = _alloc_.malloc( size() );
			_items_ = _alloc_.copy( map._items_, _items_ );
			
		}
		
		virtual ~map(){
			_alloc_.free( _items_ );
		}
		
		int findkey( const K& key, int& min, int& max ){
			if( size() ){
				while ( max > min ){
					int mid = (max + min) / 2;
					
					if( _items_[mid].const_key() > key ){
						min = mid + 1;
					} else max = mid;
					
				}
				
//				std::cout << _items_[min].const_key().c_str() << " - " << key.c_str() << std::endl;
				
				if( _items_[min].const_key() == key )
					return min;
				
				
			}
			
			return -1;
			
		}
		
		void insert( const kick::pair<K,V>& pair ){
			int min = 0;
			int max = size() - 1;
			
			std::cout << findkey( pair.const_key(), min, max ) << std::endl;
			
			min = 0;
			max = size() - 1;
			
			if( findkey( pair.const_key(), min, max ) == -1 ){
				_items_ = _alloc_.realloc( _items_, size() + 1 );
				
				if( min < size() - 1 )
					_alloc_.move( _items_, min, min + 1 );
				
				std::cout << min << std::endl; 
				
				_items_[min] = pair;
				
			}
			
		}
		
		const int size() const {
			return _alloc_.usize();
		}
		
		const int capacity() const {
			return _alloc_.asize(); 
		}
		
		V& operator[]( const K& key ){
			for( int i = 0; i < size(); ++i ){
				if( _items_[i].key() == key )
					return _items_[i].val();
					
					
			}
			
			insert( pair<K,V>( key, V() ) );
			
			return _items_[size() - 1].val();
			
		}
		
		iterator begin(){
			return iterator( 0, _items_ );
		}
		
		iterator end(){
			return iterator( size(), _items_ );
		}
		
	private:
		pair<K,V>* _items_;
		A _alloc_;
		
	};
	
}

#endif // _kick_map_h
