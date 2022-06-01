/*  program to define the class server   */


#include <server.h>
#include <vector>

Server::Server(){
	sockfd = 0 ;
};




//loading the file containing username,password and group informations to the vector

int Server::ToLoadData(){
            fstream inputfile;
            string line;
            inputfile.open("/home/cguser11/phonebook_management/db/authentication.txt");
         
	   try{
	    	if(inputfile.is_open()){                                                                                //checking whether the file is opened
            	    while(getline(inputfile,line)){
            	        stringstream ss(line);
                        string username;
                        string password;
                        string group;
                        vector<string> groups;
                        getline(ss,username,':');
                        getline(ss,password,':');


                        while(getline(ss,group,':')){
                                groups.push_back(group);                                                                //pushing the group information into a vector
                        }


                        if(username!="" && password != "" ){
                                users.push_back(User(username,password,groups));                                        //pushing the object into the user vector
                        }
                      }
              inputfile.close();                                                                                        //closing the file
            	}	
	    	else{
	    		throw string("authentication.txt doesn't exist");
            	}

	    }
	    catch(string msg){
	    	cerr << "File : " << msg << endl;
	    }
	    	
            return 0;

}





//function to create socket 

int Server::ToCreateSocket(){
            slen=sizeof(sockaddr_in);
            memset(&servaddr,0,slen);
            memset(&cliaddr,0,slen);

            servaddr.sin_family = AF_INET; //To use Internet addressing family
            servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
            servaddr.sin_port = htons(PORT);


            sockfd=socket(AF_INET, SOCK_STREAM, 0);                                                                     //creating the socket
            if(sockfd < 0){
              perror("Socket creation has not been done");
            }
            return 0;
}



//function to bind the socket
int Server::ToBindSocket(){
            int ret;
            ret=bind(sockfd, (struct sockaddr *)&servaddr, slen);                                                       //binding the socket
            if(ret < 0){
                    perror("Binding has not been done");
             }
             return 0;
}



//function to call listening to the port 8028
int Server::ToListen(){
            int ret;
            ret=listen(sockfd, 5);                                                                                      //listening to the port 8028
            if(ret< 0){
                    perror("Socket is not Listening");
            }
            return 0;
}



//function to acceptconncetion and and concurrency by using child process
void Server::ToAcceptConnections(){

	while(1){
      	connectfd=accept(sockfd,(struct sockaddr*)&servaddr,(socklen_t *)&slen);
            if(connectfd < 0){
            	perror("Conncetion is not established");
            }
            pid = fork();                                                                                               //creating the child process
            
	    if (pid == 0){
            	  string filename = "" ;
                  string type =ToAuthenticateUser();                                                                	//calling the authenticate function to check the username is authentic user
                  string type1 ;
                  
		  if(type != "admin" && type != ""){
                  	type1 = "authenticated user" ;
                  }
                  else if(type ==""){
                  	type1 ="anonymous user" ;
                  }
                  else if(type == "admin"){
                  	type1="admin";
                  }
                  mlen=send(connectfd,type1.c_str(),strlen(type1.c_str()),0);                             		//sending the type of user to the client
                  

			while(1){
                  		string recvdata = ToRecvData();                                                   	//calling the function to receive data
                        	if(type1=="authenticated user"){							//checking the user is authenticated
                        		filename=AuthenticatedUserFunctionalities(recvdata,filename,type);		//calling the funtion to perform authenticated user functionalities
                        	}
                        	if(type1=="anonymous user"){                                                            //checking whether the user id anonymous
                        		filename=AnonymousFunctions(recvdata,filename);					//calling the function to perform anonymous user functionalities
                        	}
                        	if(type1=="admin"){									//checking whether the user is admin
					filename=AdminFunction(recvdata,filename);					//calling the function to perform admin functionalities
                        	                        
                        	}
	
	
        	    	}
       		}
            signal(SIGCHLD,SIG_IGN);                                                                                	//signal to avoid Zombie process
	    close(connectfd);

       	}	
}




