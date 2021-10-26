#ifndef __PONG_H__
#define __PONG_H__

// SFML
#include "SFML/System.hpp"

// Self
#include "ball.h"
#include "bar.h"
#include "constant.h"
#include "server.h"
#include "bonus.h"

class Pong
{
public:
	Pong();
	~Pong();
	void play(); /* Main Thread function */
	void wallImpact(const float &dx, const float &dy);
	void barImpact(const float &dx, const float &dy);
	void bonusImpact(const float &dx, const float &dy);
	void reset();

protected:
	void nextStep(); /* Thread function */
	void decreaseSpeed(); /* Thread function */
	void increaseSpeed(); /* Thread function */

private:
	// System
	int m_winner; // 0: Nobody | 1: Player 1 | 2: Player 2
	bool m_proceed;
	int m_scoreP1;
	int m_scoreP2;
	int m_lastPlayer; // 1 if the last player to play is the P1 2 for the P2 and else 0

	// Ball and Bar
	Ball m_ball;
	Bar m_bar1;
	Bar m_bar2;

	// Server
	Server m_server;
	ToReceive m_receive;
	ToSend m_send;

	// Time
	sf::Clock m_clock;
	sf::Time m_time;

	// Thread
	sf::Mutex m_mutex;
	sf::Thread m_thread1; // for the nextStep
	sf::Thread m_thread2; // for the decreaseSpeed
	bool m_use2;
	sf::Thread m_thread3; // for the increaseSpeed
	bool m_use3;

	// Bonus
	Bonus m_bonus;
};

bool insideRectangle(const float &x1,const float &y1,const float &x2,const float &y2,const float &x3,const float &y3);

#endif // __PONG_H__