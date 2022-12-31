#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "scy_lexer.h"
#include "scy_stmts.h"

class Parser
{
public:
	std::vector<Token> feed;
	int index;
	Token current;

	Token Peek(int n);
	void Next();

	void ParseKeyword();
	void ParseFunction();

	std::vector<Statement> Parse(std::vector<Token> parserFeed);
};