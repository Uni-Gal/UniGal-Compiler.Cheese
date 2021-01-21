#include <iostream>
#include <fstream>
#include <algorithm>
#include "pugixml.hpp" //  建议装个vcpkg

using namespace std;

string DefaultType_text = "text";
string DefaultType_code = "code";
string DefaultType_logic = "struct";

string FormatString(string str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	str.erase(std::remove(str.begin(), str.end(), '\n'), str.end());
	return str;
}

int main(void)
{

	pugi::xml_document unigal;
	pugi::xml_parse_result result = unigal.load_file("Simple.unigal");
	//此处若未能正常打开，应给出一个UEP-E-0001
	string src = FormatString(unigal.select_node("/unigal-script/head/src/text()").node().value());
	string dst = FormatString(unigal.select_node("/unigal-script/head/dst/text()").node().value());
	string ver = FormatString(unigal.select_node("/unigal-script/head/ver/text()").node().value());
	cout << "[src=" << src << "]" << endl;
	cout << "[dst=" << dst << "]" << endl;
	cout << "[ver=" << ver << "]" << endl;
	//若源引擎或目标引擎是未定义的，应给出UEP-E-0006
	//若ver低于建议版本或高于本版本，应给出UEP-W-version
	cout << "开始解析脚本，若需要编译成目标语言则输入1，不需要编译成目标语言则输入0" << endl;
	int flag_complier = 0;
	cin >> flag_complier;
	ofstream objectfile;
	if (flag_complier == 1)
	{
		if (dst == "BKE")
		{
			objectfile.open("Simple2.bkspr");
			//如果创建文件不成功，是不是也应该给一个UEP-E？
		}
		else if (dst == "librian")
		{
			cout << "本编译器输出结果为ANSI编码，需要用户手工处理为UTF-8方可支持Librian" << endl;
			objectfile.open("入口.liber");
			//此处应给出一个UEP-W-0001（UEP-W-endode也行，毕竟不知道咋编码）
		}
	}
	int iterator = 0;
	int mode = 0;
	string LatestCharacter = "NULL";
	while (true)
	{
		cout << "==== Press 1 to next row ====" << endl;
		cout << "==== Press 2 to exit     ====" << endl;
		cin >> mode;
		if (mode == 1)
		{
			iterator += 1;
			char xpath[250];
			snprintf(xpath, 250, "%s%d%s", "/unigal-script/body/*[", iterator, "]");
#ifdef _DEBUG
			cout << "[" << iterator << "]" << xpath << endl;
			//所有在测试模式中的情况都给一个UEP-W吧
#endif // DEBUG
			cout << "[ID= " << iterator << " ]" << endl;
			cout << "[type= " << unigal.select_node(xpath).node().name() << " ]" << endl;
			string type = unigal.select_node(xpath).node().name();
			if (type == "text")
			{
				//SHOW
				cout << "[character= " << FormatString(unigal.select_node(xpath).node().child("character").child("name").child_value()) << " ]" << endl;
				cout << "[content= " << FormatString(unigal.select_node(xpath).node().child("content").child("part").child_value()) << " ]" << endl;
				//COMPLIER
				string CurrentCharacter = FormatString(unigal.select_node(xpath).node().child("content").child("part").child_value());
				if (flag_complier == 1)
				{
					if (dst == "BKE")
					{
						//【凉子】[r]
						//抱歉，等很久了么？？[p]
						if (LatestCharacter == CurrentCharacter)
						{
							//说话角色已变更
							LatestCharacter = CurrentCharacter;
							objectfile << FormatString(unigal.select_node(xpath).node().child("character").child("name").child_value()) << "[r]" << endl;
						}
						else
						{
							//说话角色未变更
							;
						}
						objectfile << FormatString(unigal.select_node(xpath).node().child("content").child("part").child_value());
					}
					else if (dst == "librian")
					{
						//潘大爺 「今天天氣不錯，去散步吧。」
						objectfile << FormatString(unigal.select_node(xpath).node().child("character").child("name").child_value()) << " ";
						objectfile << "「" << FormatString(unigal.select_node(xpath).node().child("content").child("part").child_value()) << "」" << endl;
					}
				}
			}
			else if (type == "code")
			{
				cout << "[code type= " << unigal.select_node(xpath).node().first_child().name() << " ]" << endl;//话说既然是xml那么log里面用<>会不会更好
				string codetype = unigal.select_node(xpath).node().first_child().name();
				if (codetype == "action")
				{
					string code_actiontype = unigal.select_node(xpath).node().first_child().first_child().name();
					if (code_actiontype == "newline")
					{
						//SHOW
						cout << "[action= newline ]" << endl;
						//COMPLIER
						if (flag_complier == 1)
						{
							cout << "generate obj file" << endl;
							if (dst == "BKE")
							{
								cout << "dst == BKE" << endl;
								objectfile << "[p]" << endl;
							}
							if (dst == "librian")
							{
								cout << "dst == librian" << endl;
							}
						}
						else
						{
							;
						}
					}
					if (code_actiontype == "waitclick")
					{
						cout << "[action= waitclick ]" << endl;
					}
					else{;//这时候就可以给UEP-E-0005了，因为是未定义的函数}
				}
				else if (codetype == "resource")
				{
					;
				}
				else if (codetype == "logic")
				{
					;
				}
				else if (codetype == "extension")
				{
					;
				}
				else{;//这时候就可以给UEP-E-0005了，因为是未定义的函数}
			}
			else if (type == "struct")
			{
				;
			}
			else
			{
				;
				//是未知的节点类型，是无法解析的，应该给一个UEP-E，可以考虑合并到UEP-E-0004中
			}
		}
		else
		{
			if (flag_complier != 0)
			{
				//进行后处理
				if (dst == "BKE")
				{
					objectfile << "@quit" << endl;
				}
				exit(0);
				//又到了检测是不是UEP-E-0006的时候了
			}
			else
			{
				//不进行后处理
				exit(0);
			}
		}
	}
	return 0;
}