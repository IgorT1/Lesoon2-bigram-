#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <regex>
using namespace std;


void SymbolFrequencies(string& str) { //������� ������� 
	unordered_map<char, int> freq;//��������� ��� �������� 
	for (const char& c : str) {

		freq[c]++;// ���������� �������� �� ���������� 
	}
	vector<pair<char, int>> vec(freq.begin(), freq.end());//������� ������ ������� ������ ���� � �������� 
	sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {//��� �������� ��������� �� �������� //GITH
		return a.second > b.second;
		});
	for (auto& pair : vec)
		cout << '{' << pair.first << ": " << pair.second << '}' << endl; //
	cout << endl;
}
 


void bigramsWithoutIntersection(string& str) { //, ������ � ���������
	unordered_map<string, int> bigram_counts;

	for (int i = 0; i < str.length() - 1; i++) {//�������� ����� ,����� ������
		string bigram = str.substr(i, 2); // ���� ������� ������ 
		bigram_counts[bigram]++; //������� ����� 
	}

	vector<pair<string, int>> vec(bigram_counts.begin(), bigram_counts.end());//������� ������ ������� ������ ���� � �������� 
	sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {//��� �������� ��������� �� �������� //GITH
		return a.second > b.second;
		});

	// ����� 
	for (auto& pair : vec) {
		cout << '{' << pair.first << ": " << pair.second << '}' << endl;
	}
	cout << endl;
}


void bigramsIntersection(string& str) {//, ������  ���������
	unordered_map<string, int> bigram_counts;

	for (int i = 0; i < str.length() - 1; i++) {//�������� ����� ,����� ������

		string bigram = str.substr(i++, 2); // ���� ������ �����
		bigram_counts[bigram]++; //������� ����� 
	}
	vector<pair<string, int>> vec(bigram_counts.begin(), bigram_counts.end());//������� ������ ������� ������ ���� � �������� 
	sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {//��� �������� ��������� �� �������� //GITH
		return a.second > b.second;
		});
	// ����� 
	for (auto& pair : vec) {
		cout << '{' << pair.first << ": " << pair.second << '}' << endl;
	}
	cout << endl;
}


string filterWithoutSpace(string& text, string& ABC) { //����� ���������� ������ ��� �������� 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filterText += v;

		}
		else if (isspace(v)) {
			continue; //���������� ������� 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//��� ���������� ������������������ �������� 
	string result = regex_replace(text, pattern, " ");  // ����� �� ���� �����

	for (char& c : result) {
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //���������, �������� �� ������ ������ ��������� ��� ���
		{
			filteredText += v;

		}
		else if (isspace(v)) {
			filteredText += ' '; //+ ������� 
		}
	}
	if (filteredText.back() == ' ') {
		filteredText.pop_back();
	}
	if (filteredText.front() == ' ') {
		filteredText.erase(0, 1);
	}
	return filteredText;
}



void Method(string& str) {
	SymbolFrequencies(str);//����� ��� ���������� ���������� ���������� ���� 
	bigramsWithoutIntersection(str);//����� ���  ������ ��� ��������
	bigramsIntersection(str);//����� ���  ������ � ���������
}

string Text() {
	//string str1 = " ���� � ����� ����� ������ ,����� � ����� ������ �������  ";
	string path = "..\\file.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "������ ������ ����� " << endl;
	}
	else
	{
		cout << "���� ������" << endl;
		//char ch;
		//fin.get(ch) ������� ������ �� ��������� 

		string str;
		while (!fin.eof()) // ���������� ����� ����� 
		{
			str = ""; //��� ����������� ������	
			getline(fin, str);
			res += str;
		}
	}

	//cout << res << endl;

	fin.close();

	return res;
}

void Log() {
	string res = Text();

	string ABC = "��������������������������������";
	string withoutSpace = filterWithoutSpace(res, ABC); //��� ���

	string withSpace = filterSpace(res, ABC);//  � ���������

	//���������� ������� (� ��������� ��� ��� )

	cout << "������� ��� �������� " << endl;
	Method(withoutSpace); 
	cout << "������� c ��������� " << endl;
	Method(withSpace);
}


int main() {
	setlocale(LC_ALL, "RU");

	Log();

	return 0;
}