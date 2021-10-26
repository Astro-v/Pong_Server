#include "SFML/System.hpp"
#include "bar.h"
#include "constant.h"

Bar::Bar():m_pos(0,0),m_size(SIZE_BARY)
{}

Bar::Bar(float const& x,float const& y):m_pos(x,y),m_size(SIZE_BARY)
{}

Bar::~Bar()
{}

float Bar::getPos(const int &i) const
{
	if (i == 0)
	{
		return m_pos.x;
	}
	else if (i == 1)
	{
		return m_pos.y;
	}
	else
	{
		return -1;
	}
}

void Bar::setPos(const int &i,const float &pos)
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

float Bar::getSize()
{
	return m_size;
}

void Bar::setSize(const float &size)
{
	if (size >= MAX_SIZEBAR)
	{
		m_size = MAX_SIZEBAR;
	}
	else if (size <= MIN_SIZEBAR)
	{
		m_size = MIN_SIZEBAR;
	}
	else
	{
		m_size = size;
	}
	
}