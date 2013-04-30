#ifndef _kick_smart_ptr_weak_ptr_h
#define _kick_smart_ptr_weak_ptr_h

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

#include <kick/smart_ptr.h>
#include <kick/smart_ptr/shared_ptr.h>

namespace kick {
	template <typename T>
	class shared_ptr;
	
	///////////////////////////////////////////////////////////////////////////////
	// weak_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class weak_ptr : public smart_ptr<T> {
		friend class shared_ptr<T>;
		
		weak_ptr();
		
	public:
		weak_ptr( const weak_ptr<T>& ptr )
		: smart_ptr<T>( ptr._mem_ )
		, _refs_( ptr._refs_ )
		{}
		
		weak_ptr( const shared_ptr<T>& ptr )
		: smart_ptr<T>( ptr._mem_ )
		, _refs_( ptr._refs_ )
		{}
		
		weak_ptr& operator=( const weak_ptr<T>& rhs ){
			if( this != rhs ){
				this->_mem_		= rhs._mem_;
				_refs_			= rhs._refs_;
			}
			
			return *this;
			
		}
		
		weak_ptr& operator=( const shared_ptr<T>& rhs ){
			if( this != rhs ){
				this->_mem_		= rhs._mem_;
				_refs_			= rhs._refs_;
			}
			
			return *this;
			
		}
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~weak_ptr(){}
		
		shared_ptr<T> lock() const {
			return shared_ptr<T>( *this );
		}
		
	protected:
		int* _refs_;
		
	};
	
} // namespace kick

#endif // _kick_smart_ptr_weak_ptr_h
