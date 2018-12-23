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
	while (pNode != NULL) {  //���������� ��������ֵС�ڸ���ֵ����������ֵ���ڸ���ֵ
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
//����������Ľڵ㶼��ΪҶ�ӽڵ㣬���ڵ�ֵ�����룬��
//ָ�����ã�������֮���ָ��Ҳ�ı�,��Ȼ������ô�һ������������ʵ�ʵݹ���̲����ǲ�ͬ�ġ�
bool CBinaryTree::_Insert(STreeNode*& pRoot, int value)
{
	if (!pRoot) {
		pRoot = new STreeNode(value);
		return true;
	}
	if (value < pRoot->value) {
		//��ʱpRoot->pleft �Ѿ��ı䡣
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

//ɾ��û�к��ӵĽڵ�
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
//ɾ��ֻ��һ�����ӵĽڵ�
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
//ɾ���Ľڵ��ֵ��û��Ҫһ���ѽڵ���ڴ�ṹҲ�ɵ�
/*
*ɾ�������������ӽڵ��ֵʱ��ֻ��ɾ��ֵ��
*�ýڵ���ڴ�������ڱ�����ֱ��ǰ�����̵�ֵ����ֱ��ǰ�����̵��ڴ�ṹ�ͷŵ�.
*ע����ƽ������ ��ת�ڵ���������� ������
*/
/*
*��ȻҲ���Ըɵ��ýڵ���ڴ�ṹ����ֱ��ǰ�����ߺ�̵��ڴ�ṹ����
*/
bool CBinaryTree::Delete(int value)
{
	if (!m_pRoot) {
		return false;
	}
	STreeNode* pNode = m_pRoot;
	STreeNode* pParent = NULL;
	//�ҵ���ɾ���Ľڵ� ���丸�ڵ�
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
	//û���ҵ�
	if (!pNode) {
		return false;
	}
	if (pNode->pleft == NULL && pNode->pright == NULL) {//�����û�к��ӵĽڵ㣬Ҷ�ӽڵ�
		DeleteChildless(pParent,pNode);
	}
	else if (pNode->pleft == NULL || pNode->pright == NULL) {//��֦�ڵ� ֻ��һ������
		DeleteSingleSon(pParent, pNode);
	}
	else if (pNode->pleft != NULL && pNode->pright != NULL) { //���������ӵĽڵ�
		STreeNode* pCur = pNode;//�ݴ��ɾ���ڵ�
		pParent = pNode;
		//��ֱ��ǰ���ڵ�
		pNode = pNode->pleft;
		while (pNode->pright) {
			pParent = pNode;
			pNode = pNode->pright;
		}
		pCur->value = pNode->value; //ɾ���ڵ�����ݣ�����ֱ��ǰ����ֵ����
		if (pNode->pleft == NULL) { //ֱ��ǰ�����ص㣺��������������������������Ϊ�գ���������������
			DeleteChildless(pParent, pNode);
		}
		else if (pNode->pleft) {
			DeleteSingleSon(pParent, pNode);
		}
	}
	return true;
}

//ǰ������ݹ鷽ʽ
void CBinaryTree::_PreOrder(STreeNode* pRoot, VISIT Visit) const
{
	if (pRoot)
	{
		Visit(pRoot->value);
		_PreOrder(pRoot->pleft, Visit);
		_PreOrder(pRoot->pright, Visit);
	}
}

//�ǵݹ�ǰ�����
/*
*����ջ������ջ������������������ջ����������ջ���ȵ����������ٵ���������
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
//�ݹ��������
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
		//�ҵ������������㣬��������ӣ�����Ѱ�ҵĹ����н�·���Ľڵ㣨�ݹ����ӣ�ѹջ
		//ÿ����ÿ��������������
		while (pCur) {
			s.push(pCur);
			pCur = pCur->pleft;
		}
		//����ÿ������������������������������Ϊ�գ���ջ
		if (!s.empty()) {
			pCur = s.top();  //��������Ϊ�յĽڵ㣬�������ӣ��ݹ鶨�壩
			s.pop();
			Visit(pCur->value);
			pCur = pCur->pright; //ת���Һ���
		}
	}
}

//ÿһ���ڵ�2����ѹջ���ڶ��η���
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
		//ÿһ���ڵ���ջ�Ļ���
		if (times == 0) { //��һ��ѹջ
			if (pCur->pright) {
				s.push(make_pair(pCur->pright, 0));
			}
			s.push(make_pair(pCur, 1)); //�ڶ���ѹջ
			if (pCur->pleft) {
				s.push(make_pair(pCur->pleft, 0));
			}
		}
		if(times == 1) //�ڵ�ڶ���ѹջʱ����
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
//�ݹ�������
void CBinaryTree::_PostOrder(STreeNode* pRoot, VISIT Visit) const
{
	if (pRoot) {
		_PostOrder(pRoot->pleft,Visit);
		_PostOrder(pRoot->pright, Visit);
		Visit(pRoot->value);
	}
}

//�ǵݹ�������
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
		if (times == 0) { //��һ��ѹջ
			s.push(make_pair(pCur, 1));//�ڶ��η���  ����ѹջ�������ʣ�
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