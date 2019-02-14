// Nikhil Patel
// Program 1
// CS 280 Fall 2017

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map> 
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
   // get argv place in string split string and group by arguments
   if(argc > 1)
	{
	   	ostringstream os;
	   	int strCount;
	   	for(int var = 1; var < argc; var++)
	   	{
	   		os << argv[var]<< ' '; // hold input in string
			strCount++; 
		}
		// process os string and split string
		string combo = os.str();
		int c = 0;
		int m = 0;
		int b = 0;
		int numflag = 0;
		string files = "";
		int numfiles = 0;
		istringstream mystring(combo);
		for(int j = 0; j<=argc;j++)
		{
			string temp = "";
			mystring >> temp;
			if(temp == "-c" )
			{
				c = 1;
				numflag++;	
			}
			else if(temp == "-m")
			{
				m = 1;
				numflag++;
			}
			else if(temp == "-b")
			{
				b = 1;
				numflag++;
			}
			else if(temp[0] == '-' && (temp[1] != 'c' || temp[1] != 'b' || temp[1] != 'm'))
			{
				cout<< temp << " UNRECOGNIZED FLAG" << endl;
				return 0;
			}
			else if(temp[0] != '-')
			{
				files = files + temp + " ";
				numfiles++;	
			}
		}
		// algorithm
		if(files == "")
		{
			cout <<"NO FILES" << endl;
			return 0;
		}
		istringstream filestring(files);
		for(int i =0 ; i<= numfiles;i++)
		{
			map<string, int> myMap;// mutli wordd
			map<string, int>::const_iterator it;
			map<int, int> lineMap;
			map<int, int>::const_iterator It;
			string tempfile = "";
			filestring >> tempfile; // ith file
			ifstream myfile(tempfile.c_str());
			string curword = "", curwords;
			string longest = "";
			string longline = "";
			string curline = "";
			string sameWord = "";
			int lineFreq = 0;
			int longestline = 0;
			// Calculations
			if (myfile.is_open()) 
			{
				while(getline(myfile, curline)) // get longest line
				{
					istringstream word(curline);
					while(getline(word, curword, ' '))
					{
						
						if(curword.length() > longest.length())
						{
							myMap.clear();
							myMap[curword] =1;
							longest = curword;
						}
						else if(curword.length() == longest.length())
						{
							if(myMap.find(curword) != myMap.end())
							{
								myMap[curword]++;
							}
							else
							{
								myMap[curword] = 1;
							}
						}
					}
					if(b == 1)
					{
						int count = 0;
						for(int j =0; j< curline.length(); j++)
						{
							
							if(j < (curline.length()-1))
							{
								if(curline[j] == ' ' && curline[j+1] != ' ')
									count++;
								else if(curline[j] != ' ' && curline[j+1] == ' ')
									count++;
								else if(curline[j] != ' ' && curline[j+1] != ' ')
									count++;
								
							}
							else if(count != 0 && curline[curline.length()-1] != ' ')
								count++;
							
							
						}
						
						if(count > longestline)
						{
							lineFreq = 1;
							longestline = count;
						}
						else if(count == longestline)
							lineFreq++;
					}
					else
					{
						if(curline.length() > longline.length())
						{
							lineMap.clear();
							lineMap[curline.length()]=1;
							longline = curline;
						}
						else if(curline.length() == longline.length())
						{
							if(lineMap.find(curline.length()) != lineMap.end())
							{
								lineMap[curline.length()]++;	
							}
						}
					}
				}
				if((m == 0) & (c == 1) & (b == 0))
				{	
					ostringstream os2;
					int x = 1;
					for(it = myMap.begin(); it!= myMap.end(); it++)
					{
						if((unsigned)x < myMap.size())
						{
							os2 << it->first << "(" << it->second << ")"<<", ";
						}
						else
						{
							os2 << it->first << "(" << it->second << ")";	
						}
						x++;
					}
					sameWord = os2.str();
					os2.clear();
					cout << tempfile << ":"<<endl;
					if(sameWord[0] != '(')
					{
						cout << sameWord << endl;
					}
					for(It = lineMap.begin(); It!= lineMap.end(); It++)
					{
						cout << It->first <<"("<< It->second <<")"<< endl;
					}
				}
				if((m == 0) & (c == 0) & (b == 1))
				{
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(sameWord.length() > 0)
						{
							sameWord += ", " + it->first;
						}
						else
						{
							sameWord = it->first;	
						}
					}
					myfile.close();
					cout << tempfile << ":"<<endl;
					if(sameWord.length() != 0)
					{
						cout << sameWord << endl;
					}
					cout << longestline << endl;
				}
				if((m == 1) & (c == 0) & (b == 0))
				{
					string large = "";
					int big = 0;
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second > big)
						{
							big=it->second;
						}
					}
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second == big)
						{
							if(large == "")
								large = it->first;
							else
								large += ", " + it->first;
						}
						
					}
					myfile.close();
					cout << tempfile << ":"<<endl;
					cout << large << endl; 
					cout << longline.length() << endl;
				}
				if((m == 0) & (c == 0) & (b == 0))
				{
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(sameWord.length() > 0)
						{
							sameWord += ", " + it->first;
						}
						else
						{
							sameWord = it->first;	
						}
					}
					myfile.close();
					cout << tempfile << ":"<<endl;
					cout << sameWord << endl; 
					cout << longline.length() << endl;
				}
				if((m == 1) & (c == 1) & (b == 0))
				{
					ostringstream os2;
					string large = "";
					int big = 0;
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second > big)
						{
							big=it->second;
						}
					}
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second == big)
						{
							if(large == "")
							{
								os2 << it->first << "(" << it->second << ")";
								large = it->first;
							}
							else
							{
								os2 <<", "<< it->first << "(" << it->second << ")";
								large += ", " + it->first;
							}
						}
						
					}
					sameWord = os2.str();
					os2.clear();
					myfile.close();
					cout << tempfile << ":"<<endl;
					cout << sameWord << endl; 
					for(It = lineMap.begin(); It!= lineMap.end(); It++)
					{
						cout << It->first <<"("<< It->second <<")"<< endl;
					}
				}
				if((m == 1) & (c == 1) & (b == 1))
				{
					ostringstream os2;
					string large = "";
					int big = 0;
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second > big)
						{
							big=it->second;
						}
					}
					for (it = myMap.begin(); it!= myMap.end(); it++)
					{
						if(it->second == big)
						{
							if(large == "")
							{
								os2 << it->first << "(" << it->second << ")";
								large = it->first;
							}
							else
							{
								os2 <<", "<< it->first << "(" << it->second << ")";
								large += ", " + it->first;
							}
						}
						
					}
					sameWord = os2.str();
					os2.clear();
					myfile.close();
					cout << tempfile << ":"<<endl;
					if(sameWord[0] != '(')
					{
						cout << sameWord << endl;
					} 
					cout << longestline <<"("<<lineFreq<<")"<< endl;
				}
			}
			else if(tempfile.length() == 0)
			{
				continue;	
			}
			else
			{
				cout << tempfile << " FILE NOT FOUND" << endl;// printing multi times
				continue;
			}
	    }
	}
    else
    {
    	cout <<"NO FILES" << endl;
    }
    return 0;
}
   













