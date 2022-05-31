//program to define the server main function
#include <iostream>
#include <server.h>
using namespace std;
int main(){
	Server server;				//Object creation
   	server.ToLoadData();		        //calling the function leadDAta of server class
	server.ToCreateSocket();			//calling the function createSocket() of the server class to create the socket
	server.ToBindSocket();			//calling the function bindSocket to bind the socket
	server.ToListen(); 			//calling the function listenTo of the server class 
	server.ToAcceptConnections() ;		//calling the acceptConnection of the server class
}
