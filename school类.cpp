#include"高中学校管理系统.h"
school::school(size_t tea_num) {//构造函数，初始化系统，读取学生信息和老师信息
	std::cout << "系统初始化中......\n";
	T.reserve(tea_num);
	documentreadstu();
	documentreadtea();
	system("cls");
}
school::~school() {//析构函数,保存学生信息和老师信息
	std::cout << "系统正在保存数据，请稍侯......\n";
	documentwritstu();
	documentwrittea();
	system("cls");
}
//判断年级和科目是否存在
bool school::ifexistgraorsub(cstrref ss, std::string& G, std::string& S, std::string& I) {
	std::cout << "请分别输入要" << ss << "的学生的年级、选科、和学生的任意其他信息（学号、班级、姓名）:\n";
	std::cin >> G >> S >> I;
	if (students[G][S].empty()) {//若对应的年级和选科下无学生，则提示；
		std::cout << "该年级和选科下无此学生！\n";
		return false;
	}return true;
}


void school::documentreadstu() {
	ifstream A("student.csv"); if (!A.is_open()) throw invalid_argument("学生文件打开失败!\n");
	if (A.is_open()) {	
		std::cout << "学生信息读取中\n";
		std::string line;//按行读取文件；
		while (getline(A, line)) {//逐行读取文件
			stringstream ss(line);  std::string temp[6];
			for (auto& s : temp) { getline(ss >> ws, s, ','); }
			students[temp[2]][temp[4]].emplace_back(temp[0], temp[5], temp[1], temp[2], temp[4], stoi(temp[3]));
		}A.close(); system("cls");
	}

}

void school::documentwritstu() {
	std::cout << "学生信息正在保存中......\n";
	//ofstream grade_subjectdocument[36]; ofstream gradedocument[3]; 
	std::array<ofstream,36> grade_subjectdocument; std::array<ofstream,3> gradedocument; ofstream studentdoc("student.csv");
	for (int i = 0; i < grade.size(); i++) {
		std::string filename = grade[i] + "学生信息.csv"; gradedocument[i].open(filename);
		for (int j = 0; j < Subjects.size(); j++) {
			std::string filename2 = grade[i] + Subjects[j] + "学生信息.csv";
			grade_subjectdocument[i * 12 + j].open(filename2);
			if (students[grade[i]].find(Subjects[j])!= students[grade[i]].end())
			{
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					gradedocument[i] << stu.putinfointodoc() << std::endl;
					grade_subjectdocument[static_cast<size_t>(i) * 12 + j] << stu.putinfointodoc() << std::endl;
					studentdoc << stu.putinfointodoc() << std::endl;
				}
			}
			//else cerr<<"年级"<<grade[i]<<",科目"<<Subjects[j]<<"下无学生"<<std::endl;
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
		std::cout << "年级：" << grade[i] << std::endl;
		for (int j = 0; j < Subjects.size(); j++) {
			if (students[grade[i]].find(Subjects[j])!= students[grade[i]].end()) {
				std::cout << "选科：" << Subjects[j] << std::endl;
				for (const auto& stu : students[grade[i]][Subjects[j]]) {
					stu.show();
				}
			}
		}
	}system("pause");
}
void school::addstudentsinfo() {
	std::cout << "你想添加几名学生的信息?" << std::endl;
	int num; std::cin >> num;
	for (int i = 0; i < num; i++) {
		student stu; stu.input(); std::string Grade = stu.grade; std::string Subject = stu.choice;
	    students[Grade][Subject].push_back(move(stu));
	}
	documentwritstu();
}
void school::deletestudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("删除", Grade, Subject, ID)) return;


	auto first=students[Grade][Subject].begin();
	auto last=students[Grade][Subject].end();
	students[Grade][Subject].erase(std::remove_if(first, last, [ID](student& s) {
	return (s.id == ID || to_string(s.stuclass) == ID || s.name == ID); }), last);
	
	documentwritstu(); system("pause");
}
void school::findstudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("查找", Grade, Subject, ID)) return;int count = 0;
	for (const auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == (ID) || stu.name == ID) {
			std::cout << "找到的第" << ++count << "个学生信息如下：\n";
			stu.show();
		}
	}
	if (count == 0) { std::cout << "查无此人" << std::endl; }
	system("pause");
}//查找学生信息
void school::changestudent() {
	std::string Grade, Subject, ID;
	if (!ifexistgraorsub("修改", Grade, Subject, ID)) return;
	std::vector<student*> tempP;
	for (auto& stu : students[Grade][Subject]) {
		if (stu.id == ID || to_string(stu.stuclass) == ID || stu.name == ID) {
			tempP.push_back(&stu);
		}
	}
	if (tempP.empty()) { std::cout << "查无此人" << std::endl; return; }
	else { std::cout << "找到" << tempP.size() << "个学生的信息;" << std::endl; }
	std::cout << "想要修改多少学生的信息？\n"; size_t n; std::cin >> n; size_t i = 0;
	if (n > tempP.size()) { std::cout << "输入的数量大于查找的数量，将修改全部查找的学生信息！\n";
	n = tempP.size(); }
	for (auto stu : tempP) {
		if (i >= n)break;
		std::cout << "要修改的"<<++i<<"个学生信息如下：\n";stu->show();
		std::cout << "请输入修改后的学生信息：\n";stu->input();
	}
	documentwritstu(); system("pause");
}
void school::showallteacherinfo() {
	showheadtea();
	for (auto& t : T) { t.show(1); }
	std::cout << "按任意键即可退出\n"; system("pause"); system("cls");
}
void school::addteachersinfo() {//添加老师个人信息，它会对那个文件D://teacher.txt产生宏观的影响
	int n;//新增的学生个数；
	std::cout << "你想添加多少老师的个人信息\n"; std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		teacher A; A.input(); T.push_back(move(A));
	}system("pause"); documentwrittea();
}

