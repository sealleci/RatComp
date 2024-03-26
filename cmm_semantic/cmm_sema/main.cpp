#include <bits/stdc++.h>
#include "../tree/tree.h"
#include "./symbol_table.h"
#include "./sematic.h"
#include "./inter_code.h"
using namespace std;

extern smap symbolTable;
#define stab symbolTable

void initFile(const string filePath){
	fstream file(filePath, ios::out|ios::trunc);
	file.close();
}

int main() {
	const string filePath = "../cmm_out/tree_details.out";
	const string semaFilePath = "../cmm_out/sema_err.out";
	const string irFilePath = "../cmm_out/ir.out";
	initFile(semaFilePath);
	initFile(irFilePath);

	node* root = nullptr;
	root = readTree(filePath);
	//showTree(root);

	initTable(stab);
	if(checkSematic(root)){
		//printTable(stab);
		//cout<<endl;
		ls codes=genIR(root,stab);
		fstream irfile(irFilePath,ios::out|ios::app);
		logCode(codes,irfile);
		irfile.close();
	}

	return 0;
}