#include <iostream>

using namespace std;

void HeapAjust(int* a, int n, int size)
{
	int nChild = 2 * n + 1; //�ɸ��ڵ�n������
	int t;
	while (nChild < size)
	{
		if ((nChild + 1 < size) && (a[nChild + 1] > a[nChild])) //�Ҵ���
			nChild++;
		if (a[nChild] < a[n]) //���ӱȸ��ڵ�С��˵���������
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
	//����С�ĸ��׿�ʼ����
	for (i = size / 2 - 1; i >= 0; i--) //��ʼ����  �����Ҹ��ڵ� ��k+1��/2 -1  ��ǰ���ӽڵ�k=size-1
	{
		HeapAjust(a, i, size);
	}
	int t;
	while (size > 1) {   //n�ε���
		t = a[size - 1];
		a[size - 1] = a[0];
		a[0] = t;
		size--;
		HeapAjust(a, 0, size);
	}
}

void HeapSortFrontk(int* a, int size, int k) //ǰk�����ֵ
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