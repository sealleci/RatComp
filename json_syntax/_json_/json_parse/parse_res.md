gram
====

-   start: S

1.  AC -&gt; EPS
2.  AC -&gt; {AE} {AC+}
3.  AC+ -&gt; EPS
4.  AC+ -&gt; {AES}
5.  AE -&gt; \[LB\] {AC} \[RB\]
6.  AE -&gt; \[LC\] {CS} \[RC\]
7.  AE -&gt; {W}
8.  AES -&gt; \[COMMA\] {AE} {AES+}
9.  AES+ -&gt; EPS
10. AES+ -&gt; {AES}
11. CS -&gt; EPS
12. CS -&gt; {E} {CS+}
13. CS+ -&gt; EPS
14. CS+ -&gt; {CT}
15. CT -&gt; \[COMMA\] {E} {CT+}
16. CT+ -&gt; EPS
17. CT+ -&gt; {CT}
18. E -&gt; \[STR\] \[COLON\] {E+}
19. E+ -&gt; \[LB\] {AC} \[RB\]
20. E+ -&gt; \[LC\] {CS} \[RC\]
21. E+ -&gt; {W}
22. S -&gt; \[LC\] {CS} \[RC\]
23. W -&gt; \[BOOL\]
24. W -&gt; \[NUL\]
25. W -&gt; \[NUM\]
26. W -&gt; \[STR\]

is Able To Deduce To Empty
==========================

-   empty(AC): true
-   empty(AC+): true
-   empty(AE): false
-   empty(AES): false
-   empty(AES+): true
-   empty(CS): true
-   empty(CS+): true
-   empty(CT): false
-   empty(CT+): true
-   empty(E): false
-   empty(E+): false
-   empty(S): false
-   empty(W): false

FIRST
=====

-   FIRST(AC): EPS,\[BOOL\],\[LB\],\[LC\],\[NUL\],\[NUM\],\[STR\]
-   FIRST(AC+): EPS,\[COMMA\]
-   FIRST(AE): \[BOOL\],\[LB\],\[LC\],\[NUL\],\[NUM\],\[STR\]
-   FIRST(AES): \[COMMA\]
-   FIRST(AES+): EPS,\[COMMA\]
-   FIRST(CS): EPS,\[STR\]
-   FIRST(CS+): EPS,\[COMMA\]
-   FIRST(CT): \[COMMA\]
-   FIRST(CT+): EPS,\[COMMA\]
-   FIRST(E): \[STR\]
-   FIRST(E+): \[BOOL\],\[LB\],\[LC\],\[NUL\],\[NUM\],\[STR\]
-   FIRST(S): \[LC\]
-   FIRST(W): \[BOOL\],\[NUL\],\[NUM\],\[STR\]

FOLLOW
======

-   FOLLOW(AC): \[RB\]
-   FOLLOW(AC+): \[RB\]
-   FOLLOW(AE): \[COMMA\],\[RB\]
-   FOLLOW(AES): \[RB\]
-   FOLLOW(AES+): \[RB\]
-   FOLLOW(CS): \[RC\]
-   FOLLOW(CS+): \[RC\]
-   FOLLOW(CT): \[RC\]
-   FOLLOW(CT+): \[RC\]
-   FOLLOW(E): \[COMMA\],\[RC\]
-   FOLLOW(E+): \[COMMA\],\[RC\]
-   FOLLOW(S): \[ENDF\]
-   FOLLOW(W): \[COMMA\],\[RB\],\[RC\]

SELECT
======

-   SELECT(AC -&gt; EPS): \[RB\]
-   SELECT(AC -&gt; {AE}{AC+}):
    \[BOOL\],\[LB\],\[LC\],\[NUL\],\[NUM\],\[STR\]
