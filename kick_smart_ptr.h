#ifndef _kick_smart_ptr_h
#define _kick_smart_ptr_h

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

#ifndef KICK_POLYMORPHIC_SMART_PTR
	#define KICK_POLYMORPHIC_SMART_PTR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// smart_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class smart_ptr {
	protected:
		smart_ptr( T* mem )
		: _mem_( mem )
		, _refs_( new int( 1 ) )
		{}
		
		smart_ptr( const smart_ptr<T>& ptr )
		: _mem_( ptr._mem_ )
		, _refs_( ptr._refs_ )
		{
			++(*_refs_);
		}
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		smart_ptr& operator=( const smart_ptr<T>& rhs ){
			if( this != rhs ){
				_mem_ = rhs._mem_;
				_refs_ = rhs._ref_;
				
				++(*_refs_);
				
			}
			
			return *this;
		}
		
	public:
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~smart_ptr(){}
		
		T& operator*(){
			return *_mem_; 
		}
		
		T* operator->(){
			return _mem_; 
		}
		
		int refs(){
			return *_refs_; 
		}
		
	protected:
		T*		_mem_;
		int*	_refs_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// shared_ptr
	///////////////////////////////////////////////////////////////////////////////
	template <typename T>
	class shared_ptr : public smart_ptr<T> {
	public:
		shared_ptr( T* mem )
		: smart_ptr<T>( mem )
		{}
		
		shared_ptr( const shared_ptr<T>& ptr )
		: smart_ptr<T>( ptr )
		{}
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		shared_ptr& operator=( const shared_ptr<T>& rhs ){
			if( this != rhs ){
				this->_mem_ = rhs._mem_;
				this->_refs_ = rhs._refs_;
				
				++(*this->_refs_);
				
			}
			
			return *this;
			
		}
		
#if (KICK_POLYMORPHIC_SMART_PTR > 0)
		virtual
#endif
		~shared_ptr(){
			if( *this->_refs_ )
				--(*this->_refs_);
				
			if( !*this->_refs_ ){
				delete this->_mem_;
				delete this->_refs_;
				
			}
		
		}
		
	};
	
} // namespace kick

#endif // _kick_smart_ptr_h
