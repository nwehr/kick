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
#include "./common.hpp"
#include "./link.hpp"

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


#endif // _kick_iterator_h
