//Dealer_Acceptor.cpp

#include "Dealer_Acceptor.h"
#include "Fails.h"
#include "Const.h"
#include <iostream>


int Dealer_Acceptor::handle_input(ACE_HANDLE)
{
	Dealer_Svc_Handler * dsh = new Dealer_Svc_Handler();
	if(acceptor().accept(dsh->peer()) == -1)
		return ERROR_ACCEPTOR_ACCEPT;
	std::cout << "Connection established" << std::endl;
	
	ACE_Reactor::instance()->register_handler(dsh, ACE_Event_Handler::READ_MASK);

	return 0;
}


