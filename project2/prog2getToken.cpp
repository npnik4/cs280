// Nikhil Patel
// Program 2
// CS 280 Fall 2017

#include "lexer.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int lineNumber;
Token getToken(istream* br)
{
	Token T;
	string lexeme = "";
	char ch;
	string end;
	if(br->good()){
		while(br->good()){	
			ch = br->get();
			
			if(ch == '+'){
				return T_PLUS;
			}
			else if(ch == '-'){
				return T_MINUS;
			}
			else if(ch == '*'){
				return T_STAR;
			}
			else if(ch == '/'){
				if(br->peek() == '/')// fix this
				{
					
					return T_DONE;
				}
				else if(br->peek()== '*')// fix this
				{
					do{
						ch= br->get();
					}while(ch != '*' && (br->peek())!='/');
					return T_DONE;
				}
				else
				{
					return T_SLASH;
				}
			}
			else if(ch == ';'){
				return T_SC;
			}
			else if(ch == '"'){
				lexeme += ch;
				ch = br->get();
				lexeme += ch;
				while(ch != '"'){
					ch = br->get();
					if (ch == '\n'){
						lexeme += ch;
						Token ERROR(T_ERROR, "Lexical error T_ERROR(" + lexeme + ")");
						return ERROR;
					}
					else{
						lexeme += ch;
					}
				}
				Token X(T_SCONST, lexeme);
				return X;
			}
			else if( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ){
				lexeme += ch;
				while( (br->peek() >= 'A' && br->peek() <= 'Z') || (br->peek() >= 'a' && br->peek() <= 'z') ){
					ch = br->get();
					lexeme += ch;
				}
				if(lexeme == "set"){
					Token X(T_SET, lexeme);
					return X;
				}
				else if(lexeme == "print"){
					Token X(T_PRINT, lexeme);
					return X;
				}
				else if(lexeme == "println"){
					Token X(T_PRINTLN, lexeme);
					return X;
				}
				else if(lexeme == "int")
				{
					return T_INT;
				}
				else if(lexeme == "string")
				{
					return T_STRING;
				}
				else{
					Token X(T_ID, lexeme);
					return X;
				}
			}
			else if( (ch >= '0' && ch <= '9') ){
				lexeme += ch;
				while(br->peek() >= '0' && br->peek() <= '9'){
					ch = br->get();
					lexeme += ch;
				}
				Token X(T_ICONST, lexeme);
				return X;
			}
			else if(ch == '.')
			{
				Token ERROR(T_ERROR, "Lexical error T_ERROR(.)");
				return ERROR;
			}
			else if(ch == ')')
			{
				return T_RPAREN;
			}
			else if(ch == '(')
			{
				return T_LPAREN;
			}
			else if(ch=='\n')
			{
				++lineNumber;
				end=br->peek();
				if(end.length()==0)
					return T_DONE;
			}
			else if( (ch == ' ' || ch == '\n' || ch == '\t') ){
				continue;
			}
			else{
				
				return T_DONE;
			}
		}
	}
	else
	{	
		return T_ERROR; 
	}
	return T_DONE;
}
