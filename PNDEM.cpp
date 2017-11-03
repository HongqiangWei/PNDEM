#include "stdafx.h"
# include <iostream>
# include <fstream>
# include <sstream>
# include "PerlinNoise.h"
# include "dem.h"
# include "Node.h"
# include "utils.h"
# include <string>

void calculateStatistics(const CDEM& dem, double* min, double* max, double* mean, double* stdDev)
{
	int width = dem.Get_NX();
	int height = dem.Get_NY();

	int validElements = 0;
	double minValue, maxValue;
	double sum = 0.0;
	double sumSqurVal = 0.0;
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			if (!dem.is_NoData(row, col))
			{
				double value = dem.asFloat(row, col);

				if (validElements == 0)
				{
					minValue = maxValue = value;
				}
				validElements++;
				if (minValue > value)
				{
					minValue = value;
				}
				if (maxValue < value)
				{
					maxValue = value;
				}

				sum += value;
				sumSqurVal += (value * value);
			}
		}
	}

	double meanValue = sum / validElements;
	double stdDevValue = sqrt((sumSqurVal / validElements) - (meanValue * meanValue));
	*min = minValue;
	*max = maxValue;
	*mean = meanValue;
	*stdDev = stdDevValue;
}

int PNDEM(const int height, const int width, const double frequency, const int octaves, const std::uint32_t seed, char* outputfilepath) {
	CDEM dem;
	double geoTransformArgs[6];
	geoTransformArgs[0] = 244730; geoTransformArgs[1] = 3; geoTransformArgs[2] = 0;
	geoTransformArgs[3] = 5113198;geoTransformArgs[4] = 0; geoTransformArgs[5] = -3;

	dem.SetHeight(height);
	dem.SetWidth(width);
	if (!dem.Allocate()) {
		std::cout << "Failed to allocate memory correctly!" << std::endl;
		return 0;
	}

	const PN::PerlinNoise perlin(seed);
	const double fx = width / frequency;
	const double fy = height / frequency;
	for (int y = 0; y < height; ++y){
		for (int x = 0; x < width; ++x){
			dem.Set_Value(x, y, perlin.octaveNoise0_1(x / fx, y / fy, octaves) * 1000);
		}
	}

	double min, max, mean, stdDev;
	calculateStatistics(dem, &min, &max, &mean, &stdDev);
	CreateGeoTIFF(outputfilepath, dem.Get_NY(), dem.Get_NX(),
		(void *)dem.getDEMdata(), GDALDataType::GDT_Float32, geoTransformArgs,
		&min, &max, &mean, &stdDev, -9999);
	return 1;
}