#ifndef _kick_smart_ptr_scoped_ptr_h
#define _kick_smart_ptr_scoped_ptr_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "../smart_ptr.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// scoped_ptr : smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class scoped_ptr : public smart_ptr<T> {
		scoped_ptr( const scoped_ptr<T>&  );
		scoped_ptr& operator=( const scoped_ptr<T>& );
	
	public:
		explicit scoped_ptr( T* mem = 0 );
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~scoped_ptr();
		
	};
	
}

template<typename T>
kick::scoped_ptr<T>::scoped_ptr( T* mem )
: kick::smart_ptr<T>( mem )
{}

template<typename T>
kick::scoped_ptr<T>::~scoped_ptr(){
	delete this->_mem;
}


#endif // _kick_smart_ptr_scoped_ptr_h
