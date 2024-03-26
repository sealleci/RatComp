#include <bits/stdc++.h>
#include "./symbol_table.h"
using namespace std;

string Type::getStr() {
	string str="";
	switch (this->kind) {
	case KBASE:
		if (this->tbase == BINT) {
			str="int";
		}
		else if (this->tbase == BFLOAT) {
			str="float";
		}
		break;
	case KARRAY:
		str+="[";
		str+=to_string(this->tarray.size);
		str+="]";
		if (this->tarray.element != nullptr) {
			str+=this->tarray.element->getStr();
		}
		break;
	case KSTRUCT:
		if (this->tstruct != nullptr) {
			str+=this->tstruct->getStr();
		}
		break;
	default:
		break;
	}
	return str;
}

void Type::print() {
	switch (this->kind) {
	case KBASE:
		if (this->tbase == BINT) {
			cout << "int";
		}
		else if (this->tbase == BFLOAT) {
			cout << "float";
		}
		break;
	case KARRAY:
		cout << "[" << this->tarray.size << "]";
		if (this->tarray.element != nullptr) {
			this->tarray.element->print();
		}
		break;
	case KSTRUCT:
		if (this->tstruct != nullptr) {
			this->tstruct->print();
		}
		break;
	default:
		break;
	}
}

bool Type::equal(Type* type) {
	if (this == type)return true;
	if (type == nullptr)return false;
	if (this->kind != type->kind)return false;
	switch (this->kind) {
	case KBASE:
		if (this->tbase == type->tbase)return true;
		else return false;
		break;
	case KARRAY:
		return (this->tarray.element->equal(type->tarray.element));
		break;
	case KSTRUCT:
		return (this->tstruct->equalToStruct(type->tstruct));
		break;
	default:
		break;
	}
	return false;
}

string VariableList::getStr() {
	string str="";
	VariableList* cur = this;
	if (cur->type != nullptr) {
		str+=cur->type->getStr();
	}
	if (cur->name != "") {
		str+=" ";
		str+=cur->name;
	}
	cur = cur->next;
	while (cur != nullptr) {
		str+=", ";
		if (cur->type != nullptr) {
			str+=cur->type->getStr();
		}
		if (cur->name != "") {
			str+=" ";
			str+=cur->name;
		}
		cur = cur->next;
	}
	return str;
}

void VariableList::print() {
	VariableList* cur = this;
	if (cur->type != nullptr) {
		cur->type->print();
	}
	if (cur->name != "") {
		cout << " " << cur->name;
	}
	cur = cur->next;
	while (cur != nullptr) {
		cout << ", ";
		if (cur->type != nullptr) {
			cur->type->print();
		}
		if (cur->name != "") {
			cout << " " << cur->name;
		}
		cur = cur->next;
	}
}

bool VariableList::equalToStruct(VariableList* var) {
	if (this == var)return true;
	if (var == nullptr)return false;
	if (this->name == var->name)return true;
	return false;
}

bool VariableList::equalToArguments(VariableList* varList) {
	if (this == varList)return true;
	if (varList == nullptr)return false;
	if (!(this->type->equal(varList->type)))return false;
	return (this->next->equalToArguments(varList->next));
}

Type* VariableList::getType(string name) {
	Type* type = nullptr;
	VariableList* cur = this;

	while (cur != nullptr) {
		if (cur->name == name) {
			type = cur->type;
			break;
		}
		cur = cur->next;
	}

	return type;
}

void Function::print() {
	if (this->returnType != nullptr) {
		this->returnType->print();
	}
	cout << " (";
	if (this->argumentList != nullptr) {
		this->argumentList->print();
	}
	cout << ")";
}

bool Function::equal(Function* func) {
	if (this == func)return true;
	if (func == nullptr)return false;
	if (!(this->returnType->equal(func->returnType)))return false;
	return (this->argumentList->equalToArguments(func->argumentList));
}

Symbol::Symbol() {}

Symbol::Symbol(SymbolKind kind, string name, Type* stype) {
	this->kind = kind;
	this->name = name;
	this->stype = stype;
}

