#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
void LCS(const char* str1, const char* str2, string& str)
{
	int size1 = strlen(str1);
	int size2 = strlen(str2);
	const char* s1 = str1 - 1;  //地址减1， s1[0] , 从1开始数 s1[1] = str1[0]
	const char* s2 = str2 - 1;
	vector<vector<int>> chess(size1 + 1, vector<int>(size2 + 1)); //二维数组[size+1][size2+1] [0...size1][0...size2]
	int i = 0, j = 0;
	//二维数组第0行，搞成0
	for (i = 0; i <= size1; ++i) {
		chess[i][0] = 0;
	}
	//二维数组第0列，搞成0
	for (j = 0; j <= size2; ++j) {
		chess[0][j] = 0;
	}
	//计算二维数组其它值
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
	//从后往前找，逆推回去，一条路径代表一个最长公共子序列
	i = size1; 
	j = size2;
	while (i != 0 && j != 0) {
		if (s1[i] == s2[j]) {  //从lefttop 来的
			str.push_back(s1[i]);
			--i;
			--j;
		}
		else {
			if (chess[i - 1][j] > chess[i][j - 1]) { //从left来的
				--i;
			}
			else {
				--j;  //从top来的
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