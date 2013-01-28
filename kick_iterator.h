//
//  kick_iterator.h
//  kick
//
//  Created by Nathan Wehr on 1/27/13.
//  Copyright (c) 2013 Creltek. All rights reserved.
//

#ifndef _kick_iterator_h
#define _kick_iterator_h

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
		
		T& operator*() {
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
	
}


#endif // _kick_iterator_h
