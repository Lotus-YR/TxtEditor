#pragma once
#include <iostream>
#include <string>
using namespace std;

class LineNode{
public:
	int num_line;       //ÿ���ڵ���к�
	int num_chars;          //ÿһ�е��ַ���

	//?!�ѷ��� �������
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

