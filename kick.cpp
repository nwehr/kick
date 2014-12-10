#ifndef ARDUINO

// #define KICK_POLYMORPHIC 1

// C++
#include <functional>

void test() {}

int main (int argc, char* argv[]) {
	std::function<void(void)> F( &test );
}

#endif // ARDUINO
