#include <iostream>
#include <bits/stdc++.h>
using namespace std;

enum LEXEM_TYPES {
    NUMBER,
    VARIABLE,
    OPER
};

enum OPERATOR {
    RBRACKET, LBRACKET,
    ASSIGN, 
    OR, AND, BITOR, XOR, BITAND, EQ, NEQ, LEQ, LT, GEQ, GT, SHL, SHR, MOD,
    PLUS , MINUS,
    MULT, DIV,
    PRINT, GOTO
};

int PRIORITY [] = {
    -1,-1,
    0,
    1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7,8, 8, 10,
    9, 9,
    10 , 10, -1 
};

string OPERTEXT [] = {
    "(", ")",
    ":=" ,
    "or", "and", "|", "^", "&", "==", "!=", "<=", "<", ">=", ">", "<<", ">>", "%",
    "+" , "-" ,
    "*", "/",
    "print"
};

class Lexem {
public: 
    Lexem () {};
    virtual void print () = 0;
    virtual LEXEM_TYPES check_type () = 0;
};

class Evaluatable : public Lexem {
public:
Evaluatable () {};
    virtual int getValue() = 0;
};

class Variable : public Evaluatable {
    int value; // delete
    string name;
public :
    Variable (int num) { //delete
        value = num;
    }
    Variable (string rename) {
        name = rename;
        value = 0;
    }
    int getValue () {
        return value;// delete
        return table[value]
    }
    void setValue (int num) {
        value = num;
        //table[name] = value
    }
    void print () {
        cout << value; //table[name]
    }
    string getName () {
        return name;
    }
    LEXEM_TYPES check_type () {
        return VARIABLE;
    }
};

map<string, int> table;

