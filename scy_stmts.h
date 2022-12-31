#pragma once
#include <iostream>
#include <string>
#include <vector>

enum class StatementKind
{
	FN,
	VAR,
	RET,
	IMPORT
};

class Statement
{
public:
	virtual StatementKind GetKind() = 0;
};

class Type
{};

class IdentifierType : Type
{
public:
	std::string Type;

	IdentifierType() = default;

	IdentifierType(std::string type)
	{
		Type = type;
	}
};

class PointerType : Type
{
public:
	IdentifierType Type;

	PointerType() = default;

	PointerType(IdentifierType type)
	{
		Type = type;
	}
};

class Parameter
{
	std::string Name;
	Type Type;
};

class BlockStatement : Statement
{
public:
	std::vector<Statement> Statements;

	
};

class FunctionStatement : Statement
{
public:
	std::string Name;
	std::vector<Parameter> Params;

	StatementKind GetKind()
	{
		return StatementKind::FN;
	}

	FunctionStatement(std::string name, std::vector<Parameter> params)
	{
		Name = name;
		Params = params;
	}
};

class ImportStatement : Statement
{
public:
	std::string Name;

	StatementKind GetKind()
	{
		return StatementKind::IMPORT;
	}

	ImportStatement(std::string name)
	{
		Name = name;
	}
};



