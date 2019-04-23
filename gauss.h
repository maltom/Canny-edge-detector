#pragma once
#include <SFML\graphics.hpp>


void monochrome(sf::Image &image);

void gaussKernel(double **gaussianKer, double *gaussSum, int edgelength, int sigma, int radius);

void gauss(sf::Image &image, double **gaussianKer, double gaussSum, int radius, double sigma);
