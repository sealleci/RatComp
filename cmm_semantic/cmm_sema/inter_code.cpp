#include <bits/stdc++.h>
#include "../tree/tree.h"
#include "./symbol_table.h"
#include "./inter_code.h"
using namespace std;
#define cchld cur->children
#define symi i->second
#define srcht searchInTable
#define mgcode codes.insert(codes.end(),codes2.begin(),codes2.end())
map<int, Operand*> consts;
map<string, Operand*> constv;

Operand::Operand() {}
Operand::Operand(OperandType type, string name) {
	this->kind = type;
	if (type == TVAR) {
		this->name = name;
	}
}
Operand::Operand(OperandType type, Operand* op) {
	this->kind = type;
	if (type == TREF || type == TDEREF) {
		this->op = op;
	}
}
Operand::Operand(OperandType type, int value) {
	this->kind = type;
	this->value = value;
}
bool Operand::equal(Operand* op) {
	if (this == op)return true;
	if (op == nullptr)return false;
	if (this->kind == TVAR) {
		if (this->kind == op->kind) {
			if (this->name == op->name) {
				return true;
			}
		}
	}
	if (this->kind == op->kind
	        && this->value == op->value) {
		return true;
	}
	return false;
}

InterCode::InterCode() {}
InterCode::InterCode(IncodeType type, Operand* t, Operand* a, Operand* b) {
	this->kind = type;
	this->ibin.t = t;
	this->ibin.a = a;
	this->ibin.b = b;
}

int getNewParam() {
	static int i = 1;
	return i++;
}

int getNewArg() {
	static int i = 1;
	return i++;
}

int tmpi = 1;
Operand* getNewTemp() {
	Operand* op = new Operand();
	op->kind = TTEMP;
	op->value = tmpi++;
	return op;
}

int labi = 1;
Operand* getNewLabel() {
	Operand* op = new Operand();
	op->kind = TLAB;
	op->value = labi++;
	return op;
}

void logOp(Operand* op, fstream& file) {
	if (op == nullptr) {
		cout << "nullptr OP" << endl;
		return;
	}

	switch (op->kind) {
	case TVAR:
		file << op->name;
		break;
	case TCONST:
		file << "#" << op->value;
		break;
	case TTEMP:
		file << "_t" << op->value;
		break;
	case TLAB:
		file << "lab" << op->value;
		break;
	case TREF:
		file << "&";
		logOp(op->op, file);
		break;
	case TDEREF:
		file << "*";
		logOp(op->op, file);
		break;
	default:
		file << op->value;
		break;
	}
}

int logCode(ls& codes, fstream& file) {
	if (codes.size() == 0) {
		cout << "nullptr IR" << endl;
		return 0;
	}

	int count = 0;
	lsi i = codes.begin();
	while (i != codes.end()) {
		switch (i->kind) {
		case IASGN:
			logOp(i->ibin.t, file);
			file << " := ";
			logOp(i->ibin.a, file);
			break;
		case IADD:
			logOp(i->ibin.t, file);
			file << " := ";
			logOp(i->ibin.a, file);
			file << " + ";
			logOp(i->ibin.b, file);
			break;
		case ISUB:
			logOp(i->ibin.t, file);
			file << " := ";
			logOp(i->ibin.a, file);
			file << " - ";
			logOp(i->ibin.b, file);
			break;
		case IMUL:
			logOp(i->ibin.t, file);
			file << " := ";
			logOp(i->ibin.a, file);
			file << " * ";
			logOp(i->ibin.b, file);
			break;
		case IDIV:
			logOp(i->ibin.t, file);
			file << " := ";
			logOp(i->ibin.a, file);
			file << " / ";
			logOp(i->ibin.b, file);
			break;
		case IDEC:
			file << "DEC ";
			logOp(i->ibin.a, file);
			if (i->ibin.b != nullptr) {
				file << " " << i->ibin.b->value;
			}
			break;
		case IFUNC:
			file << "FUNCTION " << i->ibin.a->name << " :";
			break;
		case IPRM:
			file << "PARAM ";
			logOp(i->ibin.a, file);
			break;
		case ILAB:
			file << "LABEL ";
			logOp(i->ibin.a, file);
			file << " :";
			break;
		case IRET:
			file << "RETURN ";
			logOp(i->ibin.a, file);
			break;
		case IGOTO:
			file << "GOTO ";
			logOp(i->ibin.a, file);
			break;
		case IJL:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " < ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IJG:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " > ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IJGE:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " >= ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IJLE:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " <= ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IJE:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " == ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IJNE:
			file << "IF ";
			logOp(i->ibin.a, file);
			file << " != ";
			logOp(i->ibin.b, file);
			file << " GOTO ";
			logOp(i->ibin.t, file);
			break;
		case IARG:
			file << "ARG ";
			logOp(i->ibin.a, file);
			break;
		case ICALL:
			logOp(i->ibin.t, file);
			file << " := CALL ";
			logOp(i->ibin.a, file);
			break;
		case IREAD:
			file << "READ ";
			logOp(i->ibin.t, file);
			break;
		case IWRITE:
			file << "WRITE ";
			logOp(i->ibin.a, file);
			break;
		case IREF:
			logOp(i->ibin.t, file);
			file << " := &";
			logOp(i->ibin.a, file);
			break;
		case IDEREF:
			logOp(i->ibin.t, file);
			file << " := *";
			logOp(i->ibin.a, file);
			break;
		default:
			cout << "code";
			break;
		}

		file << endl;
		count++;
		i++;
	}

	return count;
}

