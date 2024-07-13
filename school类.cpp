#include"����ѧУ����ϵͳ.h"
school::school(size_t tea_num) {//���캯������ʼ��ϵͳ����ȡѧ����Ϣ����ʦ��Ϣ
	std::cout << "ϵͳ��ʼ����......\n";
	T.reserve(tea_num);
	documentreadstu();
	documentreadtea();
	system("cls");
}
school::~school() {//��������,����ѧ����Ϣ����ʦ��Ϣ
	std::cout << "ϵͳ���ڱ������ݣ����Ժ�......\n";
	documentwritstu();
	documentwrittea();
	system("cls");
}
//�ж��꼶�Ϳ�Ŀ�Ƿ����
bool school::ifexistgraorsub(cstrref ss, std::string& G, std::string& S, std::string& I) {
	std::cout << "��ֱ�����Ҫ" << ss << "��ѧ�����꼶��ѡ�ơ���ѧ��������������Ϣ��ѧ�š��༶��������:\n";
	std::cin >> G >> S >> I;
	if (students[G][S].empty()) {//����Ӧ���꼶��ѡ������ѧ��������ʾ��
		std::cout << "���꼶��ѡ�����޴�ѧ����\n";
		return false;
	}return true;
}


void school::documentreadstu() {
	ifstream A("student.csv"); if (!A.is_open()) throw invalid_argument("ѧ���ļ���ʧ��!\n");
	if (A.is_open()) {	
		std::cout << "ѧ����Ϣ��ȡ��\n";
		std::string line;//���ж�ȡ�ļ���
		while (getline(A, line)) {//���ж�ȡ�ļ�
			stringstream ss(line);  std::string temp[6];
			for (auto& s : temp) { getline(ss >> ws, s, ','); }
			students[temp[2]][temp[4]].emplace_back(temp[0], temp[5], temp[1], temp[2], temp[4], stoi(temp[3]));
		}A.close(); system("cls");
	}

}

void school::documentwritstu() {
	std::cout << "ѧ����Ϣ���ڱ�����......\n";
	//ofstream grade_subjectdocument[36]; ofstream gradedocument[3]; 
	std::array<ofstream,36> grade_subjectdocument; std::array<ofstream,3> gradedocument; ofstream studentdoc("student.csv");
	for (int i = 0; i < grade.size(); i++) {
		std::string filename = grade[i] + "ѧ����Ϣ.csv"; gradedocument[i].open(filename);
		for (int j = 0; j < Subjects.size(); j++) {
			std::string filename2 = grade[i] + Subjects[j] + "ѧ����Ϣ.csv";
			grade_subjectdocument[i * 12 + j].open(filename2);
			if (students[grade[i]].find(Subjects[j])!= students[grade[i]].end())
			{
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					gradedocument[i] << stu.putinfointodoc() << std::endl;
					grade_subjectdocument[static_cast<size_t>(i) * 12 + j] << stu.putinfointodoc() << std::endl;
					studentdoc << stu.putinfointodoc() << std::endl;
				}
			}
			//else cerr<<"�꼶"<<grade[i]<<",��Ŀ"<<Subjects[j]<<"����ѧ��"<<std::endl;
			grade_subjectdocument[i * 12 + j].close();
		}
		gradedocument[i].close();
	}
	studentdoc.close();
	system("pause");
	system("cls");//A.close();
}
void school::showallstudentinfo() {
	for (int i = 0; i < grade.size(); i++) {
		std::cout << "�꼶��" << grade[i] << std::endl;
		for (int j = 0; j < Subjects.size(); j++) {
			if (students[grade[i]].find(Subjects[j])!= students[grade[i]].end()) {
				std::cout << "ѡ�ƣ�" << Subjects[j] << std::endl;
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					stu.show();
				}
			}
		}
	}system("pause");
}
void school::addstudentsinfo() {
	std::cout << "������Ӽ���ѧ������Ϣ?" << std::endl;
	int num; std::cin >> num;
	for (int i = 0; i < num; i++) {
		student stu; stu.input(); std::string Grade = stu.grade; std::string Subject = stu.choice;
	    students[Grade][Subject].push_back(move(stu));
	}
	documentwritstu();
}
void school::deletestudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("ɾ��", Grade, Subject, ID)) return;


	auto first=students[Grade][Subject].begin();
	auto last=students[Grade][Subject].end();
	students[Grade][Subject].erase(std::remove_if(first, last, [ID](student& s) {
	return (s.id == ID || to_string(s.stuclass) == ID || s.name == ID); }), last);
	
	documentwritstu(); system("pause");
}
void school::findstudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("����", Grade, Subject, ID)) return;int count = 0;
	for (const auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == (ID) || stu.name == ID) {
			std::cout << "�ҵ��ĵ�" << ++count << "��ѧ����Ϣ���£�\n";
			stu.show();
		}
	}
	if (count == 0) { std::cout << "���޴���" << std::endl; }
	system("pause");
}//����ѧ����Ϣ
void school::changestudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("�޸�", Grade, Subject, ID)) return;
	std::vector<student*> tempP;
	for (auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == ID || stu.name == ID) {
			tempP.push_back(&stu);
		}
	}
	if (tempP.empty()) { std::cout << "���޴���" << std::endl; return; }
	else { std::cout << "�ҵ�" << tempP.size() << "��ѧ������Ϣ;" << std::endl; }
	std::cout << "��Ҫ�޸Ķ���ѧ������Ϣ��\n"; size_t n; std::cin >> n; size_t i = 0;
	if (n > tempP.size()) { std::cout << "������������ڲ��ҵ����������޸�ȫ�����ҵ�ѧ����Ϣ��\n";
	n = tempP.size(); }
	for (auto stu : tempP) {
		if (i >= n)break;
		std::cout << "Ҫ�޸ĵ�"<<++i<<"��ѧ����Ϣ���£�\n";stu->show();
		std::cout << "�������޸ĺ��ѧ����Ϣ��\n";stu->input();
	}
	documentwritstu(); system("pause");
}
void school::showallteacherinfo() {
	showheadtea();
	for (auto& t : T) { t.show(1); }
	std::cout << "������������˳�\n"; system("pause"); system("cls");
}
void school::addteachersinfo() {//�����ʦ������Ϣ��������Ǹ��ļ�D://teacher.txt������۵�Ӱ��
	int n;//������ѧ��������
	std::cout << "������Ӷ�����ʦ�ĸ�����Ϣ\n"; std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		teacher A; A.input(); T.push_back(move(A));
	}system("pause"); documentwrittea();
}

