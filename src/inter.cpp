#include <iostream>
#include <bits/stdc++.h>
using namespace std;

enum LEXEM_TYPES {
    NUMBER,
    VARIABLE,
    OPER
};

//This is used for determine what type of operator we have. 

enum OPERATOR {
    COMMA ,ARRAY, SQUARELBRACKET, SQUARERBRACKET, IF, THEN, ELSE, ENDIF, WHILE, ENDWHILE,
    LBRACKET, RBRACKET, ASSIGN, COLON,
    OR, AND, BITOR, XOR, BITAND, EQ, NEQ, LEQ, LT, GEQ, GT, SHL, SHR, MOD,
    PLUS , MINUS,
    MULT, DIV,
    PRINT, GOTO, ARRAY_REAL
};

//This priority of operators in OPERATOR
int PRIORITY [] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1,-1, 0, -1,
    1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7,8, 8, 10,
    9, 9,
    10 , 10, -1, -1, -1
};

OPERATOR LVALUED [] = {ASSIGN, PRINT, COLON, GOTO, IF , THEN, ELSE, ENDIF, WHILE, ENDWHILE};

//This is used for parsing string on lexesms. If we find substring in this array - we find an operator!. 
string OPERTEXT [] = {
    ",", "array", "[", "]","if", "then", "else", "endif", "while", "endwhile",
    "(", ")", ":=", ":",
    "or", "and", "|", "^", "&", "==", "!=", "<=", "<", ">=", ">", "<<", ">>", "%",
    "+" , "-" ,
    "*", "/",
    "print", "goto"
};

//this maps used for determine tables of rows, maps and arrays respectively
map<string, int> labels;
map<string, int> Vtable;
map<string, vector<int>> Atable;

//this is the main interface of the program.
//This devided on operators, numbers and variables
class Lexem {
public: 
    Lexem () {};
    virtual void print () = 0;
    virtual LEXEM_TYPES check_type () = 0;
    virtual int getValue() = 0;  //comment for the functionx
};

class Pointer : public Lexem {
public:
    virtual void setValue(int num) = 0;
};

//This is variable that has name. With name we can get a variable located in Vtable.
class Variable : public Pointer {
    
public :
    string name;
    Variable (string rename) {
        name = rename;
    }
    int getValue () {
        return Vtable[name];
    }
    void setValue (int num) {
        Vtable[name] = num;
    }
    void print () {
        cout << name; 
    }
    string getName () {
        return name;
    }
    LEXEM_TYPES check_type () {
        return VARIABLE;
    }
    bool inLabelTable() {
        if (labels.find(name) != labels.end()) {
            return true;
        }
        else {
            return false;
        }
    }
};

//this function create new array in array table 
void addArray (string name, int len) {
    Atable[name] = vector<int>(len);
}


//this class provided numbers work
class Number : public Lexem {
    int value;
public:
    Number ( int num ) {
        value = num;
    }
    int getValue () {
        return value;
    }
    void print () {
        cout <<  value;
    }
    LEXEM_TYPES check_type () {
        return NUMBER;
    }
};