Symbol::Symbol(SymbolKind kind, string name, Function* sfunction) {
	this->kind = kind;
	this->name = name;
	this->sfunction = sfunction;
}

Symbol::Symbol(const Symbol& symbol){
	//cout<<"!"<<endl;
	this->kind=symbol.kind;
	this->name=symbol.name;
	this->lineNumber=symbol.lineNumber;
	this->stype=symbol.stype;
	this->sfunction=symbol.sfunction;
}

void Symbol::print() {
	switch (this->kind) {
	case STYPE:
		cout << "Variable " << this->name << ": ";

		if (this->stype != nullptr) {
			this->stype->print();
		}
		break;
	case SFUNCTION:
		cout << "Function " << this->name << ": ";
		if (this->sfunction != nullptr) {
			this->sfunction->print();
		}
		break;
	case SSTRUCTD:
		cout << "StructDefine " << this->name << ": ";
		if (this->stype != nullptr) {
			this->stype->print();
		}
		break;
	default:
		break;
	}
}

void Symbol::printFunctionType() {
	cout << this->name << " (";
	if (this->sfunction->argumentList != nullptr) {
		this->sfunction->argumentList->print();
	}
	cout << ")";
}

bool Symbol::equal(Symbol* symbol) {
	if (this == symbol)return true;
	if (symbol == nullptr)return false;
	if (this->kind != symbol->kind)return false;
	switch (this->kind) {
	case STYPE:
		return (this->stype->equal(symbol->stype));
		break;
	case SFUNCTION:
		return (this->sfunction->equal(symbol->sfunction));
		break;
	case SSTRUCTD:
		return (this->stype->equal(symbol->stype));
		//return (this->stype->tstruct->equalToArguments(symbol->stype->tstruct));
		break;
	default:
		break;
	}
	return false;
}

void initTable(map<string, Symbol>& table) {
	Function* funcRead = new Function();
	funcRead->returnType = new Type();
	funcRead->returnType->kind = KBASE;
	funcRead->returnType->tbase = BINT;
	funcRead->isDefined = 1;
	Symbol funcReadSymbol(SFUNCTION, "read", funcRead);
	//table["read"] = funcReadSymbol;
	table.insert(make_pair("read",funcReadSymbol));

	Function* funcWrite = new Function();
	funcWrite->returnType = new Type();
	funcWrite->returnType->kind = KBASE;
	funcWrite->returnType->tbase = BINT;
	funcWrite->argumentList = new VariableList();
	funcWrite->argumentList->type = new Type();
	funcWrite->argumentList->type->kind = KBASE;
	funcWrite->argumentList->type->tbase = BINT;
	funcWrite->isDefined = 1;
	Symbol funcWriteSymbol(SFUNCTION, "write", funcWrite);
	//table["write"] = funcWriteSymbol;
	table.insert(make_pair("write",funcWriteSymbol));
}

int getTypeSize(Type* type) {
	int size = 0;

	if (type != nullptr) {
		VariableList* cur = nullptr;

		switch (type->kind) {
		case KBASE:
			size = 4;
			break;
		case KARRAY:
			size = getTypeSize(type->tarray.element) * type->tarray.size;
			break;
		case KSTRUCT:
			cur = type->tstruct;
			while (cur != nullptr) {
				size += getTypeSize(cur->type);
				cur = cur->next;
			}
			break;
		default:
			break;
		}
	}

	return size;
}

mapi searchInTable(string name,map<string, Symbol>& table){
	return table.find(name);
}

void printTable(map<string, Symbol>& table) {
	cout<<"# symbol table"<<endl;
	map<string, Symbol>::iterator i = table.begin();
	while (i != table.end()) {
		i->second.print();
		cout << endl;
		i++;
	}
}

// int main() {
// 	cout << 114 << endl;
// 	map<string, Symbol> symbolTable;
// 	initTable(symbolTable);
// 	printTable(symbolTable);
// 	cout << 514 << endl;
// 	return 0;
// }