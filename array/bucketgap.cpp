#include <iostream>

using namespace std;

typedef struct tagSBucket
{
	bool bValid;
	int min;
	int max;
	tagSBucket() :bValid(false) {};
	void Add(int n) //将数n加入到桶中
	{
		if (!bValid) {  //桶第一次加入数据
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
	//一次放入桶中
	int delta = max -  min;
	int nBucket;
	for (i = 0; i < size; ++i) {
		nBucket = (array[i] - min) * size / delta;
		if (nBucket >= size) {
			nBucket = size - 1;
		}
		pBucket[nBucket].Add(array[i]);
	}
	//计算有效桶的间隔
	i = 0;
	int ngap = delta / size;  //初始间隔
	int gap;
	for (int j = 1; j < size; ++j) {  //桶里有数据有效，后一个桶的最小值减去前一个桶的最大值
		if (pBucket[j].bValid) {    //桶0 和桶size-1 一定有效 （最小值和最大值）
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