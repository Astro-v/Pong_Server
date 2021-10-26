// Sources library
#include <math.h>
#include <time.h>

// SFML
#include "SFML/System.hpp"

// Self
#include "pong.h"
#include "constant.h"
#include "server.h"
#include "bonus.h"

Pong::Pong():m_thread1(&Pong::nextStep,this),m_thread2(&Pong::decreaseSpeed,this),m_thread3(&Pong::increaseSpeed,this),m_bar1(INIT_BARX1,INIT_BARY1),m_bar2(INIT_BARX2,INIT_BARY2),m_ball(INIT_BALLX,INIT_BALLY,INIT_ANGLE,INIT_SENS,INIT_SPEED,SIZE_BALL),m_proceed(true),m_scoreP1(0),m_scoreP2(0),m_winner(0),m_lastPlayer(0)
{
	m_receive = {0};
	m_send = {0,0,0,0,SIZE_BARY,SIZE_BARY,0,0,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0};
	m_time = sf::milliseconds(0);
	srand(time(NULL));
	m_use2 = false;
	m_use3 = false;
}

Pong::~Pong()
{}

void Pong::play()
{
	std::cout << "starting..." << std::endl;
	m_server.initializeServer();
	sf::sleep(sf::milliseconds(TIME_PAUSE));
	m_thread1.launch();
	m_clock.restart();

	// Main loop
	while (m_proceed)
	{	

		// Receive information
		switch (m_server.receiveData(m_receive))
		{
			case 1: // player 1 move
				m_mutex.lock();
				m_bar1.setPos(1,m_receive.pos);
				m_mutex.unlock();
				break;
			case 2: // player 2 move
				m_mutex.lock();
				m_bar2.setPos(1,m_receive.pos);
				m_mutex.unlock();
				break;
			// default: // no data received
		}
	}
}

