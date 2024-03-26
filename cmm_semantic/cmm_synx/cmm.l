%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include <stack>
	#include "./init.h"
	#include "../tree/tree.h"
	#include "./cmm.tab.h"
	int yycolumn=1;
	YYLTYPE yylloc;
	#define YY_USER_ACTION \
		yylloc.first_line=yylloc.last_line=yylineno; \
		yylloc.first_column=yycolumn; \
		yylloc.last_column=yycolumn+yyleng-1; \
		yycolumn +=yyleng;

	extern "C"{
		int yywrap(void);
		int yylex(void);
	}

	void printError(const char*,const char*,int);
%}

SINGLE_COMMENT "//".*\n*
MUL_COMMENT_HEAD "/*"
MUL_COMMENT_TAIL "*/"
MUL_COMMENT_CONTENT [^*\n]*
MUL_COMMENT_STARS_CONTENT \*+[^*\n/]*
MUL_COMMENT_ENDL \n
SPACE [ \n\r\v\t\f]+
LITERAL_HEAD \"[^\"]*\"
WSTRUCT struct
WRETURN return
WIF if
WELSE else
WWHILE while
TYPE_INT int
TYPE_FLOAT float
WTYPE {TYPE_INT}|{TYPE_FLOAT}
RESERVED {WSTRUCT}|{WRETURN}|{WIF}|{WELSE}|{WWHILE}|{WTYPE}
WSEMI ";"
WCOMMA ","
WASSIGNOP "="
LESS_THAN "<"
MORE_THAN ">"
LESS_EQU "<="
MORE_EQU ">="
EQU "=="
NOT_EQU "!="
WRELOP {LESS_THAN}|{MORE_THAN}|{LESS_EQU}|{MORE_EQU}|{EQU}|{NOT_EQU}
WPLUS "+"
WMINUS "-"
WSTAR "*"
WDIV "/"
WAND "&&"
WOR "||"
WDOT "."
WNOT "!"
WLP "("
WRP ")"
WLB "["
WRB "]"
WLC "{"
WRC "}"
WDELIM [ \n\r\v\t\f\;\,<>\=\+\-\*\/\&\|\!\(\)\[\]\{\}]
NDELIM [^ \n\r\v\t\f\;\,<>\=\+\-\*\/\&\|\!\(\)\[\]\{\}]
NUMBER [0-9]
NOT_ZERO_NUMBER [1-9]
OCT_NUMBER [0-7]
HEC_LETTER [A-Fa-f]
LETTER [A-Za-z]
HEAD_SIGN [_A-Za-z]
ID_SIGN [_A-Za-z0-9]
DEC {NUMBER}|({NOT_ZERO_NUMBER}{NUMBER}+)
HEX	0[xX]({NUMBER}|{HEC_LETTER})+
OCT 0{OCT_NUMBER}+
BIN 0[bB][01]+
SCIENCE (({NUMBER}+\.{NUMBER}*)|(\.{NUMBER}+))[eE][\+-]?{NUMBER}+
WINT {DEC}|{HEX}|{OCT}|{BIN}
WFLOAT ({DEC}\.{NUMBER}+)|{SCIENCE}
WID {HEAD_SIGN}{ID_SIGN}*
INVAL_ID {NUMBER}+{WID}
ENDL \n
UNKWON_SIGN [^ \n\r\v\t\f_a-zA-z0-9\;\,<>\=\+\-\*\/\&\|\.\!\(\)\[\]\{\}]

%option yylineno
%x comment

%%

{SINGLE_COMMENT} {
	/*printf("##comment:%s\n",yytext);*/}
{MUL_COMMENT_HEAD} {BEGIN(comment);}
<comment>{MUL_COMMENT_CONTENT} {}
<comment>{MUL_COMMENT_STARS_CONTENT} {}
<comment>{MUL_COMMENT_ENDL} {yycolumn=1;}
<comment>{MUL_COMMENT_HEAD} {BEGIN(INITIAL);}
<comment>\**{MUL_COMMENT_TAIL} {BEGIN(INITIAL);}
<comment><<EOF>> {BEGIN(INITIAL);yyterminate();}
 \**{MUL_COMMENT_TAIL} {yyterminate();}
{SPACE} {}
{WSEMI} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"SEMI",yylineno,tmpVTVal);
	return SEMI;}
{WCOMMA} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"COMMA",yylineno,tmpVTVal);
	return COMMA;}
{WRELOP} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"RELOP",yylineno,tmpVTVal);
	return RELOP;}
{WASSIGNOP} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"ASSIGNOP",yylineno,tmpVTVal);
	return ASSIGNOP;}
{WPLUS} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"PLUS",yylineno,tmpVTVal);
	return PLUS;}
{WMINUS} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"MINUS",yylineno,tmpVTVal);
	return MINUS;}
{WSTAR} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"STAR",yylineno,tmpVTVal);
	return STAR;}
{WDIV} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"DIV",yylineno,tmpVTVal);
	return DIV;}
{WAND} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"AND",yylineno,tmpVTVal);
	return AND;}
{WOR} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"OR",yylineno,tmpVTVal);
	return OR;}
{WDOT} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"DOT",yylineno,tmpVTVal);
	return DOT;}
{WNOT} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"NOT",yylineno,tmpVTVal);
	return NOT;}
{WLP} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"LP",yylineno,tmpVTVal);
	return LP;}
{WRP} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"RP",yylineno,tmpVTVal);
	return RP;}
{WLB} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"LB",yylineno,tmpVTVal);
	return LB;}
{WRB} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"RB",yylineno,tmpVTVal);
	return RB;}
{WLC} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"LC",yylineno,tmpVTVal);
	return LC;}
{WRC} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"RC",yylineno,tmpVTVal);
	return RC;}
{WSTRUCT} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"STRUCT",yylineno,tmpVTVal);
	return STRUCT;}
{WRETURN} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"RETURN",yylineno,tmpVTVal);
	return RETURN;}
{WIF} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"IF",yylineno,tmpVTVal);
	return IF;}
{WELSE} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"ELSE",yylineno,tmpVTVal);
	return ELSE;}
{WWHILE} {
	typeValue tmpVTVal(-1);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"WHILE",yylineno,tmpVTVal);
	return WHILE;}
{WTYPE} {
	typeValue tmpVTVal(2);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"TYPE",yylineno,tmpVTVal);
	return TYPE;}
{WINT} {
	typeValue tmpVTVal(0);
	tmpVTVal.Integer=atoi(yytext);
	yylval=createVTNode(1,"INT",yylineno,tmpVTVal);
	return INT;}
{WFLOAT} {
	typeValue tmpVTVal(1);
	tmpVTVal.Float=atof(yytext);
	yylval=createVTNode(1,"FLOAT",yylineno,tmpVTVal);
	return FLOAT;}
{WID} {
	typeValue tmpVTVal(2);
	tmpVTVal.String=yytext;
	yylval=createVTNode(1,"ID",yylineno,tmpVTVal);
	return ID;}
{ENDL} {yycolumn=1;}
{INVAL_ID} {printError("Invalid Identifiers",yytext,yylineno);}
{UNKWON_SIGN} {printError("Mysterious characters",yytext,yylineno);}

%%

int yywrap(void)
{
	//printf("# flex read end\n");
	return 1;
}

void printError(const char* errorType,const char* text,int lineno){
	printf("Error type A at Line %d: %s \'%s\'\n",lineno,errorType,text);
}