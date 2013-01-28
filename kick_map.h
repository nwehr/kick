//
//      Copyright 2013 Nathan Wehr. All Rights Reserved.
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

#include <kick/kick_allocator.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// pair
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V>
	class pair {
	public:
		pair()
		: _key_( K() )
		, _val_( V() )
		{}
		
		pair( const K& key, const V& val )
		: _key_( key )
		, _val_( val )
		{}
		
		pair( const pair& p )
		: _key_( p.const_key() )
		, _val_( p.const_val() )
		{}
		
		virtual ~pair(){}
		
		bool operator==( const pair<K,V>& p ) const {
			return (_key_ == p.const_key() && _val_ == p.const_val());
		}
		
		bool operator!=( const pair<K,V>& p ) const {
			return (_key_ != p.const_key() || _val_ != p.const_val());
		}
		
		K& key(){
			return _key_;
		}
		
		V& val(){
			return _val_;
		}

		const K& const_key() const {
			return _key_;
		}
		
		const V& const_val() const {
			return _val_;
		}
		
	private:
		K _key_;
		V _val_;
	};
		
	///////////////////////////////////////////////////////////////////////////////
	// map_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V, typename A = array_allocator<pair<K,V>>>
	class map_iterator {
	public:
/* // DON'T NEED THIS
		map_iterator()
		: _current_( 0 )
		, _items_( 0 )
		, _alloc_( 0 )
		{}
*/		
		map_iterator( int i, pair<K,V>*& items )
		: _current_( i )
		, _items_( items )
		, _alloc_( 0 )
		{}
		
		virtual ~map_iterator(){}
		
		pair<K,V>& operator*() {
//TODO: We should do something (other than crash) if someone tries to dereference an invalid iterator (e.g. end() )
			return _items_[_current_];
		}
		
		void operator++(){
			++_current_;
		}
		
		void operator++(int){
			++_current_;
		}
		
		void operator--(){
			if( _current_ )
				--_current_;
			
		}
		
		void operator--(int){
			if( _current_ )
				--_current_;
			
		}
		
		bool operator==( const map_iterator& it ) const {
			return _current_ == it._current_;
		}
		
		bool operator!=( const map_iterator& it ) const {
			return _current_ != it._current_;
		}
		
	private:
		int _current_;
		
		pair<K,V>*& _items_;	// reference to an array of pointers-to-pairs
		A* _alloc_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// map
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V, typename A = array_allocator<pair<K,V>>>
	class map {
	public:
		typedef map_iterator<K,V> iterator; 
		
		map()
		: _items_( 0 )
		, _alloc_()
		{
			_items_ = _alloc_.malloc( 0 ); 
		}
		
		virtual ~map(){
			_alloc_.free( _items_ );
		}
		
		void insert( const pair<K,V>& p ){
			_items_ = _alloc_.realloc( _items_, size() + 1 );
			_items_[size() - 1] = p; 
			
		}
		
		const int size() const {
			return _alloc_.usize();
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
