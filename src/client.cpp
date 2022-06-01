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
#include <client.h>


#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8028

//default constructor and creating a socket
      
Client::Client(){
	connectfd = 0;
	mlen = 0 ;
	portnumber =0 ;
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
int Client::ToGetSockfd(){
	return sockfd ;
 }


//finction to credentials from the User
string Client::ToGetCredentials(){
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
int Client::ToServerConnect( ){
	connectfd=connect(sockfd,(struct sockaddr *)&servaddr,slen);								//connecting to the server
      	if(connectfd < 0){
            	perror("Socket can't be created ");
                exit(EXIT_FAILURE);
            }
            return connectfd;
}


//function to senddata from the client
int Client::ToSendData(string input){

      send(sockfd,input.c_str(),strlen(input.c_str()),0);
      if(input=="bye"||input=="Bye"){												//checks for bye if bye close client conncetion
      	ToCloseClientConnections();
      }

	return 0 ;

}



// function to receive the data from the server
string Client::ToRecvData(){
	char output[1024] ;
      memset(output,0,1024);
      mlen = recv(sockfd,output,1024,0);
      if(mlen==0){
      	ToCloseClientConnections();
      }
      return string(output);
}



//function to get the subcommands from the user
string Client::ToGetUserCommands(string type){
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
                        	cerr << "ADD command should have two fields" << endl ;
                                continue;
                                                }
                        }
                   else if(command =="rm"){											//checks for remove command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                        }
                        else{
                        	cerr << "Remove command should have only one field" << endl ;
                                continue;
                        }
                   }
                   else if(command =="list"){											//checks for list command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                        }
                        else{
                        	cerr << "List command should have only one field" << endl ;
                                continue;
                        }
                   }
                   else if(command == "chgrp"){											//checks for the chgrp command
                   	if(input1!="" && input2 == ""){
                        	return copysubcommand ;
                         }
                         else{
                         	cerr << "Enter only Groupname" << endl ;
                                continue;
                         }
                   }
                   else if(command =="Bye"||command=="bye"){									//checks for bye command 
                   	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cerr << "No inputs with bye/Bye" << endl ;
                         	continue;
                         }
                    }
                    else{
                    	cerr << "You can only use ADD,rm,list,chgrp and bye/Bye subcommands" << endl ;
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
                  if(command =="addgrp"){											//checks for the ADD command
            	      if(input1!="" && input2==""){
                  	      return copysubcommand ;
                         }
                         else{
                               cerr << "Enter groupname only" << endl ;
                               continue;
                         }
                   }
                   else if(command == "rmgrp"){											//checks for the remove command
                   	if(input1!="" && input2 ==""){
                        	return copysubcommand ;
                        }
                        else{
                        	cerr << "Enter groupname only" << endl ;
                                continue;
                        }
                    }
                    else if(command =="ADD"){											//checks for ADD command
                  	if(input1!="" && input2!="" && input3!=""){
                        	return copysubcommand;
                        }
                        else{
                        	cerr << "Provide three inputs name,phonenumber,filename " << endl ;
                                continue;
                                                }
                        }

                    else if(command =="Bye"||command=="bye"){									//checks for the bye command
                    	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cerr << "No inputs with bye/Bye" << endl ;
                                continue;
                          }
                     }
                     else{
                     	cerr << "Enter addgrp , rmgrp or ADD  subcommand only" << endl ;
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
                              cerr << "User should provide two fields to ADD" << endl ;
                              continue;
                         }
                  }
                  else if(command =="Bye"||command=="bye"){									//checks for bye command
                  	if(input1==""&&input2==""){
                        	return copysubcommand ;
                         }
                         else{
                         	cerr << "No inputs with bye/Bye" << endl ;
                         	continue;
                         }
                   }
                   else{
                   	cerr << "User should provide only ADD subcommand" << endl ;
                        continue;
                   }
               }
	}



      cout << endl ;
      return "" ;

}



//function to display data received from server
int Client::ToDisplayRecvData(string recvData){
	cout << recvData << endl ;
      	return 0;
 }



//function to close connection from the server
int Client::ToCloseClientConnections(){
      close(sockfd);
      exit(0);
 }

//destructor

Client::~Client(){
};

