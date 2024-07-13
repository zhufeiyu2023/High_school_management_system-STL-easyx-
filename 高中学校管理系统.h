#pragma once

#include"��״ͼ.h"

#include<iostream>

#include<string>

#include<fstream>

#include<algorithm>

#include<sstream>

#include<iomanip>

#include<stdexcept>

#include<array>

#include<vector>
#include<unordered_map>
using namespace std;

using cstrref = const std::string&;
//��ѡ�Ʒ���ѧ���������ӡ���ļ�
inline bool choice() {
	std::cout << "���޸��밴0,�޸��밴����\n";
	std::string choice = "0"; std::cin >> choice;
	if (choice == "0")return 0;
	return 1;
}
//person�࣬������Ա�Ļ���;
//teacher�࣬��ʦ�࣬�̳���person��;
//student�࣬ѧ���࣬�̳���person��;
//school�࣬ѧУ�࣬����ѧ������ʦ�ȣ���std::vector��myhash_mapʵ�ֵľۺ���;
//stuwithscore�࣬���ڴ��ѧ����Ϣ�ͳɼ��Ľṹ��;
//studentscore�࣬���ڴ��ѧ���ĳɼ�����;
//scoreanalysis�࣬���ڷ���ѧ���ĳɼ�����;
struct person{
	std::string name , sex , id ; 
	person(std::string n="0", std::string s="��", std::string i="0") :name(n), sex(s), id(i) {}
	virtual std::string putinfointodoc()const = 0;
};

const std::array<std::string, 3>grade = { "��һ","�߶�","����" };//�������飬���ڴ�Ÿ����꼶������
const std::array<std::string, 12> Subjects = {"�ﻯ��", "�ﻯ��", "�ﻯ��", "������", "������", "������", "������", "������", "������", "������", "������", "������"};
const std::array<std::string, 12> subjects= {"����", "��ѧ", "Ӣ��", "����", "��ѧ", "����", "��ʷ", "����", "����"," ��Ϣ", "����", "����"};
struct teacher:public person {
	std::string subject; double salary;
	teacher(cstrref n = "0", cstrref s = "��", cstrref i = "0", cstrref sub = "0", double sal = rand()%5000) :
		person(n, s, i), subject(sub), salary(sal) {}
	//�ν̿�Ŀ
	void show(bool x = 0) const;//չʾ��ʦ��Ϣ
	void input(); //������ʦ��Ϣ
	std::string putinfointodoc()const override;//����ʦ��Ϣ���ַ�������ʽд���ļ�
};
struct student:public person{//ѧ���ṹ�壬���е�Ԫ�غͺ����Ե���ѧ��������
	std::string grade, choice; int stuclass;
	student(cstrref n = "0", cstrref s = "��", cstrref i = "0", cstrref g = "0", cstrref c = "0", int sc = 0) :
		person(n, s, i), grade(g), choice(c), stuclass(sc) {}
	//�꼶��ѡ�ƣ��༶
	void show(bool x = 0) const;//չʾѧ����Ϣ
	void input(bool flag = 0);//����ѧ����Ϣ
	std::string putinfointodoc()const override;//��ѧ����Ϣ���ַ�������ʽд���ļ�
};
void showheadtea();//չʾ������ʦ��Ϣ�ı�ͷ
void showheadstu();//չʾ����ѧ����Ϣ�ı�ͷ
class school{
public:
private:std::vector<teacher> T; 
	   //myhash_map<std::string, myhash_map<std::string, std::vector<student>>> students;//��ֵ��
	   std::unordered_map<std::string,std::unordered_map<std::string,std::vector<student>>> students;
	   void documentreadstu();//��ȡѧ����Ϣ
	   void documentreadtea();//��ȡ��ʦ��Ϣ
	   void documentwritstu();//д��ѧ����Ϣ
	   void documentwrittea(); //д����ʦ��Ϣ
	   bool ifexistgraorsub(cstrref ss, std::string& G, std::string& S, std::string& I);//�ж��꼶�Ϳ�Ŀ�Ƿ����
public:
	school(size_t tea_num = 400);
	~school();
	void showallstudentinfo();//չʾ����ѧ����Ϣ
	void showallteacherinfo();//չʾ������ʦ��Ϣ
	void addstudentsinfo();//���ѧ����Ϣ
	void addteachersinfo();//�����ʦ��Ϣ
	void findstudent();//����ѧ����Ϣ
	void findteacher();//������ʦ��Ϣ
	void deleteteacher();//ɾ����ʦ��Ϣ
	void deletestudent();//ɾ��ѧ����Ϣ
	void changestudent();//�޸�ѧ����Ϣ
	void changeteacher();//�޸���ʦ��Ϣ
};


