#ifndef _kick_smart_ptr_shared_ptr_h
#define _kick_smart_ptr_shared_ptr_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "../smart_ptr.hpp"
#include "./weak_ptr.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// weak_ptr : smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class weak_ptr;
	
	///////////////////////////////////////////////////////////////////////////////
	// shared_ptr : smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class shared_ptr : public smart_ptr<T> {
		friend class weak_ptr<T>;
		
	public:
		explicit shared_ptr( T* mem = 0 );
		
		shared_ptr( const shared_ptr<T>& ptr );
		shared_ptr( const weak_ptr<T>& ptr );
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~shared_ptr();
		
		shared_ptr<T>& operator=( const shared_ptr<T>& rhs );
		shared_ptr<T>& operator=( const weak_ptr<T>& rhs );
		
	protected:
		unsigned int* _refs_;
	};
	
} // namespace kick

template <typename T>
kick::shared_ptr<T>::shared_ptr( T* mem )
: kick::smart_ptr<T>( mem )
, _refs_( new unsigned int( this->_mem_ ? 1 : 0 ) )
{}

template <typename T>
kick::shared_ptr<T>::shared_ptr( const kick::shared_ptr<T>& ptr )
: kick::smart_ptr<T>( ptr._mem_ )
, _refs_( ptr._refs_ )
{
	++(*_refs_);
}

template <typename T>
kick::shared_ptr<T>::shared_ptr( const kick::weak_ptr<T>& ptr )
: kick::smart_ptr<T>( ptr._mem_ )
, _refs_( ptr._refs_ )
{
	++(*_refs_);
}

template <typename T>
kick::shared_ptr<T>::~shared_ptr(){
	if( *_refs_ )
		--(*_refs_);
	
	if( !*_refs_ ){
		delete this->_mem_;
		delete _refs_;
	}
	
}

template <typename T>
kick::shared_ptr<T>& kick::shared_ptr<T>::operator=( const kick::shared_ptr<T>& rhs ){
	if( this != &rhs ){
		this->_mem_	= rhs._mem_;
		_refs_		= rhs._refs_;
		
		++(*_refs_);
		
	}
	
	return *this;
	
}

template <typename T>
kick::shared_ptr<T>& kick::shared_ptr<T>::operator=( const kick::weak_ptr<T>& rhs ){
	if( this != &rhs ){
		this->_mem_	= rhs._mem_;
		_refs_		= rhs._refs_;
		
		++(*_refs_);
		
	}
	
	return *this;
	
}

#endif // _kick_smart_ptr_shared_ptr_h