//this class provided operators work.
//There is getValue() function that inmplement appropriate operations
//Also, there is getPriority() that returns approprate priority from PRIORITY[]. 
class Oper : public Pointer {
public:
    OPERATOR opertype;
    Oper (int op) {
        opertype = (OPERATOR)op;
    }
    OPERATOR getType() {
        return opertype;
    }
    void print() {
        cout << OPERTEXT[(int)opertype];
    }
    int getValue() {
        return opertype;
    }
    void setValue(int num) {}
    int getValue(Lexem *operand1, Lexem *operand2) {
        if (opertype == PLUS) {
            return ( operand1->getValue() + operand2->getValue() ); 
        }
        if (opertype == MINUS) {
            return ( -operand1->getValue() + operand2->getValue() );
        }
        if (opertype == MULT) {
            return ( operand1->getValue() * operand2->getValue() );
        }
        if (opertype == ASSIGN) {
            ((Pointer *)operand2)->setValue(operand1->getValue());
            return operand2->getValue();
        }
        if (opertype == DIV) {
            return (operand2->getValue() / operand1->getValue());
        }
        if (opertype == BITOR) {
            return (operand2->getValue() | operand1->getValue());
        }
        if (opertype == OR) {
            return (operand2->getValue() || operand1->getValue());
        }
        if (opertype == AND) {
            return (operand2->getValue() && operand1->getValue());
        }
        if (opertype == XOR) {
            return (operand2->getValue() ^ operand1->getValue());
        }
        if (opertype == BITAND) {
            return (operand2->getValue() & operand1->getValue());
        }
        if (opertype == EQ) {
            return (operand2->getValue() == operand1->getValue());
        }
        if (opertype == NEQ) {
            return (operand2->getValue() != operand1->getValue());
        }
        if (opertype == LEQ) {
            return (operand2->getValue() <= operand1->getValue());
        }
        if (opertype == LT) {
            return (operand2->getValue() < operand1->getValue());
        }
        if (opertype == GEQ) {
            return (operand2->getValue() >= operand1->getValue());
        }
        if (opertype == GT) {
            return (operand2->getValue() > operand1->getValue());
        }
        if (opertype == SHL) {
            return (operand2->getValue() << operand1->getValue());
        }
        if (opertype == SHR) {
            return (operand2->getValue() >> operand1->getValue());
        }
        if (opertype == MOD) {
            return (operand2->getValue() % operand1->getValue());
        }
    }
    int getValue(Lexem *operand) {
        if (opertype == PRINT) {
            cout << operand->getValue() << endl;
        }
    }
    LEXEM_TYPES check_type() {
        return OPER;
    }
    int getPriority() {
        return PRIORITY[opertype];
    } 

};

//This class provided goto works.
class Goto : public Oper {
    int row;
public:
    enum { UNDEFINED = -INT32_MAX };
    
    Goto(OPERATOR optype) : Oper(optype) {
        row = UNDEFINED;
    }
    void setRow (string name) {
        row = labels[name];
    }
    void setRow (int row) {
        Goto::row = row;
    }
    int getRow () {
        return row;
    }
    void print() {
        cout << "[row " << row << ">" << OPERTEXT[opertype] << "] ";
    }
};


//this class provided arrays work.
class Array : public Oper {
    string name;
    int index = 0;
public:
    void setIndex(int i) {
        Array::index = i; 
    }
    int getValue () {
        return Atable[name][index];
    }
    void setValue(int num) {
        Atable[name][index] = num;
    }
    Array (string name): Oper{35} {
        opertype = ARRAY_REAL;
        Array::name = name;   
    }
    void print () {
        cout << name;
    }
};

//this function provided check availability of array with current name in Atable.
bool inArray (string name) {
    if (Atable.find(name) != Atable.end()) {
        return true;
    } else {
        return false;
    }
}

