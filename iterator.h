#ifndef _kick_iterator_h
#define _kick_iterator_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "common.h"
#include "link.h"

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
