#include "gauss.h"
#include <SFML\graphics.hpp>
#include <cmath>

#define PI 3.141592

void monochrome(sf::Image &image)
{
	int xc, yc;
	sf::Color color;
	xc = image.getSize().x;
	yc = image.getSize().y;
	
	sf::Color greyscale;

	for (int i = 0;i < xc;i++)
		for (int j = 0;j < yc;j++)
		{

			color = image.getPixel(i, j);
			greyscale.r = (color.r*0.3 + color.g*0.59 + color.b*0.11);
			greyscale.g = (color.r*0.3 + color.g*0.59 + color.b*0.11);
			greyscale.b = (color.r*0.3 + color.g*0.59 + color.b*0.11);
			image.setPixel(i, j, greyscale);
		};
}
void gaussKernel(double **gaussianKer, double *gaussSum, int edgelength, int sigma, int radius)
{
	double constFactor = 0, sum = 0, gaussFactor = 0;
	
	constFactor = 1 / (2 * PI*pow(sigma, 2));
	for (int i = 0; i < radius; i++)
	{
		for (int j = 0; j < radius; j++)
		{
			gaussFactor = gaussianKer[i][j] = constFactor / exp(((radius - i)*(radius - i) + (radius - j)*(radius - j)) / (2 * sigma*sigma));
			*gaussSum += gaussFactor;

		}
	}

}

void gauss(sf::Image &image, double **gaussianKer, double gaussSum, int radius, double sigma)
{
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	double divideFactor = 0;
	double constFactor = 0, sum = 0;
	double finalPixelVal = 0;
	sf::Color finalColor;

	constFactor = 1 / (2 * PI*pow(sigma, 2));

	sf::Image bufor;
	bufor.create(xmax, ymax,sf::Color::Cyan);
	
	for (int i = 0;i < xmax;i++)
	{
		int leftBound = 0, rightBound = 0, ceilBound = 0, bottomBound = 0;

		if (i < radius)
		{
			leftBound = 0;
			rightBound = i + radius;
		}
		else if (i >= xmax - radius)
		{
			leftBound = i - radius;
			rightBound = xmax - 1;
		}
		else
		{
			leftBound = i - radius;
			rightBound = i + radius;
		}
		
		for (int j = 0;j < ymax;j++)
		{
			
			if (j < radius)
			{
				ceilBound = 0;
				bottomBound = j + radius;
			}
			else if (j >= ymax - radius)
			{
				ceilBound = j - radius;
				bottomBound = ymax - 1;
			}
			else
			{
				ceilBound = j - radius;
				bottomBound = j + radius;
			}

			for (int l = leftBound; l <= rightBound; l++)
			{
				for (int t = ceilBound; t <= bottomBound; t++)
				{
					sum += gaussianKer[radius - (i - l)][radius - (j - t)] * image.getPixel(l, t).r;
					divideFactor += gaussianKer[radius - (i - l)][radius - (j - t)];
				}
			}
			
			finalPixelVal = sum / divideFactor;
			finalColor.r = finalColor.g = finalColor.b = (int) finalPixelVal;
			bufor.setPixel(i, j, finalColor);

			divideFactor = sum = 0;

			ceilBound = bottomBound = 0;
			
		}
		leftBound = rightBound = 0;
	}

	image.copy(bufor, 0, 0);

}