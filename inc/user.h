//program to have user class header file
#include <iostream>
#include <vector>
#include<algorithm>
#include <phonebook.h>

using namespace std;
class User{
        public:
                User();									//default constructor
                User(string username ,string password);
                User(string username ,string password ,vector<string>group);		//parameterized constructor

                bool  ToAuthenticate(User user);						//to autheticate the user
                string ToAddData(string input1 ,string input2,string filename);		//to add data to the phonebook
                string ToRemoveContact(string input,string filename);			//to remove contact
                vector<string> ToListData(string input,string filename);			//to list the data from the group
                bool ToFindUser(string username);						//to find the user 
                string ToChgrp(string input);						//to change the group
		int ToAddGrp(string filename);						//to add a group
		int ToRemoveGrp(string filename);						//to delete a group
                string ToAdminAddData(string input1 ,string input2,string filename);	//to add data to the phonebook from admin
	private:
       		string username ,password ;
        	vector<string> group;
        	vector<Phonebook> phonebooks ;


};

