#include <gtest/gtest.h>

#include "./vector.test.h"
#include "./map.test.h"

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}