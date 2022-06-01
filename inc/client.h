//program to hava header file for client class
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
using namespace std;
class Client{

        public:
                Client();					//default constructor
		~Client();					//default destructor

                int ToGetSockfd();				//to get sock id

                string ToGetCredentials();			//to get credentials
                int ToServerConnect( );				//to connect to the server

                int ToSendData(string input);			//to send data to the server

                string ToRecvData();				//to receive data from the server
                string ToGetUserCommands(string type);		//to get user subcommands
                int ToDisplayRecvData(string recvData);		//to display records from the server

                int ToCloseClientConnections();			//to close the client connections


	private:

        	int sockfd;						
        	sockaddr_in servaddr;
       		int portnumber,slen,mlen,connectfd;
        	string ip_address;
};

