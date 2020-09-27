#pragma once
//class to change x and y coordinate
#include <Windows.h>

class XY
{
public:
	void gotoXY(int x, int y)
	{
		if (x >= 0 && y >= 0)
		{
			COORD coord;
			coord.X = x;
			coord.Y = y;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		}
	}
};