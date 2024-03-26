#include <bits/stdc++.h>
#include "../tree/tree.h"
#include "./symbol_table.h"
#include "./sematic.h"
using namespace std;

map<string, Symbol> symbolTable;
Function* currentFunction=nullptr;
#define stab symbolTable
#define curf currentFunction
#define cchld cur->children
#define symi i->second
#define srcht searchInTable
#define perr printError
#define stabin stab.insert(make_pair(symbol->name,*symbol))

bool isHavingError=false;
void printError(int errType, int lineNum, string text) {
	static string outFilePath = "../cmm_out/sema_err.out";
	fstream file(outFilePath, ios::out|ios::app);
	cout << "Error type " << errType << " at Line " << lineNum << ": " << text << "." << endl;
	file << "Error type " << errType << " at Line " << lineNum << ": " << text << "." << endl;
	file.close();
	isHavingError=true;
}

bool checkSematic(node* root) {
	Program(root);
	checkFunction();
	return (!isHavingError);
}

void Program(node* cur) {
	if (cur == nullptr)return;
	if (cchld.size() >= 1) {
		ExtDefList(cchld[0]);
	}
}

void ExtDefList(node* cur) {
	if (cur == nullptr)return;
	ExtDef(cchld[0]);
	if (cchld.size() >= 2) {
		ExtDefList(cchld[1]);
	}
}

void ExtDef(node* cur) {
	if (cur == nullptr)return;
	if (cchld.size() < 2)return;

	Type* type = Specifier(cchld[0]);

	if (cchld[1]->nodeName == "funcDec") {
		Symbol* symbol = nullptr;

		if (cchld[2]->nodeName == "compSt") {
			symbol = FunDec(cchld[1], type, true);
		} else {
			symbol = FunDec(cchld[1], type, false);
		}

		symbol->lineNumber = cur->lineNumber;

		mapi i = srcht(symbol->name, stab);
		if (i != stab.end()) {
			if (symi.sfunction->isDefined && symbol->sfunction->isDefined) {
				//err
				perr(4, cchld[1]->lineNumber, "Redefined function \"" + symbol->name + "\"");
			} else if (!(symi.sfunction->isDefined) && symbol->sfunction->isDefined) {
				symi.sfunction->isDefined = true;
			}
		} else {
			stabin;
		}

		if (cchld[2]->nodeName == "compSt") {
			curf=symbol->sfunction;
			CompSt(cchld[2]);
			curf=nullptr;
		}
	} else if (cchld[1]->nodeName == "extDecList") {
		ExtDecList(cchld[1], type);
	}
}

void ExtDecList(node* cur , Type* type) {
	if (cur == nullptr)return;

	Symbol* symbol = VarDec(cchld[0], type);
	mapi i = srcht(symbol->name, stab);

	if (i != stab.end()) {
		//err
		perr(3, symbol->lineNumber, "Redefined variable \"" + symbol->name + "\"");
	} else {
		stabin;
	}

	if (cchld.size() >= 3) {
		ExtDecList(cchld[2], type);
	}
}

Type* Specifier(node* cur) {
	if (cur == nullptr)return nullptr;

	Type* type = nullptr;
	if(cchld[0]->nodeName=="TYPE"){
		type=new Type();
		type->kind=KBASE;
		if(cchld[0]->String=="int"){
			type->tbase=BINT;
		}else if(cchld[0]->String=="float"){
			type->tbase=BFLOAT;
		}
	}else if(cchld[0]->nodeName=="structSpecifier"){
		type=StructSpecifier(cchld[0]);
	}

	return type;
}

