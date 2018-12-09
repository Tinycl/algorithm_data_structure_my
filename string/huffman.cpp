#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef struct {
	int nweight;
	int nparent;
	int nleft;
	int nright;
}HuffmanNode;
//�����ַ��ĳ��ֵ�Ƶ����Ȩֵ
void CalcFrequency(const char *str, int *pweight)
{
	while (*str) {
		pweight[*str]++;
		str++;
	}

}
//��ȡ���ֵ��ַ��������ֵ��ַ���Ȩֵ������������´�0��ʼ��
void CalcExistChar(int *pweight, int N, vector<int>& pchar)
{
	int j = 0;
	for (int i = 0; i < N; ++i) {
		if (pweight[i] != 0) {
			pchar.push_back(i);
			if (j != i) {
				pweight[j] = pweight[i];
			}
			++j;
		}
	}
}

//ѡ����С���������ڵ���Ϊ0�Ľڵ㣬���һ���½ڵ�
//֮ǰѡ����Ľڵ㣬��ɸ��ڵ���������ڵ㸸��Ϊ0��
void SelectNode(const HuffmanNode *pHuffmanTree, int n, int& s1, int& s2)
{
	//�ҵ���һ�����ڵ���Ϊ0�Ľڵ�
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nleft == 0) {
			s1 = i;
			break;
		}
	}
	//�ҵ���С�ĸ��ڵ���Ϊ0�Ľڵ�
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nparent == 0 && pHuffmanTree[i].nweight < pHuffmanTree[s1].nweight) {
			s1 = i;
		}
	}
	//�ҵ���һ�����ڵ���Ϊ0�Ľڵ� �Ҳ���s1
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nparent == 0 && i != s1) {
			s2 = i;
			break;
		}
	}
	//�ҵ��ڶ�С�ĸ��ڵ���Ϊ0�Ľڵ�
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nparent == 0 && pHuffmanTree[i].nweight < pHuffmanTree[s2].nweight && i != s1) {
			s2 = i;
		}
	}
	
}
void HuffmanEncoding(HuffmanNode *pHuffmanTree, int *pweight, int N, vector<vector<char>>& code)
{
	if (N <= 0)
		return;
	int m = 2 * N - 1;//N���ڵ��huffman����Ҫ2N-1���ڵ�
	//pHuffmanTree = new HuffmanNode[m];
	//memset(pHuffmanTree,0,sizeof(HuffmanNode)*m);
	int s1, s2;
	int i;
	//����Ҷ�ӽڵ�,����Ҫ������ַ�
	for (i = 0; i < N; ++i) {
		pHuffmanTree[i].nweight = pweight[i];
		pHuffmanTree[i].nparent = 0;
		pHuffmanTree[i].nright = 0;
		pHuffmanTree[i].nleft = 0;
	}
	//ÿ��ѡ��Ȩֵ��С������˫����Ϊ0�������ڵ㣬��Ҫ����Ҷ�ӽڵ�������ɵĽڵ㣩���������½ڵ��ȨֵΪ�����ӽڵ�Ȩֵ֮��
	for (i = N; i < m; ++i) {
		SelectNode(pHuffmanTree, i, s1, s2);
		pHuffmanTree[s1].nparent = i;
		pHuffmanTree[s2].nparent = i;
		pHuffmanTree[i].nleft = s1;
		pHuffmanTree[i].nright = s2;
		pHuffmanTree[i].nweight = pHuffmanTree[s1].nweight + pHuffmanTree[s2].nweight;//�½ڵ��Ȩֵ
	}
	//���ݽ��õ�huffman������Ҷ�ӵ������������õ�ÿ��Ҷ�ӽڵ�ı��롣 �ٷ�ת��
	int node, nparent;
	for (i = 0; i < N; ++i) {
		vector<char>& cur = code[i];
		node = i;
		nparent = pHuffmanTree[node].nparent;
		while (nparent != 0) {  //Ҷ�ڵ����ϱ���
			if (pHuffmanTree[nparent].nleft == node) {
				cur.push_back('0');
			}
			if (pHuffmanTree[nparent].nright == node) {
				cur.push_back('1');
			}
			node = nparent;
			nparent = pHuffmanTree[node].nparent;
		}
		reverse(cur.begin(), cur.end()); //��תһ��
	}
}
void PrintHuffmanEnCode(vector<vector<char>>& code, vector<int>& pchar)
{
	for (int k = 0; k < code.size(); ++k) {
		cout << pchar[k] << " " << ": ";
		for (int kk = 0; kk < code[k].size(); ++kk) {
			cout << code[k].at(kk);
		}
		cout << endl;
	}
}
//huffman����
/*
HuffmanNode* pHuffmanTree  �ѽ��õ�huffman��
char *code   Ҫ�����
vector<int> pchar  ������ַ�
char *str  ���������ַ�
int n   �����ַ��ĸ���
*/
void HuffmanDecoding(HuffmanNode* pHuffmanTree,char *code, vector<int> pchar, char *str,  int N)
{
	int i = 0;
	int q = 2 * N - 1 - 1;  //�Ӹ����±��� �ҵ�Ҷ�ӽڵ���ַ�
	int k = 0; //������֮����ַ�

	for (i = 0; code[i] != '\0'; ++i) {
		if (code[i] == '0') {
			q = pHuffmanTree[q].nleft;  //������
		}
		if (code[i] == '1') {
			q = pHuffmanTree[q].nright;  //������
		}
		//�ҵ�������ַ���Ҷ�ӽڵ�
		if (pHuffmanTree[q].nleft == 0 && pHuffmanTree[q].nright == 0) {
			str[k++] = pchar[q];  //����
			q = 2 * N - 1 - 1;    //���´Ӹ���ʼ
		}
	}
	str[k] = '\0';
}
int main()
{
	const int N = 256;
	const char* str = "abcdefghijkabcaaaaaa";
	int pweight[N] = { 0 };
	//����Ȩֵ
	CalcFrequency(str, pweight);
	vector<int> pchar;
	//ͳ����Ҫ������ַ� ��Ȩֵ�����0��ʼ
	CalcExistChar(pweight, N, pchar);
	//��Ҫ������ַ�����
	int N2 = (int)pchar.size();
	vector<vector<char>> code(N2);
	HuffmanNode *pHuffmanTree = NULL;
	//huffman���ڵ����
	pHuffmanTree = new HuffmanNode[2*N2-1];
	memset(pHuffmanTree,0,sizeof(HuffmanNode)*(2 * N2 - 1));
	//huffman�����ַ�
	HuffmanEncoding(pHuffmanTree,pweight, N2, code);
	PrintHuffmanEnCode(code, pchar);
	//���ַ�����huffman���� ���б���
	vector<char> vec_code;
	for (int k = 0; k < (int)strlen(str); ++k) {
		for (int kk = 0; kk < pchar.size(); ++kk) {
			if (str[k] == pchar[kk]) {
				for (int kkk = 0; kkk < code[kk].size(); ++kkk) {
					vec_code.push_back(code[kk].at(kkk));
				}
				break;
			}
		}
	}
	//�õ��ַ�����������
	char *pcode = new char[vec_code.size()+1];
	for (int k = 0; k < vec_code.size(); ++k) {
		pcode[k] = vec_code[k];
	}
	pcode[vec_code.size()] = '\0';
	char *outstr = new char[strlen(str)];
	//huffman���� 
	HuffmanDecoding(pHuffmanTree,pcode,pchar,outstr,N2);
	cout << outstr << endl;
	system("pause");
	return 0;
}