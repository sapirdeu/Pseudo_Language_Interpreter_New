#include "AllExpressions.h"
// Value methods:
double Value::calculate(){
    return this->val;
}


// Variable methods:
double Variable::calculate(){
    return this->value;
}

Variable& Variable::operator++(){
    this->value = this->value + 1;
    return *this;
}

/* op++(int) return x++ so we keep the current value, add 1 and return the
 * previous value */
Variable& Variable::operator++(int num){
    (void)(num);
    this->value = this->value + 1;
    return *this;
}


Variable& Variable::operator--(){
    this->value = this->value - 1;
    return *this;
}

/* op--(int) return x-- so we keep the current value, reduce by 1 and return
 * the previous value */
Variable& Variable::operator--(int num){
    (void)(num);
    this->value = this->value - 1;
    return *this;
}

Variable& Variable::operator+=(double num){
    this->value += num;
    return *this;
}

Variable& Variable::operator-=(double num){
    this->value -= num;
    return *this;
}

// BinaryOperator
//constructor
BinaryOperator::BinaryOperator(Expression *newLeft, Expression *newRight):
        right(newRight), left(newLeft){}

// Plus:
Plus::Plus(Expression *newLeft, Expression *newRight):
        BinaryOperator(newLeft, newRight) {}

double Plus::calculate(){
    double num;
    num = this->left->calculate() + this->right->calculate();
    return num;
}

// Minus:
Minus::Minus(Expression *newLeft, Expression *newRight):
        BinaryOperator(newLeft, newRight) {}

double Minus::calculate(){
    double num;
    num = this->left->calculate() - this->right->calculate();
    return num;
}

// Mul:
Mul::Mul(Expression *newLeft, Expression *newRight):
        BinaryOperator(newLeft, newRight) {}

double Mul::calculate(){
    double num;
    num = this->left->calculate() * this->right->calculate();
    return num;
}

// Div:
Div::Div(Expression *newLeft, Expression *newRight):
        BinaryOperator(newLeft, newRight) {}

double Div::calculate(){
    double num;
    //if we try to divide by 0 then it's a bad input
    if (this->right->calculate() == 0 || this->right->calculate() == 0.0)
        throw "bad input";
    num = this->left->calculate() / this->right->calculate();
    return num;
}


// UnaryOperator
// UMinus:
UMinus::UMinus(Expression *newValue): UnaryOperator(newValue) {}

double UMinus::calculate(){
    double num;
    num = -1 * this->ex->calculate();
    return num;
}

// UPlus:
UPlus::UPlus(Expression *newValue): UnaryOperator(newValue) {}

double UPlus::calculate(){
    double num;
    num = 1 * this->ex->calculate();
    return num;
}

//Interpreter
int Interpreter::isOperator(char c) {
    if (c == '+'){
        return 1;
    } else if (c == '-'){
        return 1;
    } else if (c == '*'){
        return 1;
    } else if (c == '/'){
        return 1;
    } else {
        return 0;
    }
}

int Interpreter::isOperand(char c){
    if (isOperator(c) == 0 && c != '(' && c != ')'){
        return 1;
    }
    return 0;
}

int Interpreter::isNumber(string s) {
    for (unsigned int i = 0; i < s.length(); i++){
        if (!std::isdigit(s[i]) && s[i] != '.'){
            return 0;
        }
    }
    return 1;
}

int Interpreter::operatorPriority(string oper){
    //the priority of an unary operator (marked: -U or +U) is the same as mul
    if (oper.length() == 2)
        return 2;
    else{
        char op = oper[0];
        if(op == '*' || op == '/') {
            return 2;
        } else if(op == '+' || op == '-') {
            return 1;
        } else {
            return 0;
        }
    }
}

//compares the priority between 2 operators
int Interpreter::comparePriority(string opLeft, string opRight) {
    int priorityOpLeft = operatorPriority(opLeft);
    int priorityOpRight = operatorPriority(opRight);

    /* if the priority of the operator in the left side is bigger than the
     * priority operator in the right 0 -> return 1 */
    if (priorityOpLeft > priorityOpRight){
        return 1;
    }
        /* if the priority of the operator in the left side is bigger than the
         * priority operator in the right 0 -> return -1 */
    else if (priorityOpLeft < priorityOpRight){
        return -1;
    }
    //the priorities are equal
    return 0;
}

