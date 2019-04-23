#include <SFML/Graphics.hpp>

#include "gauss.h"
#include "detector.h"
#include "thinning.h"
#include "corners.h"

#define sigma 3						//gauss filter parameter
#define radius 2					//'radius' of gauss filter's kernel, kernel edge length = 1 + 2xradius
#define thinsize 1					//'radius' of thinning filter, kernel edge length = 1 + 2xthinsize
#define scharrDivision 4			//prescale of scharr's detection
#define sobelDivision 1				//prescale of sobel's detection
#define leveltest 254				//test level to colors in pre-thinned 
#define hysteresisRadius 1			//'radius' of kernel for hysteresis blob check
#define level 40					//saturation level below which pixels will be blanked during thinning
#define hysteresisUpperLevelSob 50		//saturation level above which all points will be considered strong edge
#define hysteresisLowerLevelSob 30		//saturation level below which all points will be considered weak; values between will be checked if they neighbour strong edge points
#define hysteresisUpperLevelSch 70		
#define hysteresisLowerLevelSch 50

int main()
{
	
	sf::Image imydz;
	imydz.loadFromFile("lena.jpg");
	int x = imydz.getSize().x;
	int y = imydz.getSize().y;


	pixldata **garray = new pixldata *[x];
	for (int i = 0;i < x;i++)
	{
	garray[i] = new pixldata[y];
	}
	
	int gaussEdgeLength = 2 * radius + 1;
	double gaussSum = 0;
	double **gaussianKer = new double *[gaussEdgeLength];
	for (int i = 0;i < gaussEdgeLength;i++)
	{
		gaussianKer[i] = new double[gaussEdgeLength];
	}
	

	sf::RenderWindow window(sf::VideoMode(x, y), "Edge Detector");
	
	
	monochrome(imydz);


	gaussKernel(gaussianKer, &gaussSum, gaussEdgeLength, sigma, radius);

	gauss(imydz, gaussianKer, gaussSum, radius, sigma);
	
	//roberts(imydz);
	
	//prewitt(imydz,garray);

	//sobel(imydz, garray, sobelDivision);

	
	
	//fineThinstep1(imydz, thinsize, level);
	//fineThinstep2(imydz, thinsize, level);

	scharr(imydz, garray, scharrDivision);
	intelligentThin(imydz, thinsize, garray);
	hysteresis(imydz, hysteresisRadius, hysteresisUpperLevelSch, hysteresisLowerLevelSch);

	//hysteresis(imydz, hysteresisRadius, hysteresisUpperLevelSob, hysteresisLowerLevelSob);
	
	//gradientTest(garray, imydz, leveltest);

	//imydz.flipVertically();
	//poorThin(imydz, thinsize, level);

	sf::Texture texture;
	texture.loadFromImage(imydz);
	sf::Sprite sprite(texture);



	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}



		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}
