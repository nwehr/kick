
#ifndef _kick_either_h
#define _kick_either_h

//
// See COPYRIGHT.txt or https://bitbucket.org/nwehr/kick/downloads/COPYRIGHT.txt
// See LICENSE.txt or https://bitbucket.org/nwehr/kick/downloads/LICENSE.txt
//

namespace kick {
	namespace experimental {
		template<typename L, typename R>
		struct either {
			~either() {}
			
			union {
				L left;
				R right;
			};
			
			bool is_left;
			
			const either<L, R>& map_left(void (*fn)(const L&)) const {
				if(is_left) {
					fn(left);
				}
				
				return *this;
			}

			const either<L, R>& map_right(void (*fn)(const R&)) const {
				if(!is_left) {
					fn(right);
				}
				
				return *this;
			}
		};

		template<typename L, typename R>
		either<L, R> make_left(const L& left) {
			return {.left = left, true};
		}

		template<typename L, typename R>
		either<L, R> make_right(const R& right) {
			return {.right = right, false};
		}
	}
}

#endif // _kick_either_h