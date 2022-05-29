//program to have the header file for phonebook class
#include <iostream>
using namespace std;
class Phonebook{
        string name , phonenumber ;

        public :
                Phonebook();								//default constructor
                Phonebook(string name , string phonenumber );				//parameterized constructor
                bool storeData(string filename);					//to store the data
                string removeData(vector<string> afterRemoved,string filename);		//to remove the data
};

