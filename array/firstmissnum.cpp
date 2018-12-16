#include <iostream>
#include <algorithm>
using namespace std;

int FirstMissNumber(int *array, int size)
{
	array--; //数组从索引1开始
	int  i = 1;
	while (i <= size) {
		if (array[i] == i) {
			++i; //array[i] == i
		}
		else if(array[i] > size || array[i] < i || array[array[i]] == array[i]) {
			array[i] = array[size]; //丢弃array[i]， 将array[last]复制给array[i],array长度减1
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