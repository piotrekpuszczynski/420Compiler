%{
#include <iostream>
#include <string>
#include "data.hpp"
#include "code.hpp"
using namespace std;

int yylex();
int yyerror(string);
void yyset_in(FILE*);

extern int yylineno;

Data* variables = new Data();
Code* code = new Code();
%}

%union {
std::string* pid;
long long num;
}

%start program

%token VAR TBEGIN END
%token ASSIGN
%token IF THEN ELSE ENDIF
%token WHILE DO ENDWHILE
%token REPEAT UNTIL
%token FOR FROM TO DOWNTO ENDFOR
%token READ WRITE
%token ERROR
%token LE GE LEQ GEQ EQ NEQ
%token <pid> pidentifier
%token <num> number

%left PLUS MINUS
%left TIMES DIV MOD

%%
program:        VAR declarations TBEGIN commands END                                    { code->halt(); }
                | TBEGIN commands END                                                   { code->halt(); }
;

declarations:   declarations ',' pidentifier                                            { variables->declareVariable(*$3); }
                | declarations ',' pidentifier '[' number ':' number ']'                { variables->declareArray(*$3, $5, $7); }
                | pidentifier                                                           { variables->declareVariable(*$1); }
                | pidentifier '[' number ':' number ']'                                 { variables->declareArray(*$1, $3, $5); }
;

commands:       commands command
                | command
;

command:        identifier ASSIGN expression ';'                                        {;}
                | IF condition THEN commands ELSE commands ENDIF                        {;}
                | IF condition THEN commands ENDIF                                      {;}
                | WHILE condition DO commands ENDWHILE                                  {;}
                | REPEAT commands UNTIL condition ';'                                   {;}
                | FOR pidentifier FROM value TO value DO commands ENDFOR                {;}
                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR            {;}
                | READ identifier ';'                                                   {;}
                | WRITE value ';'                                                       {;}
;

expression:     value                                                                   {;}
                | value PLUS value                                                      {;}
                | value MINUS value                                                     {;}
                | value TIMES value                                                     {;}
                | value DIV value                                                       {;}
                | value MOD value                                                       {;}
;

condition:      value EQ value                                                          {;}
                | value NEQ value                                                       {;}
                | value LE value                                                        {;}
                | value GE value                                                        {;}
                | value LEQ value                                                       {;}
                | value GEQ value                                                       {;}
;

value:          number                                                                  {;}
                | identifier                                                            {;}
;

identifier:     pidentifier                                                             {;}
                | pidentifier '[' pidentifier ']'                                       {;}
                | pidentifier '[' number ']'                                            {;}
;
%%

int yyerror(string err) {
    cout << "error in line " << yylineno << endl;
    cout << "error message: " << err << endl;
    exit(-3);
}

string parse(FILE* in){
    yyset_in(in);
    yyparse();
    return code->getCode();
}
