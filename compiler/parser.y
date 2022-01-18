%{
#include <iostream>
#include <string>
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
#include "data.hpp"
}

%union {
std::string* pid;
long long num;
Symbol* symbol;
Cond* cond;
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
%type <cond> condition

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
                | IF condition THEN commands                                            { _code->ifElseFirstBlock($2); }
                  ELSE commands ENDIF                                                   { _code->ifBlock($2); }
                | IF condition THEN commands ENDIF                                      { _code->ifBlock($2); }
                | WHILE condition DO commands ENDWHILE                                  { _code->whileBlock($2); }
                | REPEAT                                                                { _code->repeatUntilStart(); }
                  commands UNTIL condition ';'                                          { _code->repeatUntilBlock($5); }
                | FOR pidentifier FROM value TO value DO                                { _code->incForLoopCondition(*$2, $4, $6); }
                  commands ENDFOR                                                       { _code->incForLoopEnd(*$2); }
                | FOR pidentifier FROM value DOWNTO value DO                            { _code->decForLoopCondition(*$2, $4, $6); }
                  commands ENDFOR                                                       { _code->decForLoopEnd(*$2); }
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

condition:      value EQ value                                                          { $$ = _code->eq($1, $3); }
                | value NEQ value                                                       { $$ = _code->neq($1, $3); }
                | value LE value                                                        { $$ = _code->le($1, $3); }
                | value GE value                                                        { $$ = _code->ge($1, $3); }
                | value LEQ value                                                       { $$ = _code->leq($1, $3); }
                | value GEQ value                                                       { $$ = _code->geq($1, $3); }
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