-   SELECT(AC+ -&gt; EPS): \[RB\]
-   SELECT(AC+ -&gt; {AES}): \[COMMA\]
-   SELECT(AE -&gt; \[LB\]{AC}\[RB\]): \[LB\]
-   SELECT(AE -&gt; \[LC\]{CS}\[RC\]): \[LC\]
-   SELECT(AE -&gt; {W}): \[BOOL\],\[NUL\],\[NUM\],\[STR\]
-   SELECT(AES -&gt; \[COMMA\]{AE}{AES+}): \[COMMA\]
-   SELECT(AES+ -&gt; EPS): \[RB\]
-   SELECT(AES+ -&gt; {AES}): \[COMMA\]
-   SELECT(CS -&gt; EPS): \[RC\]
-   SELECT(CS -&gt; {E}{CS+}): \[STR\]
-   SELECT(CS+ -&gt; EPS): \[RC\]
-   SELECT(CS+ -&gt; {CT}): \[COMMA\]
-   SELECT(CT -&gt; \[COMMA\]{E}{CT+}): \[COMMA\]
-   SELECT(CT+ -&gt; EPS): \[RC\]
-   SELECT(CT+ -&gt; {CT}): \[COMMA\]
-   SELECT(E -&gt; \[STR\]\[COLON\]{E+}): \[STR\]
-   SELECT(E+ -&gt; \[LB\]{AC}\[RB\]): \[LB\]
-   SELECT(E+ -&gt; \[LC\]{CS}\[RC\]): \[LC\]
-   SELECT(E+ -&gt; {W}): \[BOOL\],\[NUL\],\[NUM\],\[STR\]
-   SELECT(S -&gt; \[LC\]{CS}\[RC\]): \[LC\]
-   SELECT(W -&gt; \[BOOL\]): \[BOOL\]
-   SELECT(W -&gt; \[NUL\]): \[NUL\]
-   SELECT(W -&gt; \[NUM\]): \[NUM\]
-   SELECT(W -&gt; \[STR\]): \[STR\]

is LL(1) gram: true
===================

grid
====

|      | BOOL            | COMMA                     | LB                     | LC                     | NUL             | NUM             | RB        | RC        | STR                        |
|------|-----------------|---------------------------|------------------------|------------------------|-----------------|-----------------|-----------|-----------|----------------------------|
| AC   | -&gt; {AE}{AC+} |                           | -&gt; {AE}{AC+}        | -&gt; {AE}{AC+}        | -&gt; {AE}{AC+} | -&gt; {AE}{AC+} | -&gt; EPS |           | -&gt; {AE}{AC+}            |
| AC+  |                 | -&gt; {AES}               |                        |                        |                 |                 | -&gt; EPS |           |                            |
| AE   | -&gt; {W}       |                           | -&gt; \[LB\]{AC}\[RB\] | -&gt; \[LC\]{CS}\[RC\] | -&gt; {W}       | -&gt; {W}       |           |           | -&gt; {W}                  |
| AES  |                 | -&gt; \[COMMA\]{AE}{AES+} |                        |                        |                 |                 |           |           |                            |
| AES+ |                 | -&gt; {AES}               |                        |                        |                 |                 | -&gt; EPS |           |                            |
| CS   |                 |                           |                        |                        |                 |                 |           | -&gt; EPS | -&gt; {E}{CS+}             |
| CS+  |                 | -&gt; {CT}                |                        |                        |                 |                 |           | -&gt; EPS |                            |
| CT   |                 | -&gt; \[COMMA\]{E}{CT+}   |                        |                        |                 |                 |           |           |                            |
| CT+  |                 | -&gt; {CT}                |                        |                        |                 |                 |           | -&gt; EPS |                            |
| E    |                 |                           |                        |                        |                 |                 |           |           | -&gt; \[STR\]\[COLON\]{E+} |
| E+   | -&gt; {W}       |                           | -&gt; \[LB\]{AC}\[RB\] | -&gt; \[LC\]{CS}\[RC\] | -&gt; {W}       | -&gt; {W}       |           |           | -&gt; {W}                  |
| S    |                 |                           |                        | -&gt; \[LC\]{CS}\[RC\] |                 |                 |           |           |                            |
| W    | -&gt; \[BOOL\]  |                           |                        |                        | -&gt; \[NUL\]   | -&gt; \[NUM\]   |           |           | -&gt; \[STR\]              |

