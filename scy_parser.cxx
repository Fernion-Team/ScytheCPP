#include "scy_parser.h"

void Parser::Next()
{
	this->current = this->feed[this->index++];
}

Token Parser::Peek(int n)
{
	return this->feed[this->index + n];
}

void Parser::ParseKeyword()
{
	if (this->current.rep == "fn") 
	{

	}
}

std::vector<Statement> Parser::Parse(std::vector<Token> parserFeed)
{
	this->feed = parserFeed;

	switch (this->current.kind)
	{
		case TokenType::KEYWORD:
			ParseKeyword();
			break;
	}

	this->Next();
}