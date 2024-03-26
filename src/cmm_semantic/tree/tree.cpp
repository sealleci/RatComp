#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "./tree.h"
using namespace std;
node* createVTNode(int nodeType,string nodeName,int lineNumber){
	node* cur=new node(nodeType,nodeName);
	cur->lineNumber=lineNumber;
	return cur;
}

node* createVTNode(int nodeType,string nodeName,int lineNumber,typeValue VTValue){
	node* cur=new node(nodeType,nodeName);
	cur->lineNumber=lineNumber;
	cur->vtType=VTValue.type;
	if(cur->vtType==0){
		cur->Integer=VTValue.Integer;
	}else if(cur->vtType==1){
		cur->Float=VTValue.Float;
	}else if(cur->vtType==2){
		cur->String=VTValue.String;
	}else{
    cur->String=VTValue.String;
  }
	return cur;
}

node* createVNNode(int nodeType,string nodeName,int lineNumber){
  node* cur=new node(nodeType,nodeName);
  cur->lineNumber=lineNumber;
  return cur;
}

node* createVNNode(int nodeType,string nodeName,int lineNumber,vector<node*> subs){
	node* cur=new node(nodeType,nodeName);
	cur->lineNumber=lineNumber;
	cur->children.resize((int)subs.size());
	for(int i=0;i<(int)subs.size();++i){
		cur->lineNumber=min(cur->lineNumber,subs[i]->lineNumber);
		cur->children[i]=subs[i];
	}
	return cur;
}

void detreeDFS(struct node *cur, int lvl,fstream& file)
{
  if(cur!=nullptr)
  {
    if(cur->nodeName=="EPS"){
      return;
    }
    for(int i=1; i<=2*lvl; ++i){
      file<<" ";
    }

    if(cur->nodeType==0){
      file<<"$";
    }
    file<<cur->nodeName;

    if(cur->nodeType==1){
      if(cur->vtType==0){
        file<<": "<<cur->Integer;
      }else if(cur->vtType==1){
        file<<": "<<cur->Float;
      }else if(cur->vtType==2){
        file<<": "<<cur->String;
      }else{
        //cout<<cur->nodeName<<", "<<cur->vtType<<", "<<cur->String<<"."<<endl;
        file<<": "<<cur->String;
      }
    }

    file<<" ("<<cur->lineNumber<<")"<<endl;

    for (int i=0; i<(int)(cur->children.size()); ++i) {
      detreeDFS(cur->children[i], lvl+1, file);
    }
  }
}

void treeDFS(struct node *cur, int lvl, int fflag,fstream& file)
{
  if(cur!=nullptr)
  {
  	if(cur->nodeName=="EPS"){
  		return;
  	}
    for(int i=1; i<=2*lvl; ++i){
      cout<<" ";
      if(fflag==1)file<<" ";
    }

    cout<<cur->nodeName;
    if(fflag==1)file<<cur->nodeName;
    if(cur->nodeType==0){
    	cout<<" ("<<cur->lineNumber<<")";
    	if(fflag==1)file<<" ("<<cur->lineNumber<<")";
    }else{
    	if(cur->vtType==0){
    		cout<<": "<<cur->Integer;
    		if(fflag==1)file<<": "<<cur->Integer;
    	}else if(cur->vtType==1){
    		cout<<": "<<cur->Float;
    		if(fflag==1)file<<": "<<cur->Float;
    	}else if(cur->vtType==2){
    		cout<<": "<<cur->String;
    		if(fflag==1)file<<": "<<cur->String;
    	}
    }
    cout<<endl;
    if(fflag==1)file<<endl;

    for (int i=0; i<(int)(cur->children.size()); ++i) {
      treeDFS(cur->children[i], lvl+1, fflag,file);
    }
  }
}

void printTree(struct node *cur,const string& outFilePath,int type)
{
	fstream file(outFilePath,ios::out|ios::trunc);
  if(type==0){
    treeDFS(cur, 0, 1, file);
  }else if(type==1){
    detreeDFS(cur, 0, file);
  }
  file.close();
}

void showTree(struct node *cur)
{
  fstream file;
  treeDFS(cur, 0, 0, file);
}

string join(const vector<string> &strs,const string sep){
  string res=strs[0];
  for(int i=1;i<(int)strs.size();++i){
    res+=sep;
    res+=strs[i];
  }
  return res;
}

vector<string> split(const string s,const string sep){
  vector<string> result;
  string::size_type pos1,pos2;
  pos2=s.find(sep);
  pos1=0;
  while(string::npos!=pos2)
  {
    result.push_back(s.substr(pos1,pos2-pos1));
    pos1=pos2+sep.size();
    pos2=s.find(sep,pos1);
  }
  if(pos1!=s.length())
    result.push_back(s.substr(pos1));
  return result;
}

inline int getBlanks(const string str){
  int res=0;
  for(char curChar:str){
      if(curChar==' '){
        res++;
      }else{
        break;
      }
    }
  return res;
}

node* getCurNode(const string str){
  node* curNode=nullptr;
  vector<string> components=split(str," ");
  if(components[0].back()==':'){
    string name=components[0].substr(0,components[0].length()-1);
    typeValue tmpVTVal;
    int lineNum=atoi(components[2].substr(1,components[2].length()-2).c_str());

    if(name=="TYPE"){
      tmpVTVal.type=2;
      tmpVTVal.String=components[1];
    }else if(name=="INT"){
      tmpVTVal.type=0;
      tmpVTVal.Integer=atoi(components[1].c_str());
    }else if(name=="FLOAT"){
      tmpVTVal.type=1;
      tmpVTVal.Float=atof(components[1].c_str());
    }else if(name=="ID"){
      tmpVTVal.type=2;
      tmpVTVal.String=components[1];
    }else{
      tmpVTVal.type=-1;
      tmpVTVal.String=components[1];
    }
    curNode=createVTNode(1,name,lineNum,tmpVTVal);
  }else if(components[0].front()=='$'){
    int lineNum=atoi(components[1].substr(1,components[1].length()-2).c_str());
    string name=components[0].substr(1);
    curNode=createVNNode(0,name,lineNum);
  }
  return curNode;
}

node* scanDFS(int curLine,vector<string>& content){
  int blanks=getBlanks(content[curLine]);
  string trimed=content[curLine].substr(blanks);
  blanks>>=1;

  node* curNode=getCurNode(trimed);

  if(curNode->nodeType==0){
  for(int i=curLine+1;i<(int)content.size();++i){
    int tmpBlanks=getBlanks(content[i]);
    tmpBlanks>>=1;

    if(tmpBlanks==blanks+1){
      curNode->children.push_back(scanDFS(i,content));
    }else if(tmpBlanks<=blanks){
      break;
    }
  }
  }

  return curNode;
}

node* readTree(const string &filePath){
  vector<string> content;
  fstream file(filePath,ios::in);
  string line="";

  while(getline(file,line)){
    if(line!=""){
      content.push_back(line);
    }
  }
  file.close();

  node* root=nullptr;
  root=scanDFS(0,content);
  return root;
}

string getVTStr(struct node* cur){
  if(cur->nodeType==1){
    if(cur->vtType==0){
      return to_string(cur->Integer);
    }else if(cur->vtType==1){
      return to_string(cur->Float);
    }else if(cur->vtType==2){
      return cur->String;
    }else{
      return cur->String;
    }
  }else{
    string tmp="";
    for(int i=0;i<(int)cur->children.size();++i){
      tmp+=getVTStr(cur->children[i]);
    }
    return tmp;
  }
}