IncodeType getRelopType(node* cur) {
	if (cur == nullptr)return IJL;
	if (cur->nodeName != "RELOP")return IJL;
	string relop = cur->String;
	if (relop == "<")return IJL;
	else if (relop == ">")return IJG;
	else if (relop == ">=")return IJGE;
	else if (relop == "<=")return IJLE;
	else if (relop == "==")return IJE;
	else if (relop == "!=")return IJNE;
	return IJL;
}

ls genIR(node* root, smap& stab) {
	if (root == nullptr) {
		ls tmp;
		return tmp;
	}

	return trsProgram(root, stab);
}

ls trsProgram(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "program") {
		ls tmp;
		return tmp;
	}
	ls codes = trsExtDefList(cchld[0], stab);
	return codes;
}

ls trsExtDefList(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "extDefList") {
		ls tmp;
		return tmp;
	}
	ls codes = trsExtDef(cchld[0], stab);
	if (cchld.size() >= 2) {
		ls codes2 = trsExtDefList(cchld[1], stab);
		mgcode;
	}
	return codes;
}

ls trsExtDef(node* cur, smap& stab) {
	if (cur == nullptr
	        || cur->nodeName != "extDef"
	        || cchld.size() < 2) {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld[1]->nodeName == "funcDec") {
		codes = trsFunDec(cchld[1], stab);
		ls codes2 = trsCompSt(cchld[2],nullptr,stab);
		mgcode;
	} else if (cchld[1]->nodeName == "extDecList") {
		codes = trsExtDecList(cchld[1], stab);
	}
	return codes;
}

ls trsExtDecList(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "extDecList") {
		ls tmp;
		return tmp;
	}
	ls codes = trsVarDec(cchld[0], stab);
	if (cchld.size() >= 3) {
		ls codes2 = trsExtDecList(cchld[2], stab);
		mgcode;
	}
	return codes;
}

ls trsVarDec(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "varDec") {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld[0]->nodeName == "ID") {
		mapi i = srcht(cchld[0]->String, stab);
		if (i != stab.end()) {
			if (symi.kind == STYPE
			        && symi.stype->kind != KBASE) {
				Operand* p1 = getNewTemp();
				Operand* p2 = new Operand(TCONST, getTypeSize(symi.stype));
				codes.push_back(InterCode(IDEC, nullptr, p1, p2));
				Operand* p3 = new Operand(TVAR, cchld[0]->String);
				Operand* p4 = new Operand(TREF, p1);
				codes.push_back(InterCode(IASGN, p3, p4, nullptr));
			}
		}
	} else {
		codes = trsVarDec(cchld[0], stab);
	}
	return codes;
}

ls trsFunDec(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "funcDec") {
		ls tmp;
		return tmp;
	}
	ls codes;
	mapi i = srcht(cchld[0]->String, stab);
	if (i != stab.end()) {
		Operand* p1 = new Operand(TVAR, cchld[0]->String);
		codes.push_back(InterCode(IFUNC, nullptr, p1, nullptr));
		ls codes2;
		VariableList* p = symi.sfunction->argumentList;
		while (p != nullptr) {
			Operand* p2 = new Operand(TVAR, p->name);
			codes2.push_back(InterCode(IPRM, nullptr, p2, nullptr));
			p = p->next;
		}
		mgcode;
	}
	return codes;
}

ls trsCompSt(node* cur,Operand* prevLab, smap& stab) {
	if (cur == nullptr || cur->nodeName != "compSt") {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld.size() == 3) {
		if (cchld[1]->nodeName == "defList") {
			codes = trsDefList(cchld[1], stab);
		} else if (cchld[1]->nodeName == "stmtList") {
			codes = trsStmtList(cchld[1],prevLab, stab);
		}
	} else if (cchld.size() == 4) {
		codes = trsDefList(cchld[1], stab);
		ls codes2 = trsStmtList(cchld[2],prevLab,stab);
		mgcode;
	}
	return codes;
}

