//program to have the header file for server class


#include <iostream>
#include <vector>
#include <algorithm>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <string>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <fstream>
#include <sstream>
#include <user.h>


#define ADDRSERV "127.0.0.1"
#define MAX 256
#define PORT 8028


using namespace std;



class Server{
        

	public:
        	Server();
                
		int ToLoadData();	    										 //load the data from the file

		int ToCreateSocket();											//create the socket
		int ToBindSocket();											//to bind the socket	
		int ToListen(); 											//to listen to the socket 
		
		void ToAcceptConnections();										//to accept connections
            	string ToRecvData();											//to receive data and commands from client
            	string ToAuthenticateUser();										//to authenticate the user
		

		string AuthenticatedUserFunctionalities(string recvdata,string filename,string type);			//to perform authenticated user functionalities
		int AnonymousFunctions(string recvdata,string filename);						//to perform anonymous user functionalities
		int AdminFunction(string recvdata , string filename);							//to perform admin user functionalities
        private:
		int sockfd ;
        	sockaddr_in servaddr ;
        	sockaddr_in cliaddr ;
        	vector <User> users ;
        	int slen = 0 ,connectfd = 0, mlen = 0 ;
        	pid_t pid ;

};




