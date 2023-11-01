//TxtEditorʵ���ļ�
#include "TxtEditor.h"
#include <iostream>
#include <string>
using namespace std;

//���ļ������뻺����
//���ÿ����洢��ʽ��һ��Ϊһ��㣬����ڵ������öѷ���洢ʵ��
void TxtEditor:: Open() {
	ifs.open(ifs_name, ios::out | ios::app);
	if (ifs.is_open())cout << "�ļ����ݣ�" << endl;

	//�ж��ļ��Ƿ�Ϊ�գ���Ϊ����д��һ������
	char c;
	ifs >> c;
	if (ifs.eof()) {
		ofstream i_ofs;
		string str;

		cout << "#�ļ�Ϊ��" << endl;
		ifs.close();
		i_ofs.open(ifs_name, ios::app | ios::out);
		cout << "�����ļ����ݣ�";    //�������ܺ��ո�
		cin >> str;
		i_ofs << str;
		i_ofs.close();
	}
	ifs.close();
}
void TxtEditor::Read(LineNode*& head) {
	string buf;
	int line = 0;

	//���ж�ȡ�ļ�����
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

		if (line == 1)     //��ǵ�һ���ڵ�
			firstHead = newNode;
	}
	Tline = line;       //��¼������

	ifs.close();
}

//���ݰ�������ʾ������һ�С������һ�С���ǰһ�С�����һ�С���ָ����
//����һ�С�ɾ��һ�С��滻��ǰ�С��滻ĳ�ַ���������ָ���ַ���
//ͳ���ļ��������ַ��������¶����ļ��������ļ����˳�ϵͳ
void TxtEditor::Help() {
	cout << "�����ַ�" << "\t" << "����" << endl;
	cout << "h" << "\t\t" << "Ҫ�����" << endl;
	cout << "v" << "\t\t" << "��ʾ�ļ�����" << endl;
	cout << "m" << "\t\t" << "�ƶ�" << endl;
	cout << "i" << "\t\t" << "��������" << endl;
	cout << "d" << "\t\t" << "ɾ����ǰ��" << endl;
	cout << "r" << "\t\t" << "�滻" << endl;
	cout << "s" << "\t\t" << "�����ַ���" << endl;
	cout << "c" << "\t\t" << "ͳ���ļ��������ַ���" << endl;
	cout << "a" << "\t\t" << "�ٴζ����ļ�" << endl;
	cout << "o" << "\t\t" << "���ļ����" << endl;
	cout << "q" << "\t\t" << "�˳�" << endl;
}

void TxtEditor::View(LineNode*& head) {
	//����headָ��
	LineNode* ptr = new LineNode;
	ptr = head;
	//������ʾ�ڵ�����
	for (int i = 0; i < Tline; i++) {
		cout << head->num_line << "  ";
		cout << head->charss << endl;
		head = head->before;
	}
	//headָ�뻹ԭ
	head = ptr;
}

void TxtEditor::Mov(int L, LineNode*& head, LineNode*& now) {
	//����headָ��
	LineNode* ptr = new LineNode;
	ptr = head;
	if (L > Tline || L < 0)
		cout << "#�������Ϊ" << Tline << ",������������" << endl;
	else {
		//�����ƶ���Ŀ����
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
	cout << "�������ݣ�";
	string str;
	cin.get();
	getline(cin, str);
	//cout << "�������ݣ�" <<str<< endl;

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

		//�����������	
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

void TxtEditor::Delete(int L, LineNode*& now, LineNode*& head) {          //���һ��ֻ��ɾ����
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
	cout << "#����1���滻��ǰ������\n#����2���滻ĳ�ַ���\n>>";
	int r_cmd = 0;
	cin >> r_cmd;
	switch (r_cmd) {
	case 1: {
		string replace;
		cout << "�滻�ַ����� ";
		cin >> replace;
		now->charss = replace;
	}break;
	case 2: {
		string replace;
		string newstr;
		cout << "���滻���ַ�����";
		cin >> replace;

		int pos = 0;
		pos = Search(replace, head, now);

		if (pos >= 0) {
			cout << "�滻�ַ�����";
			cin >> newstr;
		}

		LineNode* ptr = new LineNode;
		ptr = head;

		for (int i = 1; i <= Tline; i++) {
			for (int j = 0; j < head->num_chars;) {
				if ((head->charss.find(replace, j)) != head->charss.npos) {          //�ж��ַ����Ƿ��ҵ�
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
	default:cout << "#����ָ�" << endl;
	}
}

int TxtEditor::Search(string str, LineNode*& head, LineNode*& now) {

	LineNode* ptr = new LineNode;
	ptr = head;

	int pos = 0;
	int times = 0;
	for (int i = 1; i <= Tline; i++) {
		for (int j = 0; j < head->num_chars;) {
			if ((head->charss.find(str, j)) != head->charss.npos) {          //�ж��ַ����Ƿ��ҵ�
				pos = head->charss.find(str, j);
				times++;
				cout << "�ַ�����" << times << "�γ����ڵ�" << head->num_line << "�У���" << pos + 1 << "���ַ���" << endl;
				now = head;
				j = pos + size(str);
			}
			else j++;
		}
		if (i == Tline && times == 0) {
				cout << "#�޸��ַ���!" << endl;
				pos = -1;
			}
		head = head->before;
	}
	head = ptr;

	return pos;
}

void TxtEditor::Count(LineNode*& head) {
	cout << "�ļ�������Ϊ��" << Tline << endl;
	Tchars = 0;
	LineNode* ptr = new LineNode;
	ptr = head;
	for (int i = 1; i <= Tline; i++) {
		Tchars += head->num_chars;
		if (i == Tline) break;
		head = head->before;
	}
	head = ptr;
	cout << "�ļ����ַ���Ϊ��" << Tchars << endl;
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