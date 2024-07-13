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
	//�������ݿ�ĺ���
	int getRole(const std::string& name);
	//��ȡ��ɫ�ĺ���
	void Update();
	//�������ݿ�ĺ���
	void Freeze(const std::string& name);
	//�����˺ŵĺ���
	bool IsFrozen(const std::string& name);
	//�ж��˺��Ƿ񱻶���ĺ���
public:
	pw(std::string dataname1="Password.csv") //���캯�����������뱣��·��
	{
		dataname = dataname1;
		Load();
	}
	void Register();
	//ע�ắ����ǰ���û�ע���˺�����
	int Login();
	//��¼������ǰ���û���½ϵͳ
	void ChangePassword();
	//�޸����뺯��
};
inline void pw::Register()
{
	std::string zh, mm;
	std::cout << "�������˺ţ�" << std::endl;
	std::cin >> zh;
	while (map.find(zh)!= map.end()) {
		std::cout << "�����������˺ţ�" << std::endl;
		std::cin >> zh;
	}//ϵͳ���Ѿ��и��˺ţ����û����������˺ſ�ʼע��

/*---------------------------------------------------------------
	 �˺Ż�ȡ���ִ������
----------------------------------------------------------------*/

	std::cout << "���������룺" << std::endl;
	std::cin >> mm;
	std::unordered_map<std::string, Role> role_map = {{"ѧ��", Student}, {"��ʦ", Teacher}, {"����Ա", Admin}};
	std::cout << "�������û�����ѧ������ʦ������Ա\n";std::string Role_str;std::cin >> Role_str;
	while(role_map.find(Role_str)==role_map.end()){std::cout<<"�����������û�����ѧ������ʦ������Ա\n";std::cin>>Role_str;}
	map[zh] = std::make_pair(mm, role_map[Role_str]);//�����˺�--����ӳ��

/*---------------------------------------------------------------
	 �����ȡ���ִ������
----------------------------------------------------------------*/

	Update();

/*---------------------------------------------------------------
	 ���ݱ��沿�ִ������
----------------------------------------------------------------*/
	std::cout << "ע��ɹ���" << std::endl;
};

inline int pw::Login()
{   std::string tempzh, tempmm;//���ڲɼ��û�������˺��������ʱ����
	bool flag1=true,flag2=true;//flag1����˺��Ƿ���ڣ�flag2��������Ƿ����˺Ŷ�Ӧ
	int count = 0;//��������������10�δ����򶳽��˻�
	do {std::cout << "�˺ţ�";std::cin >> tempzh;
		std::cout << "���룺";std::cin >> tempmm;
		if (map.find(tempzh)==map.end()) { flag1 = false; std::cout << "�˺Ų����ڣ�" << std::endl; }
		//�˺Ų����ڣ�flag1=false
		else if (IsFrozen(tempzh)) { std::cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << std::endl; return -1; }
		//����˺��Ƿ񱻶���
		else if ((map.find(tempzh)->second.first) != tempmm) { flag2 = false; count++; std::cout << "���벻��ȷ��" <<'\t' << std::endl; }
		//���벻��ȷ��flag2=false,ͬʱ����countֵ���ﵽ���Ƶ�¼����Ч��
		else break;
		//����ѭ���������˺Ŵ��ڲ���������ȷ����ֱ������ѭ��
	} while (((flag1 == false) ||(flag2 == false)) && (count < 10));
	//ѭ������������1.�˺Ų����ڣ�flag1==false��;2.���벻��ȷ��flag2==false��;3.����������С��10			
	if (count >= 10)
	{
		std::cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << std::endl;
		Freeze(tempzh);//�����˺�
		return -1;
	}//�������������࣬��½ʧ��
	else 
	{std::cout << "��½�ɹ������ڽ���ϵͳ..." << std::endl;//��½�ɹ�
	return getRole(tempzh);}

};

