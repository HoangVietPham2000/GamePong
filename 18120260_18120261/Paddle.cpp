#include "Paddle.h"

Paddle::Paddle(float x, float y)
{
	this->x = x;
	this->y = y;
}

Paddle::Paddle()
{
	x = 10.0f;
	y = 150.0f;
}

Paddle::~Paddle()
{
	return;
}

void Paddle::drawRect(float x, float y, float width, float height)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

