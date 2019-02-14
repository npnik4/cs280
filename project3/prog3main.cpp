// Nikhil Patel
// Program 2
// CS 280 Fall 2017

#include <iostream>
#include <string>
#include <sstream>
#include <fstream> 
#include "lexer.h"
#include "parser.h" 
#include "parser.cpp" 
using namespace std;

extern string files;

int main(int argc, char* argv[])
{
	istream *br;
	ifstream infile;
	string lexeme;
	ostringstream os;
	
	int t = 0;
	//bool go = false;
	int numflag = 0;
	files = "";
	
	if(argc > 1)
	{
		ostringstream os;
	   	int strCount;
	   	for(int index = 1; index < argc; index++)
	   	{
	   		os << argv[index]<< ' '; // hold input in string
			strCount++; 
		}
		// process os string and split string
		string combo = os.str();
		// flags 0 = false
		
		istringstream mystring(combo);
		
		for(int j = 0; j<=argc;j++)
		{
			string temp = "";
			mystring >> temp;
			if(temp == "-t" )
			{
				t = 1;
				numflag++;	
			}
			else if(temp[0] == '-' && (temp[1] != 't'))
			{
				cout<< temp << " UNRECOGNIZED FLAG" << endl;
				return 0;
			}
			else if(temp[0] != '-')
			{
				if(files.length() == 0 || files == "")
				{
					files = temp;
					//go = true;
				}
				else if(temp.length() != 0)
				{
					cout<< "TOO MANY FILES" << endl;
					return 0;
				}
			}
		}
		
		//getting tokens from file
		infile.open(files.c_str());
		if( infile.is_open())
		{
			br = &infile;
			
		}
		else
		{
			cout << files << " FILE NOT FOUND" << endl;
            return 0;
	    }
	}
	else if(argc == 2 && files.length() == 0)
	{
		//getting tokens from standard user input
		ParseTree *tree = Prog( &cin );
	}
	else
	{
		// close program no arguments provided
		return 0;
	}
	
	ParseTree *tree = Prog(br);
	if(t == 1)
	{
		tree->Nodecount(TRAVERSE);
		cout<< endl;
	}

	cout<< "Total number of identifiers: " << isInID.size() << endl; //tree->Nodecount(ID_TYPE)
	cout<< "Total number of set: " << tree->Nodecount(SET_TYPE) << endl;
	cout<< "Total number of +: " << tree->Nodecount(PLUS_TYPE) << endl;
	cout<< "Total number of *: " << tree->Nodecount(STAR_TYPE) << endl;
	

	return 0;
	
}
