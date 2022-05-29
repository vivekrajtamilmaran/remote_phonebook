//program to define the server main function
#include <iostream>
#include "../include/server.h"
using namespace std;
int main(){
	Server server;				//Object creation
   	server.loadDAta();		        //calling the function leadDAta of server class
	server.createSocket();			//calling the function createSocket() of the server class to create the socket
	server.bindSocket();			//calling the function bindSocket to bind the socket
	server.listenTo(); 			//calling the function listenTo of the server class 
	server.acceptConnections() ;		//calling the acceptConnection of the server class
}