//function to do authententicated user functionalities
string Server::AuthenticatedUserFunctionalities(string recvdata,string filename ,string type){
      string command ,input1 ,input2;
      stringstream ss(recvdata);
      getline(ss,command,' ');
      
		if(command == "ADD"){                                       						//checking if the command is ADD
	   		getline(ss,input1,',');
            		getline(ss,input2,',');
            		User user;
            		string msg = user.ToAddData(input1,input2,filename);						//calling the adddata function of user class
            		if(msg!= "no"){
            		      char positive[]="Contact added" ;
            		      send(connectfd,positive,strlen(positive),0);     						//sending the message to the client
			      return filename;
           	 	}
            		else{
           		      char negative[]="The user can't add the data to the public group";
            		      send(connectfd,negative,strlen(negative),0);
            		}
            	 }
            	 else if(command == "chgrp"){                                                      			//checking if the command is chgrp
            	 	ss >> input1 ;
            	      for(auto user :users){
            		      	if(user.ToFindUser(type)){                        					//calling the find user function using vector of User object
       			            	filename=user.ToChgrp(input1);            					//calling the change group functionof user class
         		                break;
            	            	}
            	       }
            	       if(filename =="no"){
            	            char neg[]="The user doesnt belong to the group";
            	            send(connectfd,neg,strlen(neg),0);
                        }
                  	else{
                  		char pos[]="Group changed" ;
                        	send(connectfd,pos,strlen(pos),0);
				return filename ;
                  	 }
             	}
             	else if(command == "list"){                                                     			//checking if the command is list
	           ss >> input1 ;
                   User user ;
                   vector<string> contacts;
                   contacts = user.ToListData(input1,filename);								//calling the list data function to get the list into a vector
                   string concatContact = "";
                   if(!contacts.empty()){
      	             for(auto contact : contacts ){
	                         concatContact += contact ;								//the contacts are concatenated 
                         }
                   	 send(connectfd,concatContact.c_str(),concatContact.size(),0);
			 return filename;
                   }
                   else{
      	             char buffer[]="File is empty ";
                         send(connectfd,buffer,strlen(buffer),0);
                   }
            }
            else if(command == "rm"){                                   				                //checking if the command is remove
	          ss >> input1;
                  string msg = "" ;
                  User user;
                  msg = user.ToRemoveContact(input1,filename);                              				//calling the user function to remove the contact
                  if(msg=="yes"){
      	            char posi[] = "Contact removed " ;
            	      send(connectfd,posi,strlen(posi),0);
		      return filename ;
                  }
                  else{
                  	char nega[]="Entered user is not present";
                        send(connectfd,nega,strlen(nega),0);
                  }
           }
		return "";
}





//function to implement admin functionalities

int Server::AnonymousFunctions(string recvdata ,string filename){
      string command ,input1 ,input2;
      stringstream ss(recvdata);
      getline(ss,command,' ');
      if(command == "ADD"){                                                           					//checking if the command is ADD
   	   filename="public group";
         getline(ss,input1,',');
         getline(ss,input2,',');
         User user;
         string msg=user.ToAddData(input1,input2,filename);
         if(msg == "yes"){
      	   char positive[]="Contact added" ;
               send(connectfd,positive,strlen(positive),0);
         }
         else{
         	char negative[]="Contact is not added" ;
            send(connectfd,negative,strlen(negative),0);
         }
     }
	return 0;
}




//function to implement admin Function

int Server::AdminFunction(string recvdata,string filename){
      string command ,input1 ,input2 ,input3;
      stringstream ss(recvdata) ;
      getline(ss,command ,' ');
      if(command == "addgrp"){
      	ss >> input1;
            filename = input1 ;
            User user ;
            int msg = user.ToAddGrp(filename);									//calling the user class function addGrp to add the group 
            if(msg){
             	char positive []= "Group added " ;
                  send(connectfd,positive,strlen(positive),0);
            }
            else{
            	char negative[]="Error while adding the group " ;
            	send(connectfd,negative,strlen(negative),0);
            }
      }
      else if(command == "rmgrp"){
      	ss >> input1;
      	filename = input1 ;
      	User user ;
      	int msg = user.ToRemoveGrp(filename);									//calling the function remove group to remove the group
      	
	if(msg){
      		char positive []= "Group removed " ;
      	      send(connectfd,positive,strlen(positive),0);
      	}
      	else{
      		char negative[]="Error while removing the group " ;
      	      send(connectfd,negative,strlen(negative),0);
      	}
      }
      

      else if(command == "ADD"){
      	getline(ss,input1,',');
            getline(ss,input2,',');
            getline(ss,input3,',');
            filename = input3 ;
            User user ;
            string pos = user.ToAdminAddData(input1,input2,filename);
            if(pos=="yes"){
                  string positive = "";
                  positive="contact added to the group  " + filename  ;	
                  send(connectfd,positive.c_str(),strlen(positive.c_str()),0);
            }
            else{
            	char negative[]="Group doesn't exist ,Add the group to add the data  " ;
                  send(connectfd,negative,strlen(negative),0);
            }
      }
	return 0;
}





//function to receive data
string Server::ToRecvData(){
        char recvdata[1024] ;
        memset(recvdata,0,1024);
        recv(connectfd , recvdata,1024 , 0) ;
        if(strcmp(recvdata,"bye")==0 || strcmp(recvdata,"Bye")==0){                                                                     //checking for bye if bye then client closes
                close(connectfd);
                exit(0);
        }
        return string(recvdata) ;
}



//function to authenticate user
string Server::ToAuthenticateUser(){
        char  receivedata[1024];
        memset(receivedata,0,1024);
        string username ,password ;
        recv(connectfd ,receivedata,1024 , 0) ;
        string recvdata=string(receivedata);
        stringstream ss(recvdata);
        getline(ss ,username , ':');
        getline(ss , password, ':');
        for (auto user : users){
                if(user.ToAuthenticate(User(username , password))){										//checks whether the user is present it returns a bool
                        return username;
                }
        }
        return "";
}

