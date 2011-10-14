//Server.cpp

#include <iostream>

#include "Dealer.h"
#include "Fails.h"
#include "Dealer_Acceptor.h"

#include "ace/INET_Addr.h"
#include "ace/Reactor.h"

int main(int argc, char *argv[])
{
	// Dealer d;
	// int error = 0;

	// if((error = d.Init_Dealer(argc, argv)) != 0)
	// 	return d.ErrorHandler(error);

	// if ((error = d.Bind_To_Port()) != 0)
	// 	return d.ErrorHandler(error);
	
	// if ((error = d.Listen()) != 0)
	// 	return d.ErrorHandler(error);

	Dealer_Acceptor my_acceptor;
	ACE_INET_Addr server_addr;
	char addr_string[string_length];

	server_addr.get_host_name(addr_string, 200);
	server_addr.set (11111, addr_string);
	if (my_acceptor.open(server_addr) == -1)
		std::cout << "error" << std::endl;

	while(1)
		ACE_Reactor::instance()->handle_events(); 
	
	return 0;
}
