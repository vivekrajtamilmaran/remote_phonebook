//program to define the class client
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <limits>
#include <sstream>
#include <string.h>
#include<arpa/inet.h>
#include <termios.h>
#include <signal.h>
#include "../include/client.h"
#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8028

//default constructor and creating a socket
      
Client::Client(){
      slen=sizeof(sockaddr_in);
      memset(&servaddr,0,slen);

      servaddr.sin_family = AF_INET;
      servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
      servaddr.sin_port = htons(PORT);

      sockfd=socket(AF_INET, SOCK_STREAM, 0);											//creating the socket
      if(sockfd < 0){
	      fputs("Socket can't be created ",stderr);
            exit(EXIT_FAILURE);
      }
}
//function to get socket id
int Client::getSockfd(){
	return sockfd ;
 }
//finction to credentials from the User
string Client::getCredentials(){
      string  uName ;
      string password;
      cout << "Enter the Username :" ;
      getline(cin,uName);
      if(uName=="\n"){
      	uName="";
      }
      termios oldt;
      tcgetattr(STDIN_FILENO, &oldt);
      termios newt = oldt;
      newt.c_lflag &= ~ECHO;
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);

      cout  <<"Enter the password :" ;
      getline(cin, password);
      if(password=="\n"){
	      password="";
      }
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      cout << endl ;
      string concat = uName + ":" + password ;
      return concat;
}

//function to connect to the server
int Client::serverConnect( ){
	connectfd=connect(sockfd,(struct sockaddr *)&servaddr,slen);								//connecting to the server
      	if(connectfd < 0){
            	fputs("Socket can't be created ",stderr);
                  exit(EXIT_FAILURE);
            }
            return connectfd;
}
//function to senddata from the client
int Client::sendData(string input){

      send(sockfd,input.c_str(),strlen(input.c_str()),0);
      if(input=="bye"||input=="Bye"){												//checks for bye if bye close client conncetion
      	closeClientConnections();
      }

	return 0 ;

}
// function to receive the data from the server
string Client::recvData(){
	char output[1024] ;
      memset(output,0,1024);
      mlen = recv(sockfd,output,1024,0);
      if(mlen==0){
      	closeClientConnections();
      }
      return string(output);
}

//function to get the subcommands from the user
string Client::getUserCommands(string type){
	while(1){
      	string subcommand("");
            cout << "Enter the subcommand :" ;
            getline(cin, subcommand);
            string copysubcommand="";
            copysubcommand=subcommand;
            if(type=="authenticated user"){											//checks for the authenticated user
            	string command(""),input1(""),input2("");
                  stringstream ss(subcommand);
                  getline(ss,command,' ');
                  getline(ss,input1,',');
                  getline(ss,input2,',');
                  if(command =="ADD"){												//checks for ADD command
                  	if(input1!=""&&input2!=""){
                        	return copysubcommand;
                        }
                        else{
                        	cout << "ADD command should have two fields" << endl ;
                                continue;
                                                }
                        }
                   else if(command =="rm"){											//checks for remove command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                        }
                        else{
                        	cout << "Remove command should have only one field" << endl ;
                                continue;
                        }
                   }
                   else if(command =="list"){											//checks for list command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                        }
                        else{
                        	cout << "List command should have only one field" << endl ;
                                continue;
                        }
                   }
                   else if(command == "chgrp"){											//checks for the chgrp command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                         }
                         else{
                         	cout << "Enter only Groupname" << endl ;
                                continue;
                         }
                   }
                   else if(command =="Bye"||command=="bye"){									//checks for bye command 
                   	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cout << "No inputs with bye/Bye" << endl ;
                         	continue;
                         }
                    }
                    else{
                    	cout << "You can only use ADD,rm,list,chgrp and bye/Bye subcommands" << endl ;
                        continue;
                    }
	      }
            if(type=="admin"){													//checks for the type admin
      	          string command(""),input1(""),input2("") ,input3("");
                  stringstream ss(subcommand);
                  getline(ss,command,' ');
                  getline(ss,input1,',');
                  getline(ss,input2,',');
		  getline(ss,input3,',');
                  if(command =="addgrp"){												//checks for the ADD command
            	      if(input1!="" && input2==""){
                  	      return copysubcommand ;
                         }
                         else{
                        	 cout << "Enter groupname only" << endl ;
                               continue;
                         }
                   }
                   else if(command == "rmgrp"){											//checks for the remove command
                   	if(input1!="" && input2 ==""){
                        	return copysubcommand ;
                        }
                        else{
                        	cout << "Enter groupname only" << endl ;
                                continue;
                        }
                    }
                    else if(command =="ADD"){												//checks for ADD command
                  	if(input1!="" && input2!="" && input3!=""){
                        	return copysubcommand;
                        }
                        else{
                        	cout << "Provide three inputs name,phonenumber,filename " << endl ;
                                continue;
                                                }
                        }

                    else if(command =="Bye"||command=="bye"){									//checks for the bye command
                    	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cout << "No inputs with bye/Bye" << endl ;
                                continue;
                          }
                     }
                     else{
                     	cout << "Incorrect subcommand" << endl ;
                        continue;
                      }
                }
                if(type=="anonymous user"){											//checks for anonymous user
                  string command(""),input1(""),input2("");
                  stringstream ss(subcommand);
                  getline(ss,command,' ');
                  getline(ss,input1,',');
                  getline(ss,input2,',');
                  if(command =="ADD"){												//checks for ADD command
                  	if(input1!=""&&input2!=""){
                        	return copysubcommand ;
                         }
                         else{
                         	cout << "Enter two fields to ADD" << endl ;
                              continue;
                         }
                  }
                  else if(command =="Bye"||command=="bye"){									//checks for bye command
                  	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cout << "No inputs with bye/Bye" << endl ;
                         	continue;
                         }
                   }
                   else{
                   	cout << "Incorrect subcommand" << endl ;
                        continue;
                   }
               }
	}



      cout << endl ;
      return "" ;

}
//function to display data received from server
int Client::displayRecvData(string recvData){
	cout << recvData << endl ;
      	return 0;
 }
//function to close connection from the server
int Client::closeClientConnections(){
      close(sockfd);
      exit(0);
 }