string Interpreter::convertInitPostfix(string str) {
    stack<string> stack;
    string strAsPostfix = "";
    string currChar;
    char op;
    string top;
    int flag = 0;
    int preWas = 0;

    for (unsigned int i = 0; i < str.length(); i++) {
        currChar = str[i];

        //if currChar is a number -> add it to the postfix string
        if (isOperand(currChar[0])) {
            strAsPostfix = strAsPostfix + currChar[0];
            if (!stack.empty() && stack.top().length() == 2){
                /* if the top of the stack is an unary operator then we need to
                 * pop it */
                flag = 1;
            }

            /* in the next iteration (i+1) we will know that currChar at
             * iteration i wasn't '(' */
            preWas = 0;
        }

            /* pop an unary operator from the stack and add if to the postfix
             * string immediately after a number */
        else if (flag ==1 && (isOperator(currChar[0]) || currChar[0]=='(' ||
                              currChar[0]==')')){
            top= stack.top();
            stack.pop();
            strAsPostfix = strAsPostfix + " " + top + " ";
            flag = 0;
        }

            /* if currChar is '(' then we push the content of the parenthesis to
             * the stack */
        else if (currChar[0] == '(') {
            stack.push(currChar);
            preWas = 1;
        }

        //if currChar is an operator
        if (isOperator(currChar[0])) {
            strAsPostfix = strAsPostfix + " ";
            //if it's the first char in the input then it's an unary operator
            if (i == 0 && (str[0] == '-' || str[0] == '+' )){
                currChar = currChar + "U";
                stack.push(currChar);
            }
                //if the previous char was a '('
            else if (preWas == 1) {
                //if currChar is - or + then currChar is an unary operator
                if (currChar[0] == '-' || currChar[0] == '+') {
                    currChar = currChar + "U";
                    stack.push(currChar);
                }
            }
                /* else if the top of the stack is '(' then we push the operator
                 * to the tsack */
            else if (!stack.empty() && stack.top()[0] == '('){
                stack.push(currChar);
            } else {
                /* top of the stack isn't '(' but operator, then we push
                 * currChar to the stack according to the priority */
                while (!stack.empty() && stack.top()[0] != '(') {
                    if (comparePriority(stack.top(), currChar) >= 0){
                        op = stack.top()[0];
                        stack.pop();
                        if (op != '(')
                            strAsPostfix = strAsPostfix + " "+ op + " ";
                    } else
                        break;
                }
                //the stack is empty so we push the operator to the stack
                stack.push(currChar);
            }
            /* in the next iteration (i+1) we will know that currChar at
             * iteration i wasn't '(' */
            preWas = 0;
        }
            /* if currChar is ')' then we need to empting the stack till we see
             * ')'.
             * If we poped '(' and the now the top is unary we pop it and add it
             * to the postfix string */
        else if (currChar[0] == ')') {
            while (!stack.empty()) {
                top = stack.top();
                stack.pop();
                if (top[0] != '('){
                    if (top.length() == 2)
                        strAsPostfix = strAsPostfix + " " + top;
                    else
                        strAsPostfix = strAsPostfix + " " + top[0];
                }
                else {
                    if (!stack.empty() && stack.top().length() == 2){
                        top= stack.top();
                        stack.pop();
                        strAsPostfix = strAsPostfix + " " + top;
                    }
                    break;
                }
            }
            preWas = 0;
        }
    }

    //emptying the stack
    while (!stack.empty()) {
        top = stack.top();
        stack.pop();
        strAsPostfix = strAsPostfix + " " + top;
    }
    return strAsPostfix;
}

//calculate the value of number with unary operator
double Interpreter::postfixCalculateUnary(double leftNum, char op){
    double num = 0;
    Value* e1 = new Value(leftNum);

    if (op == '-'){
        UMinus* p = new UMinus(e1);
        num = p->calculate();
    } else if (op == '+'){
        UPlus* p = new UPlus(e1);
        num = p->calculate();
    }

    return num;
}

