//program to have the header file for phonebook class
#include <iostream>
using namespace std;
class Phonebook{

        public :
                Phonebook();								//default constructor
                Phonebook(string name , string phonenumber );				//parameterized constructor
                bool ToStoreData(string filename);					//to store the data
                string ToRemoveData(vector<string> afterRemoved,string filename);	//to remove the data
        
	private:
		string name , phonenumber ;
};

