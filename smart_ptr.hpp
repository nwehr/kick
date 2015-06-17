#ifndef _kick_smart_ptr_h
#define _kick_smart_ptr_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#ifndef KICK_POLYMORPHIC_SMART_PTR
#define KICK_POLYMORPHIC_SMART_PTR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class smart_ptr {
	protected:
		explicit smart_ptr( T* mem );
		
	public:
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~smart_ptr();
		
		// Get the dereferenced memory
		inline T& operator*();
		inline const T& operator*() const;
		
		// Get a pointer to memory
		inline T* operator->();
		inline const T* operator->() const;
		
		// Get a pointer to memory
		inline T* get();
		inline const T* get() const;
		
		// Determine if memory is still valid
		inline bool expired() const;
		
	protected:
		T* _mem;
		
	};
	
} // namespace kick

///////////////////////////////////////////////////////////////////////////////
// smart_ptr
///////////////////////////////////////////////////////////////////////////////
template<typename T>
kick::smart_ptr<T>::smart_ptr( T* mem )
: _mem( mem )
{}

template<typename T>
kick::smart_ptr<T>::~smart_ptr(){}

template<typename T>
T& kick::smart_ptr<T>::operator*(){
	return *_mem;
}

template<typename T>
const T& kick::smart_ptr<T>::operator*() const {
	return *_mem;
}

template<typename T>
T* kick::smart_ptr<T>::operator->(){
	return _mem;
}

template<typename T>
const T* kick::smart_ptr<T>::operator->() const {
	return _mem;
}

template<typename T>
T* kick::smart_ptr<T>::get(){
	return _mem;
}

template<typename T>
const T* kick::smart_ptr<T>::get() const {
	return _mem;
}

template<typename T>
bool kick::smart_ptr<T>::expired() const {
	return !static_cast<bool>( _mem );
}

// Kick
#include "./smart_ptr/shared_ptr.hpp"
#include "./smart_ptr/weak_ptr.hpp"
#include "./smart_ptr/scoped_ptr.hpp"

#endif // _kick_smart_ptr_h