void school::findteacher() {
	std::vector<teacher>ss; std::string find = "0";
	std::string L; std::cout << "��������ʦ��������id���ν̿�Ŀ\n"; std::cin >> L;
	showheadtea();
	for (const auto& s : T) {
		if (s.name == L || s.id == L || s.subject == L) {
			s.show(1); ss.push_back(s); find = "1";
		}
	}if (find=="0") { std::cout << "���޴���" << std::endl; system("pause"); return; }
	std::cout << "�Ƿ񽫽����ӡ���ļ���\n����ӡ����0����ӡ�ļ���������"; std::cin >> find;
	if (find=="0") { system("pause"); return; }
	std::string filename = L; std::cout << "�������ļ���(ȫ����\n"; std::cin >> filename;
	std::ofstream F(filename); F << "����" << ',' << "�Ա�" << ',' << "ѧ��" << ',' << "��ѧ��Ŀ"<<','<<"нˮ" << std::endl;
	for (const auto& l : ss) 
		F << l.putinfointodoc() << std::endl;
	std::cout << "��ӡ�ɹ�\n"; F.close();
	system("pause");
}
void school::deleteteacher() {
	bool find = 0; size_t T1 = 0, T2 = 0;
	std::string L; std::cout << "�������ɾ����ʦ��������id���ν̿�Ŀ\n"; std::cin >> L; T1 = T.size();
	auto first = T.begin();
	auto last = T.end();
	T.erase(std::remove_if(first, last, [L](teacher& s) {
		return(s.name == L || s.id == L || s.subject == L); }), last);

	T2 = T.size();bool p = (T1 != T2);
	std::cout << (p ? "ɾ���ɹ�\n" : "���޴���\n") << std::endl; if (p) { documentwrittea(); }
}


void school::changeteacher() {
	bool find = 0;
	std::string L; std::cout << "��������޸Ľ�ʦ��������id�����ν̿�Ŀ\n"; std::cin >> L;
	std::vector<teacher*> tempP;
	for (auto& s : T) {//auto&s:S�����޸����ݣ�
		if (s.name == L || s.id == L || s.subject == L)
		{
			tempP.push_back(&s); find = 1;
		}
	}if (!find) { std::cout << "���޴���" << std::endl; return; }
	size_t m,n=tempP.size(),p=0;
	std::cout << "�ҵ�" << n << "����ʦ����Ϣ;" << std::endl;
	std::cout << "��Ҫ�޸Ķ��ٽ�ʦ����Ϣ��\n"; std::cin >> m;
	if (m > n) { std::cout << "������������ڲ��ҵ����������޸�ȫ�����ҵĽ�ʦ��Ϣ��\n"; m = n; }
	for (auto &s : tempP) {
		if (p >= m)break;
		std::cout << "Ҫ�޸ĵ�" << ++p << "����ʦ��Ϣ���£�\n"; s->show(1);
		std::cout << "�Ƿ��޸Ľ�ʦ����:" << s->name << std::endl;
		if (choice()) { std::cout << "������ĺ��ʦ������"; std::cin >> s->name; }
		std::cout << "�Ƿ��޸Ľ�ʦid:" << s->id << std::endl;
		if (choice()) { std::cout << "������ĺ��ʦid��"; std::cin >> s->id; }
		std::cout << "�Ƿ��޸Ľ�ʦ��ѧ��Ŀ:" << s->subject << std::endl;
		if (choice()) { std::cout << "������ĺ��ʦ��ѧ��Ŀ��"; std::cin >> s->subject; }
		std::cout << "�Ƿ��޸Ľ�ʦнˮ:" << s->salary << std::endl;
		if (choice()) { std::cout << "������ĺ��ʦнˮ��"; std::cin >> s->salary; }
	}
	
	documentwrittea();system("pause");
}

void school::documentreadtea() {//���ж�ȡteacher.txt
	ifstream B("teacher.csv"); if (!B.is_open()) throw invalid_argument("��ʦ�ļ���ʧ��!\n");
	if (B.is_open())
	{
		std::cout << "��ʦ��Ϣ��ȡ��\n";
		std::string line;//���ж�ȡ�ļ���
		while (getline(B, line)) {

			stringstream ss(line);
			teacher tea;
			static std::array<std::string, 5> temp;
			for (auto& elem:temp) {
				getline(ss >> ws, elem, ',');
			}
			tea.name = temp[0];  tea.sex = temp[1]; tea.id = temp[2]; tea.subject = temp[3]; tea.salary = stod(temp[4]);
			T.push_back(move(tea));
		}
		B.close(); system("cls");
	}
}


void school::documentwrittea() {//��ʦ��Ϣ�ļ�����
	ofstream B("teacher.csv"); std::cout << "��ʦ��Ϣ�ļ�������......\n";
	for (const auto& tea : T) {
		B << tea.putinfointodoc() << std::endl;
	}B.close(); system("cls");
}