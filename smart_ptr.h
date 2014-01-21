#ifndef _kick_smart_ptr_h
#define _kick_smart_ptr_h

//
//      Copyright 2013 Nathan Wehr. All Rights Reserved.
//
//      Redistribution and use in source and binary forms, with or without modification, are
//      permitted provided that the following conditions are met:
//
//              1. Redistributions of source code must retain the above copyright notice, this list of
//              conditions and the following disclaimer.
//
//              2. Redistributions in binary form must reproduce the above copyright notice, this list
//              of conditions and the following disclaimer in the documentation and/or other materials
//              provided with the distribution.
//
//      THIS SOFTWARE IS PROVIDED BY NATHAN WEHR ''AS IS'' AND ANY EXPRESS OR IMPLIED
//      WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//      FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL NATHAN WEHR OR
//      CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//      CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//      SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
//      ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//      NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//      ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//      The views and conclusions contained in the software and documentation are those of the
//      authors and should not be interpreted as representing official policies, either expressed
//      or implied, of Nathan Wehr.
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
		T* _mem_;
		
	};
	
} // namespace kick

template<typename T>
kick::smart_ptr<T>::smart_ptr( T* mem )
: _mem_( mem )
{}

template<typename T>
kick::smart_ptr<T>::~smart_ptr(){}

template<typename T>
T& kick::smart_ptr<T>::operator*(){
	return *_mem_;
}

template<typename T>
const T& kick::smart_ptr<T>::operator*() const {
	return *_mem_;
}

template<typename T>
T* kick::smart_ptr<T>::operator->(){
	return _mem_;
}

template<typename T>
const T* kick::smart_ptr<T>::operator->() const {
	return _mem_;
}

template<typename T>
T* kick::smart_ptr<T>::get(){
	return _mem_;
}

template<typename T>
const T* kick::smart_ptr<T>::get() const {
	return _mem_;
}

template<typename T>
bool kick::smart_ptr<T>::expired() const {
	return !static_cast<bool>( _mem_ );
}

// Kick
#include <kick/smart_ptr/shared_ptr.h>
#include <kick/smart_ptr/weak_ptr.h>
#include <kick/smart_ptr/scoped_ptr.h>

#endif // _kick_smart_ptr_h
