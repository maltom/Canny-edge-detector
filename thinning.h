#pragma once
#include <SFML\graphics.hpp>
#include "detector.h"

struct maxpixl
{
	int x = 0, y = 0, val = 0;
};
void poorThin(sf::Image &image, int radius, int level);
void fineThinstep1(sf::Image &image, int radius, int level);
void fineThinstep2(sf::Image &image, int radius, int level);
void intelligentThin(sf::Image &image, int radius, pixldata **garray);


void hysteresis(sf::Image &image, int radius, int uplevel, int lowlevel);

//void guohall(sf::Image &image, int radius, int level);