struct stuwithscore {
	std::string name, choice, id, stuclass;
	std::array<double, 9> score; double total;
	stuwithscore (cstrref n = "0", cstrref c = "0", cstrref i = "0", cstrref sc = "0",double total=0) :
		name(n), choice(c), id(i), stuclass(sc), total(total) {
	}
	void calculatetotal() {
		total = 0;for (auto& i : score) {total += i;}
	}
	void scoreinputB();//����ѡ�ƺ�ɼ�
	void scoreinputA();//����ѡ��ǰ�ɼ�
	void print(bool k = 0)const;//��ӡѧ����Ϣ
	std::string putinfointodoc()const;//��ѧ���ɼ���Ϣ���ַ�������ʽд���ļ�
	static std::string showhead(bool t = true) {//��ӡѧ����Ϣ��ͷ
		stringstream ss;
		if (t)//��ӡ��ͷ,tΪtrueʱ��ӡ��ͷ�������ӡ����
		{ss << "����\t" << "ѧ��\t"  << "ѡ��\t" << "�༶\t";
		for (int i = 0; i < 9; i++) { ss << subjects[i]<<'\t'; }ss  << "�ܷ�\t\n"; }
		else {ss << "����" << "," << "ѡ��" << "," << "ѧ��" << "," << "�༶";
		for (int i = 0; i < 9; i++) { ss << "," << subjects[i]; }ss << "," << "�ܷ�\n";}
		return (ss.str());
	}
};

//void print(stuwithscore& A);//��ӡѧ����Ϣ

inline void writscoredoc(std::vector<stuwithscore>& A,std::array<double,10>&average,std::array<double,10>&variance, bool T = true){
		std::string filename; std::cout << "�������ļ������ļ�·��(ȫ��):\n"; 
		std::cin >> filename;//��һ��ѧ��vectorд���ļ���
		std::cout << "��Ҫ����ϵͳ��ȡ���ļ����Ǳ��ڹ���չʾ\n";
		std::cout << "���ļ�, ����yչʾ������������ȡ\n";
		std::string cho; std::cin >> cho;

		ofstream of(filename);// std::string name, choice, id, stuclass; double score[9] = { 0 }; int total = 0;
		if (cho == "y") { of << stuwithscore::showhead(false); }
		for (auto& stu : A) { of << stu.putinfointodoc() << std::endl; }

		if (T && cho == "y")
		{
			of << "ƽ����" << ','; for (int i = 0; i < 3; i++) { of << "  " << ","; }
			for (auto& i : average) { of << scientific << setprecision(3) << i << ","; }
			of << std::endl << "����" << ','; for (int i = 0; i < 3; i++) { of << "  " << ","; }
			for (auto& i : variance) { of << scientific << setprecision(3) << i << ","; }
		}
		of.close(); system("pause");
}
//д��ѧ����Ϣ���ļ���TΪtrueʱд���ͷ������д�����ݣ�average��varianceΪƽ��ֵ�ͷ���
//average_size��variance_sizeΪƽ��ֵ�ͷ�������ĳ���
inline void calculate(std::vector<stuwithscore>& temp, std::array<double, 10>& expectation, std::array<double, 10>& variance) {
	size_t n = temp.size(); size_t e_size = expectation.size(), v_size = variance.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < e_size; j++) {
			if (j < e_size - 1) { expectation[j] += temp[i].score[j]; }
			else { expectation[j] += temp[i].total; }
		}
	}
	for (auto& i : expectation) { i /= n; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < v_size; j++) {
			double diff = 0.0;
			if (j < e_size - 1) { diff = temp[i].score[j] - expectation[j]; }
			else { diff = temp[i].total - expectation[static_cast<size_t>(e_size) - 1]; }
			variance[j] += diff * diff;
		}
	}
	for (auto& i : variance)i /= n;std::cout  << left << "ƽ����\t\n";
	for (int i = 0; i < 9; i++)std::cout << subjects[i] << '\t'; std::cout << "�ܷ�\t\n";
	for (auto& i : expectation)std::cout << i<<'\t';
	std::cout << std::endl << left << "����\t\n";
	for (int i = 0; i < 9; i++)std::cout << subjects[i] << '\t'; std::cout << "�ܷ�\t\n";
	std::cout << '\n';
	for (auto& i : variance)std::cout << i<<'\t';std::cout << std::endl;
}
//����ƽ��ֵ�ͷ���;


