#ifndef __GLOBALS_H__
#define __GLOBALS_H__
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>    

enum LEXEM_TYPES {
    NUMBER,
    VARIABLE,
    OPER
};

enum OPERATOR {
    COMMA ,ARRAY, SQUARELBRACKET, SQUARERBRACKET, IF, THEN, ELSE, ENDIF, WHILE, ENDWHILE,
    LBRACKET, RBRACKET, ASSIGN, COLON,
    OR, AND, BITOR, XOR, BITAND, EQ, NEQ, LEQ, LT, GEQ, GT, SHL, SHR, MOD,
    PLUS , MINUS,
    MULT, DIV,
    PRINT, GOTO, ARRAY_REAL
};

//This is used for determine what type of operator we have. 
extern int PRIORITY[35];

extern OPERATOR LVALUED[10];

extern std::string OPERTEXT[34];

//This is used for parsing string on lexems. If we find substring in this array - we find an operator!. 
//this maps used for determine tables of rows, maps and arrays respectively
extern std::map<std::string, int> labels;
extern std::map<std::string, int> Vtable;
extern std::map<std::string, std::vector<int>> Atable;

#endif
//this is the main interface of the program.
//This devided on operators, numbers and variables


#ifndef __CCLASS_H__
#define __CCLASS_H__

class Lexem {
public: 
    Lexem();
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
public:
    std::string name;
    Variable (std::string rename);
    int getValue();
    void setValue (int num);
    void print();
    std::string getName();
    LEXEM_TYPES check_type ();
    bool inLabelTable();
};

//this class provided numbers work
class Number : public Lexem {
    int value;
public:
    Number ( int num );
    int getValue ();
    void print ();
    LEXEM_TYPES check_type ();
};

//this class provided operators work.
//There is getValue() function that inmplement appropriate operations
//Also, there is getPriority() that returns approprate priority from PRIORITY[]. 
class Oper : public Pointer {
public:
    OPERATOR opertype;
    Oper (int op);
    OPERATOR getType();
    void print();
    int getValue();
    void setValue(int num);
    int getValue(Lexem *operand1, Lexem *operand2);
    int getValue(Lexem *operand);
    LEXEM_TYPES check_type();
    int getPriority();
};

//This class provided goto works.
class Goto : public Oper {
    int row;
public:
    enum { UNDEFINED = -INT32_MAX };
    Goto(OPERATOR optype);
    void setRow (std::string name);
    void setRow (int row);
    int getRow ();
    void print();
};


//this class provided arrays work.
class Array : public Oper {
    std::string name;
    int index = 0;
public:
    void setIndex(int i);
    int getValue ();
    void setValue(int num);
    Array (std::string name);
    void print ();
};

#endif

#ifndef __FUNCS_H__
#define __FUNCS_H__

bool inArray (std::string);
void initArrays (std::vector <Lexem *> &, int);
void initLabels (std::vector <Lexem *> &, int);
std::vector<Lexem *> parseLexem (std::string);
void GoinGotoAndLabel (Variable , std::stack<Oper *>);
void initJumps (std::vector < std::vector <Lexem *> >);
std::vector <Lexem *> buildPostfix (std::vector <Lexem *>);
int evaluatePostfix (std::vector <Lexem *>, int, bool);
bool realTime (std::vector <Lexem *> &); 
void addArray (std::string name, int len);
#endif