void Pong::nextStep()
{
	while (m_proceed)
	{	
		m_mutex.lock();
		m_time += m_clock.restart();
		while (m_time.asMilliseconds() >= TIME_REFRESH)
		{
			m_time -= sf::milliseconds(TIME_REFRESH);

			// NEXT STEP
			float dx = (float)m_ball.getSens()*m_ball.getSpeed()*cos(m_ball.getAngle()*PI/180.0);
			float dy = (float)m_ball.getSpeed()*sin(m_ball.getAngle()*PI/180.0);
			
			// CHECK FOR IMPACT
			wallImpact(dx,dy);
			barImpact(dx,dy);
			bonusImpact(dx,dy);

			// UPDATE DATA
			m_ball.move(dx,dy);

			// SENDING DATA
			/* Send to the player 1*/
			// Set data to send
			m_send.posP1 = m_bar1.getPos(1);
			m_send.posP2 = m_bar2.getPos(1);
			m_send.sizeBarP1 = m_bar1.getSize();
			m_send.sizeBarP2 = m_bar2.getSize();
			m_send.posBallX = m_ball.getPos(0) - m_ball.getSize()/2;
			m_send.posBallY = m_ball.getPos(1) - m_ball.getSize()/2;
			m_send.scoreP1 = m_scoreP1;
			m_send.scoreP2 = m_scoreP2;
			m_send.winner = m_winner;
			m_send.bonus1Id =  m_bonus.getType(0);
			m_send.bonus1PosX =  m_bonus.getPos(0,0);
			m_send.bonus1PosY =  m_bonus.getPos(0,1);
			m_send.bonus2Id =  m_bonus.getType(1);
			m_send.bonus2PosX =  m_bonus.getPos(1,0);
			m_send.bonus2PosY =  m_bonus.getPos(1,1);
			m_send.bonus3Id =  m_bonus.getType(2);
			m_send.bonus3PosX =  m_bonus.getPos(2,0);
			m_send.bonus3PosY =  m_bonus.getPos(2,1);
			m_send.bonus4Id =  m_bonus.getType(3);
			m_send.bonus4PosX =  m_bonus.getPos(3,0);
			m_send.bonus4PosY =  m_bonus.getPos(3,1);
			m_send.bonus5Id =  m_bonus.getType(4);
			m_send.bonus5PosX =  m_bonus.getPos(4,0);
			m_send.bonus5PosY =  m_bonus.getPos(4,1);
			m_send.bonus6Id =  m_bonus.getType(5);
			m_send.bonus6PosX =  m_bonus.getPos(5,0);
			m_send.bonus6PosY =  m_bonus.getPos(5,1);

			// Send information
			m_server.sendData(1,m_send);

			/* Send to the player 2*/
			// Set data to send
			m_send.posP1 = m_bar2.getPos(1);
			m_send.posP2 = m_bar1.getPos(1);
			m_send.sizeBarP1 = m_bar2.getSize();
			m_send.sizeBarP2 = m_bar1.getSize();
			m_send.posBallX = SIZE_MAPX-m_ball.getPos(0) - m_ball.getSize()/2;
			m_send.posBallY = m_ball.getPos(1) - m_ball.getSize()/2;
			m_send.scoreP1 = m_scoreP2;
			m_send.scoreP2 = m_scoreP1;
			switch (m_winner)
			{
				case 0:
					m_send.winner = 0;
					break;
				case 1:
					m_send.winner = 2;
					break;
				case 2:
					m_send.winner = 1;
					break;
			}
			m_send.bonus1Id =  m_bonus.getType(0);
			m_send.bonus1PosX =  SIZE_MAPX -SIZE_BONUS - m_bonus.getPos(0,0);
			m_send.bonus1PosY =  m_bonus.getPos(0,1);
			m_send.bonus2Id =  m_bonus.getType(1);
			m_send.bonus2PosX = SIZE_MAPX -SIZE_BONUS -  m_bonus.getPos(1,0);
			m_send.bonus2PosY =  m_bonus.getPos(1,1);
			m_send.bonus3Id =  m_bonus.getType(2);
			m_send.bonus3PosX = SIZE_MAPX -SIZE_BONUS - m_bonus.getPos(2,0);
			m_send.bonus3PosY =  m_bonus.getPos(2,1);
			m_send.bonus4Id =  m_bonus.getType(3);
			m_send.bonus4PosX = SIZE_MAPX -SIZE_BONUS - m_bonus.getPos(3,0);
			m_send.bonus4PosY =  m_bonus.getPos(3,1);
			m_send.bonus5Id =  m_bonus.getType(4);
			m_send.bonus5PosX =  SIZE_MAPX -SIZE_BONUS - m_bonus.getPos(4,0);
			m_send.bonus5PosY =  m_bonus.getPos(4,1);
			m_send.bonus6Id =  m_bonus.getType(5);
			m_send.bonus6PosX =  SIZE_MAPX -SIZE_BONUS - m_bonus.getPos(5,0);
			m_send.bonus6PosY =  m_bonus.getPos(5,1);
			// Send information
			m_server.sendData(2,m_send);

			// Stop the sound
			m_send.sound = 0;
		}
		m_mutex.unlock();

		// pause the thread
		sf::sleep(sf::milliseconds(TIME_REFRESH));
	}
}


void Pong::wallImpact(const float &dx, const float &dy)
{
	// x dirrection
	if (m_ball.getPos(0)+dx <= 0)
	{
		// P2 win the point
		++m_scoreP2;
		if (m_scoreP2 >= MAX_SCORE)
		{
			m_ball.setSens(0);
			m_winner = 2;
		}
		reset();
		m_mutex.unlock();
		sf::sleep(sf::milliseconds(TIME_PAUSE));
		m_mutex.lock();
	}
	else if (m_ball.getPos(0)+dx >= SIZE_MAPX)
	{
		// P1 win the point
		++m_scoreP1;
		if (m_scoreP1 >= MAX_SCORE)
		{
			m_ball.setSens(0);
			m_winner = 1;
		}
		reset();
		m_mutex.unlock();
		sf::sleep(sf::milliseconds(TIME_PAUSE));
		m_mutex.lock();
	}

	// y dirrection
	if (m_ball.getPos(1)+dy <= 0)
	{
		// ball bounce
		m_ball.setAngle(-m_ball.getAngle());
	}
	else if (m_ball.getPos(1)+dy >= SIZE_MAPY)
	{
		// ball bouce
		m_ball.setAngle(-m_ball.getAngle());
	}
}

