# 使用说明

## 文件结构

### tree

其下包含语法树结点头文件“tree.h”与其实现文件“tree.cpp”。

### cmm_synx

其下包含词法分析源代码cmm.l与语法分析源代码cmm.y。

### cmm_sema

#### symbol_table.h & symbol_table.cpp

符号表的头文件及其实现文件。

#### sematic.h & sematic.cpp

语义分析的头文件及其实现文件。

#### inter_code.h & inter_code.cpp

中间代码生成的头文件及其实现文件。

#### main.cpp

运行时的主文件。

### cmm_in

其下包含测试样例文本。

### cmm_out

其下包含保存语法树的文件“tree_details.out”，中间代码的输出文件“ir.out”与语义分析时的错误提示输出文件“sema_err.out”。

## 运行方法

注意，要先安装windows版的flex工具与bison工具。
点击deal4.bat，输入位于cmm_in文件夹下的文件名，然后等待运行结果。
语义分析时的报错提示会出现在终端与cmm_out文件夹下的“sema_err.out”文件里。
中间代码的输出结果会出现在cmm_out文件夹下的“ir.out”文件里。
