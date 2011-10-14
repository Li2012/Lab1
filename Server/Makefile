# 		libraries used on Linux
LIBS    =       -lACE  -ldl

#               Any define flags that should be set for conditional compilation
#DEFFLAGS  = -DUNIX -D_REENTRANT

#               Any -I directories with .h files that should be included
INCFLAGS  =     -I/home/cec/class/cse532/ACE_wrappers

#               Any -L directories in which there are .so files that should
#               be linked
LIBLOCFLAGS     = -L/home/cec/class/cse532/ACE_wrappers/ace -L./

#               Any general flags that should be set for the compiler
#               NOTE: to optimize fully, change -g to -O4
CXXFLAGS  =     -Wall -W -g $(SPECIAL_FLAGS) $(INCFLAGS)

#               The concatenation of all the flags that the compiler should get
CCFLAGS = $(DEFFLAGS) $(LIBLOCFLAGS) $(SUNFLAGS) $(CXXFLAGS)

Server: Server.cpp Dealer.o Connected_Player.o Game.o Dealer_Svc_Handler.o Dealer_Acceptor.o
	g++ -o Server Server.cpp Dealer.o Connected_Player.o Game.o Dealer_Svc_Handler.o Dealer_Acceptor.o $(CCFLAGS) $(LIBS)

Dealer.o: Dealer.h Dealer.cpp Game.o
	g++ -c Dealer.cpp $(CCFLAGS) $(LIBS)

Connected_Player.o: Connected_Player.h Connected_Player.cpp
	g++ -c Connected_Player.cpp $(CCFLAGS) $(LIBS)

Game.o:	Game.h Game.cpp
	g++ -c Game.cpp 

Dealer_Svc_Handler.o: Dealer_Svc_Handler.h Dealer_Svc_Handler.cpp
	g++ -c Dealer_Svc_Handler.cpp  $(CCFLAGS) $(LIBS)

Dealer_Acceptor.o: Dealer_Acceptor.cpp Dealer_Acceptor.h
	g++ -c Dealer_Acceptor.cpp $(CCFLAGS) $(LIBS)

clean: 
	rm Server *.o