void Pong::barImpact(const float &dx, const float &dy)
{
	/*
	FOR THE P1
	*/
	if (m_ball.getPos(0)>m_bar1.getPos(0)+SIZE_BARX && m_ball.getPos(0)+dx<=m_bar1.getPos(0)+SIZE_BARX)
	{
		// potential shock
		int y = (dy/dx)*(m_bar1.getPos(0)+SIZE_BARX-m_ball.getPos(0))+m_ball.getPos(1);
		if (y>=m_bar1.getPos(1) && y<=m_bar1.getPos(1)+m_bar1.getSize())
		{
			// Obvious shock
			m_ball.setSens(1);
			m_ball.setSpeed(m_ball.getSpeed()+ACCELERATION);

			// Sound
			m_send.sound = 1;

			// Here we change the angle of the ball
			m_ball.setAngle(m_ball.getAngle()-DELTA_ANGLE*(m_bar1.getPos(1)-y+m_bar1.getSize()/2)/(m_bar1.getSize()/2));

			// The last player is now P1
			m_lastPlayer = 1;

			// New Bonus
			m_bonus.addBonus();
		}
	}

	/*
	FOR THE P2
	*/
	else if (m_ball.getPos(0)<m_bar2.getPos(0) && m_ball.getPos(0)+dx>=m_bar2.getPos(0))
	{
		// potential shock
		int y = (dy/dx)*(m_bar2.getPos(0)-m_ball.getPos(0))+m_ball.getPos(1);
		if (y>=m_bar2.getPos(1) && y<=m_bar2.getPos(1)+m_bar2.getSize())
		{
			// obvious shock
			m_ball.setSens(-1);
			m_ball.setSpeed(m_ball.getSpeed()+ACCELERATION);

			// sound
			m_send.sound = 1;

			// here we change the angle of the ball
			m_ball.setAngle(m_ball.getAngle()-DELTA_ANGLE*(m_bar2.getPos(1)-y+m_bar2.getSize()/2)/(m_bar2.getSize()/2));

			// The last player is now P2
			m_lastPlayer = 2;

			// New Bonus
			m_bonus.addBonus();
		}
	}
}

