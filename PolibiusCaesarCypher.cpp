#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
const auto sizeCyph (10);
const auto polibius(5);
using namespace std;	
string toSquare(string word); //Сокращение количество знаков сообщения до 25
void formSquare(bool sq[][sizeCyph], const int a, const int b); //Формирование таблицы подлинных символов
void showSquare(bool sq[][sizeCyph]); //Распечатка таблицы
string caesarEncryption(const string word, const int a);
string caesarDecryption(string word, const int key);
void polibiusEncryption(const bool sq[][sizeCyph], const string word, vector <int>& v1, vector <int>& v2, const int a, const int b); //Шифрование сообщения
string polibiusDecryption(const bool sq[][sizeCyph], const vector <int> v1, const vector <int> v2, const int a, const int b);
int findNgram(string word); //Поиcк N-грамм
void bruteforce(bool sq[][sizeCyph], const vector <int> v1, const vector <int> v2); //Алгоритм взлома
int main()
{
	string word = "ABCDHIKMTHEWORDISSHEYZ";
	auto a = 2; // any number 0 <= n <= polibius
	cout << "A = "<< a << " THIS IS 1ST POLIBIUS KEY" << endl;
	auto b = 3; // any number 0 <= n <= polibius
	cout << "B = " << b << " THIS IS 2ND POLIBIUS KEY"<< endl;
	auto c = 5; //any number 0 <= n <= 26
	cout << "C = " << c << " THIS IS CAESAR KEY" << endl;
	word = toSquare(word);
	cout << word << endl;
	word = caesarEncryption(word, c);
	cout << "ENCRYPTED TO CAESAR" << endl << word << endl;
	bool sq[sizeCyph][sizeCyph];
	formSquare(sq, a, b);
	cout << "THIS IS POLIBIUS SQUARE, ALL THAN ISN'T 1 IS NOISE" << endl;
	showSquare(sq);
	vector <int> v1 = {};
	vector <int> v2 = {};
	polibiusEncryption(sq, word, v1, v2, a, b);
	cout << "ENCRYPTED TO CAESAR & POLIBIUS " << endl;
	for (auto el : v1)
		cout << el << " ";
	cout << endl;
	for (auto el : v2)
		cout << el << " ";;
	cout << endl<< "DECRYPTED FROM POLIBIUS" << endl;
	cout << polibiusDecryption(sq, v1, v2, a, b) << endl;
	cout << "DECRYPTED FROM POLIBIUS & CAESAR" << endl;
	cout << caesarDecryption(polibiusDecryption(sq, v1, v2, a, b), c) << endl;
	cout << endl;
	bruteforce(sq, v1, v2);
	return 0;
}
void formSquare(bool sq[][sizeCyph], const int a, const int b)
{
	for (auto i = 0; i < sizeCyph; i++) {
		for (auto j = 0; j < sizeCyph; j++) {
			sq[i][j] = false;
		}
	}

	for (auto i = a; i < a + polibius; i++) {
		for (auto j = b; j < b + polibius; j++) {
			sq[i][j] = true;
		}
	}
}
void showSquare(bool sq[][sizeCyph])
{
	for (auto i = 0; i < sizeCyph; i++) {
		for (auto j = 0; j < sizeCyph; j++) {
			cout << sq[i][j] << " ";
		}
		cout << endl;
	}
}
string toSquare(string word)
{ //Сокращение количество знаков сообщения до 25
	string alp = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string al = "JI";
	for (auto i = 0; i < word.size(); i++) {
		if (word[i] == al[0])
			word[i] = al[1];
	}
	return word;
}
string caesarEncryption(string word, const int key)
{
	string alp = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string result = "";
	for (auto i = 0; i < word.size(); i++)
		for (auto j = 0; j < alp.size(); j++)
			if (word[i] == alp[j])
				result+=alp[(j+key)%alp.size()];
	return result;
}
string caesarDecryption(string word, const int key)
{
	string alp = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string result = "";
	for (auto i = 0; i < word.size(); i++)
		for (auto j = 0; j < alp.size(); j++)
			if (word[i] == alp[j])
				result += alp[(alp.size() + (j - key)) % alp.size()];
	return result;
}
void polibiusEncryption(const bool sq[][sizeCyph], const string word, vector <int>& v1, vector <int>& v2, const int a, const int b)
{
	string alp = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	vector <int> wordnum = {};
	for (auto i = 0; i < word.size(); i++)
		for (auto j = 0; j < alp.size(); j++)
			if (word[i] == alp[j])
				wordnum.push_back(j); //Преобразуем исходную строку в вектор чисел по номерам букв*/
	auto c = 0; //Счетчик добавленных символов
	while (c < wordnum.size()) {
		auto tmp0 = rand() % sizeCyph;
		auto tmp1 = rand() % sizeCyph;
		if (sq[tmp0][tmp1]) { //Кодируем подлинные знаки в квадрат Полибия
			v1.push_back((wordnum[c] / polibius) + a); //Строка
			v2.push_back((wordnum[c] % polibius) + b); //Столбец
			c++;
		}
		else { //Иначе шум
			v1.push_back(tmp0); //Строка
			v2.push_back(tmp1); //Столбец
		}
	}
}
string polibiusDecryption(const bool sq[][sizeCyph], const vector <int> v1, const vector <int> v2, const int a, const int b)
{
	string alpModified = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	string result = "";
	for (int i = 0; i < v1.size(); i++) {
		if (sq[v1[i]][v2[i]]) {
			//cout << (v1[i] - a) * polibius + (v2[i] - b) << endl;
			result += alpModified[(v1[i] - a) * polibius + (v2[i] - b)];
		}
	}
	return result;
}
int findNgram(string word)
{
	int result = 0;
	string ngrams[] = { "THE", "HIS", "ITI", "HER", "SHE", "YOU", "THI", "WOR", "TES" };
	for (auto i : ngrams) {
		auto tmp = word.find(i);
		if (tmp<word.size()) { //В противном случае выведется максимальное значение
			result++;
		}
	}
	return result;
}
void bruteforce(bool sq[][sizeCyph], const vector <int> v1, const vector <int> v2)
{
	vector <int> result = {};
	int c = 0;
	for (auto key0=0;key0<(sizeCyph-polibius); key0++) //Не выйти за рамки
		for (auto key1=0; key1 <(sizeCyph - polibius); key1++) //Не выйти за рамки
			for (auto key2=0; key2 < (pow(polibius,2)); key2++) {
				formSquare(sq, key0, key1);
				//cout << "KEY0 " << key0 << " KEY1 " << key1 << endl;
				string pd = polibiusDecryption(sq, v1, v2, key0, key1);
				string cd = caesarDecryption(pd, key2);
				if (findNgram(cd) > c) {
					c = findNgram(cd);
					result = { key0,key1,key2 };
				}
			}
	cout<< endl;
	if (c) {
		cout << "BRUTEFORCED, KEY0, KEY1 AND KEY 2 IS " << endl;
		for (auto el : result)
			cout << el << endl;
	}
	else {
		cout<< "BRUTEFORCE FAILED"<<endl;
	}
}

;