#ifndef _kick_pair_h
#define _kick_pair_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

// Kick
#include "common.h"

#ifndef KICK_POLYMORPHIC_PAIR
#define KICK_POLYMORPHIC_PAIR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// pair
	///////////////////////////////////////////////////////////////////////////////
	template<typename KeyT, typename ValT>
	class pair {
	public:
		pair();
		pair( const KeyT&, const ValT& );
		pair( const pair<KeyT,ValT>& );
		
#if (KICK_POLYMORPHIC_PAIR > 0)
		virtual
#endif
		~pair();
		
		pair<KeyT,ValT>& operator=( const pair<KeyT,ValT>& );
		
		inline bool operator==( const pair<KeyT,ValT>& ) const;
		inline bool operator!=( const pair<KeyT,ValT>& ) const;
		
		inline KeyT& key();
		inline const KeyT& key() const;
		
		inline ValT& val();
		inline const ValT& val() const;
		
	private:
		KeyT _key_;
		ValT _val_;
		
	};
	
} // namespace kick

template<typename KeyT, typename ValT>
kick::pair<KeyT,ValT>::pair()
: _key_( KeyT() )
, _val_( ValT() )
{}

template<typename KeyT, typename ValT>
kick::pair<KeyT,ValT>::pair( const KeyT& key, const ValT& val )
: _key_( key )
, _val_( val )
{}

template<typename KeyT, typename ValT>
kick::pair<KeyT,ValT>::pair( const pair<KeyT,ValT>& pair )
: _key_( pair._key_ )
, _val_( pair._val_ )
{}

template<typename KeyT, typename ValT>
kick::pair<KeyT,ValT>::~pair(){}

template<typename KeyT, typename ValT>
kick::pair<KeyT,ValT>& kick::pair<KeyT,ValT>::operator=( const kick::pair<KeyT,ValT>& rhs ) {
	if( this != &rhs ){
		_key_ = rhs._key_;
		_val_ = rhs._val_;
		
	}
	
	return *this;
	
}

template<typename KeyT, typename ValT>
bool kick::pair<KeyT,ValT>::operator==( const kick::pair<KeyT,ValT>& rhs ) const {
	return (_key_ == rhs._key_ && _val_ == rhs._val_);
}

template<typename KeyT, typename ValT>
bool kick::pair<KeyT,ValT>::operator!=( const kick::pair<KeyT,ValT>& rhs ) const {
	return !operator==( rhs );
}

template<typename KeyT, typename ValT>
KeyT& kick::pair<KeyT,ValT>::key() {
	return _key_;
}

template<typename KeyT, typename ValT>
const KeyT& kick::pair<KeyT,ValT>::key() const {
	return _key_;
}

template<typename KeyT, typename ValT>
ValT& kick::pair<KeyT,ValT>::val() {
	return _val_;
}

template<typename KeyT, typename ValT>
const ValT& kick::pair<KeyT,ValT>::val() const {
	return _val_;
}

#endif // _kick_pair_h
