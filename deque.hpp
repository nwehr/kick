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

		deque<T> filter(bool (*fn)(const T&)) const {
			deque<T> filtered;
			
			for(auto const& it : *this) {
				if(fn(it)) {
					filtered.push_back(it);
				}
			}

			return filtered;
		}

		template<typename O = T>
		deque<O> transform(O (*fn)(const T&)) const {
			deque<O> mapped;

			for(auto const& it : *this) {
				mapped.push_back(fn(it));
			}

			return mapped;
		}

		template<typename O = T>
		O reduce(O (*fn)(const O&, const T&)) const {
			O reduced = O();

			for(auto const& it : *this) {
				reduced = fn(reduced, it);
			}

			return reduced;
		}
		
		inline int size();
		
		inline T& front();
		inline T& back();
		
		inline link<T>*& front_link();
		inline link<T>*& back_link();
		
		inline iterator begin() const;
		inline iterator end() const;
		
	private:
		int _size;
		
		link<T>* _front;
		link<T>* _back;
		
	};
	
} // namespace kick

template<typename T>
kick::deque<T>::deque()
: _front( 0 )
, _back( 0 )
{}

template<typename T>
kick::deque<T>::~deque() {
	kick::link<T>* link = _front;
	
	while( link ){
		delete link;
		link = link->next();
		
	}
	
}

template<typename T>
void kick::deque<T>::push_back( const T& item ) {
	link<T>* t = new link<T>( item, _back, 0 );
	
	if( _back )
		_back->next() = t;
	
	if( !_front )
		_front = t;
	
	_back = t;
	
	++_size;
	
}

template<typename T>
void kick::deque<T>::push_front( const T& item ) {
	link<T>* t = new link<T>( item, 0, _front );
	
	if( _front )
		_front->prev() = t;
	
	if( !_back )
		_back = t;
	
	_front = t;
	
	++_size;
	
}

template<typename T>
void kick::deque<T>::pop_back() {
	if( _size ){
		link<T>* t = _back->prev();
		
		delete _back;
		
		_back = t;
		_back->next() = 0;
		
		--_size;
		
	}
	
}

template<typename T>
void kick::deque<T>::pop_front() {
	if( _size ){
		link<T>* t = _front->next();
		
		delete _front;
		
		_front = t;
		_front->prev() = 0;
		
		--_size;
		
	}	
}

template<typename T>
int kick::deque<T>::size() {
	return _size;
}

template<typename T>
T& kick::deque<T>::front() {
	return _front->item();
}

template<typename T>
T& kick::deque<T>::back() {
	return _back->item();
}

template<typename T>
kick::link<T>*& kick::deque<T>::front_link() {
	return _front;
}

template<typename T>
kick::link<T>*& kick::deque<T>::back_link() {
	return _back;
}

template<typename T>
typename kick::deque<T>::iterator kick::deque<T>::begin() const {
	return iterator( _front );
}

template<typename T>
typename kick::deque<T>::iterator kick::deque<T>::end() const {
	return iterator( _back->next() );
}

#endif // _kick_deque_h
