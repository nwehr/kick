#ifndef _kick_deque_h
#define _kick_deque_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "./common.hpp"
#include "./iterator.hpp"
#include "./link.hpp"

#ifndef KICK_POLYMORPHIC_DEQUE
#define KICK_POLYMORPHIC_DEQUE KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// deque
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque {
	public:
		typedef kick::deque_iterator<T> iterator;
		
		deque();
		
#if (KICK_POLYMORPHIC_DEQUE > 0)
		virtual
#endif
		~deque();
		
		void push_back( const T& item );
		void push_front( const T& item );
		
		void pop_back();
		void pop_front();
		
		inline int size();
		
		inline T& front();
		inline T& back();
		
		inline link<T>*& front_link();
		inline link<T>*& back_link();
		
		inline iterator begin();
		inline iterator end();
		
	private:
		int _size_;
		
		link<T>* _front_;
		link<T>* _back_;
		
	};
	
} // namespace kick

template<typename T>
kick::deque<T>::deque()
: _front_( 0 )
, _back_( 0 )
{}

template<typename T>
kick::deque<T>::~deque() {
	kick::link<T>* link = _front_;
	
	while( link ){
		delete link;
		link = link->next();
		
	}
	
}

template<typename T>
void kick::deque<T>::push_back( const T& item ) {
	link<T>* t = new link<T>( item, _back_, 0 );
	
	if( _back_ )
		_back_->next() = t;
	
	if( !_front_ )
		_front_ = t;
	
	_back_ = t;
	
	++_size_;
	
}

template<typename T>
void kick::deque<T>::push_front( const T& item ) {
	link<T>* t = new link<T>( item, 0, _front_ );
	
	if( _front_ )
		_front_->prev() = t;
	
	if( !_back_ )
		_back_ = t;
	
	_front_ = t;
	
	++_size_;
	
}

template<typename T>
void kick::deque<T>::pop_back() {
	if( _size_ ){
		link<T>* t = _back_->prev();
		
		delete _back_;
		
		_back_ = t;
		_back_->next() = 0;
		
		--_size_;
		
	}
	
}

template<typename T>
void kick::deque<T>::pop_front() {
	if( _size_ ){
		link<T>* t = _front_->next();
		
		delete _front_;
		
		_front_ = t;
		_front_->prev() = 0;
		
		--_size_;
		
	}
	
}

template<typename T>
int kick::deque<T>::size() {
	return _size_;
}

template<typename T>
T& kick::deque<T>::front() {
	return _front_->item();
}

template<typename T>
T& kick::deque<T>::back() {
	return _back_->item();
}

template<typename T>
kick::link<T>*& kick::deque<T>::front_link() {
	return _front_;
}

template<typename T>
kick::link<T>*& kick::deque<T>::back_link() {
	return _back_;
}

template<typename T>
typename kick::deque<T>::iterator kick::deque<T>::begin() {
	return iterator( _front_ );
}

template<typename T>
typename kick::deque<T>::iterator kick::deque<T>::end() {
	return iterator( _back_->next() );
}

#endif // _kick_deque_h