void Pong::bonusImpact(const float &dx, const float &dy)
{
	for (int i(0);i<MAX_BONUS;++i)
	{
		// We see if the ball hit the Bonus
		for (float z(0);z <= 1; z+=0.1)
		{
			if (m_bonus.isEnable(i) && insideRectangle(m_bonus.getPos(i,0),m_bonus.getPos(i,1),m_bonus.getPos(i,0)+SIZE_BONUS,m_bonus.getPos(i,1)+SIZE_BONUS,m_ball.getPos(0)+z*dx,m_ball.getPos(1)+z*dy))
			{
				// The player hit the Bonus
				/*
				0 : increase ball's speed +3
				1 : decrease ball's speed -3
				2 : increase bar's size +
				3 : decrease bar's size -
				4 : bounce the ball (as a top wall)
				5 : bounce the ball (as a side wall)
				6 : increase both bar's size +
				7 : decrease both bar's size -
				8 : one random
				*/
				int type = m_bonus.getType(i);
				if (type == 8)
				{
					type = rand()%(NUMBER_BONUS-1);
				}
				switch (type)
				{
					case 0:
						if (!m_use3)
						{
							m_use3 = true;
							m_mutex.unlock(); // We call the thread in order to make it work 10sec only
							m_thread3.launch();
							m_mutex.lock();
						}
						break;
					case 1:
						if (!m_use2)
						{
							m_use2 = true;
							m_mutex.unlock();
							m_thread2.launch();
							m_mutex.lock();
						}
						break;
					case 2:
						if (m_lastPlayer == 1)
						{
							m_bar1.setSize(m_bar1.getSize()+DELTA_SIZEBAR);
						}
						else
						{
							m_bar2.setSize(m_bar2.getSize()+DELTA_SIZEBAR);
						}
						break;
					case 3:
						if (m_lastPlayer == 1)
						{
							m_bar2.setSize(m_bar2.getSize()-DELTA_SIZEBAR);
						}
						else
						{
							m_bar1.setSize(m_bar1.getSize()-DELTA_SIZEBAR);
						}
						break;
					case 4:
						m_ball.setAngle(-m_ball.getAngle());
						break;
					case 5:
						m_ball.setSens(-m_ball.getSens());
						break;
					case 6:
						if (m_lastPlayer == 1)
						{
							m_bar1.setSize(m_bar1.getSize()+DELTA_SIZEBAR);
						}
						else
						{
							m_bar2.setSize(m_bar2.getSize()+DELTA_SIZEBAR);
						}
						break;
					case 7:
						if (m_lastPlayer == 1)
						{
							m_bar2.setSize(m_bar2.getSize()-DELTA_SIZEBAR);
						}
						else
						{
							m_bar1.setSize(m_bar1.getSize()-DELTA_SIZEBAR);
						}
						break;
				}
				m_bonus.setEnable(i,false);
			}
		}
	}
}

void Pong::reset()
{
	m_use2 = false;
	m_use3 = false;
	m_thread2.terminate();
	m_thread3.terminate();
	m_lastPlayer = 0;
	m_bar1.setPos(0,INIT_BARX1);
	m_bar1.setPos(1,INIT_BARY1);
	m_bar1.setSize(SIZE_BARY);
	m_bar2.setPos(0,INIT_BARX2);
	m_bar2.setPos(1,INIT_BARY2);
	m_bar2.setSize(SIZE_BARY);
	m_ball.setPos(0,INIT_BALLX);
	m_ball.setPos(1,INIT_BALLY);
	m_ball.setSens(-m_ball.getSens());
	m_ball.setAngle(0);
	m_ball.setSpeed(INIT_SPEED);
	m_bonus.reset();
}

void Pong::decreaseSpeed() /* Thread function */
{
	m_mutex.lock();
	float speed = m_ball.getSpeed();
	m_ball.setSpeed(speed - 3);
	speed = speed-m_ball.getSpeed();
	m_mutex.unlock();
	sf::sleep(sf::seconds(TIME_BONUS));// We wait until the end of the effect
	m_mutex.lock();
	m_ball.setSpeed(m_ball.getSpeed()+speed);
	m_mutex.unlock();
	m_use2 = false;
}

void Pong::increaseSpeed() /* Thread function */
{
	m_mutex.lock();
	float speed = m_ball.getSpeed();
	m_ball.setSpeed(speed + 3);
	speed = m_ball.getSpeed() - speed;
	m_mutex.unlock();
	sf::sleep(sf::seconds(TIME_BONUS));
	m_mutex.lock();
	m_ball.setSpeed(m_ball.getSpeed()-speed);
	m_mutex.unlock();
	m_use3 = false;
}
/*
bool insideLine(const float &x12,const float &y1,const float &y2,const float &x3,const float &y3,const float &r)
{
	if ()
}*/

bool insideRectangle(const float &x1,const float &y1,const float &x2,const float &y2,const float &x3,const float &y3)
{
	if (x3 >= x1 && y3 >= y1 && x3 <= x2 && y3 <= y2)
	{
		return true;
	}
	return false;
}
