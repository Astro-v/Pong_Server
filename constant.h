
#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include "SFML/Network.hpp"
#include <string>
#include <iostream>

/*---- BAR ----*/
#define SIZE_BARX 8
#define SIZE_BARY 64
#define INIT_BARX1 10
#define INIT_BARY1 (SIZE_MAPY/2-SIZE_BARY/2)
#define INIT_BARX2 (SIZE_MAPX-10-SIZE_BARX)
#define INIT_BARY2 (SIZE_MAPY/2-SIZE_BARY/2)
#define MIN_SIZEBAR 32
#define DELTA_SIZEBAR 32
#define MAX_SIZEBAR 128

/*---- BALL ----*/
#define SIZE_BALL 16
#define INIT_ANGLE 0
#define INIT_SENS 1
#define INIT_SPEED 3
#define INIT_BALLX (SIZE_MAPX/2-SIZE_BALL/2)
#define INIT_BALLY (SIZE_MAPY/2-SIZE_BALL/2)
#define MIN_SPEED 1
#define MAX_SPEED 10
#define MAX_SIZEBALL 64
#define MIN_SIZEBALL 8
#define MAX_ANGLE 60
#define MAX_SCORE 10
#define ACCELERATION 0.5
#define DELTA_ANGLE 30
#define DELTA_SPEED 3

/*---- MAP ----*/
#define SIZE_MAPX 1000
#define SIZE_MAPY 800

/*---- SCORE ----*/
#define SIZE_SCORE 200

/*---- BONUS ----*/
#define SIZE_BONUS 48 // pixel
#define SIZE_BONUSZONEX 10 // 8*48 pixel then
#define SIZE_BONUSZONEY 16 // 16*48
#define SIZE_BONUSZONEYBIS 16 // 16 pixel before and after
#define BONUS_RAW 2
#define BONUS_COLUMN 3
#define MAX_BONUS 6
#define NUMBER_BONUS 9

/*---- TIME ----*/
#define TIME_REFRESH 20
#define TIME_PAUSE 1000
#define TIME_BONUS 10 // second

/*---- MATH ----*/
#define PI 3.14159265

/*---- SERVER ----*/
#define SERVER_PORT 5500
// #define SERVER_ADRESS "90.39.145.229" // IP adress of the server
// #define SERVER_ADRESS sf::IpAddress::getPublicAddress()
// #define SERVER_ADRESS "25.67.69.65" // IP adress of the server
#define SERVER_ADRESS sf::IpAddress::getLocalAddress()

struct ToReceive
{
	float pos; 
	/*
	Here the player send the position of his bar
	*/
};

struct ToSend
{
	float posP1; 
	float posP2;
	float posBallX;
	float posBallY;
	float sizeBarP1;
	float sizeBarP2;
	sf::Uint16 scoreP1;
	sf::Uint16 scoreP2;
	sf::Uint16 winner; // 0: Nobody | 1: Player 1 | 2: Player 2
	sf::Uint16 sound;
	sf::Int16 bonus1Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus1PosX;
	float bonus1PosY;
	sf::Int16 bonus2Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus2PosX;
	float bonus2PosY;
	sf::Int16 bonus3Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus3PosX;
	float bonus3PosY;
	sf::Int16 bonus4Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus4PosX;
	float bonus4PosY;
	sf::Int16 bonus5Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus5PosX;
	float bonus5PosY;
	sf::Int16 bonus6Id; // -1 : No Bonus | 0 : First bonus etc ...
	float bonus6PosX;
	float bonus6PosY;
};

#endif // __CONSTANT_H__