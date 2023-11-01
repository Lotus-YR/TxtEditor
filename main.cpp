//主函数
#include <iostream>
#include <fstream>
#include <string>
#include "TxtEditor.h"
#include "LineNode.h"
using namespace std;

int main() {
	TxtEditor Txt;
	//指定输入文件名、输出文件名
	cout << "输入文件名(.txt)：";
	cin >>Txt.ifs_name ;
	cout << "输出文件名(.txt)：";
	cin >>Txt.ofs_name ;

	LineNode* ptr0 = Txt.head;         //指向当前节点
	cout << "————————————————————————————————————" << endl;
	Txt.Open();
	Txt.Read(ptr0);
	cout << "————————————————————————————————————" << endl;
	cout << "文件操作命令列表：" << endl;
	Txt.Help();

	char cmd='v';
	while (cmd != 'q') {
		cout << "————————————————————————————————————" << endl;
		cout << ">>";
		cin >> cmd;

		switch (cmd) {
		case 'h': Txt.Help(); break;
		case 'v':Txt.View(Txt.firstHead); break; 
		case 'm': {
			char m_cmd=0;
			int L = ptr0->num_line;
			cout << "#输入t：到指定行\n#输入p：到前一行\n#输入n：到下一行\n#输入f：到第一行\n#输入l：到最后一行\n>>";
			cin >> m_cmd;
			switch (m_cmd) {
			case't': {
				cout << "#当前行为：" << ptr0->num_line << endl;
				cout << "到指定行：";
				cin >> L;
			}break;
			case'p': {
				if (ptr0->num_line == 1) 
					cout << "#当前行已经是第一行了" << endl;
				else
				L = ptr0->num_line - 1;
			}break;
			case'n': {
				if (ptr0->num_line == Txt.Tline)
					cout << "#当前行已经是最后一行了" << endl;
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
			cout << "#在指定行后插入一行\n行号：" ;
			cin >> L;
			Txt.Insert(L,ptr0, Txt.firstHead); 
		} break;
		case 'd': {
			int L;
			cout << "将删除的行：";
			cin >> L;
			if (L > Txt.Tline) cout << "#错误！超过文件最大行数" << endl;
			else if (L < 0) cout << "#输入行数错误！" << endl;
			else 
				Txt.Delete(L,ptr0, Txt.firstHead); 
	
		}break;
		case 'r':Txt.Relpace(ptr0,Txt.firstHead); break;
		case 's': {
			string str;
			cout << "要查找的字符串：";
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
		default:cout << "#错误指令" << endl; break;
		}
	}
}