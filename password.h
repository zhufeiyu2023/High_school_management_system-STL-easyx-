#pragma once

#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<sstream>
#include<utility>
#include<codecvt>
#include<iomanip>
#include<stdexcept>
#include<unordered_map>
class pw 
{public:enum Role { Student, Teacher, Admin };
private:
	using Account = std::string;
	using Password = std::string;
	std::string dataname;
	fstream datafile;
	std::unordered_map<Account, std::pair<Password,Role>> map;
	void Load();
	//加载数据库的函数
	int getRole(const std::string& name);
	//获取角色的函数
	void Update();
	//更新数据库的函数
	void Freeze(const std::string& name);
	//冻结账号的函数
	bool IsFrozen(const std::string& name);
	//判断账号是否被冻结的函数
public:
	pw(std::string dataname1="Password.csv") //构造函数，设置密码保存路径
	{
		dataname = dataname1;
		Load();
	}
	void Register();
	//注册函数，前端用户注册账号密码
	int Login();
	//登录函数，前端用户登陆系统
	void ChangePassword();
	//修改密码函数
};
inline void pw::Register()
{
	std::string zh, mm;
	std::cout << "请输入账号：" << std::endl;
	std::cin >> zh;
	while (map.find(zh)!= map.end()) {
		std::cout << "请重新输入账号：" << std::endl;
		std::cin >> zh;
	}//系统中已经有该账号，让用户重新输入账号开始注册

/*---------------------------------------------------------------
	 账号获取部分代码结束
----------------------------------------------------------------*/

	std::cout << "请输入密码：" << std::endl;
	std::cin >> mm;
	std::unordered_map<std::string, Role> role_map = {{"学生", Student}, {"老师", Teacher}, {"管理员", Admin}};
	std::cout << "请输入用户级别：学生，老师，管理员\n";std::string Role_str;std::cin >> Role_str;
	while(role_map.find(Role_str)==role_map.end()){std::cout<<"请重新输入用户级别：学生，老师，管理员\n";std::cin>>Role_str;}
	map[zh] = std::make_pair(mm, role_map[Role_str]);//建立账号--密码映射

/*---------------------------------------------------------------
	 密码获取部分代码结束
----------------------------------------------------------------*/

	Update();

/*---------------------------------------------------------------
	 数据保存部分代码结束
----------------------------------------------------------------*/
	std::cout << "注册成功！" << std::endl;
};

inline int pw::Login()
{   std::string tempzh, tempmm;//用于采集用户输入的账号密码的临时变量
	bool flag1=true,flag2=true;//flag1检测账号是否存在，flag2检测密码是否与账号对应
	int count = 0;//检测次数，若连续10次错误则冻结账户
	do {std::cout << "账号：";std::cin >> tempzh;
		std::cout << "密码：";std::cin >> tempmm;
		if (map.find(tempzh)==map.end()) { flag1 = false; std::cout << "账号不存在！" << std::endl; }
		//账号不存在，flag1=false
		else if (IsFrozen(tempzh)) { std::cout << "密码错误次数过多，账号已冻结，请联系管理员解冻" << std::endl; return -1; }
		//检测账号是否被冻结
		else if ((map.find(tempzh)->second.first) != tempmm) { flag2 = false; count++; std::cout << "密码不正确！" <<'\t' << std::endl; }
		//密码不正确，flag2=false,同时增加count值，达到限制登录次数效果
		else break;
		//跳出循环条件：账号存在并且密码正确，则直接跳出循环
	} while (((flag1 == false) ||(flag2 == false)) && (count < 10));
	//循环运行条件：1.账号不存在（flag1==false）;2.密码不正确（flag2==false）;3.密码错误次数小于10			
	if (count >= 10)
	{
		std::cout << "密码错误次数过多，账号已冻结，请联系管理员解冻" << std::endl;
		Freeze(tempzh);//冻结账号
		return -1;
	}//密码错误次数过多，登陆失败
	else 
	{std::cout << "登陆成功！正在接入系统..." << std::endl;//登陆成功
	return getRole(tempzh);}

};

