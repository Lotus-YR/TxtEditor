//TxtEditor实现文件
#include "TxtEditor.h"
#include <iostream>
#include <string>
using namespace std;

//打开文件，读入缓冲区
//（用块链存储方式，一行为一结点，结点内的内容用堆分配存储实现
void TxtEditor:: Open() {
	ifs.open(ifs_name, ios::out | ios::app);
	if (ifs.is_open())cout << "文件内容：" << endl;

	//判断文件是否为空，若为空则写入一行内容
	char c;
	ifs >> c;
	if (ifs.eof()) {
		ofstream i_ofs;
		string str;

		cout << "#文件为空" << endl;
		ifs.close();
		i_ofs.open(ifs_name, ios::app | ios::out);
		cout << "输入文件内容：";    //？！不能含空格
		cin >> str;
		i_ofs << str;
		i_ofs.close();
	}
	ifs.close();
}
void TxtEditor::Read(LineNode*& head) {
	string buf;
	int line = 0;

	//逐行读取文件内容
	ifs.open(ifs_name, ios::out);
	while (getline(ifs, buf)) {
		LineNode* newNode = new LineNode;
		newNode->charss = buf;
		newNode->next = head;
		newNode->num_line = ++line;
		newNode->num_chars = size(buf);

		cout << newNode->num_line << "  ";
		cout << newNode->charss << endl;

		if (line != 1) {
			head->before = newNode;
		}
		head = newNode;

		if (line == 1)     //标记第一个节点
			firstHead = newNode;
	}
	Tline = line;       //记录总行数

	ifs.close();
}

//内容包括：显示、到第一行、到最后一行、到前一行、到后一行、到指定行
//插入一行、删除一行、替换当前行、替换某字符串、查找指定字符串
//统计文件行数及字符数、重新读入文件、保存文件、退出系统
void TxtEditor::Help() {
	cout << "命令字符" << "\t" << "命令" << endl;
	cout << "h" << "\t\t" << "要求帮助" << endl;
	cout << "v" << "\t\t" << "显示文件内容" << endl;
	cout << "m" << "\t\t" << "移动" << endl;
	cout << "i" << "\t\t" << "插入内容" << endl;
	cout << "d" << "\t\t" << "删除当前行" << endl;
	cout << "r" << "\t\t" << "替换" << endl;
	cout << "s" << "\t\t" << "查找字符串" << endl;
	cout << "c" << "\t\t" << "统计文件行数及字符数" << endl;
	cout << "a" << "\t\t" << "再次读入文件" << endl;
	cout << "o" << "\t\t" << "将文件输出" << endl;
	cout << "q" << "\t\t" << "退出" << endl;
}

void TxtEditor::View(LineNode*& head) {
	//保存head指针
	LineNode* ptr = new LineNode;
	ptr = head;
	//逐行显示节点内容
	for (int i = 0; i < Tline; i++) {
		cout << head->num_line << "  ";
		cout << head->charss << endl;
		head = head->before;
	}
	//head指针还原
	head = ptr;
}

void TxtEditor::Mov(int L, LineNode*& head, LineNode*& now) {
	//保存head指针
	LineNode* ptr = new LineNode;
	ptr = head;
	if (L > Tline || L < 0)
		cout << "#最大行数为" << Tline << ",输入行数错误" << endl;
	else {
		//逐行移动到目标行
		for (int i = 1; i <= Tline; i++) {
			if (i == L) {
				now = head;
				cout << head->num_line << "  " << head->charss << endl;
				break;
			}
			head = head->before;
		}
		head = ptr;
	}
}

void TxtEditor::Insert(int L, LineNode*& now, LineNode*& head) {
	Mov(L, head, now);
	cout << "插入内容：";
	string str;
	cin.get();
	getline(cin, str);
	//cout << "插入内容：" <<str<< endl;

	if (now->num_line == Tline) {
		LineNode* newNode = new LineNode;
		newNode->next = now;
		newNode->charss = str;
		newNode->num_line = now->num_line + 1;
		now->before = newNode;
		now = newNode;
		Tline++;
	}
	else {
		LineNode* newNode = new LineNode;
		now->before->next = newNode;
		newNode->before = now->before;
		newNode->next = now;
		now->before = newNode;

		newNode->charss = str;
		newNode->num_line = L + 1;
		Tline++;

		//更新行数编号	
		LineNode* ptr = new LineNode;
		ptr = head;
		for (int i = 1; i < Tline; i++) {

			if (i > L + 1) {
				head->num_line = i;
			}
			head = head->before;
		}
		head->num_line++;
		head = ptr;
		now = newNode;
	}
}

