#include <iostream>
#include <algorithm>
using namespace std;
int MinSubarray(const int *array, int size)
{
	int *sum = new int[size + 1];
	sum[0] = 0;   //sum[1] ��array[0] �ĺ�
	int i;
	for (i = 0; i < size; i++) {
		sum[i + 1] = sum[i] + array[i]; 
	}
	sort(sum,sum+size+1); //��sum ����������
	int difference = abs(sum[1] - sum[0]); //��ʼ��
	int result = difference;
	for (i = 1; i < size; ++i) {
		difference = abs(sum[i + 1] - sum[i]);
		result = min(difference, result);
	}
	delete[] sum;
	return result;
}
/*
int main()
{
	int array[] = { 1,-2,3,10,-4,7,2,-5 };
	cout << MinSubarray(array, sizeof(array) / sizeof(int)) <<endl;
	system("pause");
	return 0;
}
*/