void school::findteacher() {
	std::vector<teacher>ss; std::string find = "0";
	std::string L; std::cout << "请输入老师的姓名，id或任教科目\n"; std::cin >> L;
	showheadtea();
	for (const auto& s : T) {
		if (s.name == L || s.id == L || s.subject == L) {
			s.show(1); ss.push_back(s); find = "1";
		}
	}if (find=="0") { std::cout << "查无此人" << std::endl; system("pause"); return; }
	std::cout << "是否将结果打印到文件？\n不打印输入0，打印文件输入其他"; std::cin >> find;
	if (find=="0") { system("pause"); return; }
	std::string filename = L; std::cout << "请输入文件名(全名）\n"; std::cin >> filename;
	std::ofstream F(filename); F << "姓名" << ',' << "性别" << ',' << "学号" << ',' << "教学科目"<<','<<"薪水" << std::endl;
	for (const auto& l : ss) 
		F << l.putinfointodoc() << std::endl;
	std::cout << "打印成功\n"; F.close();
	system("pause");
}
void school::deleteteacher() {
	bool find = 0; size_t T1 = 0, T2 = 0;
	std::string L; std::cout << "请输入待删除老师的姓名，id或任教科目\n"; std::cin >> L; T1 = T.size();
	auto first = T.begin();
	auto last = T.end();
	T.erase(std::remove_if(first, last, [L](teacher& s) {
		return(s.name == L || s.id == L || s.subject == L); }), last);

	T2 = T.size();bool p = (T1 != T2);
	std::cout << (p ? "删除成功\n" : "查无此人\n") << std::endl; if (p) { documentwrittea(); }
}


void school::changeteacher() {
	bool find = 0;
	std::string L; std::cout << "请输入待修改教师的姓名，id，或任教科目\n"; std::cin >> L;
	std::vector<teacher*> tempP;
	for (auto& s : T) {//auto&s:S可以修改数据；
		if (s.name == L || s.id == L || s.subject == L)
		{
			tempP.push_back(&s); find = 1;
		}
	}if (!find) { std::cout << "查无此人" << std::endl; return; }
	size_t m,n=tempP.size(),p=0;
	std::cout << "找到" << n << "个教师的信息;" << std::endl;
	std::cout << "想要修改多少教师的信息？\n"; std::cin >> m;
	if (m > n) { std::cout << "输入的数量大于查找的数量，将修改全部查找的教师信息！\n"; m = n; }
	for (auto &s : tempP) {
		if (p >= m)break;
		std::cout << "要修改的" << ++p << "个教师信息如下：\n"; s->show(1);
		std::cout << "是否修改教师姓名:" << s->name << std::endl;
		if (choice()) { std::cout << "请输入改后教师姓名："; std::cin >> s->name; }
		std::cout << "是否修改教师id:" << s->id << std::endl;
		if (choice()) { std::cout << "请输入改后教师id："; std::cin >> s->id; }
		std::cout << "是否修改教师教学科目:" << s->subject << std::endl;
		if (choice()) { std::cout << "请输入改后教师教学科目："; std::cin >> s->subject; }
		std::cout << "是否修改教师薪水:" << s->salary << std::endl;
		if (choice()) { std::cout << "请输入改后教师薪水："; std::cin >> s->salary; }
	}
	
	documentwrittea();system("pause");
}

void school::documentreadtea() {//逐行读取teacher.txt
	ifstream B("teacher.csv"); if (!B.is_open()) throw invalid_argument("教师文件打开失败!\n");
	if (B.is_open())
	{
		std::cout << "教师信息读取中\n";
		std::string line;//按行读取文件；
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


void school::documentwrittea() {//教师信息文件保存
	ofstream B("teacher.csv"); std::cout << "教师信息文件保存中......\n";
	for (const auto& tea : T) {
		B << tea.putinfointodoc() << std::endl;
	}B.close(); system("cls");
}