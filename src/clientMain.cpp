//program to define the server main function
#include <iostream>
#include <signal.h>
#include "../include/client.h"
int sockid ;

using namespace std;
void signalHandler(int signal){
        if(signal==SIGINT){
                send(sockid,"bye",3,0);
                exit(0);
        }
}

//main function to execute client class

int main () {
        signal(SIGINT,signalHandler);						//signal to cut the client from server
        string recvdata,credentials , commands;
        Client client;								//creating a object of client
        sockid=client.getSockfd();						//calling the getsockfd of client class
        credentials=client.getCredentials() ;					//calling the getcredentials functions of client class
        client.serverConnect() ;						//calling the serverconnect function to connect to the server
        client.sendData(credentials);						//sending the credentials to server 
        recvdata=client.recvData();						//receiving the message from the server using recvData function
        string type =recvdata ;							
        client.displayRecvData(recvdata) ;					//calling the funtion to display the data
        while(1){
                commands = "";
                commands=client.getUserCommands(type) ;				//calling the function to get the usercommands
                if( commands != ""){
               	 client.sendData(commands);					//sending the user commands to the server
               
                   recvdata = client.recvData();				//receiving the data from the server
                   client.displayRecvData(recvdata);				//displaying the received data from the server

                }
                else{
                        cout << "Subcommand can't be Null" << endl;
                        continue;
                }

        }
        return 0;
}