//this function provided intialization of arrays.
void initArrays (vector <Lexem *> &infix, int row) {
    int start_index = 0;
    while (infix[start_index] == NULL) {
        start_index++;
    }
    if (infix[start_index]->check_type() == OPER && ((Oper *)infix[start_index])->getType() == ARRAY) { //this provided appeal of the arrays  
        infix[start_index] = nullptr;
        for (int i = 4 + start_index; i < (int)infix.size(); i++) {
            cout << i << endl;
            if (    infix[i - 1] == NULL && infix[i - 2] == NULL && infix[i - 3] == NULL && 
                    (infix[i]->check_type() == OPER && ((Oper *)infix[i])->getType() == COMMA)) {
                infix[i] = nullptr;
                cout << "COMMA" << endl;
                continue;
            }
            if (infix[i]->check_type() != OPER && (infix[i - 1] != NULL || infix[i - 2] != NULL || infix[i - 3] != NULL)) {
                continue;
            }
            if (infix[i]->check_type() == OPER && 
            (   infix[i - 1]->check_type() == NUMBER || infix[i - 1]->check_type() == VARIABLE) && 
                infix[i - 2]->check_type() == OPER && infix[i - 3]->check_type() == VARIABLE) {
                    if (((Oper *)infix[i])->getType() == SQUARERBRACKET && ((Oper *)infix[i - 2])->getType() == SQUARELBRACKET) {
                        addArray(((Variable *)infix[i - 3])->getName(), ((Number *)infix[i - 1])->getValue());
                        infix[i] = nullptr;
                        infix[i - 1] = nullptr;
                        infix[i - 2] = nullptr;
                        infix[i - 3] = nullptr;
                    }
                    else {
                        infix[i] == nullptr;
                    }
            } else {
                infix[i] = nullptr;
                continue;
            }
        }
    } else { //this provided intizalization of the arrays with operator "array"
        for (int i = 3 + start_index; i < (int)infix.size(); i++) {
            if (infix[i]->check_type() == OPER && 
            (   infix[i - 1]->check_type() == NUMBER || infix[i - 1]->check_type() == VARIABLE) && 
                infix[i - 2]->check_type() == OPER && infix[i - 3]->check_type() == VARIABLE) {
                    if (((Oper *)infix[i])->getType() == SQUARERBRACKET && ((Oper *)infix[i - 2])->getType() == SQUARELBRACKET) {
                        string name = ((Variable *)infix[i - 3])->getName();
                        if (inArray(name)) {
                            infix[i - 3] = new Array(name);
                        } else {
                            perror("You don't define Array on the row:");
                            cout << row << endl;
                            perror("Please define this with 'array' operator.");
                            exit(1);
                        }
                    }
            }
        }
    }
}
void initLabels ( std::vector <Lexem *> &infix , int row ) {
    for (int i = 1; i < (int)infix.size (); i++) {
        if (    (infix[i - 1]->check_type() == VARIABLE) &&
                (infix[i]->check_type() == OPER) ) {
            Variable * lexemvar = ( Variable *) infix [i - 1];
            Oper * lexemop = ( Oper *) infix[i];
            if (lexemop->getType() == COLON) {
                labels[lexemvar->getName()] = row;
                //delete infix [i - 1];
                //delete infix [i];
                infix [i - 1] = nullptr ;
                infix [i] = nullptr ;
                i++;
            }
        }
    }
}

//this function parsing:operators, variables and numbers.  
vector<Lexem *> parseLexem (string row) {
    int current_int = 0;
    string current_string = "";
    Lexem *a;    
    vector<Lexem *> infix;
    
    for (int i = 0; i < row.size(); ++i) {//this piece of code provided operators parsing
        int n = sizeof(OPERTEXT) / sizeof(std::string); 
        string subcodeline = ""; 
        current_string = "";
        current_int = 0;
        int sub_opertext_flag = 0; //this flag switches on 1, every time when we find operator
        for (int op = 0; op < n ; op++) {
            string subcodeline = row.substr(i, OPERTEXT[op].size());
            if (OPERTEXT[op] == subcodeline) {
                OPERATOR oper = (OPERATOR)op;
                Lexem *element_for_paste;
                if (oper == GOTO || oper == IF || oper == ELSE || 
                    oper == WHILE || oper == ENDWHILE) {
                    element_for_paste = (Goto *)(new Oper(op));
                } else {
                    element_for_paste = new Oper(op);  
                }
                infix.push_back(element_for_paste);
                i += OPERTEXT[op].size() - 1;
                sub_opertext_flag = 1;
                break;
            }
        }

        if (sub_opertext_flag == 0) {
            if (isdigit(row[i])) { //this piece of code provided numbers parsing
                while (i != row.size()  && isdigit(row[i])) {
                    current_int *= 10;
                    current_int += (row[i] - '0');
                    i++;
                }
                a = new Number(current_int);
                infix.push_back(a);
                i--;
            }  else if (row[i] == ' ') {
                continue;
            } else if (isalpha(row[i])) {//this piece of code provided variables parsing(alse used for arrays)
                while (i != row.size() && isalpha(row[i])) {
                    current_string += row[i];
                    i++;
                }
                infix.push_back(( new Variable (current_string)));
                if(Vtable[current_string] == 0){ 
                    ((Variable *)infix[infix.size() - 1])->setValue(0);
                } else { 
                    Vtable[current_string] = ((Variable *)infix[infix.size() - 1])->getValue(); 
                }
                i--;
            }
        }
    }
    return infix;
}

