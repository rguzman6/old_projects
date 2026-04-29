#include <iostream>
#include <sys/socket.h> // for socket() and bind()
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa()
#include <cstdlib>     // for atoi() and exit()
#include <cstring>     // for memset()
#include <string>
#include <unistd.h>     // for close()
#include <vector>

#define MAX 255		//longest string
using namespace std;

class User {
	public:
		
		string handle; 
		string address; 
		int rightPort; 
		int leftPort; 
		int queryPort;
	
	
	User(string name, string addr, int lport, int rport, int qport)
	{
		handle = name; 
		address = addr; 
		leftPort = lport;
		rightPort = rport; 
		queryPort = qport; 
	}
};

class Followers{
	public:
		string handle; 
		vector<string> f; 
};
