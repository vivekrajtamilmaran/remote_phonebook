//program to have user class header file
#include <iostream>
#include <vector>
#include<algorithm>
#include "../include/phonebook.h"
using namespace std;

class User{
        string username ,password ;
        vector<string> group;
        vector<Phonebook> phonebooks ;
        public:
                User();									//default constructor
                User(string username ,string password);
                User(string username ,string password ,vector<string>group);		//parameterized constructor

                bool  authenticate(User user);						//to autheticate the user
                string addData(string input1 ,string input2,string filename);		//to add data to the phonebook
                string removeContact(string input,string filename);			//to remove contact
                vector<string> listData(string input,string filename);			//to list the data from the group
                bool findUser(string username);						//to find the user 
                string chgrp(string input);						//to change the group
		int addGrp(string filename);						//to add a group
		int removeGrp(string filename);						//to delete a group


};

