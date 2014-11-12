#ifndef _kick_algorithm_sort_h
#define _kick_algorithm_sort_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	namespace algorithm {
		///////////////////////////////////////////////////////////////////////////////
		// swap
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void swap( T& a, T& b );
		
		///////////////////////////////////////////////////////////////////////////////
		// bubble_sort
		///////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void bubble_sort( T& seq );

	} // namespace algorithm
	
} // namespace kick

template<typename T>
void kick::algorithm::swap( T& a, T& b ) {
	T c( a );
	a = b;
	b = c;
	
}

template<typename T>
void kick::algorithm::bubble_sort( T& seq ) {
	for( typename T::iterator it = seq.begin(); it != seq.end(); ++it ){
		for( typename T::iterator nt = it; nt != seq.end(); ++nt ){
			if( *nt < *it )
				kick::algorithm::swap( *nt, *it );
			
			
		}
		
	}
	
}

#endif // _kick_algorithm_sort_h
