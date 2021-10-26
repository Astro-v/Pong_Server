#ifndef __BAR_H__
#define __BAR_H__

#include "SFML/System.hpp"

class Bar
{
public:
	Bar();
	Bar(float const& x,float const& y);
	~Bar();
	float getPos(const int &i) const;
	void setPos(const int &i,const float &pos);
	float getSize();
	void setSize(const float &size);

private:
	sf::Vector2f m_pos;
	float m_size;
};


#endif // __BAR_H__