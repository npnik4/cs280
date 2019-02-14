/*
 * parser.h
 *
 *  Created on: Oct 23, 2017
 *      Author: gerardryan
 */

#ifndef PARSER_H_
#define PARSER_H_

using namespace std;

#include <iostream>
using std::istream;

#include <string>
using std::string;
using std::stoi;

#include "lexer.h"

extern void error(int linenum, const string& message);


enum TypeForNode { INT_TYPE, STRING_TYPE, ERROR_TYPE, PLUS_TYPE, MINUS_TYPE, STAR_TYPE, SLASH_TYPE, ID_TYPE, DECL_TYPE, PRINT_TYPE, SET_TYPE, INT, STRING, TRAVERSE };

class ParseTree {
	int			linenumber;
	ParseTree	*left;
	ParseTree	*right;

public:
	ParseTree(int n, ParseTree *l = 0, ParseTree *r = 0) : linenumber(n), left(l), right(r) {}
	virtual ~ParseTree() {}

	ParseTree* getLeft() const { return left; }
	ParseTree* getRight() const { return right; }
	int getLineNumber() const { return linenumber; }

	virtual TypeForNode GetType() const { return ERROR_TYPE; }
	virtual int GetIntValue() const { throw "no integer value"; }
	virtual string GetStringValue() const { throw "no string value"; }
	virtual string GetIdValue() const { throw "no id value"; }

	int Nodecount(TypeForNode f) {
		int count = 0;
		if( left ){
			if(TRAVERSE == f)
				cout<< "L";
			count += left->Nodecount(f);
			if(TRAVERSE == f)
				cout<< "u";
		}
		if( right ){
			if(TRAVERSE == f)
				cout<< "R";
			count += right->Nodecount(f);
			if(TRAVERSE == f)
				cout<< "U";
		}

		if(this->GetType() == f)
			count++;
		
		if(TRAVERSE == f)
			cout<< "N";

		return count;
	}
	
	int isStar() {return 0;}
	int isPlus() {return 0;}
	int isSet() {return 0;}
	int isID() {return 0;}
};

class StatementList : public ParseTree {
public:
	StatementList(ParseTree *first, ParseTree *rest) : ParseTree(0, first, rest) {}
};

class SetNode : public ParseTree {
public:
	SetNode(int line, ParseTree *first, ParseTree *rest) : ParseTree(line, first, rest) {}

	int isSet() {return 1;}
	TypeForNode GetType() const { return SET_TYPE; }
};

class DeclNode : public ParseTree {
public:
	DeclNode(int line, ParseTree *first) : ParseTree(line, first) {}

	TypeForNode GetType() const { return DECL_TYPE; }
};

class PrintNode : public ParseTree {
public:
	PrintNode(int line, ParseTree *first) : ParseTree(line, first) {}

	TypeForNode GetType() const { return PRINT_TYPE; }
};

class Addition : public ParseTree {
public:
	Addition(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return PLUS_TYPE; }
	int isPlus() {return 1;}
};

class Subtraction : public ParseTree {
public:
	Subtraction(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return SLASH_TYPE; }
};

class Multiplication : public ParseTree {
public:
	Multiplication(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return STAR_TYPE; }
	int isStar() {return 1;}
};

class Division : public ParseTree {
public:
	Division(int line, ParseTree *op1, ParseTree *op2) : ParseTree(line, op1, op2) {}

	TypeForNode GetType() const { return MINUS_TYPE; }
};

class IntegerConstant : public ParseTree {
	int	value;

public:
	IntegerConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = stoi( tok.GetLexeme() );
	}

	TypeForNode GetType() const { return INT_TYPE; }
	int GetIntValue() const { return value; }
};

class StringConstant : public ParseTree {
	string	value;

public:
	StringConstant(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = tok.GetLexeme();
	}

	TypeForNode GetType() const { return STRING_TYPE; }
	string GetStringValue() const { return value; }
};

class Identifier : public ParseTree {
	string value;

public:
	Identifier(const Token& tok) : ParseTree(tok.GetLinenum()) {
		value = tok.GetLexeme();
	}
	int isID() {return 1;}
	
	TypeForNode GetType() const { return ID_TYPE; }
	string GetIdValue() const { return value; }
};

extern ParseTree *	Prog(istream* in);
extern ParseTree *	StmtList(istream* in);
extern ParseTree *	Stmt(istream* in);
extern ParseTree *	Decl(istream* in);
extern ParseTree *	Set(istream* in);
extern ParseTree *	Print(istream* in);
extern ParseTree *	Expr(istream* in);
extern ParseTree *	Term(istream* in);
extern ParseTree *	Primary(istream* in);


#endif /* PARSER_H_ */
