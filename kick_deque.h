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

#ifndef _kick_deque_h
#define _kick_deque_h

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// link
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class link {
	public:
		link( const T& item, link<T>* previous = 0, link<T>* next = 0 )
		: _item_( item )
		, _previous_( previous )
		, _next_( next )
		{}
		
		link<T>*& previous(){ return _previous_; }
		link<T>*& next(){ return _next_; }
		
		T& item(){ return _item_; }
		T& operator*(){ return _item_; }
		
	private:
		T _item_;
		
		link<T>* _previous_;
		link<T>* _next_;
		
	};
	
	///////////////////////////////////////////////////////////////////////////////
	// deque
	///////////////////////////////////////////////////////////////////////////////
	template<typename T>
	class deque {
	public:
		deque()
		: _current_( 0 )
		, _front_( 0 )
		, _back_( 0 )
		{}
		
		virtual ~deque(){
			_current_ = front();
			for( int i = 0; i < size(); ++i ){
				link<T>* t = _current_->next();
				
				delete _current_;
				
				_current_ = t;
				
			}
			
		}
		
		void push_back( const T& item ){
			link<T>* t = new link<T>( item, _back_, 0 );
			
			if( _back_ )
				_back_->next() = t;
			
			if( !_front_ )
				_front_ = t;
			
			_back_ = t;
			
			++_size_;
			
		}
		
		void push_front( const T& item ){
			link<T>* t = new link<T>( item, 0, _front_ );
			
			if( _front_ )
				_front_->previous() = t;
			
			if( !_back_ )
				_back_ = t;
			
			_front_ = t;
			
			++_size_;
			
		}
		
		void pop_back(){
			if( _size_ ){
				link<T>* t = _back_->previous();
				
				delete _back_;
				
				_back_ = t;
				_back_->next() = 0;
				
				--_size_;
				
			}
			
		}
		
		void pop_front(){
			if( _size_ ){
				link<T>* t = _front_->next();
				
				delete _front_;
				
				_front_ = t;
				_front_->previous() = 0;
				
				--_size_;
				
			}
			
		}
		
		link<T>*& current(){
			if( !_current_ && _front_ )
				_current_ = _front_;
			
			return _current_;
		}
		
		link<T>* front(){ return _front_; }
		link<T>* back(){ return _back_; }
		
		deque<T>& operator++(){
			_current_ = _current_->next();
		}
		
		deque<T>& operator++( int ){
			_current_ = _current_->next();
		}
		
		int size(){ return _size_; }
		
	private:
		int _size_;
		
		link<T>* _current_;
		link<T>* _front_;
		link<T>* _back_;
		
	};
	
}

#endif // _kick_deque_h