#pragma once
#include <SFML\graphics.hpp>
#include <cmath>
#define PI 3.141592
/*class pixldata
{
public:
	
	struct data
	{
		double gx = 0;
		double gy = 0;
		double fi = 0;
	};

pixldata(double x, double y, int arrayx, int arrayy)
	{
	data **dats= new data *[arrayx];
	for(int i=0;i<ar)

		data.gx = x;
		data.gy = y;
		data.fi = atan2(data.gy, data.gx);
		data.fi = data.fi * 180 / PI;
		if (data.fi < 22.5)
			data.fi = 0;
		else if (22.5 <= data.fi < 67.5)
			data.fi = 45;
		else if (67.5 <= data.fi < 112.5)
			data.fi = 90;
		else if (112.5 <= data.fi < 157.5)
			data.fi = 135;
		else
			data.fi = 180;
	}

};*/

struct pixldata
{
	double gx = 0;
	double gy = 0;
	double fi = 0;
	double gtrue = 0;
	double gsimpl = 0;
};

void roberts(sf::Image &image);
void prewitt(sf::Image &image, pixldata **garray);
void sobel(sf::Image &image, pixldata **garray, float division);
void scharr(sf::Image &image, pixldata **garray, float division);
void gradientTest(pixldata **garray, sf::Image &image, int level);