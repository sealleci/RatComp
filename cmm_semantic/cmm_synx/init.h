#ifndef INIT_H
#define INIT_H
#include <iostream>//使用C++库
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <fstream>
using namespace std;
#define YYSTYPE node*
struct YYLTYPE{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
#endif