input words
===========

\[LC\],\[STR\],\[COLON\],\[NUM\],\[COMMA\],\[STR\],\[COLON\],\[LB\],\[LB\],\[NUM\],\[COMMA\],\[NUM\],\[COMMA\],\[NUM\],\[RB\],\[COMMA\],\[LC\],\[STR\],\[COLON\],\[BOOL\],\[COMMA\],\[STR\],\[COLON\],\[BOOL\],\[RC\],\[COMMA\],\[STR\],\[RB\],\[COMMA\],\[STR\],\[COLON\],\[LC\],\[STR\],\[COLON\],\[LC\],\[STR\],\[COLON\],\[NUM\],\[RC\],\[COMMA\],\[STR\],\[COLON\],\[LB\],\[NUM\],\[COMMA\],\[NUM\],\[COMMA\],\[NUM\],\[COMMA\],\[NUL\],\[RB\],\[COMMA\],\[STR\],\[COLON\],\[NUM\],\[RC\],\[RC\]

parsing process
===============

step1
-----

> -   top: {S}
> -   thread:
>
> ~~~ json
> {"kv":1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {S} -&gt; \[LC\] {CS} \[RC\]
> -   pop: {S}
> -   push: \[RC\]
> -   push: {CS}
> -   push: \[LC\]

step2
-----

> -   top: \[LC\]
> -   thread:
>
> ~~~ json
> {"kv":1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LC\] == \[LC\]
> -   pop: \[LC\]

step3
-----

> -   top: {CS}
> -   thread:
>
> ~~~ json
> "kv":1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS} -&gt; {E} {CS+}
> -   pop: {CS}
> -   push: {CS+}
> -   push: {E}

step4
-----

> -   top: {E}
> -   thread:
>
> ~~~ json
> "kv":1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step5
-----

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "kv":1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step6
-----

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step7
-----

> -   top: {E+}
> -   thread:
>
> ~~~ json
> 1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; {W}
> -   pop: {E+}
> -   push: {W}

step8
-----

> -   top: {W}
> -   thread:
>
> ~~~ json
> 1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step9
-----

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 1.0E+2,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step10
------

> -   top: {CS+}
> -   thread:
>
> ~~~ json
> ,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS+} -&gt; {CT}
> -   pop: {CS+}
> -   push: {CT}

step11
------

> -   top: {CT}
> -   thread:
>
> ~~~ json
> ,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT} -&gt; \[COMMA\] {E} {CT+}
> -   pop: {CT}
> -   push: {CT+}
> -   push: {E}
> -   push: \[COMMA\]

