%option noyywrap
%option yylineno
%option nounput

%{
#include <iostream>
#include <string>
#include "parser.hpp"
using namespace std;
%}

%x comment

%%
"VAR"           { return VAR; }
"BEGIN"         { return TBEGIN; }
"END"           { return END; }

"ASSIGN"        { return ASSIGN; }

"IF"            { return IF; }
"THEN"          { return THEN; }
"ELSE"          { return ELSE; }
"ENDIF"         { return ENDIF; }

"WHILE"         { return WHILE; }
"DO"            { return DO; }
"ENDWHILE"      { return ENDWHILE; }

"REPEAT"        { return REPEAT; }
"UNTIL"         { return UNTIL; }

"FOR"           { return FOR; }
"FROM"          { return FROM; }
"TO"            { return TO; }
"DOWNTO"        { return DOWNTO; }
"ENDFOR"        { return ENDFOR; }

"READ"          { return READ; }
"WRITE"         { return WRITE; }

"PLUS"          { return PLUS; }
"MINUS"         { return MINUS; }
"TIMES"         { return TIMES; }
"DIV"           { return DIV; }
"MOD"           { return MOD; }

"EQ"            { return EQ; }
"NEQ"           { return NEQ; }
"LE"            { return LE; }
"GE"            { return GE; }
"LEQ"           { return LEQ; }
"GEQ"           { return GEQ; }

[_a-z]+         { yylval.pid = new string(yytext); return pidentifier; }  
-?[0-9]+        { yylval.num = stoll(yytext); return number; }
[\;\[\]\:\,]    { return yytext[0]; }

"("             BEGIN(comment);
<comment>")"    BEGIN(INITIAL);
<comment>.|\n   ;

[ \t\n\r]+      ;
.               { return ERROR; }
%%
