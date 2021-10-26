#ifndef __BALL_H__
#define __BALL_H__

#include "SFML/System.hpp"

class Ball
{
public:
	Ball();
	Ball(float x,float y,float angle,int sens,float speed,float size);
	~Ball();
	float getAngle() const;
	int getSens() const;
	float getPos(const int &i) const;
	float getSpeed() const;
	float getSize() const;
	void setAngle(const float &angle);
	void setSens(const int &sens);
	void setPos(const int &i,const float &pos);
	void move(const float &x,const float &y);
	void setSpeed(const float &speed);
	void setSize(const float &size);


private:
	sf::Vector2f m_pos;
	float m_angle;
	float m_speed;
	int m_sens;
	float m_size;
};

#endif // __BALL_H__