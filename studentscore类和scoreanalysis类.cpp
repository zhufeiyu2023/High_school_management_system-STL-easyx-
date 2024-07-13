#include"����ѧУ����ϵͳ.h"
using namespace std;
void studentscore::getinfofromschool() {
	std::cout << "���ڴ��ļ��л�ȡѧ����Ϣ...\n";
	ifstream document("student.csv");
	if (!document.is_open()) { throw invalid_argument("student.csv�ļ��޷���"); }
	string line;//���ж�ȡ�ļ���
	while (getline(document, line)) {
		stringstream ss(line);
		std::array<string, 6> temp;
		for (auto& elem : temp) {
			getline(ss >> ws, elem, ',');
		}
		studatalist[temp[2]].insert({ (temp[0] + temp[4] + temp[1] + temp[3]), stuwithscore(temp[0], temp[4], temp[1], temp[3]) });
	}
	document.close();
	std::cout << "ѧ����Ϣ��ȡ�ɹ���\n";system("pause");
}
void studentscore::inputscore() {
	std::cout << "������Ҫ����ɼ����꼶��1��2��3��\n";
	bool t = 0; int temp = choiceensure();
	if (temp == 1) { std::cout << "ѡ��ǰ����ѡ�ƺ�ѡ��ǰ��1��ѡ�κ�0;\n"; cin >> t; }
	std::cout << "������ɸѡ����:����,ѧ��,ѡ�ƻ�ѡ��+�༶"; string finder; cin >> finder; 
	std::vector<stuwithscore*> tempvec;
	for(auto& elem:studatalist[grade_map[temp]]){
		if (compareequal(finder, elem.second))tempvec.push_back(&elem.second);
	}
	std::cout<<"�ҵ�"<<tempvec.size()<<"��ѧ��\n";
	std::cout << "����Ϊ���ٸ�ѧ������/�޸ĳɼ���\n"; cin >> temp;int j = 0;
	if(j>=tempvec.size())std::cout<<"������������ѧ�����������Զ�����Ϊ���ֵ\n";
	for (auto elem : tempvec) { if(j>=temp)break; std::cout << "����Ҫ�޸ĵĵ�"<<++j<<"��ѧ������Ϣ\n"; changestuscore(*elem, t); }
	system("pause");
}
void studentscore::getscorefromdoc() {
	std::cout << "�������ļ���ѧ���ɼ����꼶(1��2��3)\n";
	bool t = 0; int temp = choiceensure(); int j = temp - 1;
	std::cout << "�������ļ������ļ�·��(ȫ����\n"; string filename; cin >> filename;
	ifstream A(filename); if (!A.is_open()) { cerr << "�ļ�" << filename << "�޷���\n"; }

	string line;//���ж�ȡ�ļ���
	while (getline(A, line)) {
		stringstream ss(line); 
		
		std::array<string, 14> tempinfo;
		for (auto& i:tempinfo) {
			getline(ss >> ws, i, ',');
		}
		stuwithscore stu(tempinfo[0],tempinfo[1],tempinfo[2],tempinfo[3]);
		for (int i = 0; i < 9; i++) { stu.score[i] = stoi(tempinfo[4 + i]); }
		stu.calculatetotal(); 
		if(studatalist.find(grade_map[j])!=studatalist.end()
			&&studatalist[grade_map[j]].find(stu.name+stu.choice+stu.id+stu.stuclass)
			!=studatalist[grade_map[j]].end())
		studatalist[grade_map[j]][stu.name + stu.choice + stu.id + stu.stuclass] = move(stu);
	}
	std::cout<<"ѧ����Ϣ��ȡ�ɹ���\n"; system("pause");
}

