#pragma once
#include "Paddle.h"


class Ball
{
public:
	float pos_x = 800 / 2;
	float pos_y = 300 / 2; 
	float dir_x = 1.0f;
	float dir_y = 0.3f;
	int size = 18;
	float speed = 2;

	Ball();
	~Ball();
	
};


