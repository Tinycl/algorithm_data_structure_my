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
//计算字符的出现的频数，权值
void CalcFrequency(const char *str, int *pweight)
{
	while (*str) {
		pweight[*str]++;
		str++;
	}

}
//提取出现的字符，并出现的字符的权值数组的索引重新从0开始。
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

//选择最小的两个父节点域为0的节点，组成一个新节点
//之前选择过的节点，组成父节点后，这两个节点父域不为0了
void SelectNode(const HuffmanNode *pHuffmanTree, int n, int& s1, int& s2)
{
	//找到第一个父节点域为0的节点
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nleft == 0) {
			s1 = i;
			break;
		}
	}
	//找到最小的父节点域为0的节点
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nparent == 0 && pHuffmanTree[i].nweight < pHuffmanTree[s1].nweight) {
			s1 = i;
		}
	}
	//找到第一个父节点域为0的节点 且不是s1
	for (int i = 0; i < n; ++i) {
		if (pHuffmanTree[i].nparent == 0 && i != s1) {
			s2 = i;
			break;
		}
	}
	//找到第二小的父节点域为0的节点
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
	int m = 2 * N - 1;//N个节点的huffman树需要2N-1个节点
	//pHuffmanTree = new HuffmanNode[m];
	//memset(pHuffmanTree,0,sizeof(HuffmanNode)*m);
	int s1, s2;
	int i;
	//建立叶子节点,就是要编码的字符
	for (i = 0; i < N; ++i) {
		pHuffmanTree[i].nweight = pweight[i];
		pHuffmanTree[i].nparent = 0;
		pHuffmanTree[i].nright = 0;
		pHuffmanTree[i].nleft = 0;
	}
	//每次选择权值最小的企且双亲域为0的两个节点，（要考虑叶子节点和新生成的节点），建树。新节点的权值为两个子节点权值之和
	for (i = N; i < m; ++i) {
		SelectNode(pHuffmanTree, i, s1, s2);
		pHuffmanTree[s1].nparent = i;
		pHuffmanTree[s2].nparent = i;
		pHuffmanTree[i].nleft = s1;
		pHuffmanTree[i].nright = s2;
		pHuffmanTree[i].nweight = pHuffmanTree[s1].nweight + pHuffmanTree[s2].nweight;//新节点的权值
	}
	//根据建好的huffman树，从叶子到根，遍历，得到每个叶子节点的编码。 再反转。
	int node, nparent;
	for (i = 0; i < N; ++i) {
		vector<char>& cur = code[i];
		node = i;
		nparent = pHuffmanTree[node].nparent;
		while (nparent != 0) {  //叶节点向上遍历
			if (pHuffmanTree[nparent].nleft == node) {
				cur.push_back('0');
			}
			if (pHuffmanTree[nparent].nright == node) {
				cur.push_back('1');
			}
			node = nparent;
			nparent = pHuffmanTree[node].nparent;
		}
		reverse(cur.begin(), cur.end()); //翻转一下
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
//huffman解码
/*
HuffmanNode* pHuffmanTree  已建好的huffman树
char *code   要解的码
vector<int> pchar  编码的字符
char *str  解码完后的字符
int n   编码字符的个数
*/
void HuffmanDecoding(HuffmanNode* pHuffmanTree,char *code, vector<int> pchar, char *str,  int N)
{
	int i = 0;
	int q = 2 * N - 1 - 1;  //从根向下遍历 找到叶子节点的字符
	int k = 0; //解码完之后的字符

	for (i = 0; code[i] != '\0'; ++i) {
		if (code[i] == '0') {
			q = pHuffmanTree[q].nleft;  //左子树
		}
		if (code[i] == '1') {
			q = pHuffmanTree[q].nright;  //右子树
		}
		//找到编码的字符，叶子节点
		if (pHuffmanTree[q].nleft == 0 && pHuffmanTree[q].nright == 0) {
			str[k++] = pchar[q];  //解码
			q = 2 * N - 1 - 1;    //重新从根开始
		}
	}
	str[k] = '\0';
}
int main()
{
	const int N = 256;
	const char* str = "abcdefghijkabcaaaaaa";
	int pweight[N] = { 0 };
	//计算权值
	CalcFrequency(str, pweight);
	vector<int> pchar;
	//统计需要编码的字符 ，权值数组从0开始
	CalcExistChar(pweight, N, pchar);
	//需要编码的字符个数
	int N2 = (int)pchar.size();
	vector<vector<char>> code(N2);
	HuffmanNode *pHuffmanTree = NULL;
	//huffman树节点个数
	pHuffmanTree = new HuffmanNode[2*N2-1];
	memset(pHuffmanTree,0,sizeof(HuffmanNode)*(2 * N2 - 1));
	//huffman编码字符
	HuffmanEncoding(pHuffmanTree,pweight, N2, code);
	PrintHuffmanEnCode(code, pchar);
	//将字符串用huffman编码 进行编码
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
	//得到字符串编码后的码
	char *pcode = new char[vec_code.size()+1];
	for (int k = 0; k < vec_code.size(); ++k) {
		pcode[k] = vec_code[k];
	}
	pcode[vec_code.size()] = '\0';
	char *outstr = new char[strlen(str)];
	//huffman解码 
	HuffmanDecoding(pHuffmanTree,pcode,pchar,outstr,N2);
	cout << outstr << endl;
	system("pause");
	return 0;
}