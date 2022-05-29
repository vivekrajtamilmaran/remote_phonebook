//program to hava header file for client class
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
using namespace std;
class Client{
        int sockfd;						
        sockaddr_in servaddr;
        int portnumber,slen,mlen,connectfd;
        string ip_address;

        public:
                Client();					//default constructor

                int getSockfd();				//to get sock id

                string getCredentials();			//to get credentials
                int serverConnect( );				//to connect to the server

                int sendData(string input);			//to send data to the server

                string recvData();				//to receive data from the server
                string getUserCommands(string type);		//to get user subcommands
                int displayRecvData(string recvData);		//to display records from the server

                int closeClientConnections();			//to close the client connections
};

