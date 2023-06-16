/*----------------------------------------
Author: Richard Stern
Description: A simple binary search tree
Date: 17/4/2015
----------------------------------------*/
#include "BinaryTree.h"
#include "TreeNode.h"
#include "raylib.h"
#include <iostream>
#include <cstdlib>
using namespace std;


BinaryTree::BinaryTree()
{
    m_pRoot = nullptr;
}

BinaryTree::~BinaryTree()
{
	while(m_pRoot)
	{
		Remove(m_pRoot->GetData());
	}
}

// Return whether the tree is empty
bool BinaryTree::IsEmpty() const 
{ 
	return (m_pRoot == nullptr);
}

// Insert a new element into the tree.
// Smaller elements are placed to the left, larger onces are placed to the right.
void BinaryTree::Insert(int a_nValue)
{
	if (!IsEmpty()) {
		TreeNode* pCurrent = m_pRoot;
		TreeNode* pNew = new TreeNode(a_nValue);

		while (true) {
			// Return to avoid duplicate values
			if (pCurrent->GetData() == a_nValue) return;

			// Continue searching if node has children
			// Otherwise just set the child

			if (a_nValue < pCurrent->GetData()) {
				if (pCurrent->HasLeft()) {
					pCurrent = pCurrent->GetLeft();
					continue;
				}

				pCurrent->SetLeft(pNew);
			}
			else {
				if (pCurrent->HasRight()) {
					pCurrent = pCurrent->GetRight();
					continue;
				}

				pCurrent->SetRight(pNew);
			}

			break;
		}
	}
	else { 
		// Set first time node
		m_pRoot = new TreeNode(a_nValue);
	}
}

TreeNode* BinaryTree::Find(int a_nValue)
{
	TreeNode* pCurrent = nullptr;
	TreeNode* pParent = nullptr;

	return FindNode(a_nValue, pCurrent, pParent) ? pCurrent: nullptr;
}

bool BinaryTree::FindNode(int a_nSearchValue, TreeNode*& ppOutNode, TreeNode*& ppOutParent)
{
	TreeNode* pCurrent = m_pRoot;

	while (true) {
		// Return when there arent any valid nodes or no data
		if (pCurrent == nullptr) return false;

		else {
			// Get the parent
			if ((pCurrent->HasLeft() && pCurrent->GetLeft() != nullptr && pCurrent->GetLeft()->GetData() == a_nSearchValue)
			|| (pCurrent->HasRight() && pCurrent->GetRight() != nullptr && pCurrent->GetRight()->GetData() == a_nSearchValue))
				ppOutParent = pCurrent;

			// Continue searching if greater or less than
			if (a_nSearchValue < pCurrent->GetData()) {
				pCurrent = pCurrent->GetLeft();
				continue;
			}

			else if (a_nSearchValue > pCurrent->GetData()) {
				pCurrent = pCurrent->GetRight();
				continue;
			}

			// Found our value !
			ppOutNode = pCurrent;
			return true;
		}
	}

	return false;
}

void BinaryTree::Remove(int a_nValue)
{
	if (!IsEmpty()) {
		TreeNode* pCurrent = nullptr;
		TreeNode* pParent = nullptr;

		FindNode(a_nValue, pCurrent, pParent);

		if (pCurrent == nullptr) return;

		// Deleting leaf node
		if (!pCurrent->HasLeft() && !pCurrent->HasRight()) {
			RemoveLeafNode(pCurrent, pParent);
			return;
		}

		// Deleting right single node
		if (!pCurrent->HasLeft() && pCurrent->HasRight()) {
			RemoveNodeSingleRight(pCurrent, pParent);
			return;
		}

		// Deleting left single node
		if (pCurrent->HasLeft() && !pCurrent->HasRight()) {
			RemoveNodeSingleLeft(pCurrent, pParent);
			return;
		}

		// Deleting double node
		if (pCurrent->HasLeft() && pCurrent->HasRight()) {

			std::cout << "Removing double node" << std::endl;

			TreeNode* pCurrentCheck = pCurrent->GetRight();

			// Find smallest node from the currents largest
			while (true) {
				if (pCurrentCheck->HasLeft()) {
					pCurrentCheck = pCurrentCheck->GetLeft();
					continue;
				}

				int temp = pCurrentCheck->GetData();
				Remove(temp);
				pCurrent->SetData(temp);
				return;
			}
		}
	}
}

void BinaryTree::RemoveLeafNode(TreeNode* pCurrent, TreeNode* pParent) {
	std::cout << "Deleting leaf node" << std::endl;

	if (pParent != nullptr) {
		if (pParent->HasLeft() && pParent->GetLeft() == pCurrent) {
			pParent->SetLeft(nullptr);
		}
		if (pParent->HasRight() && pParent->GetRight() == pCurrent) {
			pParent->SetRight(nullptr);
		}
	}

	if (pCurrent == m_pRoot)
		m_pRoot = nullptr;

	pCurrent = nullptr;
}

void BinaryTree::RemoveNodeSingleLeft(TreeNode* pCurrent, TreeNode* pParent) {
	std::cout << "Deleting left single node" << std::endl;

	if (pParent != nullptr) {
		if (pParent->HasLeft() && pParent->GetLeft() == pCurrent) {
			pParent->SetLeft(pCurrent->GetLeft());
		}
		if (pParent->HasRight() && pParent->GetRight() == pCurrent) {
			pParent->SetRight(pCurrent->GetLeft());
		}
	}

	if (pCurrent == m_pRoot)
		m_pRoot = pCurrent->GetLeft();

	pCurrent = nullptr;
}

void BinaryTree::RemoveNodeSingleRight(TreeNode* pCurrent, TreeNode* pParent) {
	std::cout << "Deleting right single node" << std::endl;

	if (pParent != nullptr) {
		if (pParent->HasLeft() && pParent->GetLeft() == pCurrent) {
			pParent->SetLeft(pCurrent->GetRight());
		}
		if (pParent->HasRight() && pParent->GetRight() == pCurrent) {
			pParent->SetRight(pCurrent->GetRight());
		}
	}

	if (pCurrent == m_pRoot)
		m_pRoot = pCurrent->GetRight();

	pCurrent = nullptr;
}

void BinaryTree::PrintOrdered()
{
	PrintOrderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintOrderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::PrintUnordered()
{
    PrintUnorderedRecurse(m_pRoot);
	cout << endl;
}

void BinaryTree::PrintUnorderedRecurse(TreeNode* pNode)
{

}

void BinaryTree::Draw(TreeNode* selected)
{
	Draw(m_pRoot, 400, 40, 400, selected);
}

void BinaryTree::Draw(TreeNode* pNode, int x, int y, int horizontalSpacing, TreeNode* selected)
{
	
	horizontalSpacing /= 2;

	if (pNode)
	{
		if (pNode->HasLeft())
		{
			DrawLine(x, y, x - horizontalSpacing, y + 80, RED);
			
			Draw(pNode->GetLeft(), x - horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		if (pNode->HasRight())
		{
			DrawLine(x, y, x + horizontalSpacing, y + 80, RED);

			Draw(pNode->GetRight(), x + horizontalSpacing, y + 80, horizontalSpacing, selected);
		}

		pNode->Draw(x, y, (selected == pNode));
	}
}