void studentscore::searchandcalculate() {
	std::cout << "������Ҫ����ѧ�����꼶��1��2��3��";
	//����������ܳɼ������뷽��ܳɼ�Ϊ�����������һ��
	std::array<double,10> expectation, variance;
	int tempnum = choiceensure();
	std::cout << "������ɸѡ����:����,ѧ��,ѡ�ƻ�ѡ��+�༶(���ﻯ��11)\n";
	string finder; cin >> finder; 
	stuwithscore::showhead(); std::cout << '\n'; std::vector<stuwithscore>temp;
	for (auto& elem : studatalist[grade_map[tempnum]]) {
		if (compareequal(finder, elem.second))
			temp.push_back(elem.second);
	}
	if (temp.empty()) { std::cout << "���޴���\n"; return; }
	std::cout << "�ҵ�" << temp.size() << "��ѧ��\n";
	std::sort(temp.begin(), temp.end(), ifgreater);//һԪν�ʣ���������
	std::for_each(temp.begin(), temp.end(), [](stuwithscore& A) {A.print(); });
	
	std::cout << "�Ƿ����ƽ�����뷽���������y��������������\n"; string y = "y"; cin >> y; bool p = (y == "y");
	if (p) { calculate(temp, expectation, variance); }
	std::cout << "�Ƿ��ӡ�ɼ�����������y��������������\n"; string z = "y"; cin >> z; bool q = (z == "y");
	if (q) { writscoredoc(temp, expectation, variance,p); }
	system("pause");
}

void studentscore::showallstuscore() {
	stuwithscore::showhead();
	for (auto& stus : studatalist) {
		for (auto& elem : stus.second) {
			elem.second.print();
		}
	}
	system("pause");
}



//scoreanalysis��
void scoreanalysis::inputscorefromdoc() {
	string t = "1"; int i = 0;
	while (t != "0") {
		std::cout << "�������" << ++i << "��ѧ���ɼ��ļ����ļ������ļ�·��\n"; string filename; cin >> filename;
		ifstream A(filename); if (!A.is_open()) { std::cout << "�ļ�" << filename << "�޷���\n"; i--; continue; }
		string line;//���ж�ȡ�ļ���
		while (getline(A, line)) {
			stringstream ss(line); stuwithscore stu;string tempinfo[14];
			for (int i = 0; i < 14; i++) 
				getline(ss >> ws, tempinfo[i], ',');
			stu.name = tempinfo[0]; stu.choice = tempinfo[1]; stu.id = tempinfo[2]; stu.stuclass = tempinfo[3];
			for (int i = 0; i < 9; i++) { stu.score[i] = stoi(tempinfo[4 + i]); }
			stu.calculatetotal(); studatalist[stu.id].push_back(move(stu));
		}std::cout << "��" << i << "���ļ�" << filename << "��ȡ���\n";
		std::cout << "�Ƿ��ȡ��" << i + 1 << "���ļ�����������0,������������\n"; cin >> t;
	}system("pause");
}
void scoreanalysis::getanalysis() {
	string temp; std::cout << "������ѧ��ѧ��\n"; cin >> temp; if (studatalist[temp].empty()) { std::cout << "���޴���\n"; return; }
	auto p = studatalist[temp].begin();
	std::cout << "����:" << p->name << "\tѡ��:" << p->choice << "\tid:" << p->id << "\t�༶:" << p->stuclass << "\t\n";
	for (int i = 0; i < 9; i++) { std::cout << '\t' << subjects[i]; }std::cout << endl;
	for (auto& studata : studatalist[temp]) {
		for (auto& fensu : studata.score) std::cout << '\t' << fensu;
		std::cout << '\t' << studata.total << endl;
	}
	std::cout << "���������ĸ���Ŀ�ɼ��仯��\n";
	static std::array<wstring, 9> Lsubjects = { L"����", L"��ѧ", L"Ӣ��", L"����", L"��ѧ", L"����", L"��ʷ", L"����", L"����"};
	wstring temp2;
	std::vector<double> tempvec; int j;
	std::cout << "���������(1-10)\n";
	std::cout << "ӳ���ϵ��1.���� 2.��ѧ 3.Ӣ�� 4.���� 5.��ѧ 6.���� 7.��ʷ 8.���� 9.���� 10.�ܷ�\n";
	do {
		cin >> j;
	} while (j < 1 || j>10);
	for (const auto& studata : studatalist[temp]) {
		if (j == 10) { tempvec.push_back(studata.total); continue; }
		tempvec.push_back(studata.score[j-1]);
	}
	if(j!=10)
	    analysis(tempvec.begin(), tempvec.end(),(Lsubjects[j-1]+L"�ɼ��仯").c_str());
	else
		analysis(tempvec.begin(), tempvec.end(), L"�ֳܷɼ��仯");
	system("pause"); 
}

