#include <SFML/Graphics.hpp>
#include "thinning.h"
#include "detector.h"
#include <cmath>



void poorThin(sf::Image &image, int radius, int level)										//simple thinning, working poorly, not used
{
	/*int **kernel = new int *[thinsize];
	for (int i = 0;i < thinsize;i++)
	{
		kernel[i] = new int[thinsize];
	}*/
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	maxpixl toppixl;

	for (int i = 0;i < xmax;i++)
	{
		int leftBound = 0, rightBound = 0, ceilBound = 0, bottomBound = 0;
		sf::Color color;


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
					if (image.getPixel(l, t).r > toppixl.val)
					{
						toppixl.x = l;
						toppixl.y = t;
						toppixl.val = image.getPixel(l, t).r;
					}

				}
			}
			if (i == toppixl.x&&j == toppixl.y&&toppixl.val>level)
				image.setPixel(i, j, sf::Color::White);
			else
				image.setPixel(i, j, sf::Color::Black);

			ceilBound = bottomBound = 0;
			toppixl.val = 0;
			toppixl.x = 0;
			toppixl.y = 0;

		}
		leftBound = rightBound = 0;
		
	}


}
void fineThinstep1(sf::Image &image, int radius, int level)										//vertical thinning, not used
{
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	bool judgeandjury = true;

	for (int i = 0;i < xmax;i++)
	{
		int ceilBound = 0, bottomBound = 0;

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

			for (int t = ceilBound; t <= bottomBound; t++)
			{
				if ((image.getPixel(i, t).r >= image.getPixel(i, j).r) && (t != j))
				{
					judgeandjury = false;
				}
				
			}
			if (judgeandjury == false || image.getPixel(i, j).r < level)
			{
				image.setPixel(i, j, sf::Color::Black);
			}
			else
			{
				image.setPixel(i, j, sf::Color::White);
			}
			ceilBound = bottomBound = 0;
			judgeandjury = true;
		}
		
	}
		
	
}
void fineThinstep2(sf::Image &image, int radius, int level)										//horizontal thnning, not used
{
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	bool judgeandjury = true;

	for (int i = 0;i < ymax;i++)
	{
		int leftBound = 0, rightBound = 0;

		for (int j = 0;j < xmax;j++)
		{

			if (j < radius)
			{
				leftBound = 0;
				rightBound = j + radius;
			}
			else if (j >= xmax - radius)
			{
				leftBound = j - radius;
				rightBound = xmax - 1;
			}
			else
			{
				leftBound = j - radius;
				rightBound = j + radius;
			}

			for (int t = leftBound; t <= rightBound; t++)
			{
				if ((image.getPixel(t, i).r >= image.getPixel(j, i).r) && (t != j))
				{
					judgeandjury = false;
				}

			}
			if (judgeandjury == false || image.getPixel(j, i).r < level)
			{
				image.setPixel(j, i, sf::Color::Black);
			}
			else
			{
				image.setPixel(j, i, sf::Color::White);
			}
			leftBound = rightBound = 0;
			judgeandjury = true;
		}
	}
}

