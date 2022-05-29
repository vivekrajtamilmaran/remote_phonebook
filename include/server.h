//program to have the header file for server class
#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <arpa/inet.h>
#include "../include/user.h"
using namespace std;

class Server{
        int sockfd ;
        sockaddr_in servaddr ;
        sockaddr_in cliaddr ;
        vector <User> users ;
        int slen = 0 ,connectfd = 0, mlen = 0 ;
        pid_t pid ;
        public:
        	Server();
                
		int loadDAta();				//load the data from the file
		int createSocket();			//create the socket
		int bindSocket();			//to bind the socket	
			
		int listenTo(); 			//to listen to the socket 
		void acceptConnections();		//to accept connections
            	string recvData();			//to receive data and commands from client
            	string authenticateUser();		//to authenticate the user

};




