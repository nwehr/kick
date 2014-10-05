#ifndef _kick_link_h
#define _kick_link_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// link
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class link {
	public:
		link( const T& item, link<T>* prev = 0, link<T>* next = 0 );
		link( const kick::link<T>& link );
		
		inline link<T>*& prev();
		inline const link<T>*& prev() const;
		
		inline link<T>*& next();
		inline const link<T>*& next() const;
		
		inline T& item();
		inline const T& item() const;
		
	private:
		T _item_;
		
		link<T>* _prev_;
		link<T>* _next_;
		
	};
	
} // namespace kick

template<typename T>
kick::link<T>::link( const T& item, kick::link<T>* prev, kick::link<T>* next )
: _item_( item )
, _prev_( prev )
, _next_( next )
{}

template<typename T>
kick::link<T>::link( const kick::link<T>& link )
: _item_( link._item_ )
, _prev_( link._prev_ )
, _next_( link._next_ )
{}

template<typename T>
kick::link<T>*& kick::link<T>::prev(){
	return _prev_;
}

template<typename T>
const kick::link<T>*& kick::link<T>::prev() const {
	return _prev_;
}

template<typename T>
kick::link<T>*& kick::link<T>::next(){
	return _next_;
}

template<typename T>
const kick::link<T>*& kick::link<T>::next() const {
	return _next_;
}

template<typename T>
T& kick::link<T>::item(){
	return _item_;
}

template<typename T>
const T& kick::link<T>::item() const {
	return _item_;
}

#endif // _kick_link_h