ls trsDefList(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "defList") {
		ls tmp;
		return tmp;
	}
	ls codes;
	codes = trsDef(cchld[0], stab);
	if (cchld.size() >= 2) {
		ls codes2 = trsDefList(cchld[1], stab);
		mgcode;
	}
	return codes;
}

ls trsDef(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "def") {
		ls tmp;
		return tmp;
	}
	ls codes = trsDecList(cchld[1], stab);
	return codes;
}

ls trsDecList(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "decList") {
		ls tmp;
		return tmp;
	}
	ls codes;
	codes = trsDec(cchld[0], stab);
	if (cchld.size() >= 3) {
		ls codes2 = trsDecList(cchld[2], stab);
		mgcode;
	}
	return codes;
}

ls trsDec(node* cur, smap& stab) {
	if (cur == nullptr || cur->nodeName != "dec") {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld.size() == 1) {
		codes = trsVarDec(cchld[0], stab);
	} else if (cchld.size() == 3) {
		if (cchld[0]->children[0]->nodeName == "ID") {
			mapi i = srcht(cchld[0]->children[0]->String, stab);
			if (i != stab.end()) {
				Operand* t1 = getNewTemp();
				Operand* p1 = new Operand(TVAR, symi.name);
				codes = trsExp(cchld[2], t1, stab);
				codes.push_back(InterCode(IASGN, p1, t1, nullptr));
			}
		}
	}
	return codes;
}

ls trsStmtList(node* cur,Operand* prevLab, smap& stab) {
	if (cur == nullptr || cur->nodeName != "stmtList") {
		ls tmp;
		return tmp;
	}
	ls codes;
	codes = trsStmt(cchld[0],prevLab,stab);
	if (cchld.size() >= 2) {
		ls codes2 = trsStmtList(cchld[1],prevLab,stab);
		mgcode;
	}
	return codes;
}

