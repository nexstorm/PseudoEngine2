# Pseudocode Syntax
## Comments
```
// This is a comment
```
Comments begin with '//' and continue till the end of the line

## Variable declaration
```
DECLARE <name> : <data type>
```
Available data types:
- INTEGER
- REAL
- BOOLEAN
- CHAR
- STRING

Multiple variables of the same type can be declared with
```
DECLARE <var1>, <var2>, ... : <data type>
```

## Array declaration:
```
DECLARE <name> : ARRAY[<lower bound>:<upper bound>] OF <data type>
```
Note: The bounds are inclusive

Multi Dimensional arrays:
```
DECLARE <name> : ARRAY[<lb1>:<ub1>, <lb2>:<ub2>, ..., <lbn>:<ubn>] OF <data type>
```

## Accessing array elements
One-dimensional array:
```
myArray[index]
```
Multi-dimensional array:
```
myArray[index1, index2, ...]
```

## Variable assignment
```
<variable name> <- <value>
```
Assigning to an undefined variable will define and initialise it to the value assigned

## Assigning to array element
```
myArray[index] <- <value>
myArray[index1, index2, ...] <- <value>
```

## Constants
```
CONSTANT <name> = <value>
```

## Arithmetic operations
- \+ (Addition)
- \- (Subtraction)
- \* (Multiplication)
- / (Division)\
Result of division operator will always be of type `REAL`
- DIV - Integer division
- MOD - Modulus

Function style syntax may be used for DIV and MOD:
```
DIV(x, y)
MOD(x, y)
```

## Comparison operators
- \> (Greater than)
- \>= (Greater than or equal to)
- < (Less than)
- <= (Less than or equal to)
- = (Equal to)
- <> (Not equal to)

## Logical operators
- AND
- OR
- NOT

## String concatenation
```
<str1> & <str2>
```

## Selection statements
If statement:
```
IF <condition> THEN
    ...
ELSE IF <another condition> THEN
    ...
ELSE
    ...
ENDIF
```
- `ELSE IF` and `ELSE` statements are optional
- Any number of `ELSE IF` statements can be used

Case statement:
```
CASE OF <variable>
    <case 1> : ...
    <case 2> : ...
    ...
    <case n> : ...
    OTHERWISE: ...
ENDCASE
```
- `OTHERWISE` is optional
- cases may be expressions, e.g (var / 2 + 1)

## Loops
While loop:
```
WHILE <condition> DO
    ...
ENDWHILE
```
Loops until condition is false

Repeat until loop:
```
REPEAT
    ...
UNTIL <condition>
```
- Loops until the condition is true
- Condition is checked at the end of an iteration

For loop:
```
FOR <counterVariable> <- <startValue> TO <stopValue> STEP <stepValue>
    ...
NEXT counterVariable
```
- Initialises counterVariable to startValue and loops till it reaches stopValue, incrementing it by stepValue each iteration if provided, otherwise incrementing it by 1
- `STEP <stepValue>` and `counterVariable` after `NEXT` are optional

## Procedures
Procedure with no paramaters:
```
PROCEDURE <name>
    ...
ENDPROCEDURE
```

Procedure with parameters:
```
PROCEDURE <name>([BYREF | BYVAL] <parameterName> : <data type>, <parameter2Name> : <data type>, ...)
    ...
ENDPROCEDURE
```
- `BYREF` - pass parameters by reference
- `BYVAL` - pass parameters by value
- If `BYREF` or `BYVAL` is not speified, `BYVAL` will be used as the default

## Calling procedures
No parameters:
```
CALL <procedureName>
OR
CALL <procedureName>()
```

With parameters:
```
CALL <procedureName>(<parameter1>, <parameter2>, ...)
```

## Functions
```
FUNCTION <name>(...) RETURNS <data type>
    ...
ENDFUNCTION
```
- Syntax for function parameters are identical to those of procedures
- Functions must have a `RETURN` statement that returns a value of the specified data type

## Calling functions
```
<functionName>(<parameter1>, <parameter2>, ...)
```
Function calls may be used inside expressions since they return a data type

## In-built functions
```
// Returns the length of a string
LENGTH(s : STRING) RETURNS INTEGER

// Returns the left n characters of a string
LEFT(s : STRING, n : INTEGER) RETURNS STRING

// Returns the right n characters of a string
RIGHT(s : STRING, n : INTEGER) RETURNS STRING

// Returns a string of length y starting at x
MID(s : STRING, x : INTEGER, y : INTEGER) RETURNS STRING

// Converts all alphabetical characters into uppercase
TO_UPPER(s : STRING) RETURNS STRING

// Converts all alphabetical characters into lowercase
TO_LOWER(s : STRING) RETURNS STRING

// Converts a number into a string
NUM_TO_STR(x : REAL) RETURNS STRING

// Converts a string into a number, returning 0 if the number is invalid
STR_TO_NUM(s : STRING) RETURNS REAL

// Returns whether a string is a valid number
IS_NUM(s : STRING) RETURNS BOOLEAN

// Converts a character into lowercase if it is alphabetic
LCASE(c : CHAR) RETURNS CHAR

// Converts a character into uppercase if it is alphabetic
UCASE(c : CHAR) RETURNS CHAR

// Returns the ASCII value of a character
ASC(c : CHAR) RETURNS INTEGER

// Returns the character representation of an ASCII value
CHR(x : INTEGER) RETURNS CHAR

// Returns the integer part of a real(floor)
INT(x : REAL) RETURNS INTEGER

// Returns a random number from 0 to x inclusive
RAND(x : INTEGER) RETURNS REAL
```

# Examples
See [tests](./tests)
