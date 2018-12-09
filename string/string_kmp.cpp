#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int BruteForceSearth(const char *s, const char *p)
{
	int i = 0;  //text ����
	int j = 0;  //pattern ����
	int lenp = strlen(p);
	int last = strlen(s) - strlen(p);
	while (i <= last && j < lenp) {
		if (s[i + j] == p[j]) {  //��ƥ�䣬pattern ��������
			++j;
		}
		else {  //����ƥ�䣬pattern�������´�0��ʼ��text ��������
			++i;
			j = 0;
		}
	}
	if (j == lenp) {  //�˳�ѭ����ԭ�����ҵ�
		return i;
	}
	return -1;
}

void KMPPatternGetNext(const char *p, int next[]) 
{
	int len = strlen(p);
	next[0] = -1;
	int k = -1;
	int j = 0;
	while (j < len - 1) {
		//p[k]��ʾǰ׺��p[j]��ʾ��׺
		//k==-1 ��ʾδ�ҵ�kǰ׺��k��׺��ȣ��״η������Ⱥ���
		if (k == -1 || p[j] == p[k]) {
			++j;
			++k;
			next[j] = k;
		}
		else{   //p[j]��p[k]ʧ�䣬������ݹ����ǰ׺p[next[k]]
			k = next[k];
		}
	}
}

int KMP(const char *s, const char *p)
{
	int i = 0; //����λ��
	int j = 0; //ģʽ��λ��
	int *next = new int[strlen(p)];
	KMPPatternGetNext(p,next);
	int size = strlen(p);
	while (i < (int)strlen(s) && (j < size)) {  //bug &&strlen(j < strlen(p))
		cout << strlen(p) << endl;
		if (j == -1 || (s[i] == p[j] && j != -1)) {  //��jΪ-1ʱ��Ҫ�ƶ�i, j��Ϊ0
			++i;
			++j;
		}
		else {
			//i����Ҫ����
			j = next[j]; //j���ݵ�ָ��λ��
		}

		if (j == strlen(p)) {
			return i - j;
		}
	}
	return -1;
}
/*
int main()
{

	const char *s = "cabcabcdefgasv";
	const char *p = "ab";
	cout << BruteForceSearth(s, p)<<endl;
	cout << KMP(s, p) << endl;
	system("pause");
	return 0;
}
*/