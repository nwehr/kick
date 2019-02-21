#ifndef _kick_hof_h
#define _kick_hof_h

#include "../../vector.hpp"
#include "../../allocator/array_allocator.hpp"

namespace kick {
	namespace experimental {
		namespace hof {
			///////////////////////////////////////////////////////////////////////////////
			// map
			///////////////////////////////////////////////////////////////////////////////
			template<typename T, typename R = T>
			vector<R> map(const vector<T>& v, R (*fn)(T)) {
				vector<R> r;

				for(typename vector<T>::iterator it = v.begin(); it != v.end(); ++it) {
					r.push_back(fn(*it));
				}

				return r;
			}

		} // namespace hof
	} // namespace experimental
} // namespace kick

#endif // _kick_hof_h