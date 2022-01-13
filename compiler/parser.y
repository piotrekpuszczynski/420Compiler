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
#include "symbol.hpp"
}

%union {
std::string* pid;
long long num;
Symbol* symbol;
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

%type <symbol> value
%type <symbol> identifier
%type <symbol> expression

%%
program:        VAR declarations TBEGIN commands END                                    { _code->halt(); }
                | TBEGIN commands END                                                   { _code->halt(); }
;

declarations:   declarations ',' pidentifier                                            { _data->declareVariable(*$3); }
                | declarations ',' pidentifier '[' number ':' number ']'                { _data->declareArray(*$3, $5, $7); }
                | pidentifier                                                           { _data->declareVariable(*$1); }
                | pidentifier '[' number ':' number ']'                                 { _data->declareArray(*$1, $3, $5); }
;

commands:       commands command
                | command
;

command:        identifier ASSIGN expression ';'                                        { _code->assign($1, $3); }
                | IF condition THEN commands ELSE commands ENDIF                        {;}
                | IF condition THEN commands ENDIF                                      {;}
                | WHILE condition DO commands ENDWHILE                                  {;}
                | REPEAT commands UNTIL condition ';'                                   {;}
                | FOR pidentifier FROM value TO value DO commands ENDFOR                {;}
                | FOR pidentifier FROM value DOWNTO value DO commands ENDFOR            {;}
                | READ identifier ';'                                                   { _code->read($2); }
                | WRITE value ';'                                                       { _code->write($2); }
;

expression:     value                                                                   { $$ = $1; }
                | value PLUS value                                                      { $$ = _code->plus($1, $3); }
                | value MINUS value                                                     { $$ = _code->minus($1, $3); }
                | value TIMES value                                                     { $$ = _code->times($1, $3); }
                | value DIV value                                                       { $$ = _code->div($1, $3); }
                | value MOD value                                                       { $$ = _code->mod($1, $3); }
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

identifier:     pidentifier                                                             { $$ = _code->getSymbol(*$1); }
                | pidentifier '[' pidentifier ']'                                       { $$ = _code->getSymbol(*$1, *$3); }
                | pidentifier '[' number ']'                                            { $$ = _code->getSymbol(*$1, $3); }
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