//calculate the value of 2 numbers with binary operator
double Interpreter::postfixCalculateBinary(double leftNum, char op,
                                           double rightNum){
    double num = 0;

    Value* e1 = new Value(rightNum);
    Value* e2 = new Value(leftNum);

    if (op == '+'){
        Plus* p = new Plus(e2, e1);
        num = p->calculate();
    } else if (op == '-'){
        Minus* p = new Minus(e2, e1);
        num = p->calculate();
    } else if (op == '*'){
        Mul* p = new Mul(e2, e1);
        num = p->calculate();
    } else if (op == '/'){
        if (rightNum == 0 || rightNum == 0.0)
            throw "bad input";
        Div* p = new Div(e2, e1);
        num = p->calculate();
    }

    return num;
}

//find token in the string (number or a '(' or a ')' or an operator)
string Interpreter::findNewToken(string str, int index){
    string token = "";
    while (str[index]!=' '){
        if (str[index]=='\0' && !token.empty()){
            return token;
        }

        token = token + str[index];
        index++;
    }
    return token;
}

//set value to each variable in the string
string Interpreter::setValueToVar(string str){
    string newString = "";
    string varName = "";
    for (unsigned int i = 0; i < str.length(); i++){
        /* if the first char is a letter or a '_' than we add it the the name of
         * the variable */
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')
            || str[i] == '_'){
            //if the first char of the name isn't a number
            if (i == 0 || (str[i-1] < '0' || str[i-1] > '9'))
                varName += str[i];
            else
                throw "bad input";
            /* if the curret char is a letter or a number or a '_' then we add
             * it to the the name of the variable */
            while (!isOperator(str[i+1]) && str[i+1] != '(' && str[i+1] != ')'
                   && str[i+1] != '\0')
            {
                varName += str[i+1];
                i++;
            }
            //if the current variable name has no value it's a bad input
            if (this->mapping[varName] == "")
                throw "bad input";
            //else, we add the value to the string
            newString += '(';
            newString += this->mapping[varName];
            newString += ')';
            varName = "";

        } else{
            newString += str[i];
        }
    }
    //return a original string without variables but with there values
    return newString;
}

Expression* Interpreter::interpret(string strInput) {
    //set value to each variable
    string noD = noDoubleOperator(strInput);

    //string str = setValueToVar(strInput);
    string str = setValueToVar(noD);

    //check that the string is valid
    checkValidExp(str);
    //convert the string to postfix
    string strAsPostfix = convertInitPostfix(str);

    string token;
    int sizeStr = strAsPostfix.length();
    stack<double> stack;
    int i = 0;
    double num;
    double firstNum;
    double secondNum;
    double numAfterOp;


    while (i < sizeStr){
        if (strAsPostfix[i] == ' '){
            i++;
            continue;
        }

        //fing new token
        token = findNewToken(strAsPostfix, i);
        i += token.length();

        if (token != ""){
            //if the current token is an operator
            if (isOperator(token[0])){
                firstNum = stack.top();
                stack.pop();

                /* if it's an unary operator then we create the matching
                 * expression and calculate it */
                if ((token[0] == '-' || token[0] == '+') &&
                    (token.length()== 2)){
                    numAfterOp = postfixCalculateUnary(firstNum, token[0]);
                } else {
                    /* if it's an binary operator then we create the matching
                     * expression and calculate it */
                    secondNum = stack.top();
                    stack.pop();
                    numAfterOp = postfixCalculateBinary(secondNum,
                                                        token[0], firstNum);
                }
                //we add the value of the calculation to the stack
                stack.push(numAfterOp);

            }
                //if it's a number then we convert it from string to double
            else if(isNumber(token)){
                num = stod(token);
                stack.push(num);
            }
        }
    }
    //return new Value that equal to the whole calculation
    return new Value(stack.top());
}

