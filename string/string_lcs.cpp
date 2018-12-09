#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
void LCS(const char* str1, const char* str2, string& str)
{
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	const char* s1 = str1 - 1;  //��ַ��1�� s1[0] , ��1��ʼ�� s1[1] = str1[0]
	const char* s2 = str2 - 1;
	vector<vector<int>> chess(size1 + 1, vector<int>(size2 + 1)); //��ά����[size+1][size2+1] [0...size1][0...size2]
	int i = 0, j = 0;
	//��ά�����0�У����0
	for (i = 0; i <= size1; ++i) {
		chess[i][0] = 0;
	}
	//��ά�����0�У����0
	for (j = 0; j <= size2; ++j) {
		chess[0][j] = 0;
	}
	//�����ά��������ֵ
	for (i = 1; i <= size1; ++i) {
		for (j = 1; j <= size2; ++j) {
			if (s1[i] == s2[j]) {
				chess[i][j] = chess[i - 1][j - 1] + 1;
			}
			else {
				chess[i][j] = max(chess[i - 1][j], chess[i][j - 1]);
			}
		}
	}
	//�Ӻ���ǰ�ң����ƻ�ȥ��һ��·������һ�������������
	i = size1; 
	j = size2;
	while (i != 0 && j != 0) {
		if (s1[i] == s2[j]) {  //��lefttop ����
			str.push_back(s1[i]);
			--i;
			--j;
		}
		else {
			if (chess[i - 1][j] > chess[i][j - 1]) { //��left����
				--i;
			}
			else {
				--j;  //��top����
			}
		}
	}
	reverse(str.begin(), str.end());
}

/*
int main()
{
	const char* str1 = "BDCABA";
	const char* str2 = "ABCBDA";
	string str;
	LCS(str1,str2,str);
	cout << str.c_str() << endl;
	system("pause");
	return 0;
}
*/