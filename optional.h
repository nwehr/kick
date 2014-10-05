#ifndef _kick_optional_h
#define _kick_optional_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#ifndef KICK_POLYMORPHIC_OPTIONAL
#define KICK_POLYMORPHIC_OPTIONAL KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// optional_exception : exception
	///////////////////////////////////////////////////////////////////////////////
	class optional_exception : public exception {
	public:
		optional_exception() : exception() {}
		
#if	(KICK_POLYMORPHIC_EXCEPTION > 0)
		virtual
#endif
		const char* what() const { return "unable to dereference uninitialized object."; }
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// optional
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class optional {
	public:
		optional();
		optional( const T& );
		optional( const optional<T>& );
		optional<T>& operator=( const optional<T>& );
		
#if	(KICK_POLYMORPHIC_OPTIONAL > 0)
		virtual
#endif
		~optional();
		
		inline bool is_initialized() const;
		inline operator bool() const;
		
		inline T& get();
		inline const T& get() const;
		
		inline T& operator*();
		inline const T& operator*() const;
		
	protected:
		T* _mem_;
		
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// optional
///////////////////////////////////////////////////////////////////////////////
template<typename T>
kick::optional<T>::optional()
: _mem_( 0 )
{}

template<typename T>
kick::optional<T>::optional( const T& item )
: _mem_( new T( item ) )
{}

template<typename T>
kick::optional<T>::optional( const kick::optional<T>& opt )
: _mem_( opt._mem_ ? new T( *(opt._mem_) ) : 0 )
{}

template<typename T>
kick::optional<T>& kick::optional<T>::operator=( const kick::optional<T>& opt ) {
	if( opt._mem_ ) {
		_mem_ = new T( *(opt._mem_) );
	}
	
	return *this;
}

template<typename T>
kick::optional<T>::~optional() {
	if( _mem_ ) {
		delete _mem_;
	}
	
}

template<typename T>
bool kick::optional<T>::is_initialized() const {
	return static_cast<bool>( _mem_ );
}

template<typename T>
kick::optional<T>::operator bool() const {
	return is_initialized();
}


template<typename T>
T& kick::optional<T>::get() {
	if( !_mem_ ) {
		throw optional_exception();
	}
	
	return *_mem_;
}

template<typename T>
const T& kick::optional<T>::get() const {
	return get();
}

template<typename T>
T& kick::optional<T>::operator*() {
	if( !_mem_ ) {
		throw optional_exception();
	}
	
	return *_mem_;
}

template<typename T>
const T& kick::optional<T>::operator*() const {
	return operator*(); 
}

#endif // _kick_optional_h
