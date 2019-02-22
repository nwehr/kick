#ifndef _kick_deque_iterator_h
#define _kick_deque_iterator_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "../common.hpp"
#include "../link.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// deque_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque_iterator {
	public:
		deque_iterator( kick::link<T>* mem )
		: _mem( mem )
		{}
		
		deque_iterator( const deque_iterator<T>& it )
		: _mem( it._mem )
		{}
		
		deque_iterator<T>& operator=( const deque_iterator<T>& it ){
			if( this != &it ) {
				_mem = it._mem;
			}
			
			return *this; 
			
		}
		
		T& operator*(){
			return _mem->item(); 
		}
		
		deque_iterator<T> operator+( unsigned int rh ){
			for( unsigned int i = 0; i < rh; ++i )
				operator++(); 
			
			return deque_iterator<T>( _mem ); 
			
		}
		
		deque_iterator<T> operator-( unsigned int rh ){
			for( unsigned int i = 0; i < rh; ++i )
				operator--(); 
			
			return deque_iterator<T>( _mem ); 
			
		}
		
		void operator++(){
			_mem = _mem->next();
		}
		
		void operator++(int){
			_mem = _mem->next();
		}
		
		void operator--(){
			_mem = _mem->prev();
		}
		
		void operator--(int){
			_mem = _mem->prev();
		}
		
		bool operator==( const deque_iterator& it ) const {
			return _mem == it._mem;
		}
		
		bool operator!=( const deque_iterator& it ) const {
			return _mem != it._mem;
		}
		
	private:
		kick::link<T>* _mem;
		
	};
	
}

#endif // _kick_deque_iterator_h
