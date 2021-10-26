// Source library
#include <iostream>

// SFML
#include "SFML/Network.hpp"

// Self
#include "constant.h"
#include "ball.h"
#include "bar.h"
#include "server.h"

Server::Server()
{
	if (m_socket.bind(SERVER_PORT,SERVER_ADRESS) != sf::Socket::Done)
	{
    	// error...
	}
	m_packetR.clear();
	m_packetS.clear();
}

/*
Wait until the two player connect to the server
*/
void Server::initializeServer() 
{
	std::cout << "waiting for 2 players ..." << std::endl;
	m_socket.setBlocking(true);
	int nbrPlayer(0);
	while (nbrPlayer!=2)
	{
		m_packetR.clear();
		if (m_socket.receive(m_packetR,m_addressClient,m_portClient) == sf::Socket::Done)
		{
			++nbrPlayer;
			if (nbrPlayer == 1)
			{
				m_portP1 = m_portClient;
				m_addressP1 = m_addressClient;
				std::cout << "Player 1 connected" << std::endl;
			}
			else if (nbrPlayer == 2)
			{
				m_portP2 = m_portClient;
				m_addressP2 = m_addressClient;
				std::cout << "Player 2 connected" << std::endl;
			}
		}
		else
		{
			// error ...
		}
		m_packetR.clear();
	}

	m_packetS.clear();
	ToSend data = {0,0,0,0,SIZE_BARY,SIZE_BARY,0,0,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0,-1,0,0};
	m_packetS << data;
	m_socket.send(m_packetS,m_addressP1,m_portP1);
	m_socket.send(m_packetS,m_addressP2,m_portP2);
	m_packetS.clear();

	m_socket.setBlocking(false);
}

/*
Return :
0 : Nothing have been send
1 : P1 have send
2 : P2 have send
*/
int Server::receiveData(ToReceive &data)
{
	m_packetR.clear();
	if (m_socket.receive(m_packetR,m_addressClient,m_portClient) == sf::Socket::Done)
	{
		m_packetR >> data;
		m_packetR.clear();
		if (m_addressClient == m_addressP1 && m_portClient == m_portP1)
		{
			return 1;
		}
		else if (m_addressClient == m_addressP2 && m_portClient == m_portP2)
		{
			return 2;
		}
		else
		{
			// Not the good sender
			return -1;
		}
	}
	else
	{
		return 0; // No data received
	}
}


void Server::sendData(const int &i, const ToSend &data)
{
	m_packetS.clear();
	m_packetS << data;
	switch (i)
	{
		case 1: // send to the player 1
			m_socket.send(m_packetS, m_addressP1, m_portP1);
			break;
		case 2: // send to the player 2
			m_socket.send(m_packetS, m_addressP2, m_portP2);
			break;
		// default: // error
	}
	m_packetS.clear();
}

sf::Packet& operator <<(sf::Packet& packet, const ToSend& data)
{
    return packet << data.posP1 << data.posP2 << data.posBallX << data.posBallY << data.sizeBarP1 << data.sizeBarP2 << data.scoreP1 << data.scoreP2 << data.winner << data.sound << data.bonus1PosX << data.bonus1PosY << data.bonus1Id << data.bonus2PosX << data.bonus2PosY << data.bonus2Id << data.bonus3PosX << data.bonus3PosY << data.bonus3Id<< data.bonus4PosX << data.bonus4PosY << data.bonus4Id << data.bonus5PosX << data.bonus5PosY << data.bonus5Id << data.bonus6PosX << data.bonus6PosY << data.bonus6Id;
}

sf::Packet& operator >>(sf::Packet& packet, ToReceive& data)
{
    return packet >> data.pos;
}