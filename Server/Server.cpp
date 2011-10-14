//Server.cpp

#include <iostream>

#include "Dealer.h"
#include "Fails.h"


int main(int argc, char *argv[])
{
	Dealer d;
	int error = 0;

	if((error = d.Init_Dealer(argc, argv)) != 0)
		return d.ErrorHandler(error);

	if ((error = d.Bind_To_Port()) != 0)
		return d.ErrorHandler(error);
	
	if ((error = d.Listen()) != 0)
		return d.ErrorHandler(error);
		
	return 0;
}
