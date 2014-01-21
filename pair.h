#ifndef _kick_pair_h
#define _kick_pair_h

//
//      Copyright 2013 Nathan Wehr. All Rights Reserved.
//      Copyright 2013 Kevin H. Patterson. All Rights Reserved.
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

// Kick
#include <kick/common.h>

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
const kick::KeyT& pair<KeyT,ValT>::key() const {
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
