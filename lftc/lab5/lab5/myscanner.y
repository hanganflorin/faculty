%{
#include <stdio.h>
#include <stdlib.h>
int memory[256];
#define YYERROR_VERBOSE
%}

%union {int num; char* id;}
%start PROGRAM
%token INT
%token ARRAY
%token CHAR
%token RETURN
%token WRT
%token RD
%token STRUCT
%token ELSE
%token STRING
%token IF
%token WHILE
%token NOR
%token BACK
%token CONSTANT


%token <num> NR
%token <id> IDENTIFIER


%%

PROGRAM : NOR '{' DECLIST '|' CMPDSTMT '}'     {printf("COMPILATION SUCCESFULL");}
        ;
DECLIST : DECLARATION DECLIST_TAIL
        ;
DECLIST_TAIL: ';' DECLARATION DECLIST_TAIL
                |
                ;
DECLARATION : VARDECL
            | ARRAYDECL
            | STRUCTDECL
            ;
VARDECL : TYPE IDENTIFIER '=' NR
        ;
ARRAYDECL : ARRAY TYPE IDENTIFIER
            ;
STRUCTDECL : STRUCT IDENTIFIER '{' DECLIST '}'
            ;
CMPDSTMT : '{' STMTLIST '}'
            ;
STMTLIST : STMT STMTLIST_TAIL
            ;
STMTLIST_TAIL : ';' STMT STMTLIST_TAIL
                |
                ;
STMT : STRUCTSTMT
        | IOSTMT
        | ASSIGNSTMT
        ;
ASSIGNSTMT : NEW_IDENTIFIER '=' TERM SECONDPART
            ;
SECONDPART : '+' TERM
            | '-' TERM
            | '*' TERM
            | '/' TERM
            |
            ;
EXPRESSION : TERM
            ;
TERM : NR
        | IDENTIFIER
     ;
IOSTMT : WRITESTMT
        | READSTMT
        ;
READSTMT : RD IDENTIFIER
        ;
WRITESTMT : WRT IDENTIFIER
        ;
STRUCTSTMT : CMPDSTMT
            | IFSTMT
            | WHILESTMT
            ;
IFSTMT : IF '(' CONDITION ')' CMPDSTMT ELSE '{' CMPDSTMT '}'
        ;
WHILESTMT : WHILE '(' CONDITION ')' CMPDSTMT
            ;
CONDITION : EXPRESSION RELATION EXPRESSION
            ;
NEW_IDENTIFIER : IDENTIFIER
                ;
RELATION : '<'
        ;
TYPE : INT
        ;
TYPE : STRING
     ;

%%
int main(void)
{
    return yyparse();
}
void yyerror (char *s) {
   fprintf (stderr, "%s at token \n", s);
 }