step12
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step13
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step14
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "arr":[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step15
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :[[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step16
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> [[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; \[LB\] {AC} \[RB\]
> -   pop: {E+}
> -   push: \[RB\]
> -   push: {AC}
> -   push: \[LB\]

step17
------

> -   top: \[LB\]
> -   thread:
>
> ~~~ json
> [[1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LB\] == \[LB\]
> -   pop: \[LB\]

step18
------

> -   top: {AC}
> -   thread:
>
> ~~~ json
> [1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC} -&gt; {AE} {AC+}
> -   pop: {AC}
> -   push: {AC+}
> -   push: {AE}

step19
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> [1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; \[LB\] {AC} \[RB\]
> -   pop: {AE}
> -   push: \[RB\]
> -   push: {AC}
> -   push: \[LB\]

step20
------

> -   top: \[LB\]
> -   thread:
>
> ~~~ json
> [1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LB\] == \[LB\]
> -   pop: \[LB\]

step21
------

> -   top: {AC}
> -   thread:
>
> ~~~ json
> 1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC} -&gt; {AE} {AC+}
> -   pop: {AC}
> -   push: {AC+}
> -   push: {AE}

step22
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step23
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step24
------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 1,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step25
------

> -   top: {AC+}
> -   thread:
>
> ~~~ json
> ,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC+} -&gt; {AES}
> -   pop: {AC+}
> -   push: {AES}

step26
------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step27
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step28
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step29
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step30
------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 2,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step31
------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; {AES}
> -   pop: {AES+}
> -   push: {AES}

step32
------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step33
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step34
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step35
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step36
------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 3],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step37
------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; EPS
> -   pop: {AES+}

step38
------

> -   top: \[RB\]
> -   thread:
>
> ~~~ json
> ],{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[RB\] == \[RB\]
> -   pop: \[RB\]

step39
------

> -   top: {AC+}
> -   thread:
>
> ~~~ json
> ,{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC+} -&gt; {AES}
> -   pop: {AC+}
> -   push: {AES}

step40
------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step41
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,{"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step42
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> {"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; \[LC\] {CS} \[RC\]
> -   pop: {AE}
> -   push: \[RC\]
> -   push: {CS}
> -   push: \[LC\]

step43
------

> -   top: \[LC\]
> -   thread:
>
> ~~~ json
> {"e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LC\] == \[LC\]
> -   pop: \[LC\]

step44
------

> -   top: {CS}
> -   thread:
>
> ~~~ json
> "e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS} -&gt; {E} {CS+}
> -   pop: {CS}
> -   push: {CS+}
> -   push: {E}

step45
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step46
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "e1":true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step47
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step48
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; {W}
> -   pop: {E+}
> -   push: {W}

step49
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[BOOL\]
> -   pop: {W}
> -   push: \[BOOL\]

step50
------

> -   top: \[BOOL\]
> -   thread:
>
> ~~~ json
> true,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[BOOL\] == \[BOOL\]
> -   pop: \[BOOL\]

step51
------

> -   top: {CS+}
> -   thread:
>
> ~~~ json
> ,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS+} -&gt; {CT}
> -   pop: {CS+}
> -   push: {CT}

step52
------

> -   top: {CT}
> -   thread:
>
> ~~~ json
> ,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT} -&gt; \[COMMA\] {E} {CT+}
> -   pop: {CT}
> -   push: {CT+}
> -   push: {E}
> -   push: \[COMMA\]

step53
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step54
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step55
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "e2":false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step56
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step57
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; {W}
> -   pop: {E+}
> -   push: {W}

step58
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[BOOL\]
> -   pop: {W}
> -   push: \[BOOL\]

step59
------

> -   top: \[BOOL\]
> -   thread:
>
> ~~~ json
> false},"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[BOOL\] == \[BOOL\]
> -   pop: \[BOOL\]

step60
------

> -   top: {CT+}
> -   thread:
>
> ~~~ json
> },"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT+} -&gt; EPS
> -   pop: {CT+}

step61
------

> -   top: \[RC\]
> -   thread:
>
> ~~~ json
> },"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[RC\] == \[RC\]
> -   pop: \[RC\]

step62
------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ,"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; {AES}
> -   pop: {AES+}
> -   push: {AES}

step63
------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step64
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step65
------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> "str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step66
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> "str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[STR\]
> -   pop: {W}
> -   push: \[STR\]

step67
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "str"],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step68
------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; EPS
> -   pop: {AES+}

step69
------

> -   top: \[RB\]
> -   thread:
>
> ~~~ json
> ],"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[RB\] == \[RB\]
> -   pop: \[RB\]

step70
------

> -   top: {CT+}
> -   thread:
>
> ~~~ json
> ,"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT+} -&gt; {CT}
> -   pop: {CT+}
> -   push: {CT}

step71
------

> -   top: {CT}
> -   thread:
>
> ~~~ json
> ,"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT} -&gt; \[COMMA\] {E} {CT+}
> -   pop: {CT}
> -   push: {CT+}
> -   push: {E}
> -   push: \[COMMA\]

