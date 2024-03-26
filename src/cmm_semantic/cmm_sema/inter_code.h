#ifndef INTER_CODE
#define INTER_CODE
#include "../tree/tree.h"
#include "./symbol_table.h"
#include <string>
#include <list>
#include <iterator>
using namespace std;

struct Operand;

typedef enum{TVAR,TCONST,TADR,TTEMP,TLAB,TREF,TDEREF} OperandType;
typedef enum{IASGN=1,IADD,ISUB,IMUL,IDIV,IDEC,IFUNC,IPRM,ILAB,IRET,IGOTO,ICALL,IARG,IJL,IJLE,IJG,IJGE,IJE,IJNE,IREAD,IWRITE,IREF,IDEREF} IncodeType;
typedef struct {Operand* t=nullptr;Operand* a=nullptr;Operand* b=nullptr;} BinOp;

struct Operand {
	OperandType kind;
	int varnum;
	int value;
	string name;
	Operand* op=nullptr;

	Operand();
	Operand(OperandType,string);
	Operand(OperandType,Operand*);
	Operand(OperandType,int);
	bool equal(Operand*);
};

struct ArgumentList{
	Operand* op=nullptr;
	ArgumentList* next=nullptr;
};

struct InterCode{
	IncodeType kind;
	BinOp ibin;

	InterCode();
	InterCode(IncodeType,Operand*,Operand*,Operand*);
};

typedef list<InterCode>::iterator lsi;
typedef list<InterCode> ls;

int getNewParam();
int getNewArg();
Operand* getNewTemp();
Operand* getNewLabel();
void logOp(Operand*,fstream&);
int logCode(list<InterCode>&,fstream&);
IncodeType getRelopType(node*);
ls genIR(node*,smap&);
ls trsProgram(node*,smap&);
ls trsExtDefList(node*,smap&);
ls trsExtDef(node*,smap&);
ls trsExtDecList(node*,smap&);
ls trsVarDec(node*,smap&);
ls trsFunDec(node*,smap&);
ls trsVarList(node*,smap&);
ls trsCompSt(node*,Operand*,smap&);
ls trsDefList(node*,smap&);
ls trsDef(node*,smap&);
ls trsDec(node*,smap&);
ls trsDecList(node*,smap&);
ls trsStmtList(node*,Operand*,smap&);
ls trsStmt(node*,Operand*,smap&);
ls trsExp(node*,Operand*&,smap&);
ls trsStructure(node*,Operand*,Type*&,smap&);
ls trsArray(node*,Operand*,Type*&,smap&);
ls trsArgs(node*,ArgumentList*&,smap&);
ls trsCond(node*,Operand*,Operand*,smap&);

#endif