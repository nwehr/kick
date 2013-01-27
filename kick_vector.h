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
#ifndef _kick_vector_h
#define _kick_vector_h

#include <kick/kick_allocator.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename A = array_allocator<T>>
	class vector {
	public:
		vector()
		: _size_( 0 )
		, _items_( 0 )
		, _alloc_( &_items_ )
		{}
		
		virtual ~vector(){
			empty();
			
			free( _items_ );
			
		}
		
		const vector<T>& operator=( const vector<T>& vec ){
			empty();
			
			for( int i = 0; i < vec.size(); ++i )
				push_back( vec[i] );
				
				return *this;
			
		}
		
		void empty(){
			for( int i = 0; i < _size_; ++i ){
				delete _items_[i];
				
				--_size_;
				
			}
			
		}
		
		void erase( int i ){
			if( i < _size_ ){
				delete _items_[i];
				
				for( int n = i; n < _size_ - 1; ++n )
					_items_[n] = _items_[n + 1];
				
				_items_ = static_cast<T**>( realloc( _items_, (sizeof( void* ) * (--_size_)) ) );
				
			}
			
		}
		
		void push_back( const T& item ){
			_items_ = static_cast<T**>( realloc( _items_, (sizeof( void* ) * (++_size_)) ) );
			_items_[_size_ - 1] = new T( item );
			
		}
		
		void push_front( const T& item ){
			_items_ = static_cast<T**>( realloc( _items_, (sizeof( void* ) * (++_size_)) ) );
			
			for( int i = (_size_ - 1); i > 0; --i )
				_items_[i] = _items_[i - 1];
			
			_items_[0] = new T( item );
			
		}
		
		void pop_back(){
			if( _size_ ){
				delete _items_[_size_ - 1];
				
				_items_ = static_cast<T**>( realloc( _items_, (sizeof( void* ) * (--_size_)) ) );
				
			}
			
		}
		
		void pop_front(){
			if( _size_ ){
				delete _items_[0];
				
				for( int i = 0; i < (_size_ - 1); ++i )
					_items_[i] = _items_[i+1];
				
				_items_ = static_cast<T**>( realloc( _items_, (sizeof( void* ) * (--_size_)) ) );
				
			}
			
		}
		
		int size() const { return _size_; }
		
		T& front(){ if( _size_ ) return *_items_[0]; }
		T& back(){ if( _size_ ) return *_items_[_size_ - 1]; }
		
		T& operator[]( int i ){
			if( i < _size_ && i > 0 )
				return *_items_[i];
			
			return *_items_[0];
			
		}
		
	private:
		int _size_;
		T** _items_;
		A _alloc_;
		
	};
	
}

#endif // _kick_vector_h