step72
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step73
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step74
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "obj":{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step75
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :{"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step76
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> {"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; \[LC\] {CS} \[RC\]
> -   pop: {E+}
> -   push: \[RC\]
> -   push: {CS}
> -   push: \[LC\]

step77
------

> -   top: \[LC\]
> -   thread:
>
> ~~~ json
> {"sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LC\] == \[LC\]
> -   pop: \[LC\]

step78
------

> -   top: {CS}
> -   thread:
>
> ~~~ json
> "sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS} -&gt; {E} {CS+}
> -   pop: {CS}
> -   push: {CS+}
> -   push: {E}

step79
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step80
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "sub_obj":{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step81
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :{"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step82
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> {"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; \[LC\] {CS} \[RC\]
> -   pop: {E+}
> -   push: \[RC\]
> -   push: {CS}
> -   push: \[LC\]

step83
------

> -   top: \[LC\]
> -   thread:
>
> ~~~ json
> {"e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LC\] == \[LC\]
> -   pop: \[LC\]

step84
------

> -   top: {CS}
> -   thread:
>
> ~~~ json
> "e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS} -&gt; {E} {CS+}
> -   pop: {CS}
> -   push: {CS+}
> -   push: {E}

step85
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step86
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "e1":1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step87
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step88
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> 1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; {W}
> -   pop: {E+}
> -   push: {W}

step89
------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step90
------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 1},"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step91
------

> -   top: {CS+}
> -   thread:
>
> ~~~ json
> },"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS+} -&gt; EPS
> -   pop: {CS+}

step92
------

> -   top: \[RC\]
> -   thread:
>
> ~~~ json
> },"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[RC\] == \[RC\]
> -   pop: \[RC\]

step93
------

> -   top: {CS+}
> -   thread:
>
> ~~~ json
> ,"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CS+} -&gt; {CT}
> -   pop: {CS+}
> -   push: {CT}

step94
------

> -   top: {CT}
> -   thread:
>
> ~~~ json
> ,"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {CT} -&gt; \[COMMA\] {E} {CT+}
> -   pop: {CT}
> -   push: {CT+}
> -   push: {E}
> -   push: \[COMMA\]

step95
------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step96
------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step97
------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "sub_arr":[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step98
------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :[1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step99
------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> [1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {E+} -&gt; \[LB\] {AC} \[RB\]
> -   pop: {E+}
> -   push: \[RB\]
> -   push: {AC}
> -   push: \[LB\]

step100
-------

> -   top: \[LB\]
> -   thread:
>
> ~~~ json
> [1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[LB\] == \[LB\]
> -   pop: \[LB\]

step101
-------

> -   top: {AC}
> -   thread:
>
> ~~~ json
> 1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC} -&gt; {AE} {AC+}
> -   pop: {AC}
> -   push: {AC+}
> -   push: {AE}

step102
-------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step103
-------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step104
-------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 1,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step105
-------

> -   top: {AC+}
> -   thread:
>
> ~~~ json
> ,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AC+} -&gt; {AES}
> -   pop: {AC+}
> -   push: {AES}

step106
-------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step107
-------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step108
-------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step109
-------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step110
-------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 2,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step111
-------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; {AES}
> -   pop: {AES+}
> -   push: {AES}

step112
-------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step113
-------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step114
-------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> 3,null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step115
-------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 3,null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step116
-------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 3,null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step117
-------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; {AES}
> -   pop: {AES+}
> -   push: {AES}

step118
-------

> -   top: {AES}
> -   thread:
>
> ~~~ json
> ,null],"kv":1.3}}#
> ~~~
>
> -   match: {AES} -&gt; \[COMMA\] {AE} {AES+}
> -   pop: {AES}
> -   push: {AES+}
> -   push: {AE}
> -   push: \[COMMA\]

step119
-------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,null],"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step120
-------

> -   top: {AE}
> -   thread:
>
> ~~~ json
> null],"kv":1.3}}#
> ~~~
>
> -   match: {AE} -&gt; {W}
> -   pop: {AE}
> -   push: {W}

step121
-------

> -   top: {W}
> -   thread:
>
> ~~~ json
> null],"kv":1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUL\]
> -   pop: {W}
> -   push: \[NUL\]