ls trsStmt(node* cur,Operand* prevLab,smap& stab) {
	if (cur == nullptr || cur->nodeName != "stmt") {
		ls tmp;
		return tmp;
	}
	// if(prevLab!=nullptr){
	// 	cout<<"prev:"<<prevLab->value<<",node:"<<cchld[0]->nodeName<<endl;
	// }
	ls codes;
	if (cchld[0]->nodeName == "exp") {
		//UNK
		Operand* t1 = nullptr;
		// if(cchld[0]->children[0]->nodeName=="ID"){
		// 	mapi i = srcht(cchld[0]->children[0]->String, stab);
		// 	if (i != stab.end()) {
		// 		t1=new Operand();
		// 		t1->kind = TVAR;
		// 		t1->name = symi.name;
		// 	}else{
		// 		t1 = getNewTemp();
		// 	}
		// }else{
		// 	t1 = getNewTemp();
		// }
		codes = trsExp(cchld[0], t1, stab);
	} else if (cchld[0]->nodeName == "compSt") {
		codes = trsCompSt(cchld[0],prevLab,stab);
	} else if (cchld[0]->nodeName == "RETURN") {
		Operand* t1 = nullptr;
		if (cchld[1]->children[0]->nodeName == "ID" && cchld[1]->children.size() == 1) {
			mapi i = srcht(cchld[1]->children[0]->String, stab);
			if (i != stab.end()) {
				t1 = new Operand();
				t1->kind = TVAR;
				t1->name = symi.name;
			} else {
				t1 = getNewTemp();
			}
		} else {
			t1 = getNewTemp();
		}
		codes = trsExp(cchld[1], t1, stab);
		codes.push_back(InterCode(IRET, nullptr, t1, nullptr));
	} else if (cchld[0]->nodeName == "IF") {
		if (cchld.size() == 5) {
			Operand* l1 = getNewLabel();
			Operand* l2=nullptr ;
			if(prevLab!=nullptr){
				l2 = prevLab;
			}else if(cchld[4]->children[0]->nodeName != "RETURN"){
				l2 = getNewLabel();
			}
			codes = trsCond(cchld[2], l1, l2, stab);
			ls codes2 = trsStmt(cchld[4],nullptr,stab);
			ls codes3, codes4;
			//codes label1 codes2 gotolable2 lable1 codes2 lable2
			codes3.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			if(prevLab==nullptr&&cchld[4]->children[0]->nodeName != "RETURN"){
				codes4.push_back(InterCode(ILAB, nullptr, l2, nullptr));
			}
			codes2.insert(codes2.end(), codes4.begin(), codes4.end());
			codes3.insert(codes3.end(), codes2.begin(), codes2.end());
			codes.insert(codes.end(), codes3.begin(), codes3.end());
		} else if (cchld.size() == 7) {
			Operand* l1 = getNewLabel();
			Operand* l2 = nullptr;
			if(prevLab!=nullptr){
				//cout<<"!"<<endl;
				l2 = prevLab;
			}else if(cchld[4]->children[0]->nodeName != "RETURN"){
				l2 = getNewLabel();
				//cout<<"cur:"<<l2->value<<endl;
			}
			codes = trsCond(cchld[2], l1, nullptr, stab);
			codes.pop_back();
			//ls codes2;
			ls codes2 = trsStmt(cchld[4],nullptr,stab);
			ls codes3 = trsStmt(cchld[6],l2,stab);
			//codes label1 codes3 gotolable2 lable1 codes2 lable2
			codes.insert(codes.end(), codes3.begin(), codes3.end());
			if(cchld[6]->children[0]->nodeName != "RETURN"){
				codes.push_back(InterCode(IGOTO, nullptr, l2, nullptr));
			}
			codes.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			codes.insert(codes.end(), codes2.begin(), codes2.end());
			if(prevLab==nullptr&&cchld[4]->children[0]->nodeName != "RETURN"){
				codes.push_back(InterCode(ILAB, nullptr, l2, nullptr));
			}
			// l3 = getNewLabel();
			// codes4.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			// codes5.push_back(InterCode(IGOTO, nullptr, l3, nullptr));
			// codes6.push_back(InterCode(ILAB, nullptr, l2, nullptr));
			// codes7.push_back(InterCode(ILAB, nullptr, l3, nullptr));

			// codes3.insert(codes3.end(), codes7.begin(), codes7.end());
			// codes6.insert(codes6.end(), codes3.begin(), codes3.end());
			// codes5.insert(codes5.end(), codes6.begin(), codes6.end());
			// codes2.insert(codes2.end(), codes5.begin(), codes5.end());
			// codes4.insert(codes4.end(), codes2.begin(), codes2.end());
			// codes.insert(codes.end(), codes4.begin(), codes4.end());
		}
	} else if (cchld[0]->nodeName == "WHILE") {
		Operand* l1 = getNewLabel();
		Operand* l2 = getNewLabel();
		Operand* l3 = getNewLabel();
		codes = trsCond(cchld[2], l2, l3, stab);
		ls codes2 = trsStmt(cchld[4],nullptr,stab);
		ls codes3, codes4, codes5, codes6;
		codes3.push_back(InterCode(ILAB, nullptr, l1, nullptr));
		codes4.push_back(InterCode(ILAB, nullptr, l2, nullptr));
		codes5.push_back(InterCode(IGOTO, nullptr, l1, nullptr));
		codes6.push_back(InterCode(ILAB, nullptr, l3, nullptr));
		codes5.insert(codes5.end(), codes6.begin(), codes6.end());
		codes2.insert(codes2.end(), codes5.begin(), codes5.end());
		codes4.insert(codes4.end(), codes2.begin(), codes2.end());
		codes.insert(codes.end(), codes4.begin(), codes4.end());
		codes3.insert(codes3.end(), codes.begin(), codes.end());
		codes.assign(codes3.begin(), codes3.end());
	}
	return codes;
}

