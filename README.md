# TxtEditor
简易命令行文本编辑器  
采用C++的ASCII码文件和串函数实现  
***
## 功能简介  
1. 在命令行中指定输入文件名、输出文件名；
2. 将输入文件打开，读入输入缓冲区；
3. 对输入缓冲区中的文件内容进行编辑，包括：
   1. 显示当前文件
   2. 到第一行、最后一行、前一行、下一行、指定的某一行
   3. 插入一行
   4. 删除一行
   5. 替换当前行、替换字符串
   6. 查找指定字符串
   7. 统计文件行数和字符数
   8. 重新读入文件
   9. 保存当前文件
   10. 退出系统
***
## 程序设计
### 类
节点类：  
文本文件中一行字符串为一个节点  
节点中包含两个指针，用于实现双向链表  
```C++
class Node{
   string charss;
   int num_line;//每一行的行号
   int num_chars;//每一行的字符数
   Node* next;
   Node* before;
}
```
文本类：  
包含文本的基本属性（文本行数、文本字符数）  
包含指向节点的指针
有多种方法，用于实现对文本的操作
```C++
class TxtEditor{
   int Tline;
   int Tchars;
   Node* ptr;
   Node* firstHead;

}
```
### 类方法  

| 方法  | 功能 | 实现细节 |
| :----------: | :-----------: | :---------------: |
| Help() | 显示命令字符信息 |  
| Open() | 打开文件，判断是否为空  若为空，则写入一行内容 | 
| Read() | 将文件内容读入输入缓冲区 | 
| View() | 显示文件内容 | 只显示，不更改当前位置 |
| Moe() | 移动到文件的某个一行 | main函数中可增加功能,如：到前一行、后一行......)
| Insert() | 在某行后插入一行 | 
| Delete() | 删除指定行 | 移动到某一行+删除当前行|
| Search() | 查找字符串所在位置 |
| Replace() | 替换当前行、替换某字符串（全文范围内）| 查找字符串+替换字符串 | 
| Count() |  计算文件行数、字符数
| Output() |  将文件输出到输出文件中
| Quit() | 退出程序 

***
### 主函数  
实现交互功能  
指定输入输出文件
输入命令，对文件进行操作
