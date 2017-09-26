// snake.cpp
// 2.0

#include "stdafx.h"
void gotoxy(int, int);
void Food(int&, int&);

int main()
{
	//HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//COORD crd = {60, 60};
	//SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	//SetConsoleWindowInfo(out_handle, true, &src);
	//SetConsoleScreenBufferSize(out_handle, crd);

	system("mode con lines=37 cols=95");		//window size

	int foodCoordX,
		foodCoordY,
		score = 0,
		length = 3,
		timeOfPause = 300,
		speedGrows = 6,
		l = 0;

	const int LENGTH_SNAKE = 50;
	char Matrix[35][60];

	int CoordT[LENGTH_SNAKE][2];

	for (int i = 0; i < 34; ++i)
	{
		for (int j = 0; j < 59; ++j)
		{
			Matrix[i][j] = ' ';
		}
	}
	for (int i = 0; i < 59; ++i)
	{
		Matrix[0][i] = '+';
		Matrix[33][i] = '+';
	}
	for (int i = 0; i < 34; ++i)
	{
			Matrix[i][0] = '+';
			Matrix[i][58] = '+';
	}

	gotoxy(72, 11);
	cout << "=========";
	gotoxy(72, 12);
	cout << "Score: " << score;
	gotoxy(72, 13);
	cout << "=========";
	gotoxy(0, 0);

	for (int i = 0; i < 34; ++i)
	{
		for (int j = 0; j < 59; ++j)
		{
			cout << Matrix[i][j];
		}
		cout << endl;
	}
	Food(foodCoordX, foodCoordY);

	//////////////////////////////////////////

	int headCoordX = 29;
	int headCoordY = 9;
	int tailCoordX = 29;
	int tailCoordY = 10;

	int xC = 0,
		yC = 1;

	for (int i = 0; i < 3; ++i)
	{
		CoordT[i][0] = tailCoordX;
		CoordT[i][1] = tailCoordY;
		tailCoordX += xC;
		tailCoordY += yC;
	}

	for (int i = 0; i < 3; ++i)				//first snake
	{
		headCoordX += xC;
		headCoordY += yC;
		gotoxy(headCoordX, headCoordY);
		cout << '*';
	}

	
	char M = 's';
	char c;

	//////////////////////////////////////////////////

	while (true)
	{
		xC = 0; yC = 0;

		if (_kbhit())
		{
			c = getch();
			if (c == 'a' || c == 's' || c == 'd' || c == 'w')
			{
				M = c;
			}
		}
		switch (M)
		{
			case 's':
				yC = 1;
				break;
			case 'w':
				yC = -1;
				break;
			case 'a':
				xC = -2;
				break;
			case 'd':
				xC = 2;
				break;
		}

		
		if (l == length)
			l = 0;

		gotoxy(CoordT[l][0], CoordT[l][1]);
		cout << ' ';

		headCoordX += xC;
		headCoordY += yC;
		if (headCoordX < 1 || headCoordX > 57 || headCoordY < 1 || headCoordY > 32) 
			break;


		gotoxy(headCoordX, headCoordY);
		cout << '*';

		CoordT[l][0] = headCoordX;
		CoordT[l][1] = headCoordY;
		l++;

		if (headCoordX == foodCoordX && headCoordY == foodCoordY)
		{
			score++;
			length++;
			Food(foodCoordX, foodCoordY);
			gotoxy(72, 12);
			cout << "Score: " << score;
			if (length > speedGrows)
			{
				speedGrows += 3;
				timeOfPause -= 15;
			}
		}

		Sleep(timeOfPause);
	}

	gotoxy(0, 36);
    return 0;
}

void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE),
		coord
	);
}

void Food(int & foodCoordX, int & foodCoordY)
{
	srand(time(NULL));
	foodCoordX = (rand() % 30 + 1) * 2 - 1;
	foodCoordY = (rand() % 15 + 1) * 2 - 1;
	gotoxy(foodCoordX, foodCoordY);
	cout << 'O';
}
