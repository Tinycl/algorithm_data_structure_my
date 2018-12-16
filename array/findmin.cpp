#include <iostream>

using namespace std;

int FindMin(int *array, int size)
{
	int low = 0;
	int high = size - 1;
	int mid;
	while (low < high) {
		mid = (low + high) / 2;
		if (array[mid] > array[mid + 1]) {
			low = mid + 1;  //��Сֵ���Ұ벿��
		}
		else
		{
			high = mid;  //��Сֵ����벿��
		}
	}
	return array[high];
}
/*
int main()
{
	int array[] = { 4,5,6,7,0,1,2 };
	cout << FindMin(array, sizeof(array) / sizeof(int))<<endl;
	system("pause");
	return 0;
}
*/