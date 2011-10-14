//Dealer_Acceptor.h

#ifndef _DEALER_ACCEPTOR_
#define _DEALER_ACCEPTOR_

#include <string>
#include "ace/Acceptor.h"
#include "ace/Svc_Handler.h"
#include "ace/SOCK_Acceptor.h"
#include "Dealer_Svc_Handler.h"

class Dealer_Acceptor : public ACE_Acceptor<Dealer_Svc_Handler, ACE_SOCK_Acceptor>
{
public:
	Dealer_Acceptor(){};
	int Bind_To_Port();// called by open()
	int Listen();
	virtual int handle_input(ACE_HANDLE); //reatively called
//	virtual int open(/*parameter*/); //actively called
	//register

private:
	std::string server_name;
	std::string server_address;
	int port;

//	ACE_SOCK_Stream peer;

};

#endif
