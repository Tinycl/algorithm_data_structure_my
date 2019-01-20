#include <iostream>

using namespace std;

void QuickSort(int* s, int l, int r)
{
	if (l < r) {
		int  i = l, j = r, x = s[l];  //left right位置，key为s[left]
		while (i < j)
		{
			while (i < j && s[j] >= x) { //从右向左找第一个小于x的元素
				j--;
			}
			if (i < j) {
				s[i++] = s[j];
			}
			while (i < j && s[i] < x) { // 从左向右找第一个大于等于x的元素
				i++;
			}
			if (i < j){
				s[j--] = s[i];
			}
		}
		s[i] = x;
		QuickSort(s, l, i - 1);  //递归调用
		QuickSort(s, i + 1, r);
	}
}

int main()
{
	int a[8] = {40,30,48,2,1,4,6,100};
	QuickSort(a,0,7);
	for (int i = 0; i < 8; ++i) {
		cout << a[i] << endl;
	}
	system("pause");
	return 0;
}