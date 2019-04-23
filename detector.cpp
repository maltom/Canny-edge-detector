#include <SFML/Graphics.hpp>
#include "detector.h"
#include <cmath>
#define PI 3.141592



void roberts(sf::Image &image)
{
	int t1 = 0, t2 = 0;
	sf::Color color;
	
	for (int i = 0;i < image.getSize().y - 1;i++)
	{
		for (int j = 0;j < image.getSize().x - 1;j++)
		{
			t1 = image.getPixel(j, i).r - image.getPixel(j+1, i+1).r;
			t2 = image.getPixel(j + 1, i).r - image.getPixel(j, i + 1).r;
			color.r = (abs(t1) + abs(t2));
			color.g = (abs(t1) + abs(t2));
			color.b = (abs(t1) + abs(t2));

			/*
			color.r = sqrt(t1*t1 + t2*t2);
			color.g = sqrt(t1*t1 + t2*t2);
			color.b = sqrt(t1*t1 + t2*t2);
			*/
			image.setPixel(j, i, color);
		}
	}


}
void prewitt(sf::Image &image, pixldata **garray)
{
	int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	sf::Color color;
	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Cyan);

	for (int i = 1;i < image.getSize().y - 1;i++)
	{
		for (int j = 1;j < image.getSize().x - 1;j++)
		{

			t1 = -image.getPixel(j - 1, i - 1).r - image.getPixel(j - 1, i).r - image.getPixel(j - 1, i + 1).r + image.getPixel(j + 1, i - 1).r + image.getPixel(j + 1, i).r + image.getPixel(j + 1, i + 1).r;
			t2 = -image.getPixel(j - 1, i).r - image.getPixel(j - 1, i + 1).r - image.getPixel(j, i + 1).r + image.getPixel(j + 1, i).r + image.getPixel(j + 1, i - 1).r + image.getPixel(j, i - 1).r;
			t3 = -image.getPixel(j - 1, i + 1).r - image.getPixel(j, i + 1).r - image.getPixel(j + 1, i + 1).r + image.getPixel(j - 1, i - 1).r + image.getPixel(j, i - 1).r + image.getPixel(j + 1, i - 1).r;
			t4 = -image.getPixel(j, i + 1).r - image.getPixel(j + 1, i + 1).r - image.getPixel(j + 1, i).r + image.getPixel(j - 1, i).r + image.getPixel(j - 1, i - 1).r + image.getPixel(j, i - 1).r;
			
			color.r = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.g = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.b = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			
			garray[j][i].gx = t1;
			garray[j][i].gy = t3;
			garray[j][i].gtrue = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			garray[j][i].gsimpl = sqrt(t1*t1 + t2*t2);
			/*if(t*1!=0)garray[j][i].fi = atan2(t3, t1) * 360 / PI;
			//else garray[j][i].fi = 0;

			if (garray[j][i].fi < 22.5)
				garray[j][i].fi = 0;
			else if (garray[j][i].fi < 67.5)
				garray[j][i].fi = 45;
			else if (garray[j][i].fi < 112.5)
				garray[j][i].fi = 90;
			else if (garray[j][i].fi < 157.5)
				garray[j][i].fi = 135;
			else
				garray[j][i].fi = 0;*/
			t1 = abs(t1);
			t2 = abs(t2);
			t3 = abs(t3);
			t4 = abs(t4);
			
			if (t1 > t4 && t1 > t3 && t1 > t2)
				garray[j][i].fi = 0;
			else if (t2 > t4 && t2 > t3 && t2 > t1)
				garray[j][i].fi = 45;
			else if (t3 > t4 && t3 > t2 && t3 > t1)
				garray[j][i].fi = 90;
			else if (t4 > t3 && t4 > t2 && t4 > t1)
				garray[j][i].fi = 135;
			else
				garray[j][i].fi = 0;
				

			if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) < 0)
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
			}
			else if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) > 255)
			{
				color.r = 255;
				color.g = 255;
				color.b = 255;
			}
			
			else 
			{

				color.r = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.g = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.b = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
			}
			bufor.setPixel(j, i, color);
		}
	}

	image.copy(bufor, 0, 0);

}
void sobel(sf::Image &image, pixldata **garray, float division)
{
	int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	sf::Color color;
	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Cyan);

	for (int i = 1;i < image.getSize().y - 1;i++)
	{
		for (int j = 1;j < image.getSize().x - 1;j++)
		{

			t1 = (- image.getPixel(j - 1, i - 1).r - 2 * image.getPixel(j - 1, i).r - image.getPixel(j - 1, i + 1).r + image.getPixel(j + 1, i - 1).r + 2 * image.getPixel(j + 1, i).r + image.getPixel(j + 1, i + 1).r) / division;
			t2 = (- image.getPixel(j - 1, i).r - 2 * image.getPixel(j - 1, i + 1).r - image.getPixel(j, i + 1).r + image.getPixel(j + 1, i).r + 2 * image.getPixel(j + 1, i - 1).r + image.getPixel(j, i - 1).r) / division;
			t3 = (- image.getPixel(j - 1, i + 1).r - 2 * image.getPixel(j, i + 1).r - image.getPixel(j + 1, i + 1).r + image.getPixel(j - 1, i - 1).r + 2 * image.getPixel(j, i - 1).r + image.getPixel(j + 1, i - 1).r) / division;
			t4 = (- image.getPixel(j, i + 1).r - 2 * image.getPixel(j + 1, i + 1).r - image.getPixel(j + 1, i).r + image.getPixel(j - 1, i).r + 2 * image.getPixel(j - 1, i - 1).r + image.getPixel(j, i - 1).r) / division;

			color.r = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.g = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.b = (abs(t1) + abs(t2) + abs(t3) + abs(t4));

			garray[j][i].gx = t1;
			garray[j][i].gy = t3;
			garray[j][i].gtrue = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
			garray[j][i].gsimpl = sqrt(t1*t1 + t2*t2);

			t1 = abs(t1);
			t2 = abs(t2);
			t3 = abs(t3);
			t4 = abs(t4);

			if (t1 > t4 && t1 > t3 && t1 > t2)
				garray[j][i].fi = 0;
			else if (t2 > t4 && t2 > t3 && t2 > t1)
				garray[j][i].fi = 45;
			else if (t3 > t4 && t3 > t2 && t3 > t1)
				garray[j][i].fi = 90;
			else if (t4 > t3 && t4 > t2 && t4 > t1)
				garray[j][i].fi = 135;
			else
				garray[j][i].fi = 0;


			if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) < 0)
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
			}
			else if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) > 255)
			{
				color.r = 255;
				color.g = 255;
				color.b = 255;
			}

			else
			{

				color.r = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.g = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.b = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
			}
			bufor.setPixel(j, i, color);
		}
	}

	image.copy(bufor, 0, 0);

}
void scharr(sf::Image &image, pixldata **garray, float division)
{
	int t1 = 0, t2 = 0, t3 = 0, t4 = 0;
	sf::Color color;
	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Cyan);

	for (int i = 1;i < image.getSize().y - 1;i++)
	{
		for (int j = 1;j < image.getSize().x - 1;j++)
		{

			t1 = (-3 * image.getPixel(j - 1, i - 1).r - 10 * image.getPixel(j - 1, i).r - 3 * image.getPixel(j - 1, i + 1).r + 3 * image.getPixel(j + 1, i - 1).r + 10 * image.getPixel(j + 1, i).r + 3 * image.getPixel(j + 1, i + 1).r) / division;
			t2 = (-3 * image.getPixel(j - 1, i).r - 10 * image.getPixel(j - 1, i + 1).r - 3 * image.getPixel(j, i + 1).r + 3 * image.getPixel(j + 1, i).r + 10 * image.getPixel(j + 1, i - 1).r + 3 * image.getPixel(j, i - 1).r) / division;
			t3 = (-3 * image.getPixel(j - 1, i + 1).r - 10 * image.getPixel(j, i + 1).r - 3 * image.getPixel(j + 1, i + 1).r + 3 * image.getPixel(j - 1, i - 1).r + 10 * image.getPixel(j, i - 1).r + 3 * image.getPixel(j + 1, i - 1).r) / division;
			t4 = (-3 * image.getPixel(j, i + 1).r - 10 * image.getPixel(j + 1, i + 1).r - 3 * image.getPixel(j + 1, i).r + 3 * image.getPixel(j - 1, i).r + 10 * image.getPixel(j - 1, i - 1).r + 3 * image.getPixel(j, i - 1).r) / division;

			color.r = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.g = (abs(t1) + abs(t2) + abs(t3) + abs(t4));
			color.b = (abs(t1) + abs(t2) + abs(t3) + abs(t4));

			garray[j][i].gx = t1;
			garray[j][i].gy = t3;
			garray[j][i].gtrue = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
			garray[j][i].gsimpl = sqrt(t1*t1 + t2*t2);
			
			t1 = abs(t1);
			t2 = abs(t2);
			t3 = abs(t3);
			t4 = abs(t4);

			if (t1 > t4 && t1 > t3 && t1 > t2)
				garray[j][i].fi = 0;
			else if (t2 > t4 && t2 > t3 && t2 > t1)
				garray[j][i].fi = 45;
			else if (t3 > t4 && t3 > t2 && t3 > t1)
				garray[j][i].fi = 90;
			else if (t4 > t3 && t4 > t2 && t4 > t1)
				garray[j][i].fi = 135;
			else
				garray[j][i].fi = 0;


			if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) < 0)
			{
				color.r = 0;
				color.g = 0;
				color.b = 0;
			}
			else if (sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4) > 255)
			{
				color.r = 255;
				color.g = 255;
				color.b = 255;
			}

			else
			{

				color.r = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.g = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
				color.b = sqrt(t1*t1 + t2*t2 + t3*t3 + t4*t4);
			}
			bufor.setPixel(j, i, color);
		}
	}

	image.copy(bufor, 0, 0);

}
void gradientTest(pixldata **garray, sf::Image& image, int level)				//test of edge direction and saturation
{
	for (int i = 0;i < image.getSize().y; i++)
	{
		for (int j = 0;j < image.getSize().x; j++)
		{
			if (garray[j][i].fi == 0 && garray[j][i].gtrue > level)
			{
				image.setPixel(j, i, sf::Color::Blue);
			}
			else if (garray[j][i].fi == 45 && garray[j][i].gtrue > level)
			{
				image.setPixel(j, i, sf::Color::Red);
			}
			else if (garray[j][i].fi == 90 && garray[j][i].gtrue > level)
			{
				image.setPixel(j, i, sf::Color::Green);
			}
			else if (garray[j][i].fi == 135 && garray[j][i].gtrue > level)
			{
				image.setPixel(j, i, sf::Color::Yellow);
			}
		}
	}
}