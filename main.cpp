#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <time.h>
using namespace std;
bool gameOver;

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
int randwidth() {
	return (rand() % (width-2)) + 1;
}
int randheight() {
	return (rand() % (height-2)) + 1;
}
void Setup() {
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = randwidth();
	fruitY = randheight();
	score = 0;
}
void Draw() {
	int i,j,k;
	system("cls");
	for (i = 0; i < width; i++) 
		cout << "#";
	cout << endl;

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "#";
			}
			else if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (k = 0; k < nTail; k++) {
					
					if (tailX[k] == j && tailY[k] == i) {
						cout << "o";
						print = true;
					}
					
				}
				if (!print)
					cout << " ";
			}
		}
		cout << endl;
	}
	
	for (i = 0; i < width; i++)
		cout << "#";
	cout << endl;
	cout << "Score :" << score << endl;

	
}
void Input() {
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameOver = true;
			break;
		default:
			break;
		}
	}
}
void Logic() {
	int i;
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	if (x >= width-1 || x<=0 || y>height-1 || y < 0)
		gameOver = true;
	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x&&tailY[y] == y) {
			gameOver = true;
		}
	}
	if (x == fruitX && y == fruitY) {
		score += 10;
		fruitX = randwidth();
		fruitY = randheight();
		nTail++;

	}
}
int main(void) {
	Setup();
	srand(time(NULL));
	while (!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(100);
	}
	
	return 0;
}