#ifndef TREE
#define TREE
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node{
	int nodeType=0;//0是非终结符，1是终结符
	string nodeName="";
	int lineNumber=1;
	int vtType=-1;//0是int,1是float,2是string
	int Integer=0;
	float Float=0.0;
	string String="";
	vector<node*> children;
	node(){}
	node(int type,string name){
		this->nodeType=type;
		this->nodeName=name;
	}
	node(node& a){
		this->nodeType=a.nodeType;
		this->nodeName=a.nodeName;
		this->lineNumber=a.lineNumber;
		this->vtType=a.vtType;
		this->Integer=a.Integer;
		this->Float=a.Float;
		this->String=a.String;
		this->children.resize(a.children.size());
		for(int i=0;i<(int)a.children.size();++i){
			this->children[i]=a.children[i];
		}
	}
};

struct typeValue{
	int type=-1;//0是int,1是float,2是string,-1是默认
	int Integer=0;
	float Float=1.0;
	string String="";
	typeValue(){}
	typeValue(int type){this->type=type;}
};

node* createVTNode(int ,string ,int );
node* createVTNode(int ,string ,int ,typeValue );
node* createVNNode(int ,string ,int );
node* createVNNode(int ,string ,int ,vector<node*> );
void detreeDFS(struct node*, int, fstream& );
void treeDFS(struct node*, int , int ,fstream& );
void printTree(struct node*,const string&,int);
void showTree(struct node*);
string join(const vector<string>&,const string);
vector<string> split(const string,const string);
inline int getBlanks(const string);
node* getCurNode(const string);
node* scanDFS(int,vector<string>&);
node* readTree(const string&);
string getVTStr(struct node*);

#endif