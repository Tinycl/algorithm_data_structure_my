#include <iostream>
#include <algorithm>
using namespace std;

int MaxSubarray(const int *array, int size)
{
	if (!array || size < 0) return 0;
	int sum = array[0];
	int result = sum;
	for (int i = 1; i < size; ++i) {
		if (sum > 0) {
			sum = sum + array[i];
		}
		else{
			sum = array[i];
		}
		result = max(sum,result);
	}
	return result;
}

int MaxSubarray1(const int *array, int size, int& from, int& to)
{
	if (!array || size < 0) {
		from = -1;
		to = -1;
		return 0;
	}
	from = 0;
	to = 0;
	int sum = array[0];
	int result = sum;
	int fromNew; //新数组起点
	for (int i = 1; i < size; ++i) {
		if (sum > 0) {
			sum = sum + array[i];
		}
		else {
			sum = array[i];
			fromNew = i;
		}
		if (result < sum) {
			result = sum;
			from = fromNew;
			to = i;
		}
	}
	return result;
}
/*
int main()
{
	int array[] = {1,-2,3,10,-4,7,2,-5};
	cout << MaxSubarray(array, sizeof(array) / sizeof(int))<<endl;
	int from;
	int to;
	cout << MaxSubarray1(array, sizeof(array) / sizeof(int),from, to) << endl;
	system("pause");
	return 0;
}
*/