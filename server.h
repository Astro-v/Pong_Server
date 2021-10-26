#ifndef __SERVER_H__
#define __SERVER_H__

#include "SFML/Network.hpp"
#include "constant.h"
#include "ball.h"
#include "bar.h"

class Server
{
public:
	Server();
	void initializeServer();
	int receiveData(ToReceive &data);
	void sendData(const int &i,const ToSend &data);
	
private:
	sf::UdpSocket m_socket;
	sf::Packet m_packetR; // packet to receive
	sf::Packet m_packetS; // packet to send
	unsigned short m_portClient;
	sf::IpAddress m_addressClient; // For the last sender
	unsigned short m_portP1;
	sf::IpAddress m_addressP1; // For the  first player
	unsigned short m_portP2;
	sf::IpAddress m_addressP2; // For the second player

};

sf::Packet& operator <<(sf::Packet& packet, const ToSend& data); // Overload of the packet in order to allow Packet << Message
sf::Packet& operator >>(sf::Packet& packet, ToReceive& data); // Overload of the packet in order to allow Packet >> Message

#endif // __SERVER_H__