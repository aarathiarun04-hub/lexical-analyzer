//open test.c,read it,call func
#include<stdio.h>
#include <string.h>
#include <ctype.h>
#include "lex.h"
char *keywords[] = {"int","char","float","double","if","else","for","while","return","void"};
int isKeyword(char word[])
{
    int i;
    for(i = 0; i < 10; i++)
    {
        if(strcmp(word, keywords[i]) == 0)
            return 1;
    }
    return 0;
}
void checkWord(FILE *fp, char ch)
{
    char word[100];
    int j = 0;
    while (isalnum(ch) || ch == '_')
    {
        word[j++] = ch;
        ch = fgetc(fp);
    }
    word[j] = '\0';
    if (isKeyword(word))
        printf("%s --> Keyword\n", word);
    else
        printf("%s --> Identifier\n", word);

    if (ch != EOF)
        fseek(fp, -1, SEEK_CUR);
}
void checkRelational(FILE *fp, char ch)
{
    char next = fgetc(fp);//points next char 
    if((ch=='<' && next=='=') ||(ch=='>' && next=='=') || (ch=='!' && next=='=') ||(ch=='=' && next=='='))
    {
        printf("%c%c --> Relational Operator\n", ch, next);
    }
    else
    {
        if(ch == '=')
            printf("%c --> Assignment Operator\n", ch);
        else
            printf("%c --> Relational Operator\n", ch);

        if(next != EOF)
            fseek(fp, -1, SEEK_CUR);
    }
}
void checkBracket(char ch)
{
    if(ch=='(' || ch=='{' || ch=='[')
        printf("%c --> Open Bracket\n", ch);
    else
        printf("%c --> Close Bracket\n", ch);
}
void  checkDelimiter(char ch)
{
    printf("%c -->Delimiter\n", ch);
}
void checkOperator(FILE *fp, char ch)
{
    char next = fgetc(fp);

    if(ch == '+' && next == '+')
        printf("++ --> Increment Operator\n");
    else if(ch == '-' && next == '-')
        printf("-- --> Decrement Operator\n");
    else
    {
        printf("%c --> Operator\n", ch);
        if(next != EOF)
            fseek(fp, -1, SEEK_CUR);
    }
}
void checkNumber(FILE *fp,char ch)
{
    char num[100];
    int j = 0;

    while(isdigit(ch))
    {
        num[j++] = ch;
        ch = fgetc(fp);
    }
    num[j] = '\0';
    printf("%s --> Constant\n", num);
    if(ch != EOF)
        fseek(fp, -1, SEEK_CUR);
}
void checkPreprocessor(FILE *fp)
{
    char line[200];
    fseek(fp, -1, SEEK_CUR);
    fgets(line, 200, fp);
    printf("%s --> Preprocessor Directive\n", line);
}
int main()
{
    FILE *fp=fopen("test.c","r");
    char ch;
    char token[100];
    if(fp==NULL)
    {
        printf("Cant open the file:error");
        return 1;
    }
    while((ch=fgetc(fp))!=EOF)
    {
         if(ch == '#')
{
    checkPreprocessor(fp);
}
else if(isalpha(ch))
{
    checkWord(fp, ch);
}
        else if(isdigit(ch))
        {
            checkNumber(fp,ch);
        }
        else if(ch=='+'|| ch=='-'|| ch=='*'|| ch=='/'|| ch=='%')
        {
            checkOperator(fp,ch);
        }
        else if(ch=='<' || ch=='>' || ch=='!' || ch=='=')
{
    checkRelational(fp, ch);
}
        else if(ch==';' || ch==',')
        {
            checkDelimiter(ch);
        }
        else if(ch=='(' || ch==')' ||ch=='{' || ch=='}' || ch=='[' || ch==']')
        {
            checkBracket(ch);
        }
    }
    fclose(fp);
    return 0;

}