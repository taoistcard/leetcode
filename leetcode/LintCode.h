#pragma once
#include "std_head.h"

namespace LintCode{
	/**
	* Definition of TreeNode:
	* class TreeNode {
	* public:
	*     int val;
	*     TreeNode *left, *right;
	*     TreeNode(int val) {
	*         this->val = val;
	*         this->left = this->right = NULL;
	*     }
	* }
	*/
	class TreeNode {
	public:
		int val;
		TreeNode *left, *right;
		TreeNode(int val)
		{
			this->val = val;
			this->left = this->right = NULL;
		}
	};
	typedef TreeNode* BiTree;

	static std::vector<std::string> split(const  std::string& s, const std::string& delim)
	{
		std::vector<std::string> elems;
		size_t pos = 0;
		size_t len = s.length();
		size_t delim_len = delim.length();
		if (delim_len == 0) return elems;
		while (pos < len)
		{
			int find_pos = s.find(delim, pos);
			if (find_pos < 0)
			{
				elems.push_back(s.substr(pos, len - pos));
				break;
			}
			elems.push_back(s.substr(pos, find_pos - pos));
			pos = find_pos + delim_len;
		}
		return elems;
	}
	static bool is_digit(const std::string& s)
	{
		for (auto c : s)
		{
			if (c >= '1' && c <= '9')
				return true;
			else
				return false;
		}
		return false;
	}
	static TreeNode* createNode(const std::string& val)
	{
		if (!is_digit(val))
			return nullptr;
		return new TreeNode(atoi(val.c_str()));
	}
	static TreeNode* createTree(const std::string& str)
	{
		unsigned int f = str.find_first_of('{');
		unsigned int l = str.find_last_of('}');
		if (f == std::string::npos || l == std::string::npos)
			return nullptr;
		std::string s = str.substr(f+1, l - f);
		std::vector<std::string> vals = split(s, ",");

		if (vals.empty())
			return nullptr;
		std::list<TreeNode*> layer_list;

		TreeNode* pRoot = createNode(vals[0]);
		if (pRoot == nullptr)
			return nullptr;
		vals.erase(vals.begin());
		layer_list.push_back(pRoot);

		while (vals.size() > 0)
		{
			std::list<TreeNode*> tmp_list;
			for (auto it = layer_list.begin(); it != layer_list.end(); ++it)
			{
				if (vals.empty())
					break;

				TreeNode* pParent = *it;
				TreeNode* pNode = createNode(vals[0]);
				vals.erase(vals.begin());
				if (pNode != nullptr)
				{
					pParent->left = pNode;
					tmp_list.push_back(pNode);
				}

				if (vals.empty())
				{
					break;
				}

				TreeNode* pRight = createNode(vals[0]);
				vals.erase(vals.begin());
				if (pRight != nullptr)
				{
					pParent->right = pRight;
					tmp_list.push_back(pRight);
				}
			}
			layer_list = tmp_list;
		}
		return pRoot;
	}
	//前序遍历二叉树并打印
	void preTraverse(BiTree T)
	{
		if (T)
		{
			std::cout << T->val << " ";
			preTraverse(T->left);
			preTraverse(T->right);
		}
	}
	//中序遍历二叉树并打印
	void midTraverse(BiTree T)
	{
		if (T)
		{
			midTraverse(T->left);
			cout << T->val << " ";
			midTraverse(T->right);
		}
	}
	//后续遍历二叉树并打印
	void postTraverse(BiTree T)
	{
		if (T)
		{
			postTraverse(T->left);
			postTraverse(T->right);
			cout << T->val << " ";
		}
	}
	static void BreadthTraverse(BiTree T)
	{
		if (!T)
			return;
		queue<BiTree> q;
		q.push(T);
		while (!q.empty())
		{
			BiTree n = q.front();
			q.pop();
			if (n)
			{
				cout << n->val;
				q.push(n->left);
				q.push(n->right);
			}
			else
				cout << '#';
		}
	}
	class Solution95 {
	public:
		/**
		* @param root: The root of binary tree.
		* @return: True if the binary tree is BST, or false
		*/
		bool isSmallerTree(TreeNode * root, int rootVal)
		{
			if (root == nullptr)
				return true;
			if (root->val >= rootVal)
			{
				return false;
			}
			if (root->left)
				if (!isSmallerTree(root->left, rootVal))
					return false;
			if (root->right)
				if (!isSmallerTree(root->right, rootVal))
					return false;
			return true;
		}
		bool isBiggerTree(TreeNode * root, int rootVal)
		{
			if (root == nullptr)
				return true;
			if (root->val <= rootVal)
			{
				return false;
			}
			if (root->left)
				if (!isBiggerTree(root->left, rootVal))
					return false;
			if (root->right)
				if (!isBiggerTree(root->right, rootVal))
					return false;
			return true;
		}

		bool isValidBST(TreeNode * root) {
			// write your code here
			if (root == nullptr)
				return true;

			if (root->left)
			{
				if (!isSmallerTree(root->left, root->val))
				{
					return false;
				}
			}
			if (root->right)
			{
				if (!isBiggerTree(root->right, root->val))
				{
					return false;
				}
			}
			if (root->left && !isValidBST(root->left))
				return false;
			if (root->right && !isValidBST(root->right))
				return false;

			return true;
		}

	};

}