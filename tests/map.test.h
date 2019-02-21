#include <gtest/gtest.h>

#include "../map.hpp"

TEST(Map, Insert) {
	kick::map<int, int> myMap;

	for(int i = 0; i < 100; ++i) {
		myMap.insert(kick::pair<int, int>((i + 1) * 100, (i + 1) * 100));
	}
	
	ASSERT_EQ(myMap.size(), 100);
}