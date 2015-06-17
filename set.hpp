#ifndef kick_set_hpp
#define kick_set_hpp

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "./common.hpp"
#include "./allocator/contiguous_allocator.hpp"

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// comparator
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class comparator {
	public:
		enum relational_operator {
			less_than = 0x1
			, greater_than = 0x2
		}
		
		comparator( relational_operator op = less_than )
		: _op( op )
		{}
		
		bool operator()( T& lhs, T& rhs ) {
			switch( _op ) {
				case less_than:
				{
					return (lhs < rhs);
				}
				break;
				case greater_than:
				{
					return (lhs > rhs);
				}
				break;
			}
		}
		
	protected:
		relational_operator _op;
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// set
	///////////////////////////////////////////////////////////////////////////////
	template <typename T, typename CompareT = ascending_comparator<T>, typename AllocT = contiguous_allocator<T> >
	class set {
		
	};
}

#endif
