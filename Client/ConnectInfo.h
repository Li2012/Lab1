#ifndef CONNECTINFO_H
#define CONNECTINFO_H

#include "Const.h"
#include <string>
#include <vector>
using namespace std;
class ConnectInfo {

public:
	ConnectInfo() : port(DEFAULT_PORT), address(DEFAULT_ADDR) { }
	ConnectInfo(string pName) : port(DEFAULT_PORT), address(DEFAULT_ADDR), name(pName) { }
	vector<string> games;
	const int getPort() { return port; }
	const string getAddress() { return address; }
	const string getName() { return name; }
	void setAddress(string addr) { address = addr; }
	void setPort(int p) {	if(port > MIN_PORT) port = p; }
	void setName(string inName) { name = inName; }
	bool isInit() { return !name.empty() && !address.empty() && port>MIN_PORT && games.size()>0; }
private:
	int port;
	string address;
	string name;
};

#endif