ls trsExp(node* cur, Operand*& place, smap& stab) {
	if (cur == nullptr || cur->nodeName != "exp") {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld[0]->nodeName == "exp") {
		if (cchld[1]->nodeName == "ASSIGNOP") {
			if (cchld[0]->children[0]->nodeName == "ID") {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					Operand* t1 = getNewTemp();
					codes = trsExp(cchld[2], t1, stab);
					Operand* l = new Operand();
					l->kind = TVAR;
					l->name = symi.name;
					ls codes2;
					codes2.push_back(InterCode(IASGN, l, t1, nullptr));
					if (place != nullptr) {
						codes2.push_back(InterCode(IASGN, place, l, nullptr));
					}
					mgcode;
				}
			} else if (cchld[0]->children[0]->nodeName == "exp") {
				if (cchld[0]->children[1]->nodeName == "DOT"
				        || cchld[0]->children[1]->nodeName == "LB") {
					Operand* t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
					Operand* t2 = getNewTemp();
					ls codes2 = trsExp(cchld[2], t2, stab);
					codes2.push_back(InterCode(IASGN, t1, t2, nullptr));
					mgcode;
					if (place != nullptr) {
						codes.push_back(InterCode(IASGN, place, t1, nullptr));
					}
				}
			}
		} else if (cchld[1]->nodeName == "PLUS") {
			Operand* t1 = nullptr;
			Operand* t2 = nullptr;
			ls codes2;
			if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					t1 = new Operand();
					t1->kind = TVAR;
					t1->name = symi.name;
				} else {
					t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
				}
			} else {
				t1 = getNewTemp();
				codes = trsExp(cchld[0], t1, stab);
			}
			if (cchld[2]->children[0]->nodeName == "ID" && cchld[2]->children.size() == 1) {
				mapi i = srcht(cchld[2]->children[0]->String, stab);
				if (i != stab.end()) {
					t2 = new Operand();
					t2->kind = TVAR;
					t2->name = symi.name;
				} else {
					t2 = getNewTemp();
					codes2 = trsExp(cchld[2], t2, stab);
				}
			} else {
				t2 = getNewTemp();
				codes2 = trsExp(cchld[2], t2, stab);
			}
			codes2.push_back(InterCode(IADD, place, t1, t2));
			mgcode;
		} else if (cchld[1]->nodeName == "MINUS") {
			Operand* t1 = nullptr;
			Operand* t2 = nullptr;
			ls codes2;
			if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					t1 = new Operand();
					t1->kind = TVAR;
					t1->name = symi.name;
				} else {
					t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
				}
			} else {
				t1 = getNewTemp();
				codes = trsExp(cchld[0], t1, stab);
			}
			if (cchld[2]->children[0]->nodeName == "ID" && cchld[2]->children.size() == 1) {
				mapi i = srcht(cchld[2]->children[0]->String, stab);
				if (i != stab.end()) {
					t2 = new Operand();
					t2->kind = TVAR;
					t2->name = symi.name;
				} else {
					t2 = getNewTemp();
					codes2 = trsExp(cchld[2], t2, stab);
				}
			} else {
				t2 = getNewTemp();
				codes2 = trsExp(cchld[2], t2, stab);
			}
			codes2.push_back(InterCode(ISUB, place, t1, t2));
			mgcode;
		} else if (cchld[1]->nodeName == "STAR") {
			Operand* t1 = nullptr;
			Operand* t2 = nullptr;
			ls codes2;
			if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					t1 = new Operand();
					t1->kind = TVAR;
					t1->name = symi.name;
				} else {
					t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
				}
			} else {
				t1 = getNewTemp();
				codes = trsExp(cchld[0], t1, stab);
			}
			if (cchld[2]->children[0]->nodeName == "ID" && cchld[2]->children.size() == 1) {
				mapi i = srcht(cchld[2]->children[0]->String, stab);
				if (i != stab.end()) {
					t2 = new Operand();
					t2->kind = TVAR;
					t2->name = symi.name;
				} else {
					t2 = getNewTemp();
					codes2 = trsExp(cchld[2], t2, stab);
				}
			} else {
				t2 = getNewTemp();
				codes2 = trsExp(cchld[2], t2, stab);
			}
			codes2.push_back(InterCode(IMUL, place, t1, t2));
			mgcode;
		} else if (cchld[1]->nodeName == "DIV") {
			Operand* t1 = nullptr;
			Operand* t2 = nullptr;
			ls codes2;
			if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					t1 = new Operand();
					t1->kind = TVAR;
					t1->name = symi.name;
				} else {
					t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
				}
			} else {
				t1 = getNewTemp();
				codes = trsExp(cchld[0], t1, stab);
			}
			if (cchld[2]->children[0]->nodeName == "ID" && cchld[2]->children.size() == 1) {
				mapi i = srcht(cchld[2]->children[0]->String, stab);
				if (i != stab.end()) {
					t2 = new Operand();
					t2->kind = TVAR;
					t2->name = symi.name;
				} else {
					t2 = getNewTemp();
					codes2 = trsExp(cchld[2], t2, stab);
				}
			} else {
				t2 = getNewTemp();
				codes2 = trsExp(cchld[2], t2, stab);
			}
			codes2.push_back(InterCode(IDIV, place, t1, t2));
			mgcode;
		} else if (cchld[1]->nodeName == "RELOP"
		           || cchld[1]->nodeName == "AND"
		           || cchld[1]->nodeName == "OR") {
			Operand* l1 = getNewLabel();
			Operand* l2 = getNewLabel();
			Operand* op1 = new Operand(TCONST, 0);
			Operand* op2 = new Operand(TCONST, 1);
			ls codes0, codes2, codes3, codes4;
			codes0.push_back(InterCode(IASGN, place, op1, nullptr));
			codes = trsCond(cur, l1, l2, stab);
			codes2.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			codes3.push_back(InterCode(IASGN, place, op2, nullptr));
			codes4.push_back(InterCode(ILAB, nullptr, l2, nullptr));
			codes2.insert(codes2.end(), codes3.begin(), codes3.end());
			codes2.insert(codes2.end(), codes4.begin(), codes4.end());
			codes.insert(codes.end(), codes2.begin(), codes2.end());
			codes0.insert(codes0.end(), codes.begin(), codes.end());
			codes.assign(codes0.begin(), codes0.end());
		} else if (cchld[1]->nodeName == "LB") {
			Type* tmptype = nullptr;
			codes = trsArray(cur, place, tmptype, stab);
		} else if (cchld[1]->nodeName == "DOT") {
			Type* tmptype = nullptr;
			codes = trsStructure(cur, place, tmptype, stab);
		}
	} else if (cchld[0]->nodeName == "ID") {
		if (cchld.size() == 1) {
			mapi i = srcht(cchld[0]->String, stab);
			if (i != stab.end()) {
				if (place != nullptr) {
					if (place->kind == TTEMP) {
						Operand* op2 = new Operand(TVAR, symi.name);
						codes.push_back(InterCode(IASGN, place, op2, nullptr));
					}
				}
			}
		} else if (cchld.size() == 3) {
			mapi i = srcht(cchld[0]->String, stab);
			if (i != stab.end()) {
				if (symi.name == "read") {
					codes.push_back(InterCode(IREAD, place, nullptr, nullptr));
				} else {
					Operand* op1 = new Operand(TVAR, symi.name);
					codes.push_back(InterCode(ICALL, place, op1, nullptr));
				}
			}
		} else if (cchld.size() == 4) {
			mapi i = srcht(cchld[0]->String, stab);
			if (i != stab.end()) {
				ArgumentList* argls = nullptr;
				codes = trsArgs(cchld[2], argls, stab);
				if (symi.name == "write") {
					ls codes2;
					codes2.push_back(InterCode(IWRITE, nullptr, argls->op, nullptr));
					mgcode;
				} else {
					ArgumentList* p = argls;
					ls codes2;
					while (p != nullptr) {
						codes2.push_back(InterCode(IARG, nullptr, p->op, nullptr));
						p = p->next;
					}
					Operand* op1 = new Operand(TVAR, symi.name);
					codes2.push_back(InterCode(ICALL, place, op1, nullptr));
					mgcode;
				}
			}
		}
	} else if (cchld[0]->nodeName == "INT") {
		Operand* op1 = place;
		Operand* op2 = new Operand(TCONST, cchld[0]->Integer);
		if (place != nullptr) {
			if (place->kind == TTEMP) {
				if (consts.find(op2->value) == consts.end()) {
					codes.push_back(InterCode(IASGN, op1, op2, nullptr));
					consts[op2->value] = op1;
				} else {
					place = consts[op2->value];
					tmpi--;
				}
			}
		} else {
			if (consts.find(op2->value) == consts.end()) {
				consts[op2->value] = op1;
			}
		}
	} else if (cchld[0]->nodeName == "FLOAT") {

	} else if (cchld[0]->nodeName == "LP") {
		codes = trsExp(cchld[1], place, stab);
	} else if (cchld[0]->nodeName == "MINUS") {
		if (cchld[1]->children[0]->nodeName == "INT") {
			Operand* op1 = new Operand(TCONST, 0 - cchld[1]->children[0]->Integer);
			//codes.push_back(InterCode(IASGN, place, op1, nullptr));
			if (place != nullptr) {
				if (place->kind == TTEMP) {
					if (consts.find(op1->value) == consts.end()) {
						codes.push_back(InterCode(IASGN, place, op1, nullptr));
						consts[op1->value] = place;
					} else {
						place = consts[op1->value];
						tmpi--;
					}
				}
			} else {
				if (consts.find(op1->value) == consts.end()) {
					codes.push_back(InterCode(IASGN, place, op1, nullptr));
					consts[op1->value] = place;
				}
			}
		} else {
			Operand* t1 = getNewTemp();
			Operand* op1 = new Operand(TCONST, 0);
			codes = trsExp(cchld[1], t1, stab);
			codes.push_back(InterCode(ISUB, place, op1, t1));
		}
	} else if (cchld[0]->nodeName == "NOT") {
		Operand* l1 = getNewLabel();
		Operand* l2 = getNewLabel();
		Operand* op1 = new Operand(TCONST, 0);
		Operand* op2 = new Operand(TCONST, 1);
		ls codes0, codes2, codes3, codes4;
		codes0.push_back(InterCode(IASGN, place, op1, nullptr));
		codes = trsCond(cur, l1, l2, stab);
		codes2.push_back(InterCode(ILAB, nullptr, l1, nullptr));
		codes3.push_back(InterCode(IASGN, place, op2, nullptr));
		codes4.push_back(InterCode(ILAB, nullptr, l2, nullptr));
		codes2.insert(codes2.end(), codes3.begin(), codes3.end());
		codes2.insert(codes2.end(), codes4.begin(), codes4.end());
		codes.insert(codes.end(), codes2.begin(), codes2.end());
		codes0.insert(codes0.end(), codes.begin(), codes.end());
		codes.assign(codes0.begin(), codes0.end());
	}
	return codes;
}

