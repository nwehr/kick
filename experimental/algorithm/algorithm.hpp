#ifndef _kick_hof_h
#define _kick_hof_h

#include "../../vector.hpp"
#include "../../allocator/array_allocator.hpp"

namespace kick {
	namespace experimental {
		namespace algorithm {
			///////////////////////////////////////////////////////////////////////////////
			// transform
			///////////////////////////////////////////////////////////////////////////////
			// template<typename T, typename O = T>
			// void transform(iterator<T> begin, iterator<T> end, R (*fn)(T)) {
			// 	for(begin; begin != end; ++begin) {
			// 		out.push_back(fn(*begin));
			// 	}
			// }

		} // namespace hof
	} // namespace experimental
} // namespace kick

#endif // _kick_hof_h