#pragma once
#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream>
#include <math.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#include "GL/glut.h"
#include <math.h>
#include "console.h"
#pragma comment(lib, "OpenGL32.lib")
#define PI 3.141592
using namespace std;
// keycodes
#define VK_W 0x57
#define VK_S 0x53

class Paddle
{
public:
	float x;
	float y;
	int width = 20;
	int height = 80;
	int speed = 3;
	Paddle(float x, float y);
	Paddle();
	~Paddle();

	void drawRect(float x, float y, float width, float height);
};

void keyboard();
string inttostr(int x);
void drawText(float x, float y, string text);
void updateBall2players();
void updateBall1players();
void updatePaddle1player();

void update2player(int value);
void update1player(int value);

void drawInf();
void drawRectrangle(float x, float y, float width, float height);
void draw_map();
void draw();

void enable2D_Winner(int width, int height);
void enable2D(int width, int height);

void menu(int argc, char** argv);

