#ifndef kick_observer_hpp
#define kick_observer_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

#include "./vector.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// observable
	///////////////////////////////////////////////////////////////////////////////
	class observable {
	public:
		void add_observer( observer& o ) {
			for( int i = 0; i < _observers.size(); ++i ) {
				
			}
		}
		
		void delete_observer( observer& o ) {
			
		}
		
	protected:
		vector<observer*> _observers;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// observer
	///////////////////////////////////////////////////////////////////////////////
	class observer {
	public:
		
	protected:
		
	};
}

#endif
