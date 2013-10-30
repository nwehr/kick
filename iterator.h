#ifndef _kick_iterator_h
#define _kick_iterator_h

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
#include <kick/link.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_iterator {
	public:
		array_iterator( int index, T* items )
		: _index_( index )
		, _items_( items )
		{}
		
		array_iterator<T>& operator=( const array_iterator<T>& it ){
			if( this != &it ) {
				_index_ = it._index_;
				_items_ = it._items_;
			}
			
			return *this; 
			
		}
		
		T& operator*(){
			return _items_[_index_];
		}
		
		array_iterator operator+( int rh ){
			return array_iterator( _index_ + rh, _items_ );
		}
		
		array_iterator operator+( const array_iterator& rh ){
			return array_iterator( _index_ + rh._index_, _items_ );
		}
		
		array_iterator operator-( int rh ){
			return array_iterator( _index_ - rh, _items_ );
		}
		
		array_iterator operator-( const array_iterator& rh ){
			return array_iterator( _index_ - rh._index_, _items_ );
		}
		
		void operator++(){
			++_index_;
		}
		
		void operator++(int){
			++_index_;
		}
		
		void operator--(){
			if( _index_ )
				--_index_;
			
		}
		
		void operator--(int){
			if( _index_ )
				--_index_;
			
		}
		
		bool operator==( const array_iterator<T>& it ) const {
			return _index_ == it._index_;
		}
		
		bool operator!=( const array_iterator<T>& it ) const {
			return _index_ != it._index_;
		}
		
		int index() const {
			return _index_; 
		}
		
	protected:
		int _index_;
		T* _items_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// const_array_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class const_array_iterator : public array_allocator<T> {
	public:
		const_array_iterator( int index, T* items )
		: array_iterator<T>( index, items )
		{}
		
		const T& operator*() const {
			return this->_items_[this->_index_];
		}
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// deque_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque_iterator {
	public:
		deque_iterator( kick::link<T>* item )
		: _item_( item )
		{}
		
		deque_iterator( const deque_iterator<T>& it )
		: _item_( it._item_ )
		{}
		
		deque_iterator<T>& operator=( const deque_iterator<T>& it ){
			if( this != &it ) {
				_item_ = it._item_;
			}
			
			return *this; 
			
		}
		
		T& operator*(){
			return _item_->item(); 
		}
		
		deque_iterator<T> operator+( unsigned int rh ){
			for( unsigned int i = 0; i < rh; ++i )
				operator++(); 
			
			return deque_iterator<T>( _item_ ); 
			
		}
		
		deque_iterator<T> operator-( unsigned int rh ){
			for( unsigned int i = 0; i < rh; ++i )
				operator--(); 
			
			return deque_iterator<T>( _item_ ); 
			
		}
		
		void operator++(){
			_item_ = _item_->next();
		}
		
		void operator++(int){
			_item_ = _item_->next();
		}
		
		void operator--(){
			_item_ = _item_->prev();
		}
		
		void operator--(int){
			_item_ = _item_->prev();
		}
		
		bool operator==( const deque_iterator& it ) const {
			return _item_ == it._item_;
		}
		
		bool operator!=( const deque_iterator& it ) const {
			return _item_ != it._item_;
		}
		
	private:
		kick::link<T>* _item_;
		
	};
	
}


#endif // _kick_iterator_h
