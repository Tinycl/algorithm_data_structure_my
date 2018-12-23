#include "bst.h"

CBinaryTree::CBinaryTree()
{
	
}
CBinaryTree::~CBinaryTree()
{
	if (m_pRoot != NULL)
	{
		delete m_pRoot;
		m_pRoot = NULL;
	}
}
STreeNode* CBinaryTree::Find(int value) const
{
	if (m_pRoot == NULL) {
		return NULL;
	}
	STreeNode* pNode = m_pRoot;
	while (pNode != NULL) {  //搜索二叉树 左子树的值小于根的值，右子树的值大于根的值
		if (value > pNode->value) {
			pNode = pNode->pright;
		}
		else if (value < pNode->value) {
			pNode = pNode->pleft;
		}
		else {
			return pNode;
		}
	}
	return NULL;
}
//二叉树插入的节点都成为叶子节点，存在的值不插入，。
//指针引用，传出的之后的指针也改变,虽然顶层调用传一个参数，但是实际递归过程参数是不同的。
bool CBinaryTree::_Insert(STreeNode*& pRoot, int value)
{
	if (!pRoot) {
		pRoot = new STreeNode(value);
		return true;
	}
	if (value < pRoot->value) {
		//此时pRoot->pleft 已经改变。
		return _Insert(pRoot->pleft, value);
	}
	else if (value > pRoot->value) {
		return _Insert(pRoot->pright, value);
	}
	else {
		return false;
	}
	return false;
}

bool CBinaryTree::_Insert2(int value)
{
	if (!m_pRoot) {
		m_pRoot = new STreeNode(value);
		return true;
	}
	STreeNode* pNode = m_pRoot;
	STreeNode* pCur = pNode;
	while (pNode) {
		pCur = pNode;
		if (value < pNode->value) {
			pNode = pNode->pleft;
		}
		else if (value > pNode->value) {
			pNode = pNode->pright;
		}
		else {
			return false;
		}
	}
	if (value < pCur->value) {
		pCur->pleft = new STreeNode(value);
	}
	else if (value > pCur->value) {
		pCur->pright = new STreeNode(value);
	}
	/*
	while (pNode->pleft != NULL && pNode->pright != NULL) {
		if (value < pNode->value) {
			pNode = pNode->pleft;
		}
		else if (value > pNode->value) {
			pNode = pNode->pright;
		}
		else {
			return false;
		}
	}
	if (value < pNode->value) {
		pNode->pleft = new STreeNode(value);
	}
	else if (value > pNode->value) {
		pNode->pright = new STreeNode(value);
	}
	*/
	return true;
}

bool CBinaryTree::Insert(int value)
{
	return _Insert(m_pRoot, value);
}
bool CBinaryTree::Insert2(int value)
{
	return _Insert2(value);
}

//删除没有孩子的节点
void CBinaryTree::DeleteChildless(STreeNode* pParent, STreeNode* pNode)
{
	if (pNode == m_pRoot) {
		m_pRoot = NULL;
	}
	else if (pParent->pleft == pNode) {
		pParent->pleft = NULL;
	}
	else if(pParent->pright == pNode)
	{
		pParent->pright = NULL;
	}
	delete pNode;
}
//删除只有一个孩子的节点
void CBinaryTree::DeleteSingleSon(STreeNode* pParent, STreeNode* pNode)
{
	STreeNode* pGrandSon = pNode->pleft ? pNode->pleft : pNode->pright;
	if (pNode == m_pRoot) {
		m_pRoot = pGrandSon;
	}
	else if (pParent->pleft == pNode) {
		pParent->pleft = pGrandSon;
	}
	else if(pParent->pright == pNode){
		pParent->pright = pGrandSon;
	}
	delete pNode;
}
//删除的节点的值，没必要一定把节点的内存结构也干掉
/*
*删除带有来个孩子节点的值时，只是删除值，
*该节点的内存继续存在保存其直接前驱或后继的值，将直接前驱或后继的内存结构释放掉.
*注意与平衡树， 旋转节点的区别（左旋 右旋）
*/
/*
*当然也可以干掉该节点的内存结构，用直接前驱或者后继的内存结构代替
*/
bool CBinaryTree::Delete(int value)
{
	if (!m_pRoot) {
		return false;
	}
	STreeNode* pNode = m_pRoot;
	STreeNode* pParent = NULL;
	//找到待删除的节点 和其父节点
	while (pNode) {
		if (value < pNode->value) {
			pParent = pNode;
			pNode = pNode->pleft;
		}
		else if(value > pNode->value){
			pParent = pNode;
			pNode = pNode->pright;
		}
		else if (value = pNode->value) {
			break;
		}
	}
	//没有找到
	if (!pNode) {
		return false;
	}
	if (pNode->pleft == NULL && pNode->pright == NULL) {//如果是没有孩子的节点，叶子节点
		DeleteChildless(pParent,pNode);
	}
	else if (pNode->pleft == NULL || pNode->pright == NULL) {//单枝节点 只有一个孩子
		DeleteSingleSon(pParent, pNode);
	}
	else if (pNode->pleft != NULL && pNode->pright != NULL) { //有两个孩子的节点
		STreeNode* pCur = pNode;//暂存待删除节点
		pParent = pNode;
		//找直接前驱节点
		pNode = pNode->pleft;
		while (pNode->pright) {
			pParent = pNode;
			pNode = pNode->pright;
		}
		pCur->value = pNode->value; //删除节点的数据，由其直接前驱的值填入
		if (pNode->pleft == NULL) { //直接前驱的特点：左子树的最右子树（其右子树为空，左子树不定），
			DeleteChildless(pParent, pNode);
		}
		else if (pNode->pleft) {
			DeleteSingleSon(pParent, pNode);
		}
	}
	return true;
}

