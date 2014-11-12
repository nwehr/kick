#ifndef kick_allocator_memory_block_hpp
#define kick_allocator_memory_block_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// memory_block
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	struct memory_block {
		T* mem;
		
		size_t psize; // populated size
		size_t asize; // allocated size
	};
	
}

#endif
