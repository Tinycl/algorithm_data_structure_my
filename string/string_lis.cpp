#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int LIS(const int *p, int length, int *pre, int& nindex)
{
	int *longest = new int[length];
	int i, j;
	for (i = 0; i < length; ++i) {
		longest[i] = 1;
		pre[i] = -1;
	}
	int nlist = 1;
	nindex = 0;
	for (i = 1; i < length; ++i) {
		for (j = 0; j < i; ++j) {
			if (p[j] <= p[i]) {
				if (longest[i] < longest[j] + 1) {
					longest[i] = longest[j] + 1;
					pre[i] = j;
				}
			}
		}
		if (nlist < longest[i]) {
			nlist = longest[i];
			nindex = i;
		}
	}
	delete[] longest;
	return nlist;
}

void GetLIS(const int *array, const int *pre, int nindex, vector<int>& lis)
{
	while (nindex >= 0) {
		lis.push_back(array[nindex]);
		nindex = pre[nindex];
	}
	reverse(lis.begin(),lis.end());
}
/*
int main()
{
	int array[] = { 1,4,5,6,2,3,8,9,10,11,12,12,1 };
	int  size = sizeof(array) / sizeof(int);
	int *pre = new int[size];
	int nindex;
	int max = LIS(array, size, pre, nindex);
	vector<int> lis;
	GetLIS(array, pre, nindex, lis);
	delete[] pre;
	cout << max << endl;
	for (int k = 0; k < lis.size(); ++k)
		cout << lis[k] << " ";
	cout << endl;
	system("pause");
	return 0;
}
*/