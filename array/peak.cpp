#include <iostream>
#include <vector>

using namespace std;
//默认边界 大于A[-1] 和A[N]
int LocalMaximum(const int *array, int size)
{
	int left = 0;
	int right = size - 1;
	int mid = 0;
	while (left < right)
	{
		mid = (left + right) / 2;
		if (array[mid] > array[mid + 1]) {
			right = mid;
		}
		else
		{
			left = mid + 1;
		}
	}
	return array[left];
}
/*
int main()
{
	const int array[] = {0,1,2,3,4,5,6,71,4,3,2};
	cout << LocalMaximum(array, 11)<<endl;
	system("pause");
	return 0;
}
*/