step122
-------

> -   top: \[NUL\]
> -   thread:
>
> ~~~ json
> null],"kv":1.3}}#
> ~~~
>
> -   match: \[NUL\] == \[NUL\]
> -   pop: \[NUL\]

step123
-------

> -   top: {AES+}
> -   thread:
>
> ~~~ json
> ],"kv":1.3}}#
> ~~~
>
> -   match: {AES+} -&gt; EPS
> -   pop: {AES+}

step124
-------

> -   top: \[RB\]
> -   thread:
>
> ~~~ json
> ],"kv":1.3}}#
> ~~~
>
> -   match: \[RB\] == \[RB\]
> -   pop: \[RB\]

step125
-------

> -   top: {CT+}
> -   thread:
>
> ~~~ json
> ,"kv":1.3}}#
> ~~~
>
> -   match: {CT+} -&gt; {CT}
> -   pop: {CT+}
> -   push: {CT}

step126
-------

> -   top: {CT}
> -   thread:
>
> ~~~ json
> ,"kv":1.3}}#
> ~~~
>
> -   match: {CT} -&gt; \[COMMA\] {E} {CT+}
> -   pop: {CT}
> -   push: {CT+}
> -   push: {E}
> -   push: \[COMMA\]

step127
-------

> -   top: \[COMMA\]
> -   thread:
>
> ~~~ json
> ,"kv":1.3}}#
> ~~~
>
> -   match: \[COMMA\] == \[COMMA\]
> -   pop: \[COMMA\]

step128
-------

> -   top: {E}
> -   thread:
>
> ~~~ json
> "kv":1.3}}#
> ~~~
>
> -   match: {E} -&gt; \[STR\] \[COLON\] {E+}
> -   pop: {E}
> -   push: {E+}
> -   push: \[COLON\]
> -   push: \[STR\]

step129
-------

> -   top: \[STR\]
> -   thread:
>
> ~~~ json
> "kv":1.3}}#
> ~~~
>
> -   match: \[STR\] == \[STR\]
> -   pop: \[STR\]

step130
-------

> -   top: \[COLON\]
> -   thread:
>
> ~~~ json
> :1.3}}#
> ~~~
>
> -   match: \[COLON\] == \[COLON\]
> -   pop: \[COLON\]

step131
-------

> -   top: {E+}
> -   thread:
>
> ~~~ json
> 1.3}}#
> ~~~
>
> -   match: {E+} -&gt; {W}
> -   pop: {E+}
> -   push: {W}

step132
-------

> -   top: {W}
> -   thread:
>
> ~~~ json
> 1.3}}#
> ~~~
>
> -   match: {W} -&gt; \[NUM\]
> -   pop: {W}
> -   push: \[NUM\]

step133
-------

> -   top: \[NUM\]
> -   thread:
>
> ~~~ json
> 1.3}}#
> ~~~
>
> -   match: \[NUM\] == \[NUM\]
> -   pop: \[NUM\]

step134
-------

> -   top: {CT+}
> -   thread:
>
> ~~~ json
> }}#
> ~~~
>
> -   match: {CT+} -&gt; EPS
> -   pop: {CT+}

step135
-------

> -   top: \[RC\]
> -   thread:
>
> ~~~ json
> }}#
> ~~~
>
> -   match: \[RC\] == \[RC\]
> -   pop: \[RC\]

step136
-------

> -   top: {CT+}
> -   thread:
>
> ~~~ json
> }#
> ~~~
>
> -   match: {CT+} -&gt; EPS
> -   pop: {CT+}

step137
-------

> -   top: \[RC\]
> -   thread:
>
> ~~~ json
> }#
> ~~~
>
> -   match: \[RC\] == \[RC\]
> -   pop: \[RC\]

step138
-------

> -   top: \[ENDF\]
> -   thread:
>
> ~~~ json
> #
> ~~~
>
> -   match: \[ENDF\] == \[ENDF\]
> -   acc

is Accepted: true
=================
