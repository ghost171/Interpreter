# Description

This porject - is interpreter with Pascal-like language implemented in C++.

# Possibilities

## Variables

It can allocates memory for variables and assign them to rvalue or lvalue. 
Variables contains letters of latin alphabet.

Example:
     
    x:= 2
    y := x
    print y
    
The result of the program: //Execution result:
    
    2

## Print
  Print can output the values of variables, numbers and expressions.
  
Example:

    x:=2
    print x

The result of the program:

    2

## Goto

You can jump through the code with "goto". You can write "goto" and then the Name of mark that you want jump. 
After that you must write this mark and then the colon: ":". The program jump to the row of code that you marked.

Example:
  
    x:=1
    goto L
    x := x + 2
    L: print x

The result of the program:
     
    1

## Cycles

You can use cycles with "while" lexem. It had been executing a bit of code that wrapped into begin and end of "while".
The begin of "while" marked as then.
Then end of "while" marked as endwhile.

Example:
  
    i:=0
    while i < 6 then
      i:=i+1
    print i

The result of the program:

    6

## The conditions

You can use conditions with lexem "if". When you wrote "if" you must must write the condition.
When you had written the condition you must write "then" and after that, wrote the piece of code that executed when that condition is true. 
Also, you can write "else" when you want describe the piece of code that executed when that condition is false.

Example:
  
    x := 1
    if x == 1 then
      x := x + 1
      print x
    else 
      x := x + 2
      print x

The result of the program:

    2

## Arrays

You can declare arrays with service word var. For example:
     
     var a[2]
where, a is name of your declared array , 2- is a memory that you need your array.

You can make operations with array elements. For example:

     a[0] := 2
     a[1] := a[1] + a[0]

# Installation
    git clone https://github.com/ghost171/Interpreter
    make
    bin/inter
# Realization
## Steps of interpritating 
### Lexem Dividing
When we get the rows of code we need to convert it to array of Lexems. Lexem can be number, variable or operator. //which are implemented in ParseLexem()
There are in ParseLexem() function.
###  Build Postfix
IN this step of program we build the postfix by available infix that we get Lexem Dividing step. 
We have operators stack and when the program see the operator it pushes this on stack. 
If that is a number or variable it pushes it in Lexems array. 
If priority of this operator greater than operator in the top the stack we push operator at the top of thge stack in Lexems array, and the start operator in the stack.

## Realization of types lexems 
### Numbers implementation
For numbers we have "Number" class that contain value of this number. 
When number parsing we supporting by condition that marks number as string of digits.
### Variables implementation
Variables implemented in  class Variable. This class have methods for getting values of declared variables.
There is Variable table(Vtable) to moved their values and names into this.
### Goto implementation
For this task was created a table with rows and names of marks that tell us where we have to go.
In EvaluatePostfix() the program returns the number of row that we have to go. 
If on the row haven't been a "goto" operator this function just return row + 1. 
But if "goto" contains in the row, this function return number of row, that contains mark denoted row that goto want to go.
Also, we have initLabels() to initialize this rows. 
     
     void initLabels ( std::vector <Lexem *> &infix , int row ) {
         for (int i = 1; i < (int)infix.size (); i++) {
             if (    (infix[i - 1]->check_type() == VARIABLE) &&
                     (infix[i]->check_type() == OPER) ) {
                 Variable * lexemvar = ( Variable *) infix [i - 1];
                 Oper * lexemop = ( Oper *) infix[i];
                 if (lexemop->getType() == COLON) {
                     labels[lexemvar->getName()] = row;
                     infix [i - 1] = nullptr ;
                     infix [i] = nullptr ;
                     i++;
                 }
             }
         }
     }
This function is used to go to the current row:
         
         void GoinGotoAndLabel (Variable *lexemvar, std::stack<Oper *> &stack) {
              if (stack.top()->getType() == GOTO) {
                  Goto *lexemgoto = (Goto *)stack.top();
                  lexemgoto->setRow(lexemvar->getName());
                   }
               }
### Condition implementation
We use goto to implement this. When the program see count the result of condition it go to the row with "then" operator
or , if the result of the condition is false to the row with "else" Operator.
### Cycles implementation
We use goto for it, like in condition realization, 
because "while" is an operator that must executed a piece of code before 
it found false result of the condition after "while" operator.
