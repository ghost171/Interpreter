# Description

This porject - is interpreter from C++ language to another "Basic" language that has Pascal syntax.

# Possibilities

## Variables

It can allocates memory for variables and assign them to rvalue or lvalue. 
Variables contains letters of latin alphabet.

Example:
     
    x:= 2
    y := x
    print y
    
The result of the program:
    
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

# Installation
    git pull 
    cd bin
    ./inter
# Realization
## Steps of interpritating 
### Lexem Dividing
When we get the rows of code we need to convert it to array of Lexems. Lexem can be number, variable or operator. 
There are in ParseLexem() function.
###  Build Postfix
IN this step of program we build the postfix by available infix that we get Lexem Dividing step. 
We have operators stack and when the program see the operator it pushes this on stack. 
If that is a number or variable it pushes it in Lexems array. 
If priority of this operator greater than operator in the top the stack we push operator at the top of thge stack in Lexems array, and the start operator in the stack.

## Realization of types lexems 
### Numbers realization
For numbers we have "Number" class that contain value of this number. 
When number parsing we supporting by condition that marks number as string of digits.
### Variables realization


