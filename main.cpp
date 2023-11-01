//������
#include <iostream>
#include <fstream>
#include <string>
#include "TxtEditor.h"
#include "LineNode.h"
using namespace std;

int main() {
	TxtEditor Txt;
	//ָ�������ļ���������ļ���
	cout << "�����ļ���(.txt)��";
	cin >>Txt.ifs_name ;
	cout << "����ļ���(.txt)��";
	cin >>Txt.ofs_name ;

	LineNode* ptr0 = Txt.head;         //ָ��ǰ�ڵ�
	cout << "������������������������������������������������������������������������" << endl;
	Txt.Open();
	Txt.Read(ptr0);
	cout << "������������������������������������������������������������������������" << endl;
	cout << "�ļ����������б�" << endl;
	Txt.Help();

	char cmd='v';
	while (cmd != 'q') {
		cout << "������������������������������������������������������������������������" << endl;
		cout << ">>";
		cin >> cmd;

		switch (cmd) {
		case 'h': Txt.Help(); break;
		case 'v':Txt.View(Txt.firstHead); break; 
		case 'm': {
			char m_cmd=0;
			int L = ptr0->num_line;
			cout << "#����t����ָ����\n#����p����ǰһ��\n#����n������һ��\n#����f������һ��\n#����l�������һ��\n>>";
			cin >> m_cmd;
			switch (m_cmd) {
			case't': {
				cout << "#��ǰ��Ϊ��" << ptr0->num_line << endl;
				cout << "��ָ���У�";
				cin >> L;
			}break;
			case'p': {
				if (ptr0->num_line == 1) 
					cout << "#��ǰ���Ѿ��ǵ�һ����" << endl;
				else
				L = ptr0->num_line - 1;
			}break;
			case'n': {
				if (ptr0->num_line == Txt.Tline)
					cout << "#��ǰ���Ѿ������һ����" << endl;
				else 
				L = ptr0->num_line + 1;
			}break;
			case'f': {
				L = 1;
			}break;
			case'l': {
				L = Txt.Tline;
			}break;
			}
		Txt.Mov(L, Txt.firstHead, ptr0);	
		}break;
		case 'i': {
			int L = 0;
			cout << "#��ָ���к����һ��\n�кţ�" ;
			cin >> L;
			Txt.Insert(L,ptr0, Txt.firstHead); 
		} break;
		case 'd': {
			int L;
			cout << "��ɾ�����У�";
			cin >> L;
			if (L > Txt.Tline) cout << "#���󣡳����ļ��������" << endl;
			else if (L < 0) cout << "#������������" << endl;
			else 
				Txt.Delete(L,ptr0, Txt.firstHead); 
	
		}break;
		case 'r':Txt.Relpace(ptr0,Txt.firstHead); break;
		case 's': {
			string str;
			cout << "Ҫ���ҵ��ַ�����";
			cin >> str;
			Txt.Search(str, Txt.firstHead, ptr0);
		}; break;
		case 'c':Txt.Count(Txt.firstHead); break;
		case 'a': {
			Txt.Open();
			Txt.Read(Txt.firstHead); 
		}break;
		case 'o':Txt.Output(Txt.firstHead); break;
		case 'q':Txt.Quit(); break;
		default:cout << "#����ָ��" << endl; break;
		}
	}
}