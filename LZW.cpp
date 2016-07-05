#include <iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;

map<string, int> myDictionary;
map<int, string> inv_myDictionary;

vector<string> dic;

void LzwEncode(vector<int> &code, string str)
{
	int idx = 1;
	for (auto i : str)
	{
		string ss(1, i);
		if (myDictionary.find(ss) == myDictionary.end())
			myDictionary.insert({ ss, idx++ });
	}
	int i = 1;
	string pos(1, str[0]);
	int len = str.length();
	while (i<=len)
	{
		char L = str[i++];
		string compareStr(pos);
		if (L!='\0')
			compareStr.push_back(L);
		if (myDictionary.find(compareStr) == myDictionary.end())
		{
			myDictionary.insert({ compareStr, idx++ });
			compareStr.erase(compareStr.end() - 1);
			pair<string, int> mypair = *(myDictionary.find(compareStr));
			code.push_back(mypair.second);
			pos.clear();
			pos.push_back(L);
		}
		else if (L != '\0')
		{
			pos.push_back(L);
		}
		else
		{
			pair<string, int> mypair = *(myDictionary.find(compareStr));
			code.push_back(mypair.second);
		}
	}
}

void LzwDecode(vector<int> code, string &line)
{
	for (auto it : code)
		line += inv_myDictionary[it];
}

int main(int argc, char **argv)
{
	//string line("ababcbababaaaaaaa");
	string line = argv[1];
	vector<int> code;
	cout << "\nEncode: \n" << line << endl;

	LzwEncode(code, line);
	for (auto c:code)
		std::cout << c << std::endl;

	for (auto iter : myDictionary)
		inv_myDictionary[iter.second] = iter.first;
	cout << "\nDictionary: " << endl;
	for (auto iter : inv_myDictionary)
		std::cout << iter.first << '\t' << iter.second << std::endl;

	/*decode*/
	string line_decode;
	LzwDecode(code,line_decode);
	cout << "\nDecode: " << endl;
	cout << line_decode << endl;
	return 0;
}
