//Dealer_Svc_Handler.h

#ifndef _DEALER_SVC_HANDLER_
#define _DEALER_SVC_HANDLER_

#include "ace/Svc_Handler.h"

#include "ace/SOCK_Stream.h"

class Dealer_Svc_Handler : public ACE_Svc_Handler<ACE_SOCK_Stream, ACE_NULL_SYNCH>
{
	
};

#endif