/*void intelligentThin(sf::Image &image, int radius, pixldata **garray)					//kernel-based thinning in four directions based on point's gradient
{
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	bool judgeandjury = true;

	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Black);

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

			if (garray[i][j].fi == 0)
			{
				for (int t = leftBound; t <= rightBound; t++)
				{
					if ((image.getPixel(t, j).r >= image.getPixel(i, j).r) && (t != i))
					{
						judgeandjury = false;
					}
				}
			}
			else if (garray[i][j].fi == 135)
			{
				for (int l = leftBound, t = ceilBound; (l <= rightBound && t <= bottomBound); l++, t++)
				{
					if ((image.getPixel(l, t).r >= image.getPixel(i, j).r) && (t != j))
					{
						judgeandjury = false;
					}
				}
			}
			else if (garray[i][j].fi == 90)
			{
				for (int t = ceilBound; t <= bottomBound; t++)
				{
					if ((image.getPixel(i, t).r >= image.getPixel(i, j).r) && (t != j))
					{
						judgeandjury = false;
					}
				}
			}
			else if (garray[i][j].fi == 45)
			{
				for (int l = rightBound, t = ceilBound; (l >= leftBound && t <= bottomBound); l--, t++)
				{
					if ((image.getPixel(l, t).r >= image.getPixel(i, j).r) && (t != j))
					{
						judgeandjury = false;
					}
				}
			}

			if (judgeandjury == false)
			{
				bufor.setPixel(i, j, sf::Color::Black);
			}
			else bufor.setPixel(i, j, image.getPixel(i,j));
			
			
			judgeandjury = true;

		}
		leftBound = rightBound = 0;
	}

	image.copy(bufor, 0, 0);
}*/
void intelligentThin(sf::Image &image, int radius, pixldata **garray)					//kernel-based thinning in four directions based on point's gradient
{
	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	bool judgeandjury = false;

	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Black);

	for (int i = 1;i < xmax - 1;i++)
	{
		
		for (int j = 1;j < ymax - 1;j++)
		{
			double currentGradient = garray[i][j].gtrue;
			if (garray[i][j].fi == 0)
			{
				if (((currentGradient >= garray[i + 1][j].gtrue) && (currentGradient > garray[i - 1][j].gtrue)) ||
					((currentGradient > garray[i + 1][j].gtrue) && (currentGradient >= garray[i - 1][j].gtrue)))
				{

					judgeandjury = true;
				}
				else judgeandjury = false;
				
			}

			else if (garray[i][j].fi == 135)
			{
				if (((currentGradient >= garray[i - 1][j - 1].gtrue) && (currentGradient > garray[i + 1][j + 1].gtrue)) ||
					((currentGradient > garray[i - 1][j - 1].gtrue) && (currentGradient >= garray[i + 1][j + 1].gtrue)))
				{
					judgeandjury = true;
				}
				else judgeandjury = false;
				
			}
			else if (garray[i][j].fi == 90)
			{
				if (((currentGradient >= garray[i][j - 1].gtrue) && (currentGradient > garray[i][j + 1].gtrue)) ||
					((currentGradient > garray[i][j - 1].gtrue) && (currentGradient >= garray[i][j + 1].gtrue)))
				{
					judgeandjury = true;
				}
				else judgeandjury = false;
			}
			else if (garray[i][j].fi == 45)
			{
				if (((currentGradient >= garray[i + 1][j - 1].gtrue) && (currentGradient > garray[i - 1][j + 1].gtrue)) ||
					((currentGradient > garray[i + 1][j - 1].gtrue) && (currentGradient >= garray[i - 1][j + 1].gtrue)))
				{
					judgeandjury = true;
				}
				else judgeandjury = false;
			}

			if (judgeandjury == false)
			{
				bufor.setPixel(i, j, sf::Color::Black);
			}
			else bufor.setPixel(i, j, image.getPixel(i, j));


			judgeandjury = false;

		}
		
	}

	image.copy(bufor, 0, 0);
}
void hysteresis(sf::Image &image, int radius, int uplevel, int lowlevel)
{

	int xmax = image.getSize().x;
	int ymax = image.getSize().y;
	bool judgeandjury = false;

	sf::Image bufor;
	bufor.create(image.getSize().x, image.getSize().y, sf::Color::Cyan);

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
			int currentPoint = image.getPixel(i, j).r;

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

			if (currentPoint > uplevel)
			{
				judgeandjury = true;
			}
			else if (currentPoint > lowlevel)
			{
				for (int t = leftBound; t <= rightBound; t++)
				{
					for (int l = ceilBound; l <= bottomBound; l++)
					{
						if (image.getPixel(t, l).r > uplevel)
						{
							judgeandjury = true;
						}
						
					}
				}
			}
			else judgeandjury = false;
			
			if (judgeandjury == true)
			{
				bufor.setPixel(i, j, sf::Color::White);
			}
			else
			{
				bufor.setPixel(i, j, sf::Color::Black);
			}

			judgeandjury = false;
			currentPoint = 0;

		}
		leftBound = rightBound = 0;
	}
	image.copy(bufor, 0, 0);
}