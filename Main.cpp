#include "stdafx.h"

//--------------------------------------------------------------------
//
//	Perlin Noise Terrain Generator for modern C++ 11
//
//	The basic function writed by Ryo Suzuki <reputeless@gmail.com>
//  
//  The PNDEM() function writed by Hongqiang Wei <cwnuweihongqiang@126.com>
//
//  We use GDAL library to write the DEM file, the version of GDAL library is 1.9.1
//
//	For the license information refer to PerlinNoise.hpp.
//
//--------------------------------------------------------------------

# include <iostream>
# include <fstream>
# include <sstream>
# include "PerlinNoise.h"
# include "dem.h"
# include "Node.h"
# include "utils.h"
# include <string>
# include <time.h>

int Random(int m, int n) {
	int pos, dis;
	if (m == n)
	{
		return m;
	}
	else if (m > n)
	{
		pos = n;
		dis = m - n + 1;
		return rand() % dis + pos;
	}
	else
	{
		pos = m;
		dis = n - m + 1;
		return rand() % dis + pos;
	}

}

template <class Type>
inline constexpr const Type& Clamp(const Type& x, const Type& min, const Type& max)
{
	return (x < min) ? min : ((max < x) ? max : x);
}

int PNDEM(const int height, const int width, const double frequency, const int octaves, const std::uint32_t seed, char* outputfilepath);
int main(int argc, char* argv[])
{
	
	//argc = 2;
	if (argc != 2) return 0;
	//argv[1] = "F:\\TestData\\DEM Data\\Source File\\SizeBig\\PNDEM6.tif";
	std::string path(argv[1]);

	std::cout << "---------------------------------\n";
	std::cout << "* height    [1 .. 1000 ..50000]  \n";
	std::cout << "* width     [1 .. 1000 ..50000]  \n";
	std::cout << "* frequency [0.1 .. 8.0 .. 64.0] \n";
	std::cout << "* octaves   [1 .. 8 .. 16]       \n";
	std::cout << "* seed      [0 .. 2^32-1]        \n";
	std::cout << "---------------------------------\n";


	//int height;
	//std::cout << "int height = ";
	//std::cin >> height;
	//height = Clamp(height, 1, 50000);

	//int width;
	//std::cout << "int width = ";
	//std::cin >> width;
	//width = Clamp(width, 1, 50000);

	//double frequency;
	//std::cout << "double frequency = ";
	//std::cin >> frequency;
	//frequency = Clamp(frequency, 0.1, 64.0);

	//int octaves;
	//std::cout << "int32 octaves    = ";
	//std::cin >> octaves;
	//octaves = Clamp(octaves, 1, 16);

	//std::uint32_t seed;
	//std::cout << "uint32 seed      = ";
	//std::cin >> seed;

	srand((int)time(NULL));
	int height = Random(1, 3000);
	srand((int)time(NULL));
	int width = Random(1, 3000);
	srand((int)time(NULL));
	double frequency = (double)Random(1, 10);
	srand((int)time(NULL));
	int octaves = Random(1, 5);
	srand((int)time(NULL));
	int seed = Random(1,300);
	std::cout << " height = " << height << " width = " << width << " frequency = " << frequency << " octaves = " << octaves << " seed = " << seed << std::endl;

	if (PNDEM(height, width, frequency, octaves, seed, &path[0]) == 1) 
		std::cout << "The new image is generated successfully!" << std::endl;
	else
		std::cout << "New image generation failed!" << std::endl;
	return 1;
}


