%{
#include "myscanner.tab.h"
%}

%%


[ \t\n]                          ;
"nor"      {printf("NOR "); return NOR;};
[{};=+\-|]   {printf("%c ", yytext[0]) ; return yytext[0];};
"int"       {printf("INT "); return INT;};
"char"      return CHAR;
"string"    return STRING;
"return"    return BACK;
"rd"       return RD;

[a-zA-Z][a-zA-Z0-9]{0,254}        {printf("%s ", yytext); yylval.id = yytext; return IDENTIFIER;}
([-]?[1-9][0-9]*)|[0]             {yylval.num = atoi(yytext); return NR;}
\"\w*\"                           {yylval.id = yytext; return CONSTANT;}
\'\w?\'                           {yylval.id = yytext[0]; return CONSTANT;}


.          return -1;

%%

int yywrap()
{
    return 1;
}