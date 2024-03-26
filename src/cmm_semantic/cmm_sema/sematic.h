#ifndef SEMATIC
#define SEMATIC
#include <bits/stdc++.h>
#include "../tree/tree.h"
#include "./symbol_table.h"
using namespace std;

void initFile(const string);
void printError(int, int, string);
bool checkSematic(node*);
void Program(node*);
void ExtDefList(node*);
void ExtDef(node*);
void ExtDecList(node*, Type*);
Type* Specifier(node*);
Type* StructSpecifier(node*);
Symbol* VarDec(node*, Type*);
Symbol* FunDec(node*, Type*, bool);
VariableList* VarList(node*, bool);
VariableList* ParamDec(node*, bool);
void CompSt(node*);
void StmtList(node*);
void Stmt(node*);
void DefList(node*, bool, VariableList*);
void Def(node*, bool, VariableList*);
void DecList(node*, Type*, bool , VariableList*);
void Dec(node*, Type*, bool , VariableList*);
Type* Exp(node*);
VariableList* Args(node*);
bool isLeftValue(node*);
void checkFunction();

#endif