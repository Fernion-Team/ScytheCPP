#include "scy_lexer.h"

int GetLineCount(std::string buf)
{
	int count = 0;

	for (char& c : buf)
	{
		if (c == '\n')
		{
			count++;
		}
	}

	return count;
}

void Lexer::Next()
{
	this->currentChar = source[index++];
	this->column++;
}

bool Lexer::isKeyword(std::string idt)
{
	return idt == "fn" || idt == "var";
}

Token Lexer::LexIdentifier()
{
	std::string idt;

	while (this->index < this->sourceLn && isalpha(this->currentChar))
	{
		idt.append(1, this->currentChar);
		Next();
	}

	if (isKeyword(idt))
	{
		return Token(TokenType::KEYWORD, idt);
	}

	return Token(TokenType::IDENTIFER, idt);
}

Token Lexer::LexNumber()
{
	std::string idt;

	while (this->index < this->sourceLn && isdigit(this->currentChar))
	{
		idt.append(1, this->currentChar);
		Next();
	}

	return Token(TokenType::INT_LIT, idt);
}

Token Lexer::LexString()
{
	std::string idt;

	Next();

	while (this->index < this->sourceLn && this->currentChar != '"')
	{
		idt.append(1, this->currentChar);
		Next();
	}

	Next();

	return Token(TokenType::STRING_LIT, idt);
}

char Lexer::Peek()
{
	if (this->index+1 < this->sourceLn)
	{
		return this->source[index + 1];
	}

	return NULL;
}

char Lexer::PeekRI(int relIndex)
{
	if (this->index + relIndex < this->sourceLn)
	{
		return this->source[index + relIndex];
	}

	return NULL;
}

std::vector<Token> Lexer::RunLexer(std::string src)
{
	this->source = src;
	this->index = 0;
	this->currentChar;
	this->sourceLn = src.length();

	while (this->index < this->sourceLn)
	{
		if (isspace(currentChar) || currentChar == 32)
		{
			this->column++;
			if (currentChar == '\n')
			{
				this->line++;
				this->column = 1;
			}
			Next();
		}

		if (isdigit(this->currentChar))
		{
			int colB4 = this->column;
			Token tk = LexNumber();
			tk.range = Range(this->line, colB4, this->column, this->line);
			this->lexOut.push_back(tk);
		}

		if (isalpha(this->currentChar))
		{
			int colB4 = this->column;
			Token tk = LexIdentifier();
			tk.range = Range(this->line, colB4, this->column, this->line);
			this->lexOut.push_back(tk);
		}

		if (this->currentChar == '"')
		{
			int colB4 = this->column;
			Token tk = LexString();
			tk.range = Range(this->line, colB4, this->column, this->line);
			this->lexOut.push_back(tk);
		}

		if (ispunct(this->currentChar) != 0)
		{
			int colB4 = this->column;
			Token tk;

			tk = Token(TokenType::SYMBOL, std::string(1, this->currentChar), Range(this->line, colB4, this->column + 1, this->line));
			
			this->lexOut.push_back(tk);
		}

		Next();
	}

	// Generate an EOF.

	this->lexOut.push_back(Token(TokenType::_EOF, "eof", Range(GetLineCount(this->source), this->index, this->index + 1, GetLineCount(this->source))));

	return this->lexOut;
}