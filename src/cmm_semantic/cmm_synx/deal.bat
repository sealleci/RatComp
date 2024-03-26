bison -d -v -t cmm.y
flex cmm.l
g++ -o parser.exe cmm.tab.c lex.yy.c "../tree/tree.cpp"
parser.exe