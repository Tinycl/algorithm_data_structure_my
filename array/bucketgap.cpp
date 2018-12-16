#include <iostream>

using namespace std;

typedef struct tagSBucket
{
	bool bValid;
	int min;
	int max;
	tagSBucket() :bValid(false) {};
	void Add(int n) //����n���뵽Ͱ��
	{
		if (!bValid) {  //Ͱ��һ�μ�������
			min = max = n;
			bValid = true;
		}
		else {
			if (max < n) {
				max = n;
			}
			else if (min > n) {
				min = n;
			}
		}
	}
}SBucket;

int CalMaxGap(const int *array, int size)
{
	SBucket *pBucket = new SBucket[size];
	int max = array[0];
	int min = array[0];
	int i;
	for (i = 1; i < size; ++i) {
		if (max < array[i]) {
			max = array[i];
		}
		else if (min > array[i]) {
			min = array[i];
		}
	}
	//һ�η���Ͱ��
	int delta = max -  min;
	int nBucket;
	for (i = 0; i < size; ++i) {
		nBucket = (array[i] - min) * size / delta;
		if (nBucket >= size) {
			nBucket = size - 1;
		}
		pBucket[nBucket].Add(array[i]);
	}
	//������ЧͰ�ļ��
	i = 0;
	int ngap = delta / size;  //��ʼ���
	int gap;
	for (int j = 1; j < size; ++j) {  //Ͱ����������Ч����һ��Ͱ����Сֵ��ȥǰһ��Ͱ�����ֵ
		if (pBucket[j].bValid) {    //Ͱ0 ��Ͱsize-1 һ����Ч ����Сֵ�����ֵ��
			gap = pBucket[j].min - pBucket[i].max;
			if (ngap < gap) {
				ngap = gap;
			}
			i = j;
		}
	}
	return ngap;
}

int main()
{	
	int array[] = {1,7,14,9,4,13};
	cout << CalMaxGap(array, sizeof(array) / sizeof(int)) << endl;
	system("pause");
	return 0;
}