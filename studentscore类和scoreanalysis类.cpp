#include"高中学校管理系统.h"
using namespace std;
void studentscore::getinfofromschool() {
	std::cout << "正在从文件中获取学生信息...\n";
	ifstream document("student.csv");
	if (!document.is_open()) { throw invalid_argument("student.csv文件无法打开"); }
	string line;//按行读取文件；
	while (getline(document, line)) {
		stringstream ss(line);
		std::array<string, 6> temp;
		for (auto& elem : temp) {
			getline(ss >> ws, elem, ',');
		}
		studatalist[temp[2]].insert({ (temp[0] + temp[4] + temp[1] + temp[3]), stuwithscore(temp[0], temp[4], temp[1], temp[3]) });
	}
	document.close();
	std::cout << "学生信息获取成功！\n";system("pause");
}
void studentscore::inputscore() {
	std::cout << "请输入要输入成绩的年级（1，2，3）\n";
	bool t = 0; int temp = choiceensure();
	if (temp == 1) { std::cout << "选科前还是选科后？选科前按1，选课后按0;\n"; cin >> t; }
	std::cout << "请输入筛选条件:姓名,学号,选科或选科+班级"; string finder; cin >> finder; 
	std::vector<stuwithscore*> tempvec;
	for(auto& elem:studatalist[grade_map[temp]]){
		if (compareequal(finder, elem.second))tempvec.push_back(&elem.second);
	}
	std::cout<<"找到"<<tempvec.size()<<"个学生\n";
	std::cout << "你想为多少个学生输入/修改成绩？\n"; cin >> temp;int j = 0;
	if(j>=tempvec.size())std::cout<<"输入数量大于学生数量，已自动调整为最大值\n";
	for (auto elem : tempvec) { if(j>=temp)break; std::cout << "这是要修改的第"<<++j<<"个学生的信息\n"; changestuscore(*elem, t); }
	system("pause");
}
void studentscore::getscorefromdoc() {
	std::cout << "请输入文件中学生成绩的年级(1，2，3)\n";
	bool t = 0; int temp = choiceensure(); int j = temp - 1;
	std::cout << "请输入文件名与文件路径(全名）\n"; string filename; cin >> filename;
	ifstream A(filename); if (!A.is_open()) { cerr << "文件" << filename << "无法打开\n"; }

	string line;//按行读取文件；
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
	std::cout<<"学生信息读取成功！\n"; system("pause");
}

void studentscore::searchandcalculate() {
	std::cout << "请输入要查找学生的年级（1，2，3）";
	//计算各科与总成绩期望与方差，总成绩为两个数组最后一项
	std::array<double,10> expectation, variance;
	int tempnum = choiceensure();
	std::cout << "请输入筛选条件:姓名,学号,选科或选科+班级(如物化生11)\n";
	string finder; cin >> finder; 
	stuwithscore::showhead(); std::cout << '\n'; std::vector<stuwithscore>temp;
	for (auto& elem : studatalist[grade_map[tempnum]]) {
		if (compareequal(finder, elem.second))
			temp.push_back(elem.second);
	}
	if (temp.empty()) { std::cout << "查无此人\n"; return; }
	std::cout << "找到" << temp.size() << "个学生\n";
	std::sort(temp.begin(), temp.end(), ifgreater);//一元谓词，降序排序；
	std::for_each(temp.begin(), temp.end(), [](stuwithscore& A) {A.print(); });
	
	std::cout << "是否计算平均分与方差？是则输入y，否则输入其他\n"; string y = "y"; cin >> y; bool p = (y == "y");
	if (p) { calculate(temp, expectation, variance); }
	std::cout << "是否打印成绩？是则输入y，否则输入其他\n"; string z = "y"; cin >> z; bool q = (z == "y");
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



//scoreanalysis类
void scoreanalysis::inputscorefromdoc() {
	string t = "1"; int i = 0;
	while (t != "0") {
		std::cout << "请输入第" << ++i << "个学生成绩文件的文件名与文件路径\n"; string filename; cin >> filename;
		ifstream A(filename); if (!A.is_open()) { std::cout << "文件" << filename << "无法打开\n"; i--; continue; }
		string line;//按行读取文件；
		while (getline(A, line)) {
			stringstream ss(line); stuwithscore stu;string tempinfo[14];
			for (int i = 0; i < 14; i++) 
				getline(ss >> ws, tempinfo[i], ',');
			stu.name = tempinfo[0]; stu.choice = tempinfo[1]; stu.id = tempinfo[2]; stu.stuclass = tempinfo[3];
			for (int i = 0; i < 9; i++) { stu.score[i] = stoi(tempinfo[4 + i]); }
			stu.calculatetotal(); studatalist[stu.id].push_back(move(stu));
		}std::cout << "第" << i << "个文件" << filename << "读取完毕\n";
		std::cout << "是否读取第" << i + 1 << "个文件？否则输入0,是则输入其他\n"; cin >> t;
	}system("pause");
}
void scoreanalysis::getanalysis() {
	string temp; std::cout << "请输入学生学号\n"; cin >> temp; if (studatalist[temp].empty()) { std::cout << "查无此人\n"; return; }
	auto p = studatalist[temp].begin();
	std::cout << "姓名:" << p->name << "\t选科:" << p->choice << "\tid:" << p->id << "\t班级:" << p->stuclass << "\t\n";
	for (int i = 0; i < 9; i++) { std::cout << '\t' << subjects[i]; }std::cout << endl;
	for (auto& studata : studatalist[temp]) {
		for (auto& fensu : studata.score) std::cout << '\t' << fensu;
		std::cout << '\t' << studata.total << endl;
	}
	std::cout << "想具体分析哪个科目成绩变化？\n";
	static std::array<wstring, 9> Lsubjects = { L"语文", L"数学", L"英语", L"物理", L"化学", L"生物", L"历史", L"政治", L"地理"};
	wstring temp2;
	std::vector<double> tempvec; int j;
	std::cout << "请输入序号(1-10)\n";
	std::cout << "映射关系：1.语文 2.数学 3.英语 4.物理 5.化学 6.生物 7.历史 8.政治 9.地理 10.总分\n";
	do {
		cin >> j;
	} while (j < 1 || j>10);
	for (const auto& studata : studatalist[temp]) {
		if (j == 10) { tempvec.push_back(studata.total); continue; }
		tempvec.push_back(studata.score[j-1]);
	}
	if(j!=10)
	    analysis(tempvec.begin(), tempvec.end(),(Lsubjects[j-1]+L"成绩变化").c_str());
	else
		analysis(tempvec.begin(), tempvec.end(), L"总分成绩变化");
	system("pause"); 
}