//this function  is used for going to current row
void GoinGotoAndLabel (Variable *lexemvar, std::stack<Oper *> &stack) {
    if (stack.top()->getType() == GOTO) {
        Goto *lexemgoto = (Goto *)stack.top();
        lexemgoto->setRow(lexemvar->getName());
    }
}

//this function initialize marks for correct work of Goto
void initJumps (vector < vector <Lexem *> >infixLines) {
    stack <Goto *> stackIfElse;
    stack <Goto *> stackWhile;
    for (int row  = 0; row < (int)infixLines.size(); row++) {
        for (int i = 0; i < (int)infixLines[row].size(); i++) {
            if (infixLines[row][i] == NULL) {
                continue;
            }

            if (infixLines[row][i]->check_type() == OPER) {
                Oper *lexemoper = (Oper *)infixLines[row][i];

                if (lexemoper->getType() == IF) {
                    stackIfElse.push((Goto *)lexemoper); 
                }

                if (lexemoper->getType() == ELSE) {
                    stackIfElse.top()->setRow(row + 1);
                    stackIfElse.pop();
                    stackIfElse.push((Goto *) lexemoper);
                }

                if (lexemoper->getType() == ENDIF) {
                    stackIfElse.top()->setRow(row + 1);
                    stackIfElse.pop();
                }
                if (lexemoper->getType() == WHILE) {
                    Goto *lexemgoto = (Goto *)lexemoper;
                    lexemgoto->setRow(row);
                    stackWhile.push(lexemgoto);
                }
                if(lexemoper->getType() == ENDWHILE) {
                    Goto * lexemgoto = (Goto *)lexemoper;
                    lexemgoto->setRow(stackWhile.top()->getRow());
                    stackWhile.top()->setRow(row + 1);
                    stackWhile.pop();
                }
            }
        }
    }
}

//this function builds postfix(if you need more details visit README)
vector <Lexem *> buildPostfix (vector <Lexem *>  infix) {
    vector <Lexem *> postfix;
    stack <Oper *> operators;  
    for (auto elem: infix) {
        if (elem ==  nullptr) {
            continue;
        }
        if (elem->check_type() == NUMBER) {
            postfix.push_back(elem);
        } else if (elem->check_type() == OPER) {
            if (operators.empty()) {
                operators.push((Oper *)elem);
            } else if (((Oper *)elem)->getType() == ARRAY_REAL) {
                operators.push((Array *)elem);
            } else if (((Oper *)elem)->getType() == SQUARERBRACKET) {
                while(((Oper *)operators.top())->getType() != ARRAY_REAL) {
                        postfix.push_back(operators.top());
                        operators.pop();
                }
                postfix.push_back(operators.top());
                operators.pop();
            } else if (((Oper  *)elem)->getType() == SQUARELBRACKET) {
                continue;
            } else if (((Oper *)elem)->getType() == ENDIF) {
                continue;
            } else if (((Oper*)elem)->getType() == RBRACKET) {
                postfix.push_back(operators.top());
                operators.pop(); 
                while(((Oper *)operators.top())->getType() != LBRACKET) {
                        postfix.push_back(operators.top());
                        operators.pop();
                }
                operators.pop();
            } else if (     ((((Oper *)elem)->getType() == LBRACKET) || 
                            operators.top()->getPriority() <= ((Oper *)elem)->getPriority())) { 
                operators.push ((Oper *)elem);
            } else {
                postfix.push_back(operators.top());
                operators.pop();
                operators.push((Oper *)elem);
            }
        }
        else {
            Variable *lexemvar = (Variable *) elem;
            if (lexemvar->inLabelTable()) {
                GoinGotoAndLabel(lexemvar, operators);
            }
            else {
                postfix.push_back(elem);
            }
        }
    }
    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop(); 
    }
    return postfix;
}



