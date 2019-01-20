#include <iostream>

using namespace std;

void QuickSort(int* s, int l, int r)
{
	if (l < r) {
		int  i = l, j = r, x = s[l];  //left rightλ�ã�keyΪs[left]
		while (i < j)
		{
			while (i < j && s[j] >= x) { //���������ҵ�һ��С��x��Ԫ��
				j--;
			}
			if (i < j) {
				s[i++] = s[j];
			}
			while (i < j && s[i] < x) { // ���������ҵ�һ�����ڵ���x��Ԫ��
				i++;
			}
			if (i < j){
				s[j--] = s[i];
			}
		}
		s[i] = x;
		QuickSort(s, l, i - 1);  //�ݹ����
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