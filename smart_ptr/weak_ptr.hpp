#ifndef _kick_smart_ptr_weak_ptr_h
#define _kick_smart_ptr_weak_ptr_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "../smart_ptr.hpp"
#include "./shared_ptr.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// shared_ptr : smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class shared_ptr;
	
	///////////////////////////////////////////////////////////////////////////////
	// weak_ptr : smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class weak_ptr : public smart_ptr<T> {
		friend class shared_ptr<T>;
		
	public:
		weak_ptr();
		weak_ptr( const weak_ptr<T>& );
		weak_ptr( const shared_ptr<T>& );
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~weak_ptr();
		
		weak_ptr<T>& operator=( const weak_ptr<T>& );
		weak_ptr<T>& operator=( const shared_ptr<T>& );
		
	protected:
		int* _refs;
		
	};
	
} // namespace kick

///////////////////////////////////////////////////////////////////////////////
// weak_ptr : smart_ptr
///////////////////////////////////////////////////////////////////////////////
template <typename T>
kick::weak_ptr<T>::weak_ptr()
: kick::smart_ptr<T>( 0 )
, _refs( 0 )
{}

template <typename T>
kick::weak_ptr<T>::weak_ptr( const kick::weak_ptr<T>& ptr )
: kick::smart_ptr<T>( ptr._mem )
, _refs( ptr._refs )
{}

template <typename T>
kick::weak_ptr<T>::weak_ptr( const kick::shared_ptr<T>& ptr )
: kick::smart_ptr<T>( ptr._mem )
, _refs( ptr._refs )
{}

template <typename T>
kick::weak_ptr<T>::~weak_ptr(){}

template <typename T>
kick::weak_ptr<T>& kick::weak_ptr<T>::operator=( const kick::weak_ptr<T>& ptr ){
	if( this != &ptr ){
		this->_mem		= ptr._mem;
		_refs			= ptr._refs;
	}
	
	return *this;
	
}

template <typename T>
kick::weak_ptr<T>& kick::weak_ptr<T>::operator=( const kick::shared_ptr<T>& ptr ){
	if( this != &ptr ){
		this->_mem		= ptr._mem;
		_refs			= ptr._refs;
	}
	
	return *this;
	
}

#endif // _kick_smart_ptr_weak_ptr_h
