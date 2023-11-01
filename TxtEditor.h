#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "LineNode.h"
using namespace std;

class TxtEditor
{
public:
	ifstream ifs;
	ofstream ofs;

	string ifs_name;
	string ofs_name;

	LineNode* head;
	LineNode* firstHead;       //永远指向第一行所在节点

	int Tline;    //行数=节点数
	int Tchars;     //文本字符总数

	TxtEditor() {
		Tchars = 0;
		Tline = 0;
		head = NULL;
		firstHead = NULL;
	};
	~TxtEditor() {};

	void Open();
	void Read(LineNode*& head);
	void View(LineNode*& head);
	void Mov(int L, LineNode*& head, LineNode*& now);//到指定行
	void Insert(int L, LineNode*& now, LineNode*& head);//在指定行后插入一行
	void Delete(int L, LineNode*& now, LineNode*& head);//删除指定行
	void Relpace(LineNode*& now, LineNode*& head);//替换字符串、替换当前行
	int Search(string str, LineNode*& head, LineNode*& now);
	void Count(LineNode*& head);
	void Output(LineNode*& head);
	void Quit();
	void Help();

};

