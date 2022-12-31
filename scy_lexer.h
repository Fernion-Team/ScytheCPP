#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class TokenType
{
	_EOF,
	ERROR,

	KEYWORD,

	ARROW_LEFT,
	ARROW_RIGHT,

	MINUS,
	PLUS,
	DIV,
	MUL,
	
	SYMBOL,

	IDENTIFER,
	STRING_LIT,
	INT_LIT
};

class Range
{
public:
	int fromLine;
	int fromCol;
	int toCol;
	int toLine;

	Range() = default;

	Range(int fL, int fC, int tC, int tL)
	{
		fromLine = fL;
		fromCol = fC;
		toCol = tC;
		toLine = tL;
	}
};

class Token
{
public:
	TokenType kind;
	std::string rep;

	Range range;

	Token(TokenType k, std::string r, Range rng)
	{
		kind = k;
		rep = r;
		range = rng;
	}

	Token() = default;

	Token(TokenType k, std::string r)
	{
		kind = k;
		rep = r;
	}
};

class Lexer
{
public:
	std::vector<Token> lexOut;
	std::string source;
	int sourceLn;
	char currentChar;
	int index = 0;

	int column = 0;
	int line = 1;

	char Peek();
	char PeekRI(int relIndex); // Peek at relative index.
	void Next();
	std::vector<Token> RunLexer(std::string src);

	Token LexIdentifier();
	bool isKeyword(std::string idt);

	Token LexNumber();
	Token LexString();
};