#ifndef _kick_array_iterator_h
#define _kick_array_iterator_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "../common.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// array_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class array_iterator {
	public:
		array_iterator( int index, T* mem )
		: _index( index )
		, _mem( mem )
		{}
		
		array_iterator<T>& operator=( const array_iterator<T>& it ){
			if( this != &it ) {
				_index = it._index;
				_mem = it._mem;
			}
			
			return *this; 
			
		}
		
		T& operator*(){
			return _mem[_index];
		}
		
		array_iterator operator+( int rh ){
			return array_iterator( _index + rh, _mem );
		}
		
		array_iterator operator+( const array_iterator& rh ){
			return array_iterator( _index + rh._index, _mem );
		}
		
		array_iterator operator-( int rh ){
			return array_iterator( _index - rh, _mem );
		}
		
		array_iterator operator-( const array_iterator& rh ){
			return array_iterator( _index - rh._index, _mem );
		}
		
		void operator++(){
			++_index;
		}
		
		void operator++(int){
			++_index;
		}
		
		void operator--(){
			if( _index )
				--_index;
			
		}
		
		void operator--(int){
			if( _index )
				--_index;
			
		}
		
		bool operator==( const array_iterator<T>& it ) const {
			return _index == it._index;
		}
		
		bool operator!=( const array_iterator<T>& it ) const {
			return _index != it._index;
		}
		
		int index() const {
			return _index; 
		}
		
	protected:
		int _index;
		T* _mem;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// const_array_iterator
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class const_array_iterator : public array_iterator<T> {
	public:
		const_array_iterator( int index, T* mem )
		: array_iterator<T>( index, mem )
		{}
		
		const T& operator*() const {
			return this->_mem[this->_index];
		}
		
	};
}

#endif // _kick_array_iterator_h
