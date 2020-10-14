#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <execinfo.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "Lexer.h"
#include "Parser.h"

using namespace std;


int main(int argc, char **argv) {
    Lexer* fileToLexer = new Lexer();
    Parser* parser = new Parser(fileToLexer->lexerFile(argv[1]));
    parser->parsing();
    return 0;
}

