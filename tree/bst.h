#pragma once
#include <iostream>
#include <stack>
using namespace std;
typedef struct tagSTreeNode
{
	int value;
	tagSTreeNode *pleft;
	tagSTreeNode *pright;
	tagSTreeNode(int v) :value(v), pleft(NULL), pright(NULL) {}
}STreeNode;
typedef void(*VISIT)(int value); //�ص�����

class CBinaryTree
{
private:
	STreeNode* m_pRoot;
private:
	bool _Insert(STreeNode*& pRoot, int value);
	bool _Insert2(int value);
	//ɾ��û�к��ӵĽڵ�
	void DeleteChildless(STreeNode* pParent, STreeNode* pNode);
	//ɾ��ֻ��һ�����ӵĵ�֦�ڵ�
	void DeleteSingleSon(STreeNode* pParent, STreeNode* pNode);
	//�ݹ�ǰ�����
	void _PreOrder(STreeNode* pRoot, VISIT Visit) const;
	//�ǵݹ�ǰ�����
	void _Preorder2(VISIT Visit) const;
	//�ݹ��������
	void _InOrder(STreeNode* pRoot, VISIT Visit) const;
	//�ǵݹ��������
	void _InOrder2(VISIT Visit) const;
	//�ǵݹ��������
	void _InOrder3(VISIT Visit) const;
	//�ݹ���� ����
	void _PostOrder(STreeNode* pRoot, VISIT Visit) const;
	//�ǵݹ� ����
	void _PostOrder2(VISIT Visit) const;
public:
	CBinaryTree();
	~CBinaryTree();
	STreeNode* Find(int value) const;
	//����Ľڵ�һ����ΪҶ�ӽڵ㣬���ÿ���ƽ�������ڵ��������������漰�ڵ��ƶ�
	//Ҳ����˵��һ���ڵ�ԭ�������������ӵĻ���һ�������ٸĽڵ��²���
	//ֻ�������Һ���Ϊ�ջ��߶�Ϊ�յĽڵ��²����½ڵ�
	bool Insert(int value);  //�ݹ鷽ʽ����
	bool Insert2(int value);  //�ǵݹ鷽ʽ����
	bool Delete(int value);  //ɾ��һ���ڵ�
	void PreOrder(VISIT Visit) const; //ǰ����� �ݹ�
	void PreOrder2(VISIT Visit) const; //ǰ����� �ǵݹ�
	void InOrder(VISIT Visit) const; //������� �ݹ�
	void InOrder2(VISIT Visit) const; //������� �ǵݹ�
	void InOrder3(VISIT Visit) const; //������� �ǵݹ�
	void PostOrder(VISIT Visit) const; //������� �ݹ�
	void PostOrder2(VISIT Visit) const; //������� �ǵݹ�
};