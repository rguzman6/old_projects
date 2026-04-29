#include <iostream>
#include <sys/socket.h> // for socket() and bind()
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa()
#include <cstdlib>     // for atoi() and exit()
#include <cstring>     // for memset()
#include <string>
#include <unistd.h>     // for close()
#include <vector>
#include <algorithm>
#include "Comparator.h"

#define MAX 255		//longest string
using namespace std;

bool comparator(User* a, User* b) {
	    return (a->handle < b->handle);
    }

int main( int argc, char *argv[] )
{
	int sock;                        // Socket
   	struct sockaddr_in servAddr; // Local address of server
    	struct sockaddr_in clntAddr; // Client address
    	unsigned int cliAddrLen;         // Length of incoming message
    	char buff[ MAX ];      // Buffer for string
    	unsigned short servPort;     // Server port
    	int recvMsgSize;                 // Size of received message
	vector<User*> clientList;	//list of all registered users
	vector<Followers*> followList; //list of who follows who

	if( argc != 2 )         // Test for correct number of parameters
    	{
        	fprintf( stderr, "Usage:  %s <UDP SERVER PORT>\n", argv[ 0 ] );
        	exit( 1 );
    	}

  	servPort = atoi(argv[1]);  // First arg: local port
    
   	//check to make sure port is in a valid range - exit if not
    	if(servPort < 6000 || servPort > 6499)
    	{
    		printf("\nERROR: Port must be in the range of 6000-6499, inclusive.");
		exit(2);
    	}

    	// Create socket for sending/receiving datagrams
    	sock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP );
    
    	// Construct local address structure */
    	memset( &servAddr, 0, sizeof( servAddr ) ); // Zero out structure
    	servAddr.sin_family = AF_INET;                  // Internet address family
    	servAddr.sin_addr.s_addr = htonl( INADDR_ANY ); // Any incoming interface
    	servAddr.sin_port = htons( servPort );      // Local port

    	// Bind to the local address
    	bind( sock, (struct sockaddr *) &servAddr, sizeof(servAddr));

    	printf( "server: Port server is listening to is: %d\n", servPort );

    	for(;;) // Run forever
    	{
       		cliAddrLen = sizeof( clntAddr );
       		recvMsgSize = recvfrom( sock, buff, MAX, 0, (struct sockaddr *) &clntAddr, &cliAddrLen );
		buff[ recvMsgSize ] = '\0';

		//fail-safe acknowledgment
		string ack = "FAILURE: Invalid command";
		
       		printf( "server: received string ``%s'' from client on IP address %s\n", buff, inet_ntoa( clntAddr.sin_addr ) );

		//parse the input
		string msg = buff; 
		string delim = " ";
    		vector<string> words{};

    		size_t pos = 0;
    		while ((pos = msg.find(delim)) != string::npos) 
		{
        		words.push_back(msg.substr(0, pos));
        		msg.erase(0, pos + delim.length());
    		}
	    	words.push_back(msg);
	
		//REGISTER COMMAND
		//make sure that there is the correct number of arguments for register command and check that user is wanting register command
		//register @handle IPAddress Port1 Port2 Port3
		if(words.size() == 6 && words[0].compare("register")==0)
		{
			//create new client
			User* newClient = new User(words[1], words[2], stoi(words[3]), stoi(words[4]), stoi(words[5]));
			
			//no clients yet registered
			if(clientList.empty())
			{
				clientList.push_back(newClient);
				ack = "SUCCESS!";
			}
			//have registered clients
			else
			{
				int vecindex = -1;
				//search clientList for newClient->handle
				for (int i = 0; i < clientList.size(); i++) {
					if (clientList[i]->handle == newClient->handle) {
						vecindex = i;
						break;
					}
				}
				//if client already exists
				if (vecindex > -1) {
					ack = "FAILURE: Username already registered.";
				}
				//client does not exist yet
				else
				{
					clientList.push_back(newClient);
					ack = "SUCCESS!";
				}
			}
		}
		//END OF REGISTER
					  

		//QUERY COMMAND
		//make sure to get full query command
		//query handles
		else if(words.size() == 2 && words[0].compare("query")==0 && words[1].compare("handles")==0)
		{
			//empty client list
			if(clientList.empty())
			{
				ack = "0";
			}
			//there are clients registered
			else
			{
				//sort the list
				//Comparator* comp = new Comparator();
				std::sort(clientList.begin(), clientList.end(), comparator);
				string numClients = to_string(clientList.size());
				ack = numClients;
				for(User* c: clientList)
				{
					ack += "\n";
					ack += c->handle;
				}
			}
		}
		//END QUERY
		
		//FOLLOW COMMAND
		//follow @follower @tofollow
		else if(words.size()==3 && words[0].compare("follow")==0)
		{
			//no followers have been established yet
			if(followList.empty())
			{
				Followers* newf = new Followers();
				newf->handle = words[2];
				newf->f.push_back(words[1]);
				followList.push_back(newf); 
				ack = "SUCCESS!";
			}
			//there already exists followers
			else
			{
				int vecindex = -1;
				// search followList to see if the person already has followers
				for (int i = 0; i < followList.size(); i++) {
					if (followList[i]->handle == words[2]) {
						vecindex = i;
						break;
					}
				}

				if (vecindex > -1) {	//if person has followers, search their followers to see if the user is already following
					bool found = false;
					for (int j = 0; j < followList[vecindex]->f.size(); j++) {
						if (followList[vecindex]->f[j] == words[1]) {
							found = true;
							break;
						}
					}
					if (found) {	// if they are already following 
						ack = "FAILURE: User " + words[1] + " already follows " + words[2];
					} else {	// add follower to list
						followList[vecindex]->f.push_back(words[1]);
						ack = "SUCCESS!"; 
					}

				} else {	//this person has not been followed by anyone yet
					Followers* newf = new Followers();
					newf->handle = words[2];
					newf->f.push_back(words[1]);
					followList.push_back(newf);
					ack = "SUCCESS!";
				}
				   
			}
		}
		//END FOLLOW
		
		//DROP COMMAND
		//drop @handle1 @handle2
		//words index -- 0: command to drop; 1: handle that wants to drop; 2: handle that will lose a follower
		else if(words.size()==3 && words[0].compare("drop")==0)
		{
			if(followList.empty())	// if the followList is empty then there are no follow relationships
			{
				ack = "FAILURE: no one is following anyone.";
			}
			else
			{
				// remove words[1] from words[2]
				int foundCount = 0; 
				int index = -1;
				// search words[2] inside followList
				for (int i = 0; i < followList.size(); i++) {
					if (followList[i]->handle == words[2]) {
						index = i;
						break;
					}
				}
				if (index > -1) {	//if words[2] was found, that means it has followers
					bool found = false;
					for (int j = 0; j < followList[index]->f.size(); j++) {	//searching words[2] follower list for words[1]
						if (followList[index]->f[j] == words[1]) {
							found = true;
							break;
						}
					}
					if (found) {	// if words[1] was found
						ack = "SUCCESS!";
					} else {	// if words[1] was not found then they are not following words[2]
						ack = "FAILURE: " + words[1] + " is not following " + words[2];
					}
				}
				else {// words[2] was not found, it has no followers
					ack = "FAILURE: User " + words[2] + "does not have followers"; 
				} 
			}
		}
		//END DROP
		
		//EXIT
		//exit @handle
		else if(words.size()==2 && words[0].compare("exit")==0)
		{
			vector<User*>::iterator it;
			it = clientList.begin();
			for (int i = 0; i < clientList.size(); i++) {
				if (clientList[i]->handle == words[1]) {
					clientList.erase(it);
					break;
				}
				it++;
			}	
			ack = "SUCCESS!"; 
		}
		//END EXIT
		
		char endAck[ack.length()+1];
		strcpy(endAck, ack.c_str());
        	// Send received datagram back to the client
        	sendto( sock, endAck, strlen(endAck), 0, (struct sockaddr *) &clntAddr, sizeof( clntAddr ) );
    	}
    // NOT REACHED */
}
          
