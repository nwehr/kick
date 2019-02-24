
#ifndef _kick_either_h
#define _kick_either_h

//
// Copyright 2012-2014 Kick project developers.
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
//
// This file is part of the Kick project and subject to license terms.
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	namespace experimental {
		///////////////////////////////////////////////////////////////////////////////
		// either
		///////////////////////////////////////////////////////////////////////////////
		template<typename L, typename R>
		class either {
		public:
			typedef union {
				L* left;
				R* right;
			} left_or_right_t;
			
			either(left_or_right_t left_or_right, bool is_left) {
				if(_is_left) {
					_left_or_right.left = left_or_right.left;
				} else {
					_left_or_right.right = left_or_right.right;
				}
				
				_refs = new unsigned int(1);
				_is_left = is_left;
			}
			
			either(const either<L, R>& rhs) {
				if(rhs._is_left) {
					_left_or_right.left = rhs._left_or_right.left;
				} else {
					_left_or_right.right = rhs._left_or_right.right;
				}
				
				_refs = rhs._refs;
				++(*_refs);
			}
			
			~either() {
				--(*_refs);
				
				if(*_refs == 0) {
					if(_is_left) {
						delete _left_or_right.left;
					} else {
						delete _left_or_right.right;
					}
					
					delete _refs;	
				}
			}
			
			const either<L, R>& map_left(void (*fn)(const L&)) const {
				if(_is_left) {
					fn(*_left_or_right.left);
				}
				
				return *this;
			}

			const either<L, R>& map_right(void (*fn)(const R&)) const {
				if(!_is_left) {
					fn(*_left_or_right.right);
				}
				
				return *this;
			}
			
		public:
			left_or_right_t _left_or_right;
			unsigned int* _refs;
			bool _is_left;
		};

		///////////////////////////////////////////////////////////////////////////////
		// make_left
		///////////////////////////////////////////////////////////////////////////////
		template<typename L, typename R>
		either<L, R> make_left(const L& left) {
			return either<L, R>({.left = new L(left)}, true);
		}

		///////////////////////////////////////////////////////////////////////////////
		// make_right
		///////////////////////////////////////////////////////////////////////////////
		template<typename L, typename R>
		either<L, R> make_right(const R& right) {
			return either<L, R>({.right = new R(right)}, false);
		}
	}
}

#endif // _kick_either_h