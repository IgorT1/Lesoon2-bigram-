#include<iostream>
#include<string>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <regex>
using namespace std;


void SymbolFrequencies(string& str) { //частоти символів 
	unordered_map<char, int> freq;//контейнер для елементів 
	for (const char& c : str) {

		freq[c]++;// добавляемо елементи до контецнеру 
	}
	vector<pair<char, int>> vec(freq.begin(), freq.end());//создаем вектор который хранит ключ и значение 
	sort(vec.begin(), vec.end(), [](const pair<char, int>& a, const pair<char, int>& b) {//для удобства сортируем по убиванию //GITH
		return a.second > b.second;
		});
	for (auto& pair : vec)
		cout << '{' << pair.first << ": " << pair.second << '}' << endl; //
	cout << endl;
}
 


void bigramsWithoutIntersection(string& str) { //, біграми з перетином
	unordered_map<string, int> bigram_counts;

	for (int i = 0; i < str.length() - 1; i++) {//перебира рядок ,рахуе біграми
		string bigram = str.substr(i, 2); // бере поточну біграму 
		bigram_counts[bigram]++; //кількість біграм 
	}

	vector<pair<string, int>> vec(bigram_counts.begin(), bigram_counts.end());//создаем вектор который хранит ключ и значение 
	sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {//для удобства сортируем по убиванию //GITH
		return a.second > b.second;
		});

	// вивод 
	for (auto& pair : vec) {
		cout << '{' << pair.first << ": " << pair.second << '}' << endl;
	}
	cout << endl;
}


void bigramsIntersection(string& str) {//, біграми  перетином
	unordered_map<string, int> bigram_counts;

	for (int i = 0; i < str.length() - 1; i++) {//перебира рядок ,рахуе біграми

		string bigram = str.substr(i++, 2); // бере біграму парну
		bigram_counts[bigram]++; //кількість біграм 
	}
	vector<pair<string, int>> vec(bigram_counts.begin(), bigram_counts.end());//создаем вектор который хранит ключ и значение 
	sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {//для удобства сортируем по убиванию //GITH
		return a.second > b.second;
		});
	// вивод 
	for (auto& pair : vec) {
		cout << '{' << pair.first << ": " << pair.second << '}' << endl;
	}
	cout << endl;
}


string filterWithoutSpace(string& text, string& ABC) { //метод фильтрации текста без пробелов 

	string filterText = "";
	for (char c : text)
	{
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filterText += v;

		}
		else if (isspace(v)) {
			continue; //пропускаем пробелы 
		}
	}

	return filterText;
}

string filterSpace(string& text, string& ABC) {
	string filteredText = "";

	regex pattern("\\s+");//для нахождения последовательности пробелов 
	string result = regex_replace(text, pattern, " ");  // заміна на один пробіл

	for (char& c : result) {
		char v = tolower(c);


		if (ABC.find(v) != string::npos)  //проверяет, является ли данный символ алфавитом или нет
		{
			filteredText += v;

		}
		else if (isspace(v)) {
			filteredText += ' '; //+ пробелы 
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
	SymbolFrequencies(str);//метод для нахождения совпадания одинаковых букв 
	bigramsWithoutIntersection(str);//медод для  біграми без перетину
	bigramsIntersection(str);//медод для  біграми з перетином
}

string Text() {
	//string str1 = " Карл у Клары Украл корали ,Карла у Карлы украла кларнет  ";
	string path = "..\\file.txt";
	ifstream fin;
	fin.open(path);
	string res = "";
	if (!fin.is_open()) {
		cout << "Ошибка вывода файла " << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		//char ch;
		//fin.get(ch) выводит данные по символьно 

		string str;
		while (!fin.eof()) // отлвливает конец вайла 
		{
			str = ""; //для корректного счетия	
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

	string ABC = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	string withoutSpace = filterWithoutSpace(res, ABC); //без них

	string withSpace = filterSpace(res, ABC);//  с пробелами

	//подставить значени (с пробелами или нет )

	cout << "Таблици без пробелов " << endl;
	Method(withoutSpace); 
	cout << "Таблици c пробелами " << endl;
	Method(withSpace);
}


int main() {
	setlocale(LC_ALL, "RU");

	Log();

	return 0;
}