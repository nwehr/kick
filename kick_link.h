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

#ifndef _kick_link_h
#define _kick_link_h

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// link
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class link {
	public:
		link( const T& item, link<T>* prev = 0, link<T>* next = 0 )
		: _item_( item )
		, _prev_( prev )
		, _next_( next )
		{}
		
		link( const kick::link<T>& link )
		: _item_( link._item_ )
		, _prev_( link._prev_ )
		, _next_( link._next_ )
		{}
		
		link<T>*& prev(){
			return _prev_; 
		}
		
		const link<T>*& prev() const {
			return _prev_;
		}
		
		link<T>*& next(){
			return _next_; 
		}
		
		const link<T>*& next() const {
			return _next_; 
		}
		
		T& item(){
			return _item_; 
		}
		
		const T& item() const {
			return _item_; 
		}
		
	private:
		T _item_;
		
		link<T>* _prev_;
		link<T>* _next_;
		
	};
	
}

#endif // _kick_link_h
