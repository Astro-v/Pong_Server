// Source library
#include <math.h>
#include <vector>
#include <time.h>

// SFML
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

// Self
#include "bonus.h"
#include "constant.h"

Bonus::Bonus()
{
	srand(time(NULL));
	for (int i(0);i<MAX_BONUS;++i)
	{
		m_bonusType.push_back(-1);
		m_pos.push_back(sf::Vector2f());
		m_player.push_back(-1);
		m_enable.push_back(false);
	}
}

Bonus::~Bonus()
{}

void Bonus::addBonus()
{
	int i = getAble();
	if (i != -1)
	{
		m_bonusType[i] = (rand()%NUMBER_BONUS);
		sf::Vector2f pos;
		do
		{
			pos = sf::Vector2f(SIZE_MAPX/2-SIZE_BONUSZONEX*SIZE_BONUS/2+(rand()%SIZE_BONUSZONEX)*SIZE_BONUS,SIZE_BONUSZONEYBIS+(rand()%SIZE_BONUSZONEY)*SIZE_BONUS);
		}while(!posEnable(pos));
		m_pos[i] = pos;
		m_enable[i] = true;
	}
}

int Bonus::getAble()
{
	for (int i(0);i<MAX_BONUS;++i)
	{
		if (!m_enable[i])
		{
			return i;
		}
	}
	return -1;
}

void Bonus::setPos(const int &i,const sf::Vector2f &pos)
{
	if (i>= 0 && i < MAX_BONUS)
	{
		m_pos[i]=pos;
	}
}

float Bonus::getPos(const int &i,const int &j)
{
	if (i>= 0 && i < MAX_BONUS)
	{
		if (j==0)
		{
			return m_pos[i].x;
		}
		else if (j==1)
		{
			return m_pos[i].y;
		}
		else
		{
			// error
			return 0;
		}
	}
	// error
	return 0;
}


void Bonus::setEnable(const int &i,const bool &enable)
{
	if (i>= 0 && i < MAX_BONUS)
	{
		if (!enable)
		{
			m_bonusType[i] = -1;
		}
		m_enable[i]=enable;
	}
}

bool Bonus::isEnable(const int &i) const
{
	if (i>= 0 && i < MAX_BONUS)
	{
		return m_enable[i];
	}
	else
	{
		// error
		return false;
	}
}

bool Bonus::posEnable(const sf::Vector2f &pos) const 
{
	for (int i(0);i<= MAX_BONUS;++i)
	{
		if (pos == m_pos[i])
		{
			return false;
		}
	}
	return true;
}

int Bonus::getType(const int &i)
{
	if (i>= 0 && i < MAX_BONUS)
	{
		return m_bonusType[i];
	}
	else
	{
		// error
		return 0;
	}
}

void Bonus::reset()
{
	for (int i(0);i<MAX_BONUS;++i)
	{
		setEnable(i,false);
	}
}