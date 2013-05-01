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
#include <kick/config.h>

#ifndef KICK_POLYMORPHIC_PAIR
	#define KICK_POLYMORPHIC_PAIR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// pair
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V>
	class pair {
	public:
		pair();
		pair( const K& key, const V& val );
		pair( const pair<K,V>& pair );

		pair<K,V>& operator=( const pair<K,V>& pair );
		
#if (KICK_POLYMORPHIC_PAIR > 0)
		virtual
#endif
		~pair();
		
		bool operator==( const pair<K,V>& pair ) const;
		bool operator!=( const pair<K,V>& pair ) const;
		
		K& key();
		const K& key() const;
		
		V& val();
		const V& val() const;
		
	private:
		K _key_;
		V _val_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// pair
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V>
	pair<K,V>::pair()
	: _key_( K() )
	, _val_( V() )
	{}
	
	template<typename K, typename V>
	pair<K,V>::pair( const K& key, const V& val )
	: _key_( key )
	, _val_( val )
	{}
	
	template<typename K, typename V>
	pair<K,V>::pair( const pair<K,V>& pair )
	: _key_( pair._key_ )
	, _val_( pair._val_ )
	{}
	
	template<typename K, typename V>
	pair<K,V>& pair<K,V>::operator=( const pair<K,V>& pair ){
		if( *this != pair ){
			_key_ = pair._key_;
			_val_ = pair._val_;
			
		}
		
		return *this;
		
	}
	
	template<typename K, typename V>
	pair<K,V>::~pair(){}
	
	template<typename K, typename V>
	bool pair<K,V>::operator==( const pair<K,V>& pair ) const {
		return (_key_ == pair._key_ && _val_ == pair._val_);
	}
	
	template<typename K, typename V>
	bool pair<K,V>::operator!=( const pair<K,V>& pair ) const {
		return !operator==( pair );
	}
	
	template<typename K, typename V>
	K& pair<K,V>::key(){
		return _key_;
	}
	
	template<typename K, typename V>
	const K& pair<K,V>::key() const {
		return _key_;
	}
	
	template<typename K, typename V>
	V& pair<K,V>::val(){
		return _val_;
	}
	
	template<typename K, typename V>
	const V& pair<K,V>::val() const {
		return _val_;
	}
	
} // namespace kick

#endif // _kick_pair_h
