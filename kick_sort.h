//
//      Copyright 2012-2013 Nathan Wehr. All Rights Reserved.
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

#ifndef _kick_sort_h
#define _kick_sort_h

#include <kick/kick_common.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// swap
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	void swap( T& a, T& b ){
		T c( a );
		a = b;
		b = c;
		
	}
	
	///////////////////////////////////////////////////////////////////////////////
	// bubble_sort
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	void bubble_sort( vector<T>& vec ){
		int size = vec.size();
		
		for( int i = 0; i < size; ++i ){
			for( int j = i; j < size; ++j ){
				if( vec[j] < vec[i] )
					swap( vec[j], vec[i] );
				
				
			}
			
		}
		
	}
	
	template<typename T>
	void bubble_sort( deque<T>& deq ){
		int size = deq.size();
		
		link<T>* it = deq.front();
		
		for( int i = 0; i < size; ++i ){
			link<T>* ij = it;
			
			for( int j = i; j < size; ++j ){
				if( **ij < **it )
					swap( **it, **ij );
				
				ij = ij->next();
				
			}
			
			it = it->next();
			
		}
		
	}
	
}

#endif // _kick_sort_h
