#ifndef __BONUS_H__
#define __BONUS_H__

// Source library
#include <vector>

// SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// 

class Bonus
{
public:
	Bonus();
	~Bonus();
	void addBonus();
	void setPos(const int &i,const sf::Vector2f &pos);
	float getPos(const int &i,const int &j);
	void setEnable(const int &i,const bool &enable);
	bool isEnable(const int &i) const;
	bool posEnable(const sf::Vector2f &pos) const;
	int getType(const int &i);
	int getAble();
	void reset();

private:
	std::vector<sf::Vector2f> m_pos;
	std::vector<bool> m_enable;
	std::vector<int> m_player; // -1 : nobody have the Bonus | 0 : everybody have it ...
	std::vector<int> m_bonusType;
	/*
	0 : increase ball's speed +3
	1 : decrease ball's speed -3
	2 : increase bar's size *2 
	3 : decrease bar's size /2
	4 : bounce the ball (as a top wall)
	5 : bounce the ball (as a side wall)
	*/
};


#endif // __BONUS_H__