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
	LineNode* firstHead;       //��Զָ���һ�����ڽڵ�

	int Tline;    //����=�ڵ���
	int Tchars;     //�ı��ַ�����

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
	void Mov(int L, LineNode*& head, LineNode*& now);//��ָ����
	void Insert(int L, LineNode*& now, LineNode*& head);//��ָ���к����һ��
	void Delete(int L, LineNode*& now, LineNode*& head);//ɾ��ָ����
	void Relpace(LineNode*& now, LineNode*& head);//�滻�ַ������滻��ǰ��
	int Search(string str, LineNode*& head, LineNode*& now);
	void Count(LineNode*& head);
	void Output(LineNode*& head);
	void Quit();
	void Help();

};

