# Lexical Analyzer

A small lexer written in C. It reads a source file character by character and
prints every token together with the category it belongs to — the first phase
any compiler performs on source code.

## Tokens recognized

| Category | Examples |
| --- | --- |
| Keyword | `int`, `char`, `float`, `double`, `if`, `else`, `for`, `while`, `return`, `void` |
| Identifier | any other alphanumeric/underscore word (`sum`, `x1`) |
| Number | integer literals |
| Arithmetic operator | `+ - * / %` |
| Relational operator | `< > <= >= != ==` |
| Assignment operator | `=` |
| Bracket | `( ) { } [ ]` |
| Delimiter | `;` `,` |
| Preprocessor line | `#include ...` |

A word is a **keyword** only if it matches the keyword table, otherwise it is an
**identifier**.

## Build & run

```sh
gcc -o lex main.c
./lex            # lex.exe on Windows
```

The program always opens `test.c` in the current directory (the call is
`fopen("test.c", "r")` in `main.c`). To analyze your own code, replace the
contents of `test.c` — or change that filename to anything you like.

## Sample run

Input `test.c`:

```c
#include<stdio.h>
#include "lex.h"
int main()
{
    int sum;
    for (x1 = 0; x1 <= 10; x1++)
    {
        sum=sum + x1;
    }
    return 0;
}
```

Output:

```
int --> Keyword
main --> Identifier
( --> Open Bracket
) --> Close Bracket
{ --> Open Bracket
int --> Keyword
sum --> Identifier
; --> Delimiter
for --> Keyword
( --> Open Bracket
x1 --> Identifier
= --> Assignment Operator
0 --> Number
; --> Delimiter
x1 --> Identifier
<= --> Relational Operator
10 --> Number
...
```

## Project structure

| File | Purpose |
| --- | --- |
| `lex.h` | Prototypes for the token classifiers |
| `main.c` | Lexer driver and all classifier functions |
| `test.c` | Sample input that gets tokenized |
