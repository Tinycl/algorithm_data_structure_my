#include <iostream>
#include <algorithm>
using namespace std;

//递归
void swap(char *a, char *b)
{
	char temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
bool isSwap(char *pstr, int begin, int end)
{
	for (int i = begin; i < end; ++i) {
		if (pstr[i] == pstr[end])
			return false;
	}
	return true;
}
void Permutation(char *pstr, int begin, int end)
{
	if (begin == end)
	{
		//最后一位索引
		cout << pstr << endl;
	}
	else
	{
		for (int i = begin; i <= end; ++i) {
			//确定第几位，交换
			swap(&pstr[begin], &pstr[i]);
			//对第几位之后的全部排列
			Permutation(pstr, begin + 1, end);
			//恢复字符串，交换
			swap(&pstr[begin], &pstr[i]);
		}

	}
}
void Permutation1(char *pstr, int begin, int end)
{
	if (begin == end)
	{
		//最后一位索引
		cout << pstr << endl;
	}
	else
	{
		for (int i = begin; i <= end; ++i) {
			if (isSwap(pstr, begin, i)) {
				//确定第几位，交换
				swap(&pstr[begin], &pstr[i]);
				//对第几位之后的全部排列
				Permutation1(pstr, begin + 1, end);
				//恢复字符串，交换
				swap(&pstr[begin], &pstr[i]);
			}
		}
	}
}

//非递归
void Reverse(int *from, int* to)
{
	int t;
	while (from < to) {
		t = *from;
		*from = *to;
		*to = t;
		++from;
		--to;
	}
}
bool GetNextPermutatio(int *array, int size)
{
	int i = size - 2;
	while (i >= 0 && array[i] >= array[i + 1]) {
		--i;
	}
	if (i < 0) {
		return false;
	}

	int j = size - 1;
	while (array[j] <= array[i]) {
		--j;
	}

	swap(array[j], array[i]);
	Reverse(array + i + 1, array + size - 1);
	return true;
}
int main()
{
	int array[] = { 1,2,2,3 };
	int size = sizeof(array) / sizeof(int);
	while (GetNextPermutatio(array, size)) {
		cout << array[0]<<array[1]<<array[2]<<array[3] << endl;
	}
	system("pause");
	return 0;
}