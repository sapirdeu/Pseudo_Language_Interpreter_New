#include "Lexer.h"


vector<string> Lexer::uniteTokens(vector<string> line) {
    vector<string> newLine;
    string firstTok = line.at(0);
    int operI;
    int operLen = 0;
    string fullLine;
    // push first token to the new line
    newLine.push_back(firstTok);

    // if the line is while or if we split the condition to left expr, operator and right expr
    if (firstTok == "while" || firstTok == "While" || firstTok == "if" || firstTok == "If") {
        // read full condition
        for (int i = 1; i < line.size(); i++) {
            fullLine += line.at(i);
        }
        // find the oper (can be 1 char or 2 chars: ==, !=, <, >, <=, >=
        for (int j = 0; j < fullLine.length(); j++) {
            char oper = fullLine[j];
            if (!operLen && (oper == '=' || oper == '!' || oper == '>' || oper == '<')) {
                operI = j;
                operLen = 1;
                if (fullLine[j + 1] == '=') {
                    operLen = 2;
                }
            }
        }

        // push right expression
        string right = fullLine.substr(0, operI);
        newLine.push_back(right);
        // push operator
        newLine.push_back(fullLine.substr(operI, operLen));
        // push left expression
        string left = fullLine.substr(operI + operLen, (fullLine.size() - (operI + operLen) - 1));
        newLine.push_back(left);
        // push parenthesis {
        newLine.push_back(fullLine.substr(fullLine.size() - 1, 1));
    } // if line is a function that takes one argument
    else if (firstTok == "openDataServer" || firstTok == "Print" || firstTok == "Sleep") {
        // read the entire argument
        for (int k = 1; k < line.size(); k++) {
            fullLine += line.at(k);
        }

        // push argument
        newLine.push_back(fullLine);
    } // if line is a function that takes two arguments
    else if (firstTok == "connectControlClient") {
        for (int k = 2; k < line.size(); k++) {
            fullLine += line.at(k);
        }

        // push first argument
        newLine.push_back(line.at(1));
        // push second argument
        newLine.push_back(fullLine);
    } else {
        return
                line;
    }

    return newLine;
}


vector<string> Lexer::lexerOneLine(string line) {
    vector<string> lexLine;
    char currChar;
    string token = "";

    // flag to identify a sentence (string that begins and ends with ")
    int inSentence = 0;
    // flag to identify an assigment (for example: variable = something)
    bool isAssign = false;

    for (int i = 0; i < line.length(); i++) {
        currChar = line[i];

        // if char is " we are inside a sentence- need to take it as one token.
        if (currChar == '"') {
            if (inSentence < 2) {
                inSentence++;
            }
        }

        // if the char is inside a sentence- add it to the token regardless what char it is.
        if (inSentence == 1) {
            token += currChar;
            continue;
        }
            // if we see the second " we finished reading the sentence, now we can push the token to the vector.
        else if (inSentence == 2) {
            lexLine.push_back(token + currChar);
            token = "";
            inSentence = 0;
            continue;
        }
            // if the char we see is not in a sentence (inSentence = 0)
        else {
            // if the char is '=' alone we deal with assigning.
            if (currChar == '=') {
                if (line[i - 1] != '<' && line[i - 1] != '>' && line[i - 1] != '!' && line[i - 1] != '=' &&
                    line[i + 1] != '=') {
                    lexLine.emplace_back("=");
                    token = "";
                    isAssign = true;
                    continue;
                }
            }

            // reaches here when the char isn't in a sentence and isn't an assignment.
            if (!isAssign) {
                // if the char is comma, parenthesis or space we split it to a token
                if (currChar == ',' || currChar == '(' || currChar == ')' || currChar == ' ') {
                    if (!token.empty()) {
                        lexLine.push_back(token);
                    }
                    token = "";
                    continue;
                }
                    // if the char is  { or  } it needs a separate token.
                else if (currChar == '{' || currChar == '}') {
                    lexLine.push_back(token + currChar);
                    token = "";
                    continue;
                }
            }
        }

        // if char is regular- not in a sentence and not a special char- add to token.
        if (currChar != ' ' && currChar != '\t' && currChar != '\n') {
            token += currChar;
        }
    }

    // if in assign- add the last token (right side of assignment)
    if (isAssign) {
        lexLine.push_back(token);
    }

    lexLine = uniteTokens(lexLine);
    return lexLine;
}

vector<vector<string>> Lexer::lexerFile(string fileName) {
    vector<vector<string>> allLines;
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.size()!=0) {
                allLines.push_back(lexerOneLine(line));
            }
        }
        file.close();
    } else
        cout << "Error: cannot open the required file." << endl;
    return allLines;
}