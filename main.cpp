#include "pong.h"
#include <iostream>

int main()
{
	std::cout << "------SERVER------" << std::endl;
	std::cout << SERVER_ADRESS << std::endl;
	Pong pong;
	pong.play();
	return 0;
}