void TxtEditor::Delete(int L, LineNode*& now, LineNode*& head) {          //最后一行只能删两次
	Mov(L, head, now);

	LineNode* ptr_del = new LineNode;
	ptr_del = now;

	if (now->num_line == Tline) {
		now = now->next;
		now->before = NULL;
		Tline--;
	}
	else if (now->num_line == 1) {
		now = now->before;
		now->next = NULL;

		head = now;
		Tline--;

		LineNode* ptr = new LineNode;
		ptr = head;
		for (int i = 1; i <= Tline; i++) {
			if (i >= ptr_del->num_line) {
				head->num_line--;
			}
			head = head->before;
		}
		head = ptr;
	}
	else {
		now = now->before;
		now->next = ptr_del->next;
		ptr_del->next->before = now;
		Tline--;

		LineNode* ptr = new LineNode;
		ptr = head;
		for (int i = 1; i <= Tline; i++) {
			if (i >= ptr_del->num_line) {
				head->num_line--;
			}
			head = head->before;
		}
		head = ptr;
	}
}

void TxtEditor::Relpace(LineNode*& now, LineNode*& head) {
	cout << "#输入1：替换当前行内容\n#输入2：替换某字符串\n>>";
	int r_cmd = 0;
	cin >> r_cmd;
	switch (r_cmd) {
	case 1: {
		string replace;
		cout << "替换字符串： ";
		cin >> replace;
		now->charss = replace;
	}break;
	case 2: {
		string replace;
		string newstr;
		cout << "被替换的字符串：";
		cin >> replace;

		int pos = 0;
		pos = Search(replace, head, now);

		if (pos >= 0) {
			cout << "替换字符串：";
			cin >> newstr;
		}

		LineNode* ptr = new LineNode;
		ptr = head;

		for (int i = 1; i <= Tline; i++) {
			for (int j = 0; j < head->num_chars;) {
				if ((head->charss.find(replace, j)) != head->charss.npos) {          //判断字符串是否被找到
					pos = head->charss.find(replace, j);
					now->charss = now->charss.replace(pos, replace.size(), newstr);
					now = head;
					j = pos + size(newstr);
				}
				else j++;
			}
			head = head->before;
		}
		head = ptr;


	}break;
	default:cout << "#错误指令！" << endl;
	}
}

int TxtEditor::Search(string str, LineNode*& head, LineNode*& now) {

	LineNode* ptr = new LineNode;
	ptr = head;

	int pos = 0;
	int times = 0;
	for (int i = 1; i <= Tline; i++) {
		for (int j = 0; j < head->num_chars;) {
			if ((head->charss.find(str, j)) != head->charss.npos) {          //判断字符串是否被找到
				pos = head->charss.find(str, j);
				times++;
				cout << "字符串第" << times << "次出现在第" << head->num_line << "行，第" << pos + 1 << "个字符处" << endl;
				now = head;
				j = pos + size(str);
			}
			else j++;
		}
		if (i == Tline && times == 0) {
				cout << "#无该字符串!" << endl;
				pos = -1;
			}
		head = head->before;
	}
	head = ptr;

	return pos;
}

void TxtEditor::Count(LineNode*& head) {
	cout << "文件总行数为：" << Tline << endl;
	Tchars = 0;
	LineNode* ptr = new LineNode;
	ptr = head;
	for (int i = 1; i <= Tline; i++) {
		Tchars += head->num_chars;
		if (i == Tline) break;
		head = head->before;
	}
	head = ptr;
	cout << "文件总字符数为：" << Tchars << endl;
}

void TxtEditor::Output(LineNode*& head) {
	ofs.open(ofs_name, ios::out);
	string str;
	LineNode* ptr = new LineNode;
	ptr = head;
	for (int i = 1; i <= Tline; i++) {
		str = head->charss;
		ofs << str;
		ofs << "\n";
		if (i == Tline) break;
		head = head->before;
	}
	head = ptr;
	ofs.close();
}

void TxtEditor::Quit() {
	exit(0);
}