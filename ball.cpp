#include "SFML/System.hpp"
#include "ball.h"
#include "constant.h"

Ball::Ball():m_pos(0,0),m_angle(0),m_sens(0),m_speed(0),m_size(1)
{}

Ball::Ball(float x,float y,float angle,int sens,float speed,float size):m_pos(x,y),m_angle(angle),m_sens(sens),m_speed(speed),m_size(size)
{}

Ball::~Ball()
{}

float Ball::getAngle() const
{
	return m_angle;
}

int Ball::getSens() const
{
	return m_sens;
}

float Ball::getPos(const int &i) const
{
	if (i == 0)
	{
		return m_pos.x + m_size/2;
	}
	else if (i == 1)
	{
		return m_pos.y + m_size/2;
	}
	else
	{
		return -1;
	}
}

float Ball::getSpeed() const
{
	return m_speed;
}

void Ball::setAngle(const float &angle)
{
	if (-MAX_ANGLE <= angle && angle <= MAX_ANGLE){m_angle = angle;}
	else if (angle < -MAX_ANGLE){m_angle = -MAX_ANGLE;}
	else if (angle > MAX_ANGLE){m_angle = MAX_ANGLE;}
}

void Ball::setSens(const int &sens)
{
	switch (sens)
	{
		case 1:
			m_sens = 1;
			break;
		case -1:
			m_sens = -1;
			break;
		case 0: // stop the ball 
			m_sens = 0;
			break;
		// default: // error
	}
}

void Ball::setPos(const int &i,const float &pos)
{
	switch (i)
	{
		case 0:
			m_pos.x = pos;
			break;
		case 1:
			m_pos.y = pos;
			break;
		// default: // error
	}
}

void Ball::move(const float &x,const float &y)
{
	m_pos += sf::Vector2f(x,y);
}


void Ball::setSpeed(const float &speed)
{
	if (speed >= MAX_SPEED)
	{
		m_speed = MAX_SPEED;
	}
	else if (speed <= MIN_SPEED)
	{
		m_speed = MIN_SPEED;
	}
	else
	{
		m_speed = speed;
	}
}

float Ball::getSize() const
{
	return m_size;
}

void Ball::setSize(const float &size)
{
	if (size >= MAX_SIZEBALL)
	{
		m_size = MAX_SIZEBALL;
	}
	else if (size <= MIN_SIZEBALL)
	{
		m_size = MIN_SIZEBALL;
	}
	else
	{
		m_size = size;
	}
}