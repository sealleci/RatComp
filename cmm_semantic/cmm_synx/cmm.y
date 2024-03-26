%{
	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "./init.h"
	#include "../tree/tree.h"
	using namespace std;

	extern "C"{
		extern void yyerror(const char *);
		extern int yylex(void);
		extern int yylineno;
		extern FILE* yyin;
	}
	int isHavingError=0;
	node* root=nullptr;
	//string outFilePath="../cmm_out/tree.out";
	string outFilePath2="../cmm_out/tree_details.out";
	//fstream outfile(outFilePath,ios::out|ios::trunc);
	//%type <node*> program extDefList extDef extDecList specifier structSpecifier optTag tag varDec funcDec varList paramDec compSt stmtList stmt defList def decList dec exp args
	//%type <node*> SEMI COMMA ASSIGNOP RELOP PLUS MINUS STAR DIV AND OR DOT NOT TYPE LP RP LB RB LC RC STRUCT RETURN IF ELSE WHILE INT FLOAT ID
%}

%token SEMI
%token COMMA
%right ASSIGNOP
%left RELOP
%left PLUS
%left MINUS
%left STAR
%left DIV
%left AND
%left OR
%left DOT
%right NOT
%token TYPE
%left LP
%left RP
%left LB
%left RB
%token LC
%token RC
%token STRUCT
%token RETURN
%token IF
%nonassoc ELSE
%token WHILE
%token INT
%token FLOAT
%token ID

%nonassoc LOWER_THAN_ELSE
%left NEG

%token-table
%error-verbose
%start program

%%

program: extDefList{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"program",yylineno,subs);
	root=$$;
}
	;

extDefList:extDef extDefList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"extDefList",yylineno,subs);
}
	|{
	vector<node*> subs;
	$$=createVNNode(0,"EPS",yylineno,subs);
}
	;

extDef: specifier extDecList SEMI{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"extDef",yylineno,subs);
}
	| specifier SEMI{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"extDef",yylineno,subs);
}
	| specifier funcDec compSt{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"extDef",yylineno,subs);
}
	| error SEMI{yyerror("Missing \";\"");}
	;

extDecList: varDec{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"extDecList",yylineno,subs);
}
	| varDec COMMA extDecList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"extDecList",yylineno,subs);
}
	;

specifier: TYPE{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"specifier",yylineno,subs);
}
	| structSpecifier{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"specifier",yylineno,subs);
}
	;

structSpecifier: STRUCT optTag LC defList RC{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	subs.push_back($5);
	$$=createVNNode(0,"structSpecifier",yylineno,subs);
}
	| STRUCT tag{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"structSpecifier",yylineno,subs);
}
	//| STRUCT optTag LC defList RC error{yyerror("Missing \";\"");yyclearin;}
	|STRUCT optTag error RC{yyerror("Missing \"{\"");}
	;

optTag: ID{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"optTag",yylineno,subs);
}
	|{
	vector<node*> subs;
	$$=createVNNode(0,"EPS",yylineno,subs);
}
	;

tag: ID{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"tag",yylineno,subs);
}
	;

varDec: ID{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"varDec",yylineno,subs);
}
	| varDec LB INT RB{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	$$=createVNNode(0,"varDec",yylineno,subs);
}
	| varDec LB error RB{yyerror("Missing \"]\"");yyerrok; }
	//| varDec LB error RB{yyerror("Missing \"]\"");yyerrok;}
	//| varDec LB error {yyerror("Missing \"]\"");}
	;

funcDec: ID LP varList RP{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	$$=createVNNode(0,"funcDec",yylineno,subs);
}
	| ID LP RP{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"funcDec",yylineno,subs);
}
	| ID error RP{yyerror("Missing \"(\"");}
	;

varList: paramDec COMMA varList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"varList",yylineno,subs);

}	| paramDec{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"varList",yylineno,subs);
}
	//| error COMMA varList{yyerror("Unexpected Sign");}
	//| error paramDec{yyerror("Unexpected Sign");}
	//| paramDec COMMA error{yyerror("Unexpected Sign");}
	;

