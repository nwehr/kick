//
//  kick_iterator.h
//  kick
//
//  Created by Nathan Wehr on 1/27/13.
//  Copyright (c) 2013 Creltek. All rights reserved.
//

#ifndef _kick_iterator_h
#define _kick_iterator_h

#include <kick/kick_link.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename A = array_allocator<T>>
	class array_iterator {
	public:
		array_iterator( int i, T*& items )
		: _current_( i )
		, _items_( items )
		, _alloc_( 0 )
		{}
		
		virtual ~array_iterator(){}
		
		T& operator*(){
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
		
		bool operator==( const array_iterator& it ) const {
			return _current_ == it._current_;
		}
		
		bool operator!=( const array_iterator& it ) const {
			return _current_ != it._current_;
		}
		
	private:
		int _current_;
		
		T*& _items_; 
		A* _alloc_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// deque_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque_iterator {
	public:
		deque_iterator()
		: _link_( 0 )
		{}
		
		deque_iterator( kick::link<T>*& link )
		: _link_( link )
		{}
		
		T& operator*(){
			return _link_->item();
		}
		
		void operator++(){
			_link_ = _link_->next();
		}
		
		void operator++(int){
			_link_ = _link_->next();
		}
		
		void operator--(){
			_link_ = _link_->previous();
		}
		
		void operator--(int){
			_link_ = _link_->previous();
		}
		
		bool operator==( const deque_iterator& it ) const {
			return _link_ == it._link_;
		}
		
		bool operator!=( const deque_iterator& it ) const {
			return _link_ != it._link_;
		}
		
	private:
		kick::link<T>*& _link_;
		
	};
	
}


#endif // _kick_iterator_h