ls trsStructure(node* cur, Operand* place, Type*& type, smap& stab) {
	// if(type==nullptr){
	// 	cout<<"strc type emp!"<<endl;
	// 	ls tmp;
	// 	return tmp;
	// }
	if (cur == nullptr) {
		ls tmp;
		return tmp;
	}
	ls codes, codes2;
	VariableList* list = nullptr;
	Operand* addr = nullptr;
	if (cchld[0]->children[0]->nodeName == "ID") {
		mapi i = srcht(cchld[0]->children[0]->String, stab);
		if (i != stab.end()) {
			//cout<<"id."<<endl;
			if (symi.kind == STYPE
			        && symi.stype->kind == KSTRUCT) {
				list = symi.stype->tstruct;
				//list->print();
				addr = getNewTemp();
				Operand* op1 = new Operand(TVAR, symi.name);
				codes2.push_back(InterCode(IASGN, addr, op1, nullptr));
			}
		}
	} else if (cchld[0]->children[1]->nodeName == "DOT") {
		Type* tmptype = nullptr;
		addr = getNewTemp();
		codes2 = trsStructure(cchld[0], addr, tmptype, stab);
		if (tmptype != nullptr
		        && tmptype->kind == KSTRUCT) {
			list = tmptype->tstruct;
		}
	} else if (cchld[0]->children[1]->nodeName == "LB") {
		Type* tmptype = nullptr;
		addr = getNewTemp();
		codes2 = trsArray(cchld[0], addr, tmptype, stab);
		if (tmptype != nullptr
		        && tmptype->kind == KSTRUCT) {
			list = tmptype->tstruct;
		}
	}
	int offset = 0;
	while (list != nullptr
	        && list->name != cchld[2]->String) {
		//list->type->print();
		//cout<<endl;
		offset += getTypeSize(list->type);
		list = list->next;
	}

	type = list->type;
	//cout<<offset<<endl;
	// if(list->type==nullptr){
	// 	cout<<"s list ty emp!"<<endl;
	// }
	Operand* poffset = new Operand(TCONST, offset);
	if (list->type->kind == KBASE) {
		Operand* t2 = getNewTemp();
		codes2.push_back(InterCode(IADD, t2, addr, poffset));
		place->kind = TDEREF;
		place->op = t2;
		mgcode;
	} else {
		codes2.push_back(InterCode(IADD, place, addr, poffset));
		mgcode;
	}
	return codes;
}

