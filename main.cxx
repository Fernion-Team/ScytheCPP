#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "scy_lexer.h"

std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
            << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[])
{
    std::string source = readFileIntoString("test.sy");

    // LEXER STEP:
    Lexer lexer;
    std::vector<Token> tks = lexer.RunLexer(source);

    for (Token& i : tks)
    {
        std::cout << (int)i.kind << ":" << i.rep << '\n';
    }
}
