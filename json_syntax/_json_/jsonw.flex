%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>

	const int arrSizeOfUnit=1000;
	const int strlenOfUnit=50;
	char wordUnits[arrSizeOfUnit][strlenOfUnit];

	int indexOfWordUnits=0;
	void addUnit(const char*,const char*);
%}

SPACE [ \n\r\v\t\f]+
STRING_HEAD \"[^\"]*\"
BTRUE "true"
BFALSE "false"
BOOL {BTRUE}|{BFALSE}
NUL "null"
COMMA ","
COLON ":"
LB "["
RB "]"
LC "{"
RC "}"
NUMBER [0-9]
NZ_NUMBER [1-9]
DEC {NUMBER}|({NZ_NUMBER}{NUMBER}+)
POINT {DEC}\.{NUMBER}+
SCIENCE (({NUMBER}+\.{NUMBER}*)|(\.{NUMBER}+))[eE][\+-]?{NUMBER}+
NUMVAL {POINT}|{SCIENCE}|{DEC}
LETTER [A-Za-z]
HEAD_SIGN [_A-Za-z]
ID_SIGN [_A-Za-z0-9]
UNKWON [^ \n\r\v\t\f\,\:\[\]\{\}]

%option yylineno
%option noyywrap

%%

{SPACE} {}
{COMMA} {addUnit("COMMA", yytext);}
{COLON} {addUnit("COLON", yytext);}
{LB} {addUnit("LB", yytext);}
{RB} {addUnit("RB", yytext);}
{LC} {addUnit("LC", yytext);}
{RC} {addUnit("RC", yytext);}
{BOOL} {addUnit("BOOL", yytext);}
{NUL} {addUnit("NUL", yytext);}
{NUMVAL} {addUnit("NUM", yytext);}
{STRING_HEAD} {
		if(yytext[yyleng-2]=='\\'){
			yyless(yyleng-1);
			yymore();
		}else{
			strcpy(wordUnits[indexOfWordUnits],"STR$");
			strcat(wordUnits[indexOfWordUnits],yytext);
			indexOfWordUnits++;
		}
	}
{UNKWON} {addUnit("UNKWON", yytext);}

%%

int main(int argc, char** argv){
	const int strlenOfName=20;
	const int strlenOfPath=80;
	char fileName[strlenOfName];
	char filePath[strlenOfPath]="./json_in/";
	FILE* file;
	YY_BUFFER_STATE buffer;

	if(argc>1){
		file=fopen(argv[1],"r");
	}else{
		printf("-input the file name:");
		scanf("%s",fileName);
		strcat(filePath,fileName);
		file=fopen(filePath,"r");
	}
	buffer=yy_create_buffer(file,YY_BUF_SIZE);
	yy_switch_to_buffer(buffer);

	yylex();

	yy_delete_buffer(buffer);
	fclose(file);

	const char* outFile="./json_parse/json_words.out";
	file=fopen(outFile,"w");
	for(int i=0;i<indexOfWordUnits;i++){
		//printf("%s\n",wordUnits[i]);
		fputs(wordUnits[i],file);
		fputs("\n",file);
	}
	fclose(file);

	//system("pause");
	return 0;
}

void addUnit(const char* wordType, const char* text){
	strcpy(wordUnits[indexOfWordUnits],wordType);
	strcat(wordUnits[indexOfWordUnits],"$");
	strcat(wordUnits[indexOfWordUnits],yytext);
	indexOfWordUnits++;
}