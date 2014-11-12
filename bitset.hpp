#ifndef kick_bitset_h
#define kick_bitset_h

//
// Copyright 2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// bitset
	///////////////////////////////////////////////////////////////////////////////
	template<size_t n>
	class bitset {
	public:
		bitset() {}
		bitset( size_t val ) {
			for( size_t i = 0; i < n; ++i ) {
				this->_b_[(n - 1) - i] = val & (1 << i);
			}
		}
		
		bitset& operator=( size_t val ) {
			for( size_t i = 0; i < n; ++i ) {
				_b_[(n - 1) - i] = val & (1 << i);
			}
			
			return *this;
		}
		
		~bitset() {}
		
		bool& operator[] ( size_t pos ) {
			return _b_[pos];
		}
		
		void set( size_t pos, bool val ) {
			_b_[pos] = val;
		}
		
		size_t size() {
			return n;
		}
		
	private:
		bool _b_[n];
	};
	
}

///////////////////////////////////////////////////////////////////////////////
// bitset
///////////////////////////////////////////////////////////////////////////////
#endif
