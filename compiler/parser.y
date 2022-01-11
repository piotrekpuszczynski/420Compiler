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

Data* _data = new Data();
Code* _code = new Code(_data);
%}

%code requires {
#include "variable.hpp"
}

%union {
std::string* pid;
long long num;
Variable* variable;
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

%type <variable> value
%type <variable> identifier

%%
program:        VAR declarations TBEGIN commands END                                    { _code->halt(); }
                | TBEGIN commands END                                                   { _code->halt(); }
;

declarations:   declarations ',' pidentifier                                            { _data->declareVariable(*$3); }
                | declarations ',' pidentifier '[' number ':' number ']'                { _data->declareArray(*$3, $5, $7); }
                | pidentifier                                                           { _data->declareVariable(*$1); }
                | pidentifier '[' number ':' number ']'                                 { _data->declareArray(*$1, $3, $5); }
;

commands:       commands command    {;}
                | command   {;}
;

command:        identifier ASSIGN expression ';'                                        {;}
                | IF condition THEN commands ELSE commands ENDIF                        {;}
                | IF condition THEN commands ENDIF                                      {;}
                | WHILE condition DO commands ENDWHILE                                  {;}
                | REPEAT commands UNTIL condition ';'                                   {;}
                | FOR pidentifier FROM value TO value DO commands ENDFOR                {;}
                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR            {;}
                | READ identifier ';'                                                   { _code->read($2); }
                | WRITE value ';'                                                       { _code->write($2); }
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

value:          number                                                                  { $$ = _code->getNumber($1); }
                | identifier                                                            { $$ = $1; }
;

identifier:     pidentifier                                                             { $$ = _code->getVariable(*$1); }
                | pidentifier '[' pidentifier ']'                                       { $$ = _code->getVariable(*$1, *$3); }
                | pidentifier '[' number ']'                                            { $$ = _code->getVariable(*$1, $3); }
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
    return _code->getCode();
}
