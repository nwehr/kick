#ifndef _kick_deque_h
#define _kick_deque_h

//
//      Copyright 2012-2013 Nathan Wehr. All Rights Reserved.
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
#include <kick/iterator.h>
#include <kick/link.h>

#ifndef KICK_POLYMORPHIC_DEQUE
	#define KICK_POLYMORPHIC_DEQUE KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// deque
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque {
	public:
		typedef kick::deque_iterator<T> iterator;
		
		deque();
		
#if (KICK_POLYMORPHIC_DEQUE > 0)
		virtual
#endif
		~deque();
		
		void push_back( const T& item );
		void push_front( const T& item );
		
		void pop_back();
		void pop_front();
		
		int size();
		
		T& front();
		T& back();
		
		link<T>*& front_link();
		link<T>*& back_link(); 
		
		iterator begin();
		iterator end();
		
	private:
		int _size_;
		
		link<T>* _front_;
		link<T>* _back_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// deque
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	deque<T>::deque()
	: _front_( 0 )
	, _back_( 0 )
	{}
	
	template<typename T>
	deque<T>::~deque(){
		kick::link<T>* link = _front_;
		
		while( link ){
			delete link;
			link = link->next();
			
		}
		
	}
	
	template<typename T>
	void deque<T>::push_back( const T& item ){
		link<T>* t = new link<T>( item, _back_, 0 );
		
		if( _back_ )
			_back_->next() = t;
		
		if( !_front_ )
			_front_ = t;
		
		_back_ = t;
		
		++_size_;
		
	}
	
	template<typename T>
	void deque<T>::push_front( const T& item ){
		link<T>* t = new link<T>( item, 0, _front_ );
		
		if( _front_ )
			_front_->prev() = t;
		
		if( !_back_ )
			_back_ = t;
		
		_front_ = t;
		
		++_size_;
		
	}
	
	template<typename T>
	void deque<T>::pop_back(){
		if( _size_ ){
			link<T>* t = _back_->prev();
			
			delete _back_;
			
			_back_ = t;
			_back_->next() = 0;
			
			--_size_;
			
		}
		
	}
	
	template<typename T>
	void deque<T>::pop_front(){
		if( _size_ ){
			link<T>* t = _front_->next();
			
			delete _front_;
			
			_front_ = t;
			_front_->prev() = 0;
			
			--_size_;
			
		}
		
	}
	
	template<typename T>
	int deque<T>::size(){
		return _size_;
	}
	
	template<typename T>
	T& deque<T>::front(){
		return _front_->item();
	}
	
	template<typename T>
	T& deque<T>::back(){
		return _back_->item();
	}
	
	template<typename T>
	link<T>*& deque<T>::front_link(){
		return _front_;
	}
	
	template<typename T>
	link<T>*& deque<T>::back_link(){
		return _back_;
	}
	
	template<typename T>
	typename deque<T>::iterator deque<T>::begin(){
		return iterator( _front_ );
	}
	
	template<typename T>
	typename deque<T>::iterator deque<T>::end(){
		return iterator( _back_->next() );
	}
	
} // namespace kick

#endif // _kick_deque_h