inline int choiceensure() {
	std::string i = "0"; std::cin >> i;
	while (i != "1" && i != "2" && i != "3") { std::cout << "�������,������\n"; std::cin >> i; }
	return stoi(i);
}
//ȷ��ѡ��
inline bool compareequal(std::string finder, stuwithscore& A) {//�жϵ���stuwithscore�Ƿ���������
	return (A.name == finder || A.id == finder || A.choice == finder || A.choice + A.stuclass == finder);
}
//�жϵ���stuwithscore�Ƿ����������ν��
inline bool ifgreater(const stuwithscore& A,const stuwithscore& B) {//�Ƚ�ѧ������������
	if (A.total != B.total)  return A.total > B.total;
	size_t n = A.score.size();
	for (size_t i = 0; i < n-1; i++) {//�ȱȽ��ܷ֣��ٱȽϸ��Ʒ�����
		if (A.score[i] != B.score[i])  return A.score[i] > B.score[i];
	}return A.score[n-1] > B.score[n-1];
}
//�Ƚ�ѧ������������
inline void changestuscore(stuwithscore& A, bool t) {
	std::cout << "��Ϊ��ѧ�����루���޸ģ�������\n"; A.print(1);
	if (!t) { A.scoreinputB(); }//��ѡ�ư棬
	else { A.scoreinputA(); }//��ѡ�ư棬
	std::cout << "��ѧ���޸ĺ�ĳɼ�Ϊ:\n"; A.print(); system("pause"); system("cls");
}
//�޸�ѧ��������










class studentscore {//���ڴ��Ϳ��ԣ�
private:
	std::unordered_map<int, std::string> grade_map; 
	//std::vector<myhash_map<std::string, stuwithscore>> studatalist;//ѧ����Ϣ�б�
	std::unordered_map<std::string,std::unordered_map<std::string,stuwithscore>> studatalist;
	void getinfofromschool();//��school�������µ��ļ��л�ȡѧ����Ϣ��
	//��school���еĶ�ȡʦ����Ϣ���ƣ�
public:
	studentscore():grade_map({ {1, "��һ"}, {2, "�߶�"}, {3, "����"} }) {
	getinfofromschool(); randomget(); }//���캯������school�������µ��ļ��л�ȡѧ����Ϣ
	void inputscore();//���ݲ�����������ѧ������,��school::changestudent���ƣ�
	void getscorefromdoc();//�Ӻ�ѧ���������ļ��ж�ȡѧ����Ϣ
	void searchandcalculate(); //���ݲ�����������ѧ����Ϣ������ƽ��ֵ�ͷ���
	//���Ҳ�����school::findstudent���ƣ�
	void showallstuscore();//չʾ����ѧ������
	void randomget() {
		
		for (auto& i : studatalist) {
			for (auto& j : i.second) {
				if (j.second.total == 0) {
					for (int k = 0; k < 3; k++) {
						j.second.score[k] = rand() % 150;
					}
					for (int i = 3; i < 6; i++) {
						j.second.score[i] = rand() % 100;
					}
					j.second.calculatetotal();
				}
			}
		}
	}
};


class scoreanalysis :public school,public studentscore{//���ݵ���Ķ��ųɼ������Գɼ����з�����S
	std::unordered_map<std::string, std::vector<stuwithscore>> studatalist;//ͨ����ֵ�Դ�ţ���ѧ�������ģ�ѧ����Ϣ
public:
	 void inputscorefromdoc();//���ļ��ж�ȡ����ѧ�������ģ����ųɼ���������
	 void getanalysis();//��ȡ������������������̨��
};

