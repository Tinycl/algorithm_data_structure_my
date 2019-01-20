#include <iostream>

using namespace std;

void HeapAjust(int* a, int n, int size)
{
	int nChild = 2 * n + 1; //由父节点n找左孩子
	int t;
	while (nChild < size)
	{
		if ((nChild + 1 < size) && (a[nChild + 1] > a[nChild])) //找大孩子
			nChild++;
		if (a[nChild] < a[n]) //孩子比父节点小，说明调整完毕
			break;
		t = a[nChild];
		a[nChild] = a[n];
		a[n] = t;
		n = nChild;
		nChild = 2 * n + 1;
	}
}
void HeapSort(int* a, int size)
{
	int i;
	//从最小的父亲开始调整
	for (i = size / 2 - 1; i >= 0; i--) //初始化堆  孩子找父节点 （k+1）/2 -1  当前孩子节点k=size-1
	{
		HeapAjust(a, i, size);
	}
	int t;
	while (size > 1) {   //n次调整
		t = a[size - 1];
		a[size - 1] = a[0];
		a[0] = t;
		size--;
		HeapAjust(a, 0, size);
	}
}

void HeapSortFrontk(int* a, int size, int k) //前k个大的值
{
	int i;
	for (i = size / 2 - 1; i >= 0; i--) {
		HeapAjust(a, i, size);
	}
	int t;
	int s = size - k;
	while (size > s) {
		t = a[size - 1];
		a[size - 1] = a[0];
		a[0] = t;
		size--;
		HeapAjust(a, 0, size);
	}
}
int main()
{
	int aa[8] = {10,11,3,4,2,20,8,18};
	HeapSort(aa, 8);
	for (int i = 0; i < 8; ++i) {
		cout << aa[i] << endl;
	}
	system("pause");
	return 0;
}