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
typedef void(*VISIT)(int value); //回调函数

class CBinaryTree
{
private:
	STreeNode* m_pRoot;
private:
	bool _Insert(STreeNode*& pRoot, int value);
	bool _Insert2(int value);
	//删除没有孩子的节点
	void DeleteChildless(STreeNode* pParent, STreeNode* pNode);
	//删除只有一个孩子的单枝节点
	void DeleteSingleSon(STreeNode* pParent, STreeNode* pNode);
	//递归前序遍历
	void _PreOrder(STreeNode* pRoot, VISIT Visit) const;
	//非递归前序遍历
	void _Preorder2(VISIT Visit) const;
	//递归中序遍历
	void _InOrder(STreeNode* pRoot, VISIT Visit) const;
	//非递归中序遍历
	void _InOrder2(VISIT Visit) const;
	//非递归中序遍历
	void _InOrder3(VISIT Visit) const;
	//递归遍历 后序
	void _PostOrder(STreeNode* pRoot, VISIT Visit) const;
	//非递归 后序
	void _PostOrder2(VISIT Visit) const;
public:
	CBinaryTree();
	~CBinaryTree();
	STreeNode* Find(int value) const;
	//插入的节点一定成为叶子节点，不用考虑平衡树，节点左旋或右旋，涉及节点移动
	//也就是说，一个节点原本就有两个孩子的话，一定不会再改节点下插入
	//只有在左右孩子为空或者都为空的节点下插入新节点
	bool Insert(int value);  //递归方式插入
	bool Insert2(int value);  //非递归方式插入
	bool Delete(int value);  //删除一个节点
	void PreOrder(VISIT Visit) const; //前序遍历 递归
	void PreOrder2(VISIT Visit) const; //前序遍历 非递归
	void InOrder(VISIT Visit) const; //中序遍历 递归
	void InOrder2(VISIT Visit) const; //中序遍历 非递归
	void InOrder3(VISIT Visit) const; //中序遍历 非递归
	void PostOrder(VISIT Visit) const; //后序遍历 递归
	void PostOrder2(VISIT Visit) const; //后序遍历 非递归
};