//前序遍历递归方式
void CBinaryTree::_PreOrder(STreeNode* pRoot, VISIT Visit) const
{
	if (pRoot)
	{
		Visit(pRoot->value);
		_PreOrder(pRoot->pleft, Visit);
		_PreOrder(pRoot->pright, Visit);
	}
}

//非递归前序遍历
/*
*利用栈，根入栈，弹出根。右子树入栈，左子树入栈（先弹左子树，再弹右子树）
*/
void CBinaryTree::_Preorder2(VISIT Visit) const
{
	if (m_pRoot == NULL) {
		return;
	}
	stack<STreeNode*> s;
	s.push(m_pRoot);
	STreeNode* pCur;
	while (!s.empty()) {
		pCur = s.top();
		s.pop();
		Visit(pCur->value);
		if (pCur->pright) {
			s.push(pCur->pright);
		}
		if (pCur->pleft) {
			s.push(pCur->pleft);
		}
	}
}

void CBinaryTree::PreOrder(VISIT Visit) const
{
	_PreOrder(m_pRoot, Visit);
}
void CBinaryTree::PreOrder2(VISIT Visit) const
{
	_Preorder2(Visit);
}
//递归中序遍历
void CBinaryTree::_InOrder(STreeNode* pRoot, VISIT Visit) const
{
	if (pRoot) {
		_InOrder(pRoot->pleft, Visit);
		Visit(pRoot->value);
		_InOrder(pRoot->pright,Visit);
	}
}
void CBinaryTree::_InOrder2(VISIT Visit) const
{
	stack<STreeNode*> s;
	STreeNode* pCur = m_pRoot;
	while (pCur || !s.empty()) {
		//找到中序遍历的起点，最左的左孩子，并在寻找的过程中将路径的节点（递归左孩子）压栈
		//每次找每次中序遍历的起点
		while (pCur) {
			s.push(pCur);
			pCur = pCur->pleft;
		}
		//访问每次最左左子树，并将其右子树（不为空）入栈
		if (!s.empty()) {
			pCur = s.top();  //访问左孩子为空的节点，最左左孩子（递归定义）
			s.pop();
			Visit(pCur->value);
			pCur = pCur->pright; //转向右孩子
		}
	}
}

//每一个节点2都次压栈，第二次访问
void CBinaryTree::_InOrder3(VISIT Visit) const
{
	if (m_pRoot == NULL) {
		return;
	}
	stack <pair<STreeNode*, int>> s;
	s.push(make_pair(m_pRoot, 0));
	int times;
	STreeNode* pCur;
	while (!s.empty()) {
		pCur = s.top().first;
		times = s.top().second;
		s.pop();
		//每一个节点入栈的机会
		if (times == 0) { //第一次压栈
			if (pCur->pright) {
				s.push(make_pair(pCur->pright, 0));
			}
			s.push(make_pair(pCur, 1)); //第二次压栈
			if (pCur->pleft) {
				s.push(make_pair(pCur->pleft, 0));
			}
		}
		if(times == 1) //节点第二次压栈时访问
		{
			Visit(pCur->value);
		}
	}
}
void CBinaryTree::InOrder(VISIT Visit) const
{
	_InOrder(m_pRoot, Visit);
}
void CBinaryTree::InOrder2(VISIT Visit) const
{
	_InOrder2(Visit);
}
void CBinaryTree::InOrder3(VISIT Visit) const
{
	_InOrder3(Visit);
}
//递归后序遍历
void CBinaryTree::_PostOrder(STreeNode* pRoot, VISIT Visit) const
{
	if (pRoot) {
		_PostOrder(pRoot->pleft,Visit);
		_PostOrder(pRoot->pright, Visit);
		Visit(pRoot->value);
	}
}

//非递归后序遍历
void CBinaryTree::_PostOrder2(VISIT Visit) const
{
	if (m_pRoot == NULL) {
		return;
	}
	stack<pair<STreeNode*, int>> s;
	s.push(make_pair(m_pRoot, 0));
	int times;
	STreeNode* pCur;
	while (!s.empty()) {
		pCur = s.top().first;
		times = s.top().second;
		s.pop();
		if (times == 0) { //第一次压栈
			s.push(make_pair(pCur, 1));//第二次访问  （限压栈的最后访问）
			if (pCur->pright) {
				s.push(make_pair(pCur->pright, 0));
			}
			if (pCur->pleft) {
				s.push(make_pair(pCur->pleft, 0));
			}
		}
		if(times == 1)
		{
			Visit(pCur->value);
		}
	}
}

void CBinaryTree::PostOrder(VISIT Visit) const
{
	_PostOrder(m_pRoot,Visit);
}
void CBinaryTree::PostOrder2(VISIT Visit) const
{
	_PostOrder2(Visit);
}