inline void pw::ChangePassword()
{std::string mm1;std::string tempzh, tempmm;//用于采集用户输入的账号密码的临时变量
	bool flag1 = true, flag2 = true;//flag1检测账号是否存在，flag2检测密码是否与账号对应
	int count = 0;//检测次数，若连续10次错误则冻结账户
	do {std::cout << "账号：";std::cin >> tempzh;std::cout << "密码：";std::cin >> tempmm;
		if (map.find(tempzh)==map.end()) { flag1 = false; std::cout << "账号不存在！" << std::endl; }
		//账号不存在，flag1=false
		else if (IsFrozen(tempzh)) { std::cout << "密码错误次数过多，账号已冻结，请联系管理员解冻" << std::endl; return; }
		//检测账号是否被冻结
		else if ((map.find(tempzh)->second.first) != tempmm) { flag2 = false; count++; std::cout << "密码不正确！" << '\t' << std::endl; }
		//密码不正确，flag2=false,同时增加count值，达到限制登录次数效果
		else break;
		//跳出循环条件：账号存在并且密码正确，则直接跳出循环
	} while (((flag1 == false) || (flag2 == false)) && (count < 10));
	//循环运行条件：1.账号不存在（flag1==false）;2.密码不正确（flag2==false）;3.密码错误次数小于10
	if (count >= 10)
	{std::cout << "密码错误次数过多，账号已冻结，请联系管理员解冻" << std::endl;
		Freeze(tempzh);//冻结账号
	}//密码错误次数过多，登陆失败
	else std::cout << "登陆成功！正在接入系统..." << std::endl;//登陆成功
	//首先登陆，然后才能进行后续操作
	std::cout << "请输入新密码" << std::endl;std::cin >> mm1;map[tempzh].first = mm1;
	//建立新的密码账号hash_map关系
	Update();
	//更新数据库
	std::cout << "密码修改成功！" << std::endl;
};

inline void pw::Load()
{
	datafile.open(dataname, ios::in);
	if (datafile)
	{std::string zh, mm; int r;
		std::cout << "正在加载数据..." << std::endl; std::string temp;
		while (getline(datafile, temp))
		{   stringstream ss(temp); getline(ss >> ws, zh, ','); 
			getline(ss >> ws, mm, ','); ss >> r;
			map.insert({ zh, std::make_pair(mm, Role(r)) });
		}
		datafile.close();
		std::cout<<"加载数据成功！"<<std::endl;
	}
	else std::cout << "加载数据失败！" << std::endl;
	datafile.clear(0);

};//加载数据库的函数

inline void clearfile(std::string s) 
{
	fstream tempfile;
	tempfile.open(s, ios::trunc, ios::out);
	tempfile.close();

}

inline void copy(const std::string &s1,const std::string &s2)//文件复制函数，从s1拷贝到s2
{
	std::string line;
	ifstream ini_file(s1);
	ofstream out_file(s2);
	if (ini_file && out_file) {

		while (getline(ini_file, line)) {
			out_file << line << "\n";
		}
	}
	else cerr << "在复制文件时遇到了错误" << std::endl;
	ini_file.close();
	out_file.close();
	
};

inline void pw::Update()
{
	/*思路：
	1.清空已存在的拷贝文件password_back_up.txt
	2.拷贝当前password.txt内的数据，到password_back_up.txt文件，作为备份
	3.清空password.txt文件内的所有数据
	4.遍历hash_map，逐组输出数据到password.txt

	需要用到的辅助函数：
	void clearfile(std::string s)；
	void copy(std::string s1,std::string s2);
	*/
	clearfile("password_back_up.csv");
	//步骤1
	copy(dataname, "password_back_up.csv");
	//步骤2
	clearfile(dataname);
	//步骤3
	datafile.open(dataname, ios::out);
	for (const auto& mypair : map) {
		datafile << mypair.first << ',' << mypair.second.first << ',' << mypair.second.second << "\n";
	}
	datafile << std::endl;
	datafile.close();
	//步骤4


};


//更新数据库的函数

inline int pw::getRole(const std::string& name) {
	if (map.find(name)!= map.end()) return map.find(name)->second.second;
	else return -1;
}

inline void pw::Freeze(const std::string &name)
{
	/*思路：
	1.设定txt文件 banlist
	2.将name导入至banlist中
	 */
	datafile.open("banlist.txt", ios::out);
	datafile << name << std::endl;
	datafile.close();
}

inline bool pw::IsFrozen(const std::string &name) 
{

	std::string temp;
	datafile.open("banlist.txt", ios::in);
	if (datafile)
	{
		while (!datafile.eof())
		{
			datafile >> temp;
			if (temp.find(name, 0) != std::string::npos) return true;
			
		}
		datafile.close(); //打开成功才能关闭
	}

	datafile.clear(0);
	return false;


}


