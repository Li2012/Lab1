//Dealer_Acceptor.h

#ifndef _DEALER_ACCEPTOR_
#define _DEALER_ACCEPTOR_

#include "ace/Acceptor.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "Dealer_Svc_Handler.h"

class Dealer_Acceptor : public ACE_Acceptor<Dealer_Svc_Handler, ACE_SOCK_Acceptor>
{
public:
private:
	std::string server_name;
	std::string server_address;
	ACE_SOCK_Acceptor acceptor;
	int port;
};

#endif
