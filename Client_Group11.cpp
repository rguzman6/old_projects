#include <iostream>
#include <sys/socket.h> // for socket() and bind()
#include <arpa/inet.h>  // for sockaddr_in and inet_ntoa()
#include <cstdlib>     // for atoi() and exit()
#include <cstring>     // for memset()
#include <string>
#include <unistd.h>     // for close()
#include <vector>

#define MAX 255     // Longest string to echo
using namespace std; 

void DieWithError( const char *errorMessage ) // External error handling function
{
    perror(errorMessage);
    exit(1);
}

int main( int argc, char *argv[] )
{
    size_t nread;
    int sock;                        // Socket descriptor
    struct sockaddr_in servAddr; // Echo server address
    struct sockaddr_in fromAddr;     // Source address of echo
    unsigned short recvPort;     // port
    unsigned int fromSize;           // In-out of address size for recvfrom()
    char *servIP;                    // IP address of server
    char *mesg = NULL;         // String to send to echo server
    size_t mesgLen = MAX;               // Length of string to echo
    int respStringLen;               // Length of received response

    mesg = (char *) malloc( MAX );

    if (argc < 3)    // Test for correct number of arguments
    {
        fprintf( stderr, "Usage: %s <Server IP address> <Port> \n", argv[0] );
        exit( 1 );
    }

    servIP = argv[ 1 ];  // First arg: server IP address (dotted decimal)
    recvPort = atoi( argv[2] );  // Second arg: Use given port 

    printf( "client: Arguments passed: server IP %s, port %d\n", servIP, recvPort);

    // Create a datagram/UDP socket
    sock = socket( PF_INET, SOCK_DGRAM, IPPROTO_UDP );

    // Construct the server address structure
    memset( &servAddr, 0, sizeof( servAddr ) ); // Zero out structure
    servAddr.sin_family = AF_INET;                  // Use internet addr family
    servAddr.sin_addr.s_addr = inet_addr( servIP ); // Set server's IP address
    servAddr.sin_port = htons( recvPort );      // Set server's port 
    //DOUBLE CHECK ABOVE LINE


    for(;;) //run forever until get exit command
    {
        printf( "\nEnter command to execute: \n" );
        if( ( nread = getline( &mesg, &mesgLen, stdin ) ) != -1 )
        {
            mesg[ (int) strlen(mesg) - 1 ] = '\0'; // Overwrite newline
            printf( "\nclient: reads string ``%s''\n", mesg );
        }
        else
            DieWithError( "client: error reading string\n" );

	//parse input of user to check when to exit    
	string exit1 = mesg; 
	string delim = " ";
    	vector<string> words{};

    	size_t pos = 0;
    	while ((pos = exit1.find(delim)) != string::npos) 
	{
        	words.push_back(exit1.substr(0, pos));
        	exit1.erase(0, pos + delim.length());
    	}
	words.push_back(exit1);
	    
        // Send the string to the server
        if( sendto( sock, mesg, strlen(mesg), 0, (struct sockaddr *) &servAddr, sizeof( servAddr ) ) != strlen(mesg) )
       		DieWithError( "client: sendto() sent a different number of bytes than expected" );

        // Receive a response
        fromSize = sizeof( fromAddr );

        respStringLen = recvfrom( sock, mesg, MAX, 0, (struct sockaddr *) &fromAddr, &fromSize );
        mesg[ respStringLen ] = '\0';

        if( servAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr )
            DieWithError( "client: Error: received a packet from unknown source.\n" );
	
	//second string to check if can exit    
	string exit2 = mesg; 
	    
	printf( "client: received string ``%s'' from server on IP address %s\n", mesg, inet_ntoa( fromAddr.sin_addr ) );

	//exit if correct values are sent and received    
	if(words[0].compare("exit") == 0 && exit2.compare("SUCCESS!") == 0)
	{
		break; 
	}
    }
    
    close( sock );
    exit( 0 );
}
