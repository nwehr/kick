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

#include "./error.hpp"
#include "./experimental/either.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// optional_error
	///////////////////////////////////////////////////////////////////////////////
	struct optional_error : public error {
		optional_error() : error() {
			code = 0;
			what = "unable to dereference uninitialized object";
		}
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// optional
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class optional {
	public:
		typedef experimental::either<T, optional_error> either;

		optional();
		optional( const T& );
		optional( const optional<T>& ); 
		optional<T>& operator=( const optional<T>& ); 
		
		~optional();
		
		inline bool is_initialized() const;
		inline operator bool() const;
		
		inline T& get();
		inline const T& get() const;

		inline either get_safe() {
			if(is_initialized()) {
				return make_left();	
			} else {
				return make_right();
			}
		}
		
		inline const either get_safe() const {
			return get_safe();
		}
		
		inline T& operator*();
		inline const T& operator*() const;
		
	protected:
		T* _mem;

		either make_left() {
			return experimental::make_left<T, optional_error>(*_mem);
		}

		either make_right() {
			return experimental::make_right<T, optional_error>(optional_error());
		}
	};

	///////////////////////////////////////////////////////////////////////////////
	// optional
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	optional<T>::optional()
	: _mem( nullptr )
	{}

	template<typename T>
	optional<T>::optional( const T& obj )
	: _mem( new T( obj ) )
	{}

	template<typename T>
	optional<T>::optional( const optional<T>& opt )
	: _mem(opt.is_initialized() ? new T( *(opt._mem) ) : nullptr)
	{}

	template<typename T>
	optional<T>& optional<T>::operator=( const optional<T>& opt ) {
		if(opt.is_initialized()) {
			_mem = new T(*(opt._mem));
		} else {
			_mem = nullptr;
		}
		
		return *this;
	}

	template<typename T>
	optional<T>::~optional() {
		if(is_initialized()) {
			delete _mem;
		}
	}

	template<typename T>
	bool optional<T>::is_initialized() const {
		return static_cast<bool>(_mem);
	}

	template<typename T>
	optional<T>::operator bool() const {
		return is_initialized();
	}

	template<typename T>
	T& optional<T>::get() {
		return *_mem;
	}

	template<typename T>
	const T& optional<T>::get() const {
		return get();
	}

	template<typename T>
	T& optional<T>::operator*() {
		return *_mem;
	}

	template<typename T>
	const T& optional<T>::operator*() const {
		return operator*(); 
	}

}

#endif // _kick_optional_h
