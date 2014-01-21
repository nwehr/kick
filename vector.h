#ifndef _kick_vector_h
#define _kick_vector_h

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

#include <kick/allocator.h>
#include <kick/iterator.h>

#ifndef KICK_POLYMORPHIC_VECTOR
	#define KICK_POLYMORPHIC_VECTOR KICK_POLYMORPHIC_CONTAINERS
#endif

namespace kick {
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename AllocT = array_allocator<T> >
	class vector {
	public:
		typedef kick::array_iterator<T> iterator;
		typedef kick::const_array_iterator<T> const_iterator;
		
		vector( kick::size_t size = 0 );
		vector( const vector<T>& vec );

#if (KICK_POLYMORPHIC_VECTOR > 0)
		virtual
#endif
		~vector();
		
		const vector<T>& operator=( const vector<T>& );
		
		inline void clear();
		inline bool empty() const;
		
		void erase( size_t );
		void erase( array_iterator<T> );
		
		void push_back( const T& );
		void push_front( const T& );
		
		void pop_back();
		void pop_front();
		
		inline const size_t size() const;
		inline const size_t capacity() const;
		
		inline T& front();
		inline T& back();
		
		inline iterator begin();
		inline iterator end();
		
		inline T& operator[]( size_t );
		
	private:
		T* _items_;
		AllocT _alloc_;
		
	};
		
	
	///////////////////////////////////////////////////////////////////////////////
	// vector
	///////////////////////////////////////////////////////////////////////////////
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( kick::size_t size )
	: _items_( 0 )
	, _alloc_( AllocT() )
	{
		_items_ = _alloc_.malloc( _items_, size );
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::vector( const vector<T>& vec )
	: _items_( 0 )
	, _alloc_( vec._alloc_ )
	{
		_items_ = _alloc_.malloc( _items_, size() );
		
		for( kick::size_t i = 0; i < vec.size(); ++i )
			_items_[i] = vec._items_[i];
		
		
	}
	
	template<typename T, typename AllocT>
	vector<T,AllocT>::~vector() {
		if( _items_ )
			_alloc_.free( _items_ );
		
	}
	
	template<typename T, typename AllocT>
	const vector<T>& vector<T,AllocT>::operator=( const vector<T>& vec ) {
		if( this != &vec ) {
			_alloc_.free( _items_ );
			
			_items_ = _alloc_.malloc( _items_, vec.size() );
			
			for( int i = 0; i < size(); ++i )
				_items_[i] = vec._items_[i];
			
			
		}
		
		return *this;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::clear() {
		_alloc_.free( _items_ );
	}
	
	template<typename T, typename AllocT>
	bool vector<T,AllocT>::empty() const {
		return size();
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase( size_t index ) {
		if( index < size() ){
			_items_ = _alloc_.move( _items_, index + 1, index );
			_items_ = _alloc_.realloc( _items_, size() - 1 );
			
		}
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::erase( array_iterator<T> pos ) {
		_items_ = _alloc_.move( _items_, pos.index() + 1, pos.index() );
		_items_ = _alloc_.realloc( _items_, size() - 1 );
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_back( const T& item ) {
		_items_ = _alloc_.realloc( _items_, size() + 1 );
		
		_items_[size() - 1] = item;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::push_front( const T& item ) {
		_items_ = _alloc_.realloc( _items_, size() + 1 );
		_items_ = _alloc_.move( _items_, 0, 1 );
		
		_items_[0] = item;
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::pop_back() {
		if( size() )
			_items_ = _alloc_.realloc( _items_, size() - 1 );
		
	}
	
	template<typename T, typename AllocT>
	void vector<T,AllocT>::pop_front() {
		if( size() ){
			_items_ = _alloc_.move( _items_, 1, 0 );
			_items_ = _alloc_.realloc( _items_, size() - 1 );
			
		}
		
	}
	
	template<typename T, typename AllocT>
	const size_t vector<T,AllocT>::size() const {
		return _alloc_.usize();
	}
	
	template<typename T, typename AllocT>
	const size_t vector<T,AllocT>::capacity() const {
		return _alloc_.asize();
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::front() {
		return _items_[0];
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::back() {
		return _items_[size() - 1];
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::begin() {
		return iterator( 0, _items_ );
	}
	
	template<typename T, typename AllocT>
	typename vector<T,AllocT>::iterator vector<T,AllocT>::end() {
		return iterator( size(), _items_ );
	}
	
	template<typename T, typename AllocT>
	T& vector<T,AllocT>::operator[]( size_t index ) {
		return _items_[index];
	}

} // namespace kick

#endif // _kick_vector_h
