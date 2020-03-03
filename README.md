# Description

This porject - is interpreter from C++ language to another "Basic" language that has Pascal syntax.

#Possibilities

##Variables

It can allocates memory for variables and assign them to rvalue or lvalue. 
Variables contains letters of latin alphabet.

##Print
  Print can output the values of variables, numbers and expressions.
  
Example:

  x:=2
  print x

The result of the program:

  2

##Goto

You can jump through the code with "goto". You can write "goto" and then the Name of mark that you want jump. 
After that you must write this mark and then the colon: ":". The program jump to the row of code that you marked.

Example:
  
  x:=1
  goto L
  x := x + 2
  L: print x

The result of the program:
  1

##Cycles

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

##The conditions

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
  