Type* StructSpecifier(node* cur) {
	if (cur == nullptr)return nullptr;

	Type* type=nullptr;
	VariableList* strc = new VariableList();

	if(cchld[1]->nodeName=="tag"){
		mapi i=srcht(cchld[1]->children[0]->String,stab);

		if(i==stab.end()){
			//err
			perr(1, cchld[1]->children[0]->lineNumber, "Undefined variable \"" + cchld[1]->children[0]->String + "\"");
		}else if(symi.kind!=SSTRUCTD){
			//err
			perr(1, cchld[1]->children[0]->lineNumber, "Undefined variable \"" + cchld[1]->children[0]->String + "\"");
		}

		type=symi.stype;
	}else if(cchld[1]->nodeName=="optTag"){
		if(cchld[1]->children.size()!=0){
			strc->name=cchld[1]->children[0]->String;
		}

		DefList(cchld[3],false,strc);

		type=new Type();
		type->kind=KSTRUCT;
		type->tstruct=strc;

		Symbol* symbol= new Symbol(SSTRUCTD,strc->name,type);
		mapi i=srcht(symbol->name,stab);

		if(i!=stab.end()){
			//err
			perr(3, cur->lineNumber, "Redefined variable \"" + symbol->name + "\"");
		}else{
			stabin;
		}
	}

	return type;
}

Symbol* VarDec(node*cur , Type* type) {
	if (cur == nullptr)return nullptr;

	Symbol* symbol= nullptr;

	if(cchld[0]->nodeName=="ID"){
		symbol= new Symbol(STYPE,cchld[0]->String,type);
		symbol->lineNumber=cur->lineNumber;
	}else if(cchld[0]->nodeName=="varDec"){
		Type* newt=new Type();
		newt->kind=KARRAY;
		newt->tarray.element=type;
		newt->tarray.size=cchld[2]->Integer;

		symbol=VarDec(cchld[0],newt);
	}

	return symbol;
}

Symbol* FunDec(node* cur, Type* type, bool defined) {
	if (cur == nullptr)return nullptr;

	Function* func = new Function();
	func->returnType = type;
	func->argumentList = nullptr;
	func->isDefined = defined;

	if (cchld[2]->nodeName == "varList") {
		func->argumentList = VarList(cchld[2], defined);
	}

	return (new Symbol(SFUNCTION, cchld[0]->String, func));
}

VariableList* VarList(node* cur, bool toAdd) {
	if (cur == nullptr)return nullptr;

	VariableList* list=ParamDec(cchld[0],toAdd);

	if(cchld.size()>1){
		list->next=VarList(cchld[2],toAdd);
	}

	return list;
}

VariableList* ParamDec(node* cur, bool toAdd) {
	if (cur == nullptr)return nullptr;

	Type* type= Specifier(cchld[0]);
	Symbol* symbol= VarDec(cchld[1],type);

	if(toAdd){
		mapi i=srcht(symbol->name,stab);
		if(i!=stab.end()){
			//err
			perr(3, symbol->lineNumber, "Redefined variable \"" + symbol->name + "\"");
		}else{
			stabin;
		}
	}

	VariableList* list=new VariableList();
	list->name=symbol->name;
	list->type=symbol->stype;

	return list;
}

void CompSt(node* cur) {
	if (cur == nullptr)return;

	VariableList* list=new VariableList();

	if(cchld.size()==3){
		if(cchld[1]->nodeName=="defList"){
			DefList(cchld[1],true,list);
		}else if(cchld[1]->nodeName=="stmtList"){
			StmtList(cchld[1]);
		}
	}else if(cchld.size()==4){
		DefList(cchld[1],true,list);
		StmtList(cchld[2]);
	}

}
void StmtList(node* cur) {
	if (cur == nullptr)return;

	Stmt(cchld[0]);
	if(cchld.size()>=2){
		StmtList(cchld[1]);
	}
}

void Stmt(node* cur) {
	if (cur == nullptr)return;

	Type* type=nullptr;

	if(cchld[0]->nodeName=="exp"){
		Exp(cchld[0]);
	}else if(cchld[0]->nodeName=="compSt"){
		CompSt(cchld[0]);
	}else if(cchld[0]->nodeName=="RETURN"){
		type=Exp(cchld[1]);

		if(curf==nullptr
			||!(curf->returnType->equal(type))){
			//err
			perr(7, cur->lineNumber, "Type mismatched for return");
		}
	}else if(cchld[0]->nodeName=="IF"){
		type=Exp(cchld[2]);

		if(type!=nullptr){
			if(type->kind!=KBASE
				||type->tbase!=BINT){
				//err
				perr(6, cchld[2]->lineNumber, "Type mismatched for operands");
			}
		}

		Stmt(cchld[4]);

		if(cchld.size()>=7){
			Stmt(cchld[6]);
		}
	}else if(cchld[0]->nodeName=="WHILE"){
		type=Exp(cchld[2]);

		if(type!=nullptr){
			if(type->kind!=KBASE
				||type->tbase!=BINT){
				//err
				perr(6, cchld[2]->lineNumber, "Type mismatched for operands");
			}
		}

		Stmt(cchld[4]);
	}
}

