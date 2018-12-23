#include <iostream>
#include "bst.h"

using namespace std;
void Oper(int value)
{
	cout << value << endl;
}
//已知前序，中序遍历结果 求后续遍历结果
void InPre2Post(const char* pInoOder, const char* pPreOrder, int nLength, char* pPostOrder, int& nIndex)
{
	if (nLength <= 0) {
		return;
	}
	if (nLength == 1) {
		pPostOrder[nIndex] = *pPreOrder;
	}
	char root = *pPreOrder;
	int nRoot = 0;;
	for (; nRoot < nLength; ++nRoot) {
		if (pInoOder[nRoot] == root) {
			break;
		}
	}
	InPre2Post(pInoOder, pPreOrder + 1, nRoot, pPostOrder, nIndex);
	InPre2Post(pInoOder + nRoot + 1, pPreOrder + nRoot + 1, nLength - (nRoot + 1), pPostOrder, nIndex);
	pPostOrder[nIndex] = root;
	nIndex++;
}
//已知中序和后序，求前序
void InPost2Pre(const char* pInOrder, const char* pPostOrder, int nLength, char* pPreOrder, int& nIndex)
{
	if (nLength <= 0) {
		return;
	}
	if (nLength == 1) {
		pPreOrder[nIndex] = *pPostOrder;
		nIndex++;
		return;
	}
	char root = pPostOrder[nLength - 1];
	pPreOrder[nIndex] = root;
	nIndex++;
	int nRoot = 0;
	for(; nRoot < nLength; nRoot++){
		if (pInOrder[nRoot] == root) {
			break;
		}
	}
	InPost2Pre(pInOrder,pPostOrder, nRoot, pPreOrder,nIndex);
	InPost2Pre(pInOrder + nRoot + 1, pPostOrder + nRoot, nLength - (nRoot + 1), pPreOrder,nIndex);
}
int main()
{
	CBinaryTree bt;
	bt.Insert(15);
	bt.Insert(5);
	bt.Insert(3);
	bt.Insert(12);
	bt.Insert(16);
	bt.Insert(20);
	bt.Insert(23);
	bt.Insert(13);
	bt.Insert(18);
	bt.Insert(10);
	bt.Insert(6);
	bt.Insert(7);
	bt.PostOrder2(Oper);
	cout << "find 12" << endl;
	STreeNode *pnode = bt.Find(12);
	cout << pnode->value << endl;
	cout << "delete 12" << endl;
	bt.Delete(12);
	bt.PostOrder2(Oper);
	cout << "inpost2pre "<< endl;
	char pPostOrder[] = "AEFDHZMG";
	char pInOrder[] = "ADEFGHMZ";
	int size = sizeof(pInOrder) / sizeof(char);
	char* pPreOrder = new char[size];
	int nIndex = 0;
	InPost2Pre(pInOrder,pPostOrder,size-1,pPreOrder,nIndex);
	pPreOrder[size - 1] = 0;
	cout << pPreOrder << endl;

	cout << "inpre2post " << endl;
	
	char pPreOrder1[] = "GDAFEMHZ";
	char pInOrder1[] = "ADEFGHMZ";
	int size1 = sizeof(pInOrder1) / sizeof(char);
	char* pPostOrder1 = new char[size];
	int nIndex1 = 0;
	InPre2Post(pInOrder1, pPreOrder1, size - 1, pPostOrder1, nIndex1);
	pPostOrder1[size - 1] = 0;
	cout << pPostOrder1 << endl;

	system("pause");
	return 0;
}