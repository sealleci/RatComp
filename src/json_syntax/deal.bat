cd /d "./_json_"
flex jsonw.flex
g++ lex.yy.c -o lex.yy
call lex.yy
g++ jsonl.cpp -o jsonl.exe
call jsonl.exe
pause
