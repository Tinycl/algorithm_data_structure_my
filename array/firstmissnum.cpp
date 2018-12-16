#include <iostream>
#include <algorithm>
using namespace std;

int FirstMissNumber(int *array, int size)
{
	array--; //���������1��ʼ
	int  i = 1;
	while (i <= size) {
		if (array[i] == i) {
			++i; //array[i] == i
		}
		else if(array[i] > size || array[i] < i || array[array[i]] == array[i]) {
			array[i] = array[size]; //����array[i]�� ��array[last]���Ƹ�array[i],array���ȼ�1
			--size;
		}
		else
		{
			//array[i] > i
			swap(array[i], array[array[i]]);
		}
	}
	return i;
}
/*
int main()
{
	int a[] = { 1,2,3,4,5,8,9,10 };
	cout<< FirstMissNumber(a,sizeof(a)/sizeof(int)) <<endl;
	int *p = new int[10];
	cout << sizeof(a) << endl;
	system("pause");
	return 0;
}
*/