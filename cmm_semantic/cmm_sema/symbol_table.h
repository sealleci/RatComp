#ifndef SYMBOL_TABLE
#define SYMBOL_TABLE

#include <string>
#include <map>
#include <iterator>
using namespace std;

struct Type;
struct VariableList;
struct Function;
struct Symbol;

typedef enum {KBASE, KARRAY, KSTRUCT} TypeKind;
typedef enum {BINT, BFLOAT} BaseKind;
typedef enum {STYPE, SFUNCTION, SSTRUCTD} SymbolKind;
typedef struct {Type* element; int size;} ArrayKind;
typedef union {BaseKind tbase; ArrayKind tarray; VariableList* tstruct;} TypeContent;
typedef union {Type* stype; Function* sfunction;} SymbolContent;
typedef map<string, Symbol> smap;
typedef map<string, Symbol>::iterator mapi;

struct Type {
	TypeKind kind;
	BaseKind tbase;
	ArrayKind tarray;
	VariableList* tstruct = nullptr;

	string getStr();
	void print();
	bool equal(Type*);
};

struct VariableList {
	string name = "";
	Type* type = nullptr;
	VariableList* next = nullptr;

	string getStr();
	void print();
	bool equalToStruct(VariableList*);
	bool equalToArguments(VariableList*);
	Type* getType(string);
};

struct Function {
	Type* returnType = nullptr;
	VariableList* argumentList = nullptr;
	bool isDefined;

	void print();
	bool equal(Function*);
};

struct Symbol {
	SymbolKind kind;
	string name = "";
	int lineNumber=1;
	Type* stype = nullptr;
	Function* sfunction = nullptr;

	Symbol();
	Symbol(SymbolKind, string, Type*);
	Symbol(SymbolKind, string, Function*);
	Symbol(const Symbol&);
	void print();
	void printFunctionType();
	bool equal(Symbol*);
};

void initTable(map<string, Symbol>&);
int getTypeSize(Type*);
mapi searchInTable(string,map<string, Symbol>&);
void printTable(map<string, Symbol>&);


#endif