void DefList(node* cur, bool toAdd, VariableList* list) {
	if(cur==nullptr)return;

	Def(cchld[0],toAdd,list);
	if(cchld.size()>=2){
		DefList(cchld[1],toAdd,list);
	}
}

void Def(node* cur, bool toAdd, VariableList* list) {
	if(cur==nullptr)return;

	Type* type= Specifier(cchld[0]);
	DecList(cchld[1],type,toAdd,list);
}

void DecList(node* cur,Type* type, bool toAdd, VariableList* list) {
	if(cur==nullptr)return;

	Dec(cchld[0],type,toAdd,list);

	if(cchld.size()>=3){
		DecList(cchld[2],type,toAdd,list);
	}
}

void Dec(node* cur,Type* type, bool toAdd, VariableList* list) {
	if(cur==nullptr)return;

	Symbol* symbol=VarDec(cchld[0],type);

	if(toAdd){
		mapi i = srcht(symbol->name, stab);

		if (i != stab.end()) {
			//err
			perr(3, symbol->lineNumber, "Redefined variable \"" + symbol->name + "\"");
		} else {
			stabin;
		}
	}

	VariableList* tmpl = new VariableList();
	tmpl->name=symbol->name;
	tmpl->type=symbol->stype;
	VariableList* p=list;

	if(!toAdd && p!=nullptr){
		while(p->next!=nullptr){
			if(p->name==symbol->name){
				//err
				perr(3, symbol->lineNumber, "Redefined variable \"" + symbol->name + "\"");
			}
			p=p->next;
		}

		p->next=tmpl;
	}

	if(cchld.size()>=3){
		Type* rtype=Exp(cchld[2]);

		if(!(type->equal(rtype))){
			//err
			perr(5, cur->lineNumber, "Type mismatched for assignment");
		}
	}
}

