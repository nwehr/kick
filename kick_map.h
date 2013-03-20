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

#include <kick/kick_config.h>
#include <kick/kick_allocator.h>
#include <kick/kick_iterator.h>
#include <kick/kick_pair.h>

/// enable or disable virtual methods to support polymorphism
#ifndef kick_polymorphic_map
	#define kick_polymorphic_map kick_polymorphic_containers
#endif

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

#if (kick_polymorphic_map == 1)
		virtual
#endif
		~map(){
			_alloc_.free( _items_ );
		}
		
		V find( const K& key, unsigned int* tokens = 0 ){
			kick::size_t min = 0;
			kick::size_t mid = 0;
			kick::size_t max = size();
			
			while( min + 1 < max ){
				mid = (min + max) / 2;
				
				if( _items_[mid].key() > key ) max = mid;
				else min = mid;
				
			}
			
			if( tokens ){
				tokens[0] = 0;
				tokens[1] = 0;
				
			}
			
			if( max ){
				if( _items_[min].key() == key ){
					if( tokens ){
						tokens[0] = 1;
						tokens[1] = min;
						
					}
					
					std::cout << "(" << key << ") found at [" << tokens[1] << "]" << std::endl;
					
					return _items_[min].val();
					
				} else {
					if( tokens ){
						tokens[0] = 0;
						tokens[1] = _items_[min].key() > key ? min - 1 : min + 1;
						
					}
					
					std::cout << "(" << key << ") not found, insert at [" << tokens[1] << "]" << std::endl;
					
				}
				
			}
			
			return V();
			
		}
		
		void insert( const kick::pair<K,V>& pair ){
			unsigned int tokens[2];
			
			find( pair.const_key(), tokens );
			
			if( !tokens[0] ){
				_items_ = _alloc_.realloc( _items_, size() + 1 );
				
				if( tokens[1] < size() - 1 ){
					std::cout << "moving [" << tokens[1] << "] to [" << tokens[1] + 1 << "]" << std::endl;
					_alloc_.move( _items_, tokens[1], tokens[1] + 1 );
					
				}
				
				std::cout << "inserting (" << pair.const_key() << ") at [" << tokens[1] << "]" << std::endl;
				_items_[tokens[1]] = pair;
				
			}
			
			std::cout << std::endl;
			
			for( iterator it = begin(); it != end(); ++it )
				std::cout << (*it).key() << std::endl;
				
			std::cout << std::endl;
			
			
		}
		
		const kick::size_t size() const {
			return _alloc_.usize();
		}
		
//		1
//		5
//		0
//		0
//		0
//		0
		
		const kick::size_t capacity() const {
			return _alloc_.asize(); 
		}
		
		V& operator[]( const K& key ){
			unsigned int tokens[2];
			
			find( key, tokens );
			
			if( !tokens[0] ){
				std::cout << "inserting " << key << " at " << tokens[1] << std::endl; 
				
				_items_ = _alloc_.realloc( _items_, size() + 1 );
				_alloc_.move( _items_, tokens[1], tokens[1] + 1 );
				
				_items_[tokens[1]] = kick::pair<K,V>();
				
			}
			
			return _items_[tokens[1]].val();
			
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