ls trsArray(node* cur, Operand* place, Type*& type, smap& stab) {
	if (cur == nullptr) {
		ls tmp;
		return tmp;
	}
	ls codes, codes2;
	Operand* addr = nullptr;
	Type* arrtype = nullptr;
	if (cchld[0]->children[0]->nodeName == "ID") {
		mapi i = srcht(cchld[0]->children[0]->String, stab);
		if (i != stab.end()) {
			if (symi.kind == STYPE
			        && symi.stype->kind == KARRAY) {
				//cout<<"1"<<endl;
				arrtype = symi.stype;
				//arrtype->print();
				//cout<<endl;
				addr = getNewTemp();
				Operand* op1 = new Operand(TVAR, symi.name);
				codes2.push_back(InterCode(IASGN, addr, op1, nullptr));
			}
		}
	} else if (cchld[0]->children[1]->nodeName == "DOT") {
		Type* tmptype = nullptr;
		addr = getNewTemp();
		codes2 = trsStructure(cchld[0], addr, tmptype, stab);
		if (tmptype != nullptr
		        && tmptype->kind == KARRAY) {
			arrtype = tmptype;
		}
	} else if (cchld[0]->children[1]->nodeName == "LB") {
		Type* tmptype = nullptr;
		addr = getNewTemp();
		//cout<<"2"<<endl;
		codes2 = trsArray(cchld[0], addr, tmptype, stab);

		if (tmptype != nullptr
		        && tmptype->kind == KARRAY) {

			arrtype = tmptype;
		}else{
			cout<<"!"<<endl;
		}
	}

	type = arrtype->tarray.element;
	// cout<<"1"<<endl;
	// if(arrtype==nullptr){
	// 	cout<<"!!"<<endl;
	// }
	Operand* t2 = getNewTemp();
	ls codes3 = trsExp(cchld[2], t2, stab);
	int elmsize = 0;
	elmsize =getTypeSize(arrtype->tarray.element);
	Operand* op1 = new Operand(TCONST, elmsize);
	Operand* poffset = getNewTemp();
	ls codes4;
	codes4.push_back(InterCode(IMUL, poffset, op1, t2));

	if (arrtype->tarray.element->kind == KBASE) {
		Operand* t3 = getNewTemp();
		place->kind = TDEREF;
		place->op = t3;
		codes4.push_back(InterCode(IADD, t3, addr, poffset));
		codes3.insert(codes3.end(), codes4.begin(), codes4.end());
		codes2.insert(codes2.end(), codes3.begin(), codes3.end());
		mgcode;
	} else {
		codes4.push_back(InterCode(IADD, place, addr, poffset));
		codes3.insert(codes3.end(), codes4.begin(), codes4.end());
		codes2.insert(codes2.end(), codes3.begin(), codes3.end());
		mgcode;
	}
	return codes;
}

