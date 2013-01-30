#include <time.h>

#include <iostream>
#include <vector>

#include <kick/kick.h>

int main( int argc, char* argv[] ){
	double KickAvgTime( 0.0 );
	double StdAvgTime( 0.0 );
	
	kick::vector<float> KickTimes;
	kick::vector<float> StdTimes;
	
	kick::vector<int> KickVector;
	std::vector<int> StdVector;
	
	for( int i = 0; i < 100000; ++i ){
		clock_t kt1 = clock();
		KickVector.push_front( i );
		clock_t kt2 = clock();
		
		KickTimes.push_back( (((float)kt2 - (float)kt1) / 1000000.0F ) * 1000 );
		
		clock_t st1 = clock();
		StdVector.insert( StdVector.begin(), i );
		clock_t st2 = clock();
		
		StdTimes.push_back( (((float)st2 - (float)st1) / 1000000.0F ) * 1000 );
		
	}
	
	for( int i = 0; i < KickTimes.size(); ++i )
		KickAvgTime += KickTimes[i];
	
	for( int i = 0; i < StdTimes.size(); ++i )
		StdAvgTime += StdTimes[i];
	
	std::cout << "average push_back time for kick::vector" << std::endl;
	std::cout << KickAvgTime / KickTimes.size() << std::endl;
	std::cout << KickVector.capacity() << " allocated items" << std::endl;
	
	std::cout << std::endl;
	
	std::cout << "average push_back time for std::vector" << std::endl;
	std::cout << StdAvgTime / StdTimes.size() << std::endl;
	std::cout << StdVector.capacity() << " allocated items" << std::endl;
	
}
