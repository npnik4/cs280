/*
 * parser.cpp
 *
 */
#include <vector>
#include <string>
#include <algorithm>
using std::string;
#include "prog3getToken.cpp"
#include "parser.h"
using namespace std;

vector<string> isInID;

string files;
class ParserToken {
private:
	Token	tok;
	bool	pushedBack;

public:
	ParserToken() : pushedBack(false) {}

	Token getToken(istream *in) {
		if( pushedBack ) {
			pushedBack = false;
			return tok;
		}

		return ::getToken(in);
	}
	void pushbackToken(const Token& t) {
		if( pushedBack ) {
			// error
		}
		tok = t;
		pushedBack = true;
	}
}
ParserToken;

void error( int num, const string& msg)
{
	cout<<files<<":"<< num+1 <<":"<< msg<<endl;
	return;
}

ParseTree *Prog(istream* in)
{
	return StmtList(in);
}

ParseTree *StmtList(istream* in)
{
	ParseTree *stmt = Stmt(in);
	if( stmt == 0 )
		return 0;
	return new StatementList( stmt, StmtList(in) );
}

ParseTree *	Stmt(istream* in) {
	Token t = ParserToken.getToken(in);

	if( t.GetTokenType() == T_ERROR ) {
		error(t.GetLinenum(), "Invalid token");
	
		return 0;
	}
	if( t.GetTokenType() == T_DONE )
		return 0;
		
	if(t.GetTokenType() == T_INT || t.GetTokenType() == T_STRING){
		return Decl(in);
	}
	else if(t.GetTokenType() == T_SET){
		return Set(in);
	}
	else if(t.GetTokenType() == T_PRINT || t.GetTokenType() == T_PRINTLN){
		ParserToken.pushbackToken(t);
		return Print(in);
	}
	return 0;
}

ParseTree *	Decl(istream* in) {
	Token t = ParserToken.getToken(in);

	if( t.GetTokenType() != T_ID)
	{
		error(t.GetLinenum(), "expected Identifier");
		return 0;
	}
	if( ParserToken.getToken(in).GetTokenType() != T_SC ) {
		error(t.GetLinenum(), "Missing semicolon");
		return 0;
	}
	// if t not in vector then go
	bool go = true;
	if(find(isInID.begin(), isInID.end(), t.GetLexeme()) != isInID.end())
	{
		go = false;
	}
	if( go == true)
	{
		isInID.push_back(t.GetLexeme());
		return new DeclNode(t.GetLinenum(), new Identifier(t));
	}
	else
       return new DeclNode(t.GetLinenum(), new Identifier(t));
}

ParseTree *	Set(istream* in) {
	Token tid = ParserToken.getToken(in);
	if(tid.GetTokenType() != T_ID){
		error(tid.GetLinenum(), "Expecting identifier after set");
		return 0;
	}
	ParseTree *ex = Expr(in);
	if( ex == 0 ) {
		error(tid.GetLinenum(), "Syntax error expression required");
		return 0;
	}
	if( ParserToken.getToken(in).GetTokenType() != T_SC ) {
		error(tid.GetLinenum(), "Missing semicolon");
		return 0;
	}
	return new SetNode(tid.GetLinenum(),  new Identifier(tid), ex);
}

ParseTree *	Print(istream* in) {
	Token t = ParserToken.getToken(in);
	ParseTree *ex = Expr(in);

	if( ex == 0 ) {
		error(t.GetLinenum(), "Syntax error expression required");
		return 0;
	}
	if( ParserToken.getToken(in).GetTokenType() != T_SC ) {
		error(t.GetLinenum(), " Missing semicolon");
		return 0;
	}
	return new PrintNode(t.GetLinenum(), ex);
}

ParseTree *Expr(istream* in) {
	ParseTree *t1 = Term(in);
	if( t1 == 0 ){
		Token t = getToken(in);
		error(t.GetLinenum(), "Syntax error primary expected");
		ParserToken.pushbackToken(t);
		return 0;
	}

	for(;;) {
		Token op = ParserToken.getToken(in);
		if( op != T_PLUS && op != T_MINUS ) {
			ParserToken.pushbackToken(op);
			return t1;
		}

		ParseTree *t2 = Expr(in);
		if( t2 == 0 ) {
			error(op.GetLinenum(), "Syntax error expression required after + or - operator");
			return 0;
		}

		// combine t1 and t2 together
		if( op == T_PLUS )
			t1 = new Addition(op.GetLinenum(), t1, t2);
		else
			t1 = new Subtraction(op.GetLinenum(), t1, t2);
	}

	// should never get here...
	return 0;
}

ParseTree *	Term(istream* in) {
	ParseTree *p1 = Primary(in);
	if( p1 == 0 )
		return 0;

	for(;;) {
		Token op = ParserToken.getToken(in);
		if( op != T_STAR && op != T_SLASH) {
			ParserToken.pushbackToken(op);
			return p1;
		}
		ParseTree *p2 = Term(in);
		if( p2 == 0 ) {
			error(op.GetLinenum(), "Syntax error expression required");
			return 0;
		}
	
		if( op == T_STAR )
			p1 = new Multiplication(op.GetLinenum(), p1, p2);
		else
			p1 = new Division(op.GetLinenum(), p1, p2);
	}
	
	return 0;
}

ParseTree *	Primary(istream* in) {
	Token t = ParserToken.getToken(in);
	if( t.GetTokenType() == T_ID ) {
		return new Identifier(t);
	}
	else if( t.GetTokenType() == T_ICONST ) {
		return new IntegerConstant(t);
	}
	else if( t.GetTokenType() == T_SCONST ) {
		return new StringConstant(t);
	}
	else if( t.GetTokenType() == T_LPAREN ) {
		ParseTree *ex = Expr(in);
		if( ex == 0 )
			return 0;
		t = ParserToken.getToken(in);
		if( t.GetTokenType() != T_RPAREN ) {
			error(t.GetLinenum(), " expected right parens");
			return 0;
		}
		return ex;
	}
	return 0;
}
