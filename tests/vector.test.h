#include <gtest/gtest.h>

#include "../vector.hpp"

TEST(Vector, Size) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}
	
	ASSERT_EQ(myVec.size(), 100);
}

TEST(Vector, PushBack) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}

	ASSERT_EQ(myVec.front(), 100);
	ASSERT_EQ(myVec.back(), 10000);
}

TEST(Vector, PushFront) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_front((i + 1) * 100);	
	}

	ASSERT_EQ(myVec.front(), 10000);
	ASSERT_EQ(myVec.back(), 100);
}

TEST(Vector, PopBack) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}

	for(int i = 0; i < 99; ++i) {
		myVec.pop_back();	
	}

	ASSERT_EQ(myVec.size(), 1);
	ASSERT_EQ(myVec.front(), 100);
}

TEST(Vector, PopFront) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}

	for(int i = 0; i < 99; ++i) {
		myVec.pop_front();	
	}

	ASSERT_EQ(myVec.size(), 1);
	ASSERT_EQ(myVec.front(), 10000);
}

TEST(Vector, Erase) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}

	myVec.erase(0);

	ASSERT_EQ(myVec.front(), 200);
	ASSERT_EQ(myVec.size(), 99);
}

TEST(Vector, Clear) {
	kick::vector<int> myVec;

	for(int i = 0; i < 100; ++i) {
		myVec.push_back((i + 1) * 100);	
	}

	myVec.clear();

	ASSERT_EQ(myVec.size(), 0);
}