paramDec: specifier varDec{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"paramDec",yylineno,subs);
}
	;

compSt: LC defList stmtList RC{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	$$=createVNNode(0,"compSt",yylineno,subs);
}
	| LC error RC {yyerror("Missing Sign");}
	;

stmtList: stmt stmtList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"stmtList",yylineno,subs);
}
	|{
	vector<node*> subs;
	$$=createVNNode(0,"EPS",yylineno,subs);
}
	;

stmt: exp SEMI{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	| compSt{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	| RETURN exp SEMI{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	| IF LP exp RP stmt{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	subs.push_back($5);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	| IF LP exp RP stmt ELSE stmt{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	subs.push_back($5);
	subs.push_back($6);
	subs.push_back($7);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	| WHILE LP exp RP stmt{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	subs.push_back($5);
	$$=createVNNode(0,"stmt",yylineno,subs);
}
	//|error{yyerror("Missing \";\"");}
	| exp error{yyerror("Missing \";\"");}
	;

defList: def defList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"defList",yylineno,subs);
}
	|{
	vector<node*> subs;
	$$=createVNNode(0,"EPS",yylineno,subs);
}
	;

def: specifier decList SEMI{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"def",yylineno,subs);
}
	| specifier decList error SEMI{yyerror("Missing \";\"");}
	;

decList: dec{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"decList",yylineno,subs);
}
	| dec COMMA decList{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"decList",yylineno,subs);
}
	;

dec: varDec{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"dec",yylineno,subs);
}
	| varDec ASSIGNOP exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"dec",yylineno,subs);
}
	;

exp: exp ASSIGNOP exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp AND exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp OR exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp RELOP exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp PLUS exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp MINUS exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp STAR exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp DIV exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| LP exp RP{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| MINUS exp %prec NEG{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| NOT exp{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| ID LP args RP{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| ID LP RP{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp LB exp RB{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	subs.push_back($4);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp DOT ID{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| ID{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| INT{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| FLOAT{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"exp",yylineno,subs);
}
	| exp LB error RB{yyerror("Missing \"]\"");yyerrok;}
	;

args: exp COMMA args{
	vector<node*> subs;
	subs.push_back($1);
	subs.push_back($2);
	subs.push_back($3);
	$$=createVNNode(0,"args",yylineno,subs);
}
	| exp{
	vector<node*> subs;
	subs.push_back($1);
	$$=createVNNode(0,"args",yylineno,subs);
}
	//| error COMMA args{yyerror("Unexpected Sign");}
	//| error exp{yyerror("Unexpected Sign");}
	//| exp COMMA error{yyerror("Unexpected Sign");}
	;

%%

int main(int argc, char** argv){
	const int strlenOfName=20;
	const int strlenOfPath=30;
	char fileName[strlenOfName];
	char filePath[strlenOfPath]="../cmm_in/";

	FILE* file;
	file=fopen(filePath,"r");

	if(argc>1){
		file=fopen(argv[1],"r");
	}else{
		printf("-input the file name:");
		scanf("%s",fileName);
		strcat(filePath,fileName);
		file=fopen(filePath,"r");
	}

	yyin=file;
	//yydebug=1;

	if(!yyparse()){
		//printf("# bison parse completed\n");
		//outfile.close();
		if(isHavingError==0){
			//printTree(root,outFilePath,0);
			printTree(root,outFilePath2,1);
		}
	}
	else{
		//printf("# bison parse failed\n");
	}

	fclose(file);
    return 0;
}

void yyerror(const char *s){
	//cout<<yylval->nodeName<<": ";
	string ts=s;
	if(ts.substr(0,12)=="syntax error")return;
	fprintf (stderr, "Error Type B at Line %d: %s.\n",yylineno,s);
	//outfile<<"Error Type B at Line "<<yylineno<<": "<<s<<"."<<endl;
	isHavingError=1;
}