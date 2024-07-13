#include"高中学校管理系统.h"
using namespace std;
void teacher::show(bool x) const {
	if (x == 0)
		cout << "姓名：" << name << "性别" << sex << "教师id:" << id << "学科:" << subject <<"工资:"<<salary << endl;
	else cout << name << '\t' << sex << '\t' << id << '\t' << subject << '\t' << salary <<"\t\n" ;
}
void teacher::input() {//输入老师信息；
	cout << "请输入姓名:\n"; cin >> name;
	cout << "请输入性别:\n"; cin >> sex;
	cout << "请输入教师id:\n"; cin >> id;
	cout << "提示：教师任教的学科包括:\n";
	cout << "语文, 数学, 英语, 物理, 化学, 生物,\n 政治, 历史, 地理, 信息, 体育, 艺术\n";
	cout << "请输入学科\n"; cin >> subject;
	cout << "请输入工资:\n"; cin >> salary;
}
string teacher::putinfointodoc()const {
	stringstream temp; temp << name << ',' << sex << ',' << id << ',' << subject<<','<<salary; return move(temp.str());
}

void student::show(bool x) const {
	if (!x)
		cout << "姓名：" << name << " 性别：" << sex << " 学号:" << id << " 年级:" << grade << " 班级" << stuclass << " 选科:" << choice << endl;
	else
		cout  << name << '\t' << sex << '\t' << id << '\t' << grade << '\t' << stuclass << '\t' << choice <<"\t\n";
}
void student::input(bool flag) {//输入学生信息；
	cout << "请输入姓名：\n"; cin >> name;
	cout << "请输入性别(男/女):\n"; cin >> sex;
	cout << "请输入学号:\n"; cin >> id;
	cout << "请输入年级\n";
	cout << "(提示：年级包括：高一，高二，高三):\n"; cin >> grade;
	cout << "请输入班级:\n"; cin >> stuclass;
	cout << "请输入选科\n";
	cout << "提示:选科包括:\n物化生,物化政,物化地,物生政,物生地,物政地,\n历化生,历化政,历化地,历生政,历生地,历政地:\n"; cin >> choice;
}
string student::putinfointodoc()const {
	stringstream temp; 
	temp << name << "," << id << "," << grade << "," << stuclass << "," << choice << "," << sex; return temp.str();
}
void showheadtea() {
	cout <<  "姓名\t" <<"性别\t"  << "教师id\t"  << "学科\t" << "工资\t\n";

}
void showheadstu() {
	cout << "姓名\t" << "性别\t" << "学号\t" << "年级\t" << "班级\t" << "选科\t\n" ;
}
void stuwithscore::scoreinputB() {  //选科后的成绩输入函数，语数英物3化4生5历6政7地8
	static std::unordered_map<string, std::vector<int>> subject_to_indices = {
	 {"物化生", {3, 4, 5}},{"物化政", {3, 4, 7}},{"物化地", {3, 4, 8}},{"物生政", {3, 5, 7}},{"物生地", {3, 5, 8}},{"物政地", {3, 7, 8}},
	 {"历化生", {6, 4, 5}},{"历化政", {6, 4, 7}},{"历化地", {6, 4, 8}},{"历生政", {6, 5, 7}},{"历生地", {6, 5, 8}},{"历政地", {6, 7, 8}} };
	string i;
	do {
		for (auto& data : score)data = 0;
		cout << "请输入语文，数学，英语成绩\n";
		for (int i = 0; i < 3; i++)
			cin >> score[i];
		cout << "请输入" << choice << "成绩\n";
		// 根据选择输入对应的成绩  
		auto it = subject_to_indices.find(choice);
		if (it!= subject_to_indices.end()) {
			for (int index : it->second) {
				cout << "请输入" << subjects[index] << "成绩\n";
				cin >> score[index];
			}
		}
		else {
			cout << "选科无效\n";
			break;
		}
		cout << "是否确定？确定请按0，不确定请按其他\n"; cin >> i;
	} while (i != to_string(0)); calculatetotal();
}
void stuwithscore::scoreinputA() {//cout << "请输入语文，数学，英语，物理，化学，生物，历史，政治，地理成绩\n";
	for (size_t i = 0; i < 9; i++) { cout << "请输入" << subjects[i] << "成绩\n"; cin >> score[i]; }calculatetotal();
}

void stuwithscore::print(bool k )const {
	if (!k) {
		cout  << name << '\t' << id << '\t' << choice << '\t' << stuclass;
	}
	else {
		cout << '\t' << "姓名:" << '\t' << name << '\t' << "学号:" <<'\t' << id;
	}
	cout << "\n";
	for (int i = 0; i < 9; i++) {
		cout  << score[i]<<'\t';
	}cout << endl;
	cout  << total <<"\t\n";
}
string stuwithscore::putinfointodoc() const{
	stringstream of; of << name << "," << choice << "," << id << "," << stuclass;
	for (int i = 0; i < 9; i++) {
		of << "," << score[i];
	}of << "," << total; return of.str();
}