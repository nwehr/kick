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

#ifndef _kick_pair_h
#define _kick_pair_h

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// pair
	///////////////////////////////////////////////////////////////////////////////
	template<typename K, typename V>
	class pair {
	public:
		pair()
		: _key_( K() )
		, _val_( V() )
		{}
		
		pair( const K& key, const V& val )
		: _key_( key )
		, _val_( val )
		{}
		
		pair( const kick::pair<K,V>& pair )
		: _key_( pair.const_key() )
		, _val_( pair.const_val() )
		{}
		
		virtual ~pair(){}
		
		bool operator==( const kick::pair<K,V>& pair ) const {
			return (_key_ == pair.const_key() && _val_ == pair.const_val());
		}
		
		bool operator!=( const kick::pair<K,V>& pair ) const {
			return (_key_ != pair.const_key() || _val_ != pair.const_val());
		}
		
		K& key(){
			return _key_;
		}
		
		V& val(){
			return _val_;
		}
		
		const K& const_key() const {
			return _key_;
		}
		
		const V& const_val() const {
			return _val_;
		}
		
	private:
		K _key_;
		V _val_;
		
	};
	
}

#endif // _kick_pair_h
