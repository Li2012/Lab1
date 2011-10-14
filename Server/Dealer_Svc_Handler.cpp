// Dealer_Svc_Handler.cpp

#include "Dealer_Svc_Handler.h"

#include <iostream>


int Dealer_Svc_Handler::handle_input(ACE_HANDLE)
{
	//std::cout << "In handle input" << std::endl;
	
	char buffer[50];
	if(this->peer().recv(buffer, sizeof(buffer)) > 0)
	{
		std::cout << buffer << std::endl;
	}
	return 0;
}