Type* Exp(node* cur) {
	if(cur==nullptr) return nullptr;

	Type* lt=nullptr;
	Type* rt=nullptr;

	if(cchld[0]->nodeName=="exp"){
		lt=Exp(cchld[0]);

		if(cchld[1]->nodeName=="ASSIGNOP"){
			if(lt!=nullptr){
				if(!isLeftValue(cchld[0])){
					//err
					perr(5,cur->lineNumber,"Type mismatched for assignment");
					lt=nullptr;
				}else{
					rt=Exp(cchld[2]);
					if(rt!=nullptr){
						if(!(lt->equal(rt))){
							//err
							perr(5,cur->lineNumber,"Type mismatched for assignment");
							lt=nullptr;
						}
					}
				}
			}
		}else if(cchld[1]->nodeName=="AND"
			||cchld[1]->nodeName=="OR"){
			rt=Exp(cchld[2]);

			if((lt!=nullptr&&lt->kind!=KBASE)
				||(rt!=nullptr&&rt->kind!=KBASE)){
				perr(6,cur->lineNumber,"Type mismatched for operands");
				lt=nullptr;
			}
		}else if(cchld[1]->nodeName=="PLUS"
			||cchld[1]->nodeName=="MINUS"
			||cchld[1]->nodeName=="STAR"
			||cchld[1]->nodeName=="DIV"
			||cchld[1]->nodeName=="RELOP"){
			rt=Exp(cchld[2]);

			if(lt!=nullptr
				&&(lt->kind!=KBASE
					||!(lt->equal(rt)))){
				perr(6,cur->lineNumber,"Type mismatched for operands");
				lt=nullptr;
			}
		}else if(cchld[1]->nodeName=="LB"){
			rt=Exp(cchld[2]);

			if(lt->kind!=KARRAY){
				//err
				perr(9,cchld[0]->lineNumber,"\""+getVTStr(cchld[0])+"\" is not an array");
				lt=nullptr;
			}else if(rt!=nullptr
				&& (rt->kind!=KBASE
					||rt->tbase!=BINT)){
				//err
				perr(11,cchld[2]->lineNumber,"\""+getVTStr(cchld[2])+"\" is not an integer");
			}else{
				lt=lt->tarray.element;
			}
		}else if(cchld[1]->nodeName=="DOT"){
			rt=lt->tstruct->getType(cchld[2]->String);
			lt=rt;
		}
	}else if(cchld[0]->nodeName=="ID"){
		if(cchld.size()==1){
			mapi i=srcht(cchld[0]->String,stab);

			if(i==stab.end()){
				//err
				perr(1, cur->lineNumber, "Undefined variable \"" + cchld[0]->String + "\"");
				lt=nullptr;
			}else{
				lt=symi.stype;
			}
		}else if(cchld[1]->nodeName=="LP"){
			mapi i=srcht(cchld[0]->String,stab);

			if(i==stab.end()){
				//err
				perr(2, cur->lineNumber, "Undefined function \"" + cchld[0]->String + "\"");
				lt=nullptr;
			}else if(symi.kind!=SFUNCTION){
				//err
				perr(10,cchld[0]->lineNumber,"\""+cchld[0]->nodeName+"\" is not a function");
				lt=nullptr;
			}else{
				VariableList* argl=nullptr;
				lt=symi.sfunction->returnType;
				if(cchld.size()==4){
					argl=Args(cchld[2]);
				}

				if(!(argl->equalToArguments(symi.sfunction->argumentList))){
					perr(8, cur->lineNumber, "Function \"" +symi.name+"("+symi.sfunction->argumentList->getStr()+ ")\" is not applicable for arguments \"("+argl->getStr()+")\"");
					lt=nullptr;
				}
			}
		}
	}else if(cchld[0]->nodeName=="INT"){
		lt=new Type();
		lt->kind=KBASE;
		lt->tbase=BINT;
	}else if(cchld[0]->nodeName=="FLOAT"){
		lt=new Type();
		lt->kind=KBASE;
		lt->tbase=BFLOAT;
	}else if(cchld[0]->nodeName=="LP"
		||cchld[0]->nodeName=="MINUS"
		||cchld[0]->nodeName=="NOT"){
		lt=Exp(cchld[1]);
	}

	return lt;
}


VariableList* Args(node* cur) {
	if(cur==nullptr)return nullptr;

	VariableList* list=new VariableList();

	if(cchld.size()==1){
		list->type=Exp(cchld[0]);
	}else if(cchld.size()==3){
		list->type=Exp(cchld[0]);
		list->next=Args(cchld[2]);
	}

	return list;
}

bool isLeftValue(node* cur) {
	if (cur == nullptr)return true;

	if (cur->nodeName == "ID") {
		mapi i = srcht(cur->String, stab);

		if (i != stab.end()) {
			if (symi.kind == STYPE)
				return true;
		}
	} else if (cur->nodeName == "exp" && cchld[0]->nodeName == "ID") {
		mapi i = srcht(cchld[0]->String, stab);

		if (i != stab.end()) {
			if (symi.kind == STYPE)
				return true;
		}
	} else if (cur->nodeName == "exp" && cchld[0]->nodeName == "exp") {
		if (cchld[1]->nodeName == "LB"
		       || cchld[1]->nodeName == "DOT")
			return true;

	}
	return false;
}

void checkFunction() {
	mapi i = stab.begin();

	while (i != stab.end()) {
		if (symi.kind == SFUNCTION) {
			if (!(symi.sfunction->isDefined)) {
				//err
				perr(2, symi.lineNumber, "Undefined function \"" + symi.name + "\"");
			}
		}

		i++;
	}
}
