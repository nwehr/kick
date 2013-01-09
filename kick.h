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

#ifndef _kick_h
#define _kick_h

#include <cstdlib>
#include <iostream>

namespace kick {
	template<typename T>
	class link {
	public:
		link( const T& i_item, link<T>* i_previous = 0, link<T>* i_next = 0 )
		: _item_( i_item )
		, _previous_( i_previous )
		, _next_( i_next )
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
		
		void push_back( const T& i_item ){
			link<T>* t = new link<T>( i_item, _back_, 0 );
			
			if( _back_ )
				_back_->next() = t;
			
			if( !_front_ )
				_front_ = t;
			
			_back_ = t;
			
			++_size_;
			
		}
		
		void push_front( const T& i_item ){
			link<T>* t = new link<T>( i_item, 0, _front_ );
			
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
	
	template<typename T>
	class vector {
	public:
		vector()
		: _size_( 0 )
		, _items_( 0 )
		{}
		
		virtual ~vector(){
			empty();
			
			free( _items_ );
		}
		
		const vector<T>& operator=( const vector<T>& i_vector ){
			empty();
			
			for( int i = 0; i < i_vector.size(); ++i ){
				push_back( i_vector[i] );
			}
			
			return *this;
			
		}
		
		void empty(){
			for( int i = 0; i < _size_; ++i ){
				delete _items_[i];
				--_size_;
			}
			
		}
		
		void erase( int i_index ){
			if( i_index < _size_ ){
				delete _items_[i_index];
				
				for( int i = i_index; i < _size_ - 1; ++i )
					_items_[i] = _items_[i+1];
				
				_items_ = reinterpret_cast<T**>( realloc( _items_, (sizeof( T* ) * (--_size_)) ) );
				
			}
			
		}
		
		void push_back( const T& i_item ){
			_items_ = reinterpret_cast<T**>( realloc( _items_, (sizeof( T* ) * (++_size_)) ) );
			_items_[_size_ - 1] = new T( i_item );
			
		}
		
		void push_front( const T& i_item ){
			_items_ = reinterpret_cast<T**>( realloc( _items_, (sizeof( T* ) * (++_size_)) ) );
			
			for( int i = (_size_ - 1); i > 0; --i ){
				_items_[i] = _items_[i-1];
			}
			
			_items_[0] = new T( i_item );
			
		}
		
		void pop_back(){
			if( _size_ ){
				delete _items_[_size_ - 1];
				_items_ = reinterpret_cast<T**>( realloc( _items_, (sizeof( T* ) * (--_size_)) ) );
				
			}
			
		}
		
		void pop_front(){
			if( _size_ ){
				delete _items_[0];
				
				for( int i = 0; i < (_size_ - 1); ++i ){
					_items_[i] = _items_[i+1];
				}
				
				_items_ = reinterpret_cast<T**>( realloc( _items_, (sizeof( T* ) * (--_size_)) ) );
				
			}
			
		}
		
		int size(){ return _size_; }
		
		T& front(){ if( _size_ ) return *_items_[0]; }
		T& back(){ if( _size_ ) return *_items_[_size_ - 1]; }
		
		T& operator[]( int i_index ){
			if( i_index < _size_ && i_index > 0 )
				return *_items_[i_index];
			
			return *_items_[0];
			
		}
		
	private:
		int _size_;
		T** _items_;
		
	};
	
	class string {
	public:
		string()
		: _size_( 0 )
		, _c_str_( 0 )
		{}
		
		string( const char* cstr )
		: _size_( sizeof( cstr ) )
		, _c_str_( 0 )
		{
			_c_str_ = reinterpret_cast<char**>( realloc( _c_str_, (sizeof( char* ) * --_size_ ) ) );

			for( int i = 0; i < _size_; ++i ){
				*_c_str_[i] = cstr[i];

				std::cout << *_c_str_[i] << std::endl;

			}

		}
		
//		string( const string& str ){
//			int size = str.size();
//
//			char t[size];
//
//			for( int i = 0; i < size; ++i ){
//				t[i] = str[i];
//			}
//
//			_c_str_ = t;
//
//		}
//
//		string& operator=( const string& str ){
//			if( this != &str ){
//				int size = str.size();
//
//				char t[size];
//
//				for( int i = 0; i < size; ++i ){
//					t[i] = str[i];
//				}
//
//				_c_str_ = t;
//
//			}
//
//			return *this;
//
//		}
		
		virtual ~string(){}
		
		char operator[]( int index ) const {
			return *_c_str_[index];
		}
		
		int size() const { return _size_; }
		
		const char* c_str(){
			return *_c_str_;
		}
		
	private:
		int _size_;
		char** _c_str_;

	};
	
	template<typename T>
	void swap( T& a, T& b ){
		T c( a );
		a = b;
		b = c;
	}
	
	template<typename T>
	void bubble_sort( vector<T>& i_vector ){
		int size = i_vector.size();
		
		for( int i = 0; i < size; ++i ){
			for( int j = i; j < size; ++j ){
				if( i_vector[j] < i_vector[i] )
					swap( i_vector[j], i_vector[i] );
				
				
			}
			
		}
		
	}
	
	template<typename T>
	void bubble_sort( deque<T>& i_deque ){
		int size = i_deque.size();
		
		link<T>* it = i_deque.front();
		
		for( int i = 0; i < size; ++i ){
			
			link<T>* ij = it;
			
			for( int j = i; j < size; ++j ){
				if( **ij < **it )
					swap( **it, **ij );
				
				ij = ij->next();
				
			}
			
			it = it->next();
			
		}
		
	}
	
}

#endif
