#include"高中学校管理系统.h"
#include"password.h"

typedef void(scoreanalysis::* scorefunc)();
int main() {
	srand(time(0));
	std::unordered_map<string, scorefunc> funcmap = {
		{"添加学生信息",        &scoreanalysis::addstudentsinfo},
		{"添加教师信息",        &scoreanalysis::addteachersinfo},
		{"修改学生信息",        &scoreanalysis::changestudent},
		{"修改教师信息",        &scoreanalysis::changeteacher},
		{"删除学生信息",        &scoreanalysis::deletestudent},
		{"删除教师信息",        &scoreanalysis::deleteteacher},
		{"查看学生信息",        &scoreanalysis::findstudent},
		{"查看教师信息",        &scoreanalysis::findteacher},
		{"查看成绩",            &scoreanalysis::searchandcalculate},
		{"从文件导入成绩",       &scoreanalysis::getscorefromdoc},
		{"从文件导入用于分析的成绩", &scoreanalysis::inputscorefromdoc},
		{"录入成绩",            &scoreanalysis::inputscore},
		{"查看所有学生信息",     &scoreanalysis::showallstudentinfo},
		{"查看所有学生成绩",     &scoreanalysis::showallstuscore},
		{"查看所有教师信息",     &scoreanalysis::showallteacherinfo},
		{"对成绩进行分析",      &scoreanalysis::getanalysis}
	};
	std::unordered_map<char, std::unordered_map<int, string>> map = {
		{'A',
		{{1,"查看学生信息"},{2,"修改学生信息"},{3,"查看成绩"}}
		},
		{'B',
		{{1,"查看教师信息"},{2,"修改教师信息"},{3,"查看成绩"} ,
		{4,"从文件导入用于分析的成绩"}, {5,"从文件导入成绩"},{6,"录入成绩"},{7,"对成绩进行分析"}}
	    },
		{'C',{
		{1,"添加学生信息"},{2,"添加教师信息"},
		{3,"修改学生信息"},{4,"修改教师信息"},
		{5,"查看成绩"},{6,"删除学生信息"},
		{7,"删除教师信息"},{8,"查看学生信息"},
		{9,"查看教师信息"},{10,"从文件导入用于分析的成绩"},
		{11,"从文件导入成绩"},{12,"录入成绩"},
		{13,"查看所有学生信息"},{14,"查看所有学生成绩"},
		{15,"查看所有教师信息"} ,{16,"对成绩进行分析"}
	    }
	    }
	};
	scoreanalysis A; string identity; int num; pw pwsystem; 
	do{
		std::cout << "输入“1”注册账号密码" << '\n';
		std::cout << "输入“2”登录账号" << '\n';
		std::cout << "输入“3”修改密码" << '\n';
		cin >> num;
		if (num == 1) { pwsystem.Register(); system("pause"); }
		else if (num == 2) { identity = to_string(pwsystem.Login()); system("pause"); break; }
		else if (num == 3) { pwsystem.ChangePassword(); system("pause");}
		else { cerr << "未知指令,请重新输入！\n"; cin.clear(); cin.ignore(0, '\n'); }
		system("cls");
	} while (1);
	int Choice;
    {
		if (identity == to_string(pw::Role::Student)) {
			do {
				system("cls");
				std::cout << "欢迎进入学生模式！\n";
				std::cout << "1.查看个人信息;\n2.修改个人信息;\n3.查看成绩;\n4.退出学生模式\n";
				cin >> Choice; if (Choice == 4)break;
				if (map['A'].find(Choice)==map['A'].end())
				{
					cerr << "未知指令！\n"; cin.clear(); cin.ignore(0, '\n');  continue;
				}
				else (A.*funcmap[map['A'][Choice]])();
			} while (1);
		}
		
		else if (identity == to_string(pw::Role::Teacher)) {
			do
			{
				system("cls");
				std::cout << "欢迎进入教师模式！\n";
				std::cout << "1.查看老师个人信息;\n2.修改老师个人信息;\n3.查看学生成绩;\n4.从文件导入用于分析的成绩;\n5.从文件导入成绩;\n6.给学生录入成绩;\n7.对成绩进行分析\n8.退出教师模式\n";
				cin >> Choice; if (Choice == 8)break;
				if (map['B'].find(Choice)==map['B'].end()) { cerr << "未知指令！\n"; cin.clear(); cin.ignore(0, '\n'); continue; }
				else (A.*funcmap[map['B'][Choice]])();
			} while (1);
		}
		else if (identity == to_string(pw::Role::Admin) ) {
			//管理员身份,拥有所有权限
			do
			{system("cls");
				std::cout << "欢迎进入管理员模式！\n";
				std::cout << "1.录入学生信息;\n2.录入教师信息;\n3.修改学生信息;\n4.修改教师信息;\n5.查看成绩;\n6.删除学生信息;\n7.删除教师信息;\n8.查询学生信息;\n9.查询教师信息;\n10.从文件导入用于分析的成绩;\n11.从文件导入成绩;\n12.录入成绩;\n13.查看所有学生信息;\n14.查看所有学生成绩;\n15.查看所有教师信息;\n16.对成绩进行分析\n17.退出管理员模式\n" << endl;
				cin >> Choice; if (Choice == 17)break; 
				if (map['C'].find(Choice)==map['C'].end()) { cerr << "未知指令！\n"; cin.clear(); cin.ignore(0, '\n'); continue; }
				else (A.*funcmap[map['C'][Choice]])();
			} while (1);
		}
		
		system("cls");
	} 

	return 0;
}