ls trsArgs(node* cur, ArgumentList*& argls , smap& stab) {
	if (cur == nullptr) {
		ls tmp;
		return tmp;
	}
	ls codes;
	Operand* t1 = nullptr;
	if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
		mapi i = srcht(cchld[0]->children[0]->String, stab);
		if (i != stab.end()) {
			t1 = new Operand();
			t1->kind = TVAR;
			t1->name = symi.name;
		} else {
			t1 = getNewTemp();
			codes = trsExp(cchld[0], t1, stab);
		}
	} else {
		t1 = getNewTemp();
		codes = trsExp(cchld[0], t1, stab);
	}
	//codes=trsExp(cchld[0],t1,stab);
	ArgumentList* p = new ArgumentList();
	p->op = t1;
	if (argls != nullptr) {
		argls = p;
	} else {
		p->next = argls;
		argls = p;
	}
	if (cchld.size() >= 3) {
		ls codes2 = trsArgs(cchld[2], argls, stab);
		mgcode;
	}
	return codes;
}

ls trsCond(node* cur, Operand* lt, Operand* lf, smap& stab) {
	if (cur == nullptr) {
		ls tmp;
		return tmp;
	}
	ls codes;
	if (cchld[0]->nodeName == "exp") {
		if (cchld[1]->nodeName == "RELOP") {
			Operand* t1 = nullptr;
			Operand* t2 = nullptr;
			ls codes2;
			if (cchld[0]->children[0]->nodeName == "ID" && cchld[0]->children.size() == 1) {
				mapi i = srcht(cchld[0]->children[0]->String, stab);
				if (i != stab.end()) {
					t1 = new Operand();
					t1->kind = TVAR;
					t1->name = symi.name;
				} else {
					t1 = getNewTemp();
					codes = trsExp(cchld[0], t1, stab);
				}
			} else {
				t1 = getNewTemp();
				codes = trsExp(cchld[0], t1, stab);
			}
			if (cchld[2]->children[0]->nodeName == "ID" && cchld[2]->children.size() == 1) {
				mapi i = srcht(cchld[2]->children[0]->String, stab);
				if (i != stab.end()) {
					t2 = new Operand();
					t2->kind = TVAR;
					t2->name = symi.name;
				} else {
					t2 = getNewTemp();
					codes2 = trsExp(cchld[2], t2, stab);
				}
			} else {
				t2 = getNewTemp();
				codes2 = trsExp(cchld[2], t2, stab);
			}
			IncodeType op = getRelopType(cchld[1]);
			ls codes3, codes4;
			codes3.push_back(InterCode(op, lt, t1, t2));
			codes4.push_back(InterCode(IGOTO, nullptr, lf, nullptr));
			codes3.insert(codes3.end(), codes4.begin(), codes4.end());
			codes2.insert(codes2.end(), codes3.begin(), codes3.end());
			codes.insert(codes.end(), codes2.begin(), codes2.end());
		} else if (cchld[1]->nodeName == "AND") {
			Operand* l1 = getNewLabel();
			codes = trsCond(cchld[0], l1, lf, stab);
			ls codes2 = trsCond(cchld[2], lt, lf, stab);
			ls codes3;
			codes3.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			codes3.insert(codes3.end(), codes2.begin(), codes2.end());
			codes.insert(codes.end(), codes3.begin(), codes3.end());
		} else if (cchld[1]->nodeName == "OR") {
			Operand* l1 = getNewLabel();
			codes = trsCond(cchld[0], lt, l1, stab);
			ls codes2 = trsCond(cchld[2], lt, lf, stab);
			ls codes3;
			codes3.push_back(InterCode(ILAB, nullptr, l1, nullptr));
			codes3.insert(codes3.end(), codes2.begin(), codes2.end());
			codes.insert(codes.end(), codes3.begin(), codes3.end());
		}
	} else if (cchld[0]->nodeName == "NOT") {
		codes = trsCond(cur, lf, lt, stab);
	} else {
		Operand* t1 = getNewTemp();
		codes = trsExp(cur, t1, stab);
		Operand* op1 = new Operand(TCONST, 0);
		ls codes2, codes3;
		codes2.push_back(InterCode(IJNE, lt, t1, op1));
		codes3.push_back(InterCode(IGOTO, nullptr, lf, nullptr));
		codes2.insert(codes2.end(), codes3.begin(), codes3.end());
		codes.insert(codes.end(), codes2.begin(), codes2.end());
	}
	return codes;
}