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

#ifndef _kick_vector_h
#define _kick_vector_h

#include <kick/kick_typdef.h>

#include <kick/kick_allocator.h>
#include <kick/kick_iterator.h>

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename A = array_allocator<T> >
	class vector {
	public:
		typedef kick::array_iterator<T> iterator;
		
		vector( int size = 0 )
		: _items_( 0 )
		, _alloc_( A() )
		{
			_items_ = _alloc_.malloc( size );
		
		}
		
		vector( const vector<T>& vec )
		: _items_( 0 )
		, _alloc_( vec._alloc_ )
		{
			_items_ = _alloc_.malloc( size() );
			_items_ = _alloc_.copy( vec._items_, _items_ );
			
		}
		
		virtual ~vector(){
			_alloc_.free( _items_ ); 
		}
		
		const vector<T>& operator=( const vector<T>& vec ){
			_alloc_.free( _items_ );

			_items_ = _alloc_.malloc( vec.size() );
			
			for( int i = 0; i < size(); ++i )
				_items_[i] = vec._items_[i];
				
			return *this;
			
		}
		
		void clear(){
			_alloc_.free( _items_ );			
		}
		
		bool empty() const {
			return size(); 
		}
		
		void erase( int index ){
			if( index < size() ){
				_alloc_.move( _items_, index + 1, index );
				_items_ = _alloc_.realloc( _items_, size() - 1 );
				
			}
			
		}
		
		void erase( array_iterator<T> pos ){
			_alloc_.move( _items_, pos.index() + 1, pos.index() );
			_items_ = _alloc_.realloc( _items_, size() - 1 );
			
		}
		
		void push_back( const T& item ){
			_items_ = _alloc_.realloc( _items_, size() + 1 );
			
			_items_[size() - 1] = item;
			
		}
		
		void push_front( const T& item ){
			_items_ = _alloc_.realloc( _items_, size() + 1 );
			_alloc_.move( _items_, 0, 1 );
			
			_items_[0] = item;
			
		}
		
		void pop_back(){
			if( size() )
				_items_ = _alloc_.realloc( _items_, size() - 1 );
			
			
		}
		
		void pop_front(){
			if( size() ){
				_alloc_.move( _items_, 1, 0 );
				_items_ = _alloc_.realloc( _items_, size() - 1 );
				
			}
			
		}
		
		int size() const {
			return _alloc_.usize();
		}
		
		int capacity() const {
			return _alloc_.asize(); 
		}
		
		T& front(){
			if( size() )
				return _items_[0];
			
			exit( -1 );
			
		}
		
		T& back(){
			if( size() )
				return _items_[size() - 1];
			
			exit( -1 ); 
			
		}
		
		iterator begin(){
			return iterator( 0, _items_ );
		}
		
		iterator end(){
			return iterator( size(), _items_ );
		}
		
		T& operator[]( int index ){
			if( index < size() && index >= 0 )
				return _items_[index];
			
			exit( -1 ); //TODO: out-of-range, do something!!!
			
		}
		
	private:
		T* _items_;
		A _alloc_; 
		
	};
	
}

#endif // _kick_vector_h
