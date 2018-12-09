#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int BruteForceSearth(const char *s, const char *p)
{
	int i = 0;  //text 索引
	int j = 0;  //pattern 索引
	int lenp = strlen(p);
	int last = strlen(s) - strlen(p);
	while (i <= last && j < lenp) {
		if (s[i + j] == p[j]) {  //若匹配，pattern 索引后移
			++j;
		}
		else {  //若不匹配，pattern索引重新从0开始，text 索引后移
			++i;
			j = 0;
		}
	}
	if (j == lenp) {  //退出循环的原因是找到
		return i;
	}
	return -1;
}

void KMPPatternGetNext(const char *p, int next[]) 
{
	int len = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < len - 1) {
		//p[k]表示前缀，p[j]表示后缀
		//k==-1 表示未找到k前缀与k后缀相等，首次分析可先忽略
		if (k == -1 || p[j] == p[k]) {
			++j;
			++k;
			next[j] = k;
		}
		else{   //p[j]与p[k]失配，则继续递归计算前缀p[next[k]]
			k = next[k];
		}
	}
}

int KMP(const char *s, const char *p)
{
	int i = 0; //主串位置
	int j = 0; //模式串位置
	int *next = new int[strlen(p)];
	KMPPatternGetNext(p,next);
	int size = strlen(p);
	while (i < (int)strlen(s) && (j < size)) {  //bug &&strlen(j < strlen(p))
		cout << strlen(p) << endl;
		if (j == -1 || (s[i] == p[j] && j != -1)) {  //当j为-1时，要移动i, j搞为0
			++i;
			++j;
		}
		else {
			//i不需要回溯
			j = next[j]; //j回溯到指定位置
		}

		if (j == strlen(p)) {
			return i - j;
		}
	}
	return -1;
}
/*
int main()
{

	const char *s = "cabcabcdefgasv";
	const char *p = "ab";
	cout << BruteForceSearth(s, p)<<endl;
	cout << KMP(s, p) << endl;
	system("pause");
	return 0;
}
*/