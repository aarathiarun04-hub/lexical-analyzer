#ifndef LEX_H
#define LEX_H
#include<stdio.h>
void checkWord(FILE *fp, char ch);
void checkNumber(FILE *fp, char ch);
void checkOperator(FILE *fp, char ch);
void checkRelational(FILE *fp, char ch);
void checkBracket(char ch);
void checkDelimiter(char ch);
void checkPreprocessor(FILE *fp);
#endif