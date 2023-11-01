#pragma once
#include <iostream>
#include <string>
using namespace std;

class LineNode{
public:
	int num_line;       //每个节点的行号
	int num_chars;          //每一行的字符数

	//?!堆分配 结点内容
	string charss;

	LineNode* next;
	LineNode* before;

	LineNode() {
		num_line = 0;
		num_chars = 0;
		next = NULL;
		before = NULL;
		}
};

