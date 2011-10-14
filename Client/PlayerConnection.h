#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H

#include <ace/ACE.h>
#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>
#include <ace/Connector.h>
#include <ace/Reactor.h>

#include "Player_Svc_Handler.h"

class PlayerConnection : public ACE_Connector<Player_Svc_Handler, ACE_SOCK_Connector>
{
public:
	Player() : serverCount(0) {}
	int open( int connectionCount, ACE_Reactor * reactor = ACE_Reactor::instance(), int flag = 0 );
	const int getServerCount() { return serverCount; }
	void removeServer();
	typedef ACE_Connector<Player_Svc_Handler, ACE_SOCK_Connector> connectorBase;	

private:
	int serverCount;
};

#endif