//in this function we execute all operations 
int evaluatePostfix (vector <Lexem *> postfix, int row, bool rvalue) {
    stack <Lexem *> numbers;
    Lexem *operand1;
    Lexem *operand2;
    for (auto elem: postfix) {
        if (elem == NULL) {
            continue;
        } else if (elem->check_type() == NUMBER) {
            numbers.push((Number *)elem);
        } else if (elem->check_type() == OPER ) {
            Oper *lexemop = (Oper *)elem;
            if (lexemop->getType() == GOTO || 
                lexemop->getType() == ELSE ||
                lexemop->getType() == ENDWHILE) {
                Goto *lexemgoto = (Goto *)lexemop;
                return lexemgoto->getRow();
            } else if (lexemop->getType() == ARRAY_REAL) {
                Lexem *top = (Array *)lexemop;
                ((Array *)lexemop)->setIndex(numbers.top()->getValue());
                numbers.pop();
                numbers.push(top);
            } else if (lexemop->getType() == THEN) {
                continue;
            }else if (lexemop->getType() == IF || lexemop->getType() == WHILE) {
                Goto *lexemgoto = (Goto *)lexemop;
                int rvalue = numbers.top()->getValue();
                numbers.pop();
                if (!rvalue) {
                    return lexemgoto->getRow(); 
                }
            } else if (((Oper *)elem)->getType() == PRINT) {
                operand1 = numbers.top();
                numbers.pop();
                ((Oper *)elem)->getValue(operand1);    
            } else {
                operand1 = numbers.top();
                numbers.pop();
                operand2 = numbers.top();
                numbers.pop();
                int result = ((Oper *)elem)->getValue(operand1, operand2);
                numbers.push(new Number(result));
            }
        } else {
            numbers.push(((Lexem *)elem));
        }
    }
    cout << numbers.top()->getValue() << endl;   
    return row + 1;  
}

bool realTime (vector <Lexem *> &postfix) {
    for (auto const elem : postfix) {
        for (auto const lvalued_elem : LVALUED) {
            if (elem->check_type() == OPER && ((Oper *)elem)->getType() == lvalued_elem) {
                return true;
            }
        }
    }
    return false;
}

int main (void) {
    string  codeline;
    vector < vector <Lexem *> > infixLines;
    vector < vector <Lexem *> > postfixLines;
    int value;
    int row = 0;
    cout << ">>>";
    while ( getline( cin, codeline ) ) {
        if (codeline == "end") {
            break;
        }
        infixLines.push_back(parseLexem(codeline));
        initLabels(infixLines[row], row);
        initArrays(infixLines[row], row);
    /*cout << "INFIX" << endl;
    for (int row = 0; row < (int)infixLines.size(); ++row) {    
        for(auto elem: infixLines[row]) {
            if (elem != NULL) {
                elem->print();
            }            
        }
        cout << endl;
    }*/
        initJumps(infixLines);

        postfixLines.push_back(buildPostfix(infixLines[row]));
        bool rvalue = realTime(postfixLines[row]);
        if (!rvalue) {
            evaluatePostfix(postfixLines[row], row, rvalue);
        }
        row++;
        cout << ">>>";
    }
    /*cout << "POSTFIX" << endl;
    for (int row = 0; row < (int)postfixLines.size(); ++row) {
        for (const auto elem: postfixLines[row]) {
            if (elem != NULL) {
                elem->print();
            }
        }
        cout << endl;
    }*/
    row = 0;
    while (0 <= row && row < (int)postfixLines.size()) {
        row = evaluatePostfix(postfixLines[row], row, false);
    }
    return 0;
}