class Number : public Evaluatable {
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

class Oper : public Lexem {
    OPERATOR opertype;
public:
    Oper (int op) {
        //opertype = (OPERATOR)op;
        if (op == 1) {
            opertype =  RBRACKET;
        }
        if (op == 0) {
            opertype = LBRACKET;
        }
        
        if (op == 2) {
            opertype = ASSIGN;
        }
        if (op == 3) {
            opertype = OR;
        }
        if (op == 4) {
            opertype = AND;
        }
        if (op == 5) {
            opertype = BITOR;
        }
        if (op == 6) {
            opertype = XOR;
        }
        if (op == 7) {
            opertype = BITAND;
        }
        if (op == 8) {
            opertype = EQ;
        }
        if (op == 9) {
            opertype = NEQ;
        }
        if (op == 10) {
            opertype = LEQ;
        }
        if (op == 11) {
            opertype = LT;
        }
        if (op == 12) {
            opertype = GEQ;
        }
        if (op == 13) {
            opertype = GT;
        }
        if (op == 14) {
            opertype = SHL;
        }
        if (op == 15) {
            opertype = SHR;
        }
        if (op == 16) {
            opertype = MOD;
        }
        if (op == 17) {
            opertype = PLUS;
        }
        if (op == 18) {
            opertype = MINUS;
        }
        if (op == 19) {
            opertype = MULT;
        }
        if (op == 20) {
            opertype = DIV;
        }
        if (op == 22) {
            opertype == PRINT;
        }
    }
    OPERATOR getType() {
        return opertype;
    }
    void print() {
        //OperText[(int)opertype]
        if (opertype == ASSIGN) {
            cout << ":=";
        }
        if (opertype == MINUS) {
            cout << "-";
        }
        if (opertype == PLUS) {
            cout << "+";
        }
        if (opertype == MULT) {
            cout <<  "*";
        }
        if(opertype == LBRACKET) {
            cout <<  "(";
        }
        if (opertype == RBRACKET) {
            cout <<  ")";
        }
        if (opertype == DIV) {
            cout << "/";
        }
        if (opertype == BITOR) {
            cout << "|";
        }
        if (opertype == PRINT) {
            cout << "print";
        }
    }
    int getValue(Evaluatable *operand1, Evaluatable *operand2) {
        if (opertype == PLUS) {
            return ( operand1->getValue() + operand2->getValue() ); 
        }
        if (opertype == MINUS) {
            return ( - operand1->getValue() + operand2->getValue() );
        }
        if (opertype == MULT) {
            return ( operand1->getValue() * operand2->getValue() );
        }
        if (opertype == ASSIGN) {
            ((Variable *)operand2)-> setValue(operand1->getValue());
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
    int getValue(Evaluatable *operand) {
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


// bool std::isalpha(char)
int isletter (char ch) {
    if (ch <= 'z' && ch >= 'a') {
        return 1;
    }
    else {
        return 0;
    }
}

vector<Lexem *> parseLexem (string row) {
    int current_int = 0;
    string current_string = "";
    Lexem *a;    
    vector<Lexem *> infix;
    
    for (int i = 0; i < row.size(); ++i) {
        int n = sizeof(OPERTEXT) / sizeof(std::string); 
        string subcodeline = ""; 
        current_string = "";
        current_int = 0;
        int sub_opertext_flag = 0; //this flag switches on 1, every time when we find operator
        for (int op = 0; op < n ; op++) {
            string subcodeline = row.substr(i, OPERTEXT[op].size());
            if (OPERTEXT[op] == subcodeline) {
                Lexem * element_for_paste = new Oper(op);  
                infix.push_back(element_for_paste);
                i += OPERTEXT[op].size() - 1;
                sub_opertext_flag = 1;
                break;
            }
        }
        if (sub_opertext_flag == 0) {
            if (isdigit(row[i])) {
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
            } else if (isletter(row[i])) {
                while (i != row.size() && isletter(row[i])) {
                    current_string += row[i];
                    i++;
                }
                infix.push_back(((Evaluatable *) new Variable (current_string)));
                if(table[current_string] == 0){ 
                    infix.top()->setValue(0);
                }
                else { table[current_string] = infix.top()->getValue(); }
                i--;
            }
        }
    }
    return infix;
}

vector <Lexem *> buildPostfix (vector <Lexem *>  infix) {
    vector <Lexem *> postfix;
    stack <Oper *> operators;  
    for (auto elem: infix) {
        if (elem->check_type() == NUMBER) {
            postfix.push_back(elem);
        } else if (elem->check_type() == OPER) {
            if (((Oper*)elem)->getType() == RBRACKET) {
                postfix.push_back(operators.top());
                operators.pop(); 
                while(((Oper *)operators.top())->getType() != LBRACKET) {
                        postfix.push_back(operators.top());
                        operators.pop();
                }
                operators.pop();
            } else if (operators.empty()) {
                operators.push((Oper *)elem);
            } else if (     (operators.top()->getPriority() <= ((Oper *)elem)->getPriority()) ||      
                            (((Oper *)elem)->getType() == LBRACKET)) { 
                operators.push ((Oper *)elem);
            } else {
                postfix.push_back(operators.top());
                operators.pop();
                operators.push((Oper *)elem);
            }
        }
        else {
            postfix.push_back(elem);
        }
    }
    while (!operators.empty()) {
        postfix.push_back(operators.top());
        operators.pop(); 
    }
    return postfix;
}

int evaluatePostfix ( vector <Lexem *> postfix) {
    stack <Evaluatable *> numbers;
    Evaluatable *operand1;
    Evaluatable *operand2;
    for (auto elem: postfix) {
        if (elem->check_type() == NUMBER) {
            numbers.push((Number *)elem);
        } else if (elem->check_type() == OPER && ((Oper *)elem)->getType() != PRINT) {
            operand1 = numbers.top();
            numbers.pop();
            operand2 = numbers.top();
            numbers.pop();
            int result = ((Oper *)elem)->getValue(operand1, operand2);
            numbers.push(new Number(result));
        } else if (elem->check_type() == OPER && ((Oper *)elem)->getType() == PRINT) {
            cout << "T" << endl;
            operand1 = numbers.top();
            numbers.pop();
            ((Oper *)elem)->getValue(operand1);
        } else {
            numbers.push(((Evaluatable *)elem));
        }
    }
    return numbers.top()->getValue();  
}

int main (void) {
    string  codeline;
    vector <Lexem *> infix;
    vector <Lexem *> postfix;
    int value;
    while ( getline( cin, codeline ) ) {
        infix = parseLexem (codeline);
        postfix = buildPostfix (infix);
        value = evaluatePostfix (postfix); 
        for( auto elem: infix ) {
            elem->print();        
        }
        cout << endl;
        for( auto elem: postfix ) {
            elem->print();
        }
        cout << endl;
        cout << value << endl;
    }
    return 0;
}