inline void pw::ChangePassword()
{std::string mm1;std::string tempzh, tempmm;//���ڲɼ��û�������˺��������ʱ����
	bool flag1 = true, flag2 = true;//flag1����˺��Ƿ���ڣ�flag2��������Ƿ����˺Ŷ�Ӧ
	int count = 0;//��������������10�δ����򶳽��˻�
	do {std::cout << "�˺ţ�";std::cin >> tempzh;std::cout << "���룺";std::cin >> tempmm;
		if (map.find(tempzh)==map.end()) { flag1 = false; std::cout << "�˺Ų����ڣ�" << std::endl; }
		//�˺Ų����ڣ�flag1=false
		else if (IsFrozen(tempzh)) { std::cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << std::endl; return; }
		//����˺��Ƿ񱻶���
		else if ((map.find(tempzh)->second.first) != tempmm) { flag2 = false; count++; std::cout << "���벻��ȷ��" << '\t' << std::endl; }
		//���벻��ȷ��flag2=false,ͬʱ����countֵ���ﵽ���Ƶ�¼����Ч��
		else break;
		//����ѭ���������˺Ŵ��ڲ���������ȷ����ֱ������ѭ��
	} while (((flag1 == false) || (flag2 == false)) && (count < 10));
	//ѭ������������1.�˺Ų����ڣ�flag1==false��;2.���벻��ȷ��flag2==false��;3.����������С��10
	if (count >= 10)
	{std::cout << "�������������࣬�˺��Ѷ��ᣬ����ϵ����Ա�ⶳ" << std::endl;
		Freeze(tempzh);//�����˺�
	}//�������������࣬��½ʧ��
	else std::cout << "��½�ɹ������ڽ���ϵͳ..." << std::endl;//��½�ɹ�
	//���ȵ�½��Ȼ����ܽ��к�������
	std::cout << "������������" << std::endl;std::cin >> mm1;map[tempzh].first = mm1;
	//�����µ������˺�hash_map��ϵ
	Update();
	//�������ݿ�
	std::cout << "�����޸ĳɹ���" << std::endl;
};

inline void pw::Load()
{
	datafile.open(dataname, ios::in);
	if (datafile)
	{std::string zh, mm; int r;
		std::cout << "���ڼ�������..." << std::endl; std::string temp;
		while (getline(datafile, temp))
		{   stringstream ss(temp); getline(ss >> ws, zh, ','); 
			getline(ss >> ws, mm, ','); ss >> r;
			map.insert({ zh, std::make_pair(mm, Role(r)) });
		}
		datafile.close();
		std::cout<<"�������ݳɹ���"<<std::endl;
	}
	else std::cout << "��������ʧ�ܣ�" << std::endl;
	datafile.clear(0);

};//�������ݿ�ĺ���

inline void clearfile(std::string s) 
{
	fstream tempfile;
	tempfile.open(s, ios::trunc, ios::out);
	tempfile.close();

}

inline void copy(const std::string &s1,const std::string &s2)//�ļ����ƺ�������s1������s2
{
	std::string line;
	ifstream ini_file(s1);
	ofstream out_file(s2);
	if (ini_file && out_file) {

		while (getline(ini_file, line)) {
			out_file << line << "\n";
		}
	}
	else cerr << "�ڸ����ļ�ʱ�����˴���" << std::endl;
	ini_file.close();
	out_file.close();
	
};

inline void pw::Update()
{
	/*˼·��
	1.����Ѵ��ڵĿ����ļ�password_back_up.txt
	2.������ǰpassword.txt�ڵ����ݣ���password_back_up.txt�ļ�����Ϊ����
	3.���password.txt�ļ��ڵ���������
	4.����hash_map������������ݵ�password.txt

	��Ҫ�õ��ĸ���������
	void clearfile(std::string s)��
	void copy(std::string s1,std::string s2);
	*/
	clearfile("password_back_up.csv");
	//����1
	copy(dataname, "password_back_up.csv");
	//����2
	clearfile(dataname);
	//����3
	datafile.open(dataname, ios::out);
	for (const auto& mypair : map) {
		datafile << mypair.first << ',' << mypair.second.first << ',' << mypair.second.second << "\n";
	}
	datafile << std::endl;
	datafile.close();
	//����4


};


//�������ݿ�ĺ���

inline int pw::getRole(const std::string& name) {
	if (map.find(name)!= map.end()) return map.find(name)->second.second;
	else return -1;
}

inline void pw::Freeze(const std::string &name)
{
	/*˼·��
	1.�趨txt�ļ� banlist
	2.��name������banlist��
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
		datafile.close(); //�򿪳ɹ����ܹر�
	}

	datafile.clear(0);
	return false;


}