//keep each var and it's value in a map
void Interpreter::setVariables(string str){
    string varName;
    string num;

    unsigned int i = 0;
    while (i < str.length()){
        /* if we reached the last char and it's equal to';' then we know that we
         * finished the variable placement */
        if ((i+1) == str.length() && str[i] == ';')
            break;


        //find the name of the variable
        while (str[i] != '='){
            if (str[i] != ';'){
                varName += str[i];
            }
            i++;
        }

        /* if there is == in the string or a var without a value then it's a bad
         * input */

        if (str[i+1] == '=' || str[i+1] == ';' || str[i+1] == '\0'){

            throw "bad input";
        }


        //find the value of the variable
        while (str[i] != ';' && str[i] != '\0'){
            if (str[i] != '='){
                num += str[i];
            }
            i++;
        }

        checkValidSet(varName, num);

        //add new variable to the map
        if (mapping.count(varName) == 0){
            mapping.insert(pair<string, string>(varName, num));
        } else {
            //update the value of variable in the map
            mapping[varName] = num;
        }

        varName = "";
        num = "";

    }
}

//check that each name and value of variable is suitables with the conditions
void Interpreter::checkValidSet(string varName, string value){
    char c = varName[0];
    //if the first char isn't a '_' or a letter then it's a bad input
    if (c < 'A' || (c > 'Z' && c < 'a' && c != '_') || c > 'z'){
        throw "bad input";
    }


    /* if their is a char that isn't a '_' or a letter or a number then it's a
     * bad input */
    for (unsigned int i = 0; i < varName.length(); i++){
        c = varName[i];
        if ((c != '.' && c < '0') || (c > '9' && c < 'A') ||
            (c > 'Z' && c < 'a' && c != '_') || c > 'z'){
            throw "bad input";
        }

    }

    //if the value isn't contains just s numbers then it's a bad input
    for (unsigned int i = 0; i < value.length(); i++){
        c = value[i];
        //the first char of the number must be a digit
        if (i == 0 && (c < '0' || c > '9') && c != '-')
            throw "bad input";
            //the other char of the number must be a '.' or a digit
        else if (i != 0 && (c < '0' || c > '9') && c != '.')
            throw "bad input";
    }
}

/* check that each char in the string expression is only an operator or a number
 * or a '(' or a ')' */
void Interpreter::checkValidExp(string str){
    for (unsigned int i = 0; i < str.length(); i++){
        if (!isOperator(str[i]) && str[i] != '\0' && str[i] != '('
            && str[i] != ')' && str[i] != '.' && (str[i] < '0' || str[i] > '9'))
        {
            throw "bad input";
        }

        if (isOperator(str[i]) && str[i+1] != '\0' && isOperator(str[i+1])){
            throw "bad input";
        }
    }
}


// the method returns true if there is a double operator of form ++ or --.
// else false
bool Interpreter::isDoubleOperator(string infix) {
    for (unsigned int i = 0; i < infix.length() - 1; i++) {
        if ((infix[i] == '+' && infix[i + 1] == '+') || (infix[i] == '-' && infix[i + 1] == '-'))
            return true;
    }
    return false;
}


// the method converts the infix to be with x+1 or x-1 instead of x++ or x--
string Interpreter::noDoubleOperator(string infix) {
    if (!isDoubleOperator(infix)) {
        return infix;
    }
    int len = infix.size();
    if (infix[0] == '(' && infix[len - 1] == ')') {
        infix = infix.substr(1, len - 2);
        len = infix.size();
    }
    string newInfix = "";
    int flag = 0;

    if (len > 2) {
        if ((infix[0] == '+' && infix[1] == '+') || (infix[len - 1] == '+' && infix[len - 2] == '+')) {
            newInfix = "(1+";
            if (infix[0] == '+') {
                flag = 1;
            } else {
                flag = 2;
            }
        } else if ((infix[0] == '-' && infix[1] == '-') || (infix[len - 1] == '-' && infix[len - 2] == '-')) {
            newInfix = "(-1+";
            if (infix[0] == '-') {
                flag = 1;
            } else {
                flag = 2;
            }
        }

        if (flag == 1) {
            for (int i = 2; i < len; i++) {
                newInfix += infix[i];
            }
        } else if (flag == 2) {
            for (int i = 0; i < len - 2; i++) {
                newInfix += infix[i];
            }
        }
        newInfix += ')';
    }
    return newInfix;
}


