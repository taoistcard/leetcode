#pragma once
#include <assert.h>

#include "std_head.h"


namespace CppTest
{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode *parent;

		int flag = 0;
		TreeNode(int x) : val(x), left(NULL), right(NULL), parent(NULL) {}
	};

	//struct PrintNode
	//{
	//	TreeNode* pNode;
	//	int depth;
	//};

	class BTree {
	public:
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
			std::string s = str.substr(f + 1, l - f);
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

		static TreeNode* createTree(int level, int flag)
		{
			std::string dir = "左";
			if (flag == 1){
				dir = "左";
			}else if (flag == 2){
				dir = "右";
			}
			else{
				dir = "根";
			}
			int data;
			cout << "create level=" << level << " "<< dir << endl;
			cin >> data;
			if (0 == data){
				cout << "ignore level=" << level << " " << dir << endl;
				return NULL;
			}
			TreeNode* root = new TreeNode(data);
			TreeNode* left = createTree(level+1,1);
			TreeNode* right = createTree(level+1,2);
			if (left)
			{
				left->parent = root;
				root->left = left;
			}
			if (right)
			{
				right->parent = root;
				root->right = right;
			}

			return root;
		}

		static TreeNode* createTree(std::stringstream& ss, int level, int flag)
		{
			std::string dir = "左";
			if (flag == 1){
				dir = "左";
			}
			else if (flag == 2){
				dir = "右";
			}
			else{
				dir = "根";
			}
			int data;
			cout << "create level=" << level << " " << dir << endl;
			ss >> data;
			if (0 == data){
				cout << "ignore level=" << level << " " << dir << endl;
				return NULL;
			}
			TreeNode* root = new TreeNode(data);
			TreeNode* left = createTree(ss, level + 1, 1);
			TreeNode* right = createTree(ss, level + 1, 2);
			if (left)
			{
				left->parent = root;
				root->left = left;
			}
			if (right)
			{
				right->parent = root;
				root->right = right;
			}

			return root;
		}

		static int calcDepth(TreeNode* pRoot)
		{
			if (pRoot == NULL)
				return 0;
			return 1 + calcDepth(pRoot->left) + calcDepth(pRoot->right);
		}

		static void print(TreeNode* pRoot, int dp, int cur_depth)
		{
		}

		//广度优先
		static void breadthTraverse(TreeNode* root)
		{
			list<TreeNode*> q;
			q.push_back(root);
			while (!q.empty())
			{
				auto it = q.begin();
				TreeNode* node = *it;
				if (node == NULL)
					break;
				q.pop_front();

				cout << setw(4) << node->val << ' ';
				if (node->left)
				{
					q.push_back(node->left);
				}

				if (node->right)
				{
					q.push_back(node->right);
				}
			}
		}
		//先序遍历
		static void preOrderTraverse(TreeNode* root)
		{
			if (root)
			{
				cout << setw(4) << root->val << ' ';
				preOrderTraverse(root->left);
				preOrderTraverse(root->right);
			}
		}

		//中序遍历
		static void inOrderTraverse(TreeNode* root)
		{
			if (root)
			{
				inOrderTraverse(root->left);
				cout << setw(4) << root->val << ' ';
				inOrderTraverse(root->right);
			}
		}

		//后序遍历
		static void lastOrderTraverse(TreeNode* root)
		{
			if (root)
			{
				lastOrderTraverse(root->left);
				lastOrderTraverse(root->right);

				cout << setw(4) << root->val << ' ';
			}
		}

		static void printNode(TreeNode* pNode)
		{
			cout << setw(4) << pNode->val << ' ';
		}

		static void preOrderTraverse_NonRecursion(TreeNode* root)
		{
			std::stack<TreeNode*> st;
			st.push(root);
			while (!st.empty())
			{
				TreeNode* pNode = st.top();
				cout << setw(4) << pNode->val << ' ';
				st.pop();
				if (pNode->right)
					st.push(pNode->right);
				if (pNode->left)
					st.push(pNode->left);
			}
		}
		static void preOrderTraverse_NonRecursion1(TreeNode* root)
		{
			if (root == nullptr)
				return;
			std::stack<TreeNode*> st; //存访问过的根节点
			TreeNode* pNode = root;
			while (!st.empty() || !pNode)
			{
				while (pNode)
				{
					cout << setw(4) << pNode->val << ' ';
					st.push(pNode);
					pNode = pNode->left;
				}
				if (!st.empty())
				{
					pNode = st.top();
					st.pop();
					pNode = pNode->right;
				}
			}
		}
		static void preOrderTraverse_NonRecursion2(TreeNode* root)
		{
			if (root == nullptr)
				return;
			std::stack<TreeNode*> st; //存访问过的根节点
			TreeNode* pNode = root;
			while (!st.empty() || !pNode)
			{
				if (pNode)
				{
					cout << setw(4) << pNode->val << ' ';
					st.push(pNode);
					pNode = pNode->left;
				}
				else
				{
					pNode = st.top();
					st.pop();
					pNode = pNode->right;
				}
			}
		}

		static void inOrderTraverse_NonRecursion(TreeNode* root)
		{
			std::stack<TreeNode*> st;
			st.push(root);
			while (!st.empty())
			{
				TreeNode* pNode = st.top();
				st.pop();
				if (pNode->right)
				{
					st.push(pNode->right);
				}

				if (pNode->left)
				{
					st.push(pNode);
					st.push(pNode->left);
				}
				else
					cout << setw(4) << pNode->val << ' ';
			}
		}
		static void inOrderTraverse_NonRecursion1(TreeNode* root)
		{
			if (root == nullptr)
				return;
			std::stack<TreeNode*> st;
			TreeNode* pNode = root;
			while (!st.empty() || !pNode)
			{
				if (pNode)
				{
					st.push(pNode);
					pNode = pNode->left;
				}
				else
				{
					pNode = st.top();
					st.pop();
					cout << setw(4) << pNode->val << ' ';
					pNode = pNode->right;
				}
			}
		}
		static void inOrderTraverse_NonRecursion2(TreeNode* root)
		{
			if (root == nullptr)
				return;
			std::stack<TreeNode*> st;
			TreeNode* pNode = root;
			while (!st.empty() || !pNode)
			{
				while (pNode)
				{
					st.push(pNode);
					pNode = pNode->left;
				}
				
				pNode = st.top();
				st.pop();
				cout << setw(4) << pNode->val << ' ';
				pNode = pNode->right;
			}
		}
		static void lastOrderTraverse_NonRecursion(TreeNode* root)
		{
			TreeNode* pNode = root;
			while (pNode)
			{
				if (pNode->flag == 0)
				{// 子节点都未遍历
					if (pNode->left)
					{//向左
						pNode->flag = 1;
						pNode = pNode->left;
					}
					else if (pNode->right)
					{//向右
						pNode->flag = 2;
						pNode = pNode->right;
					}
					else
					{//叶子节点，输入数据，向上回溯
						printNode(pNode);
						pNode->flag = 3;
						pNode = pNode->parent;
					}
				}
				else if (pNode->flag == 1)
				{
					if (pNode->right)
					{//向右
						pNode->flag = 2;
						pNode = pNode->right;
					}
					else
					{
						//叶子节点，输入数据，向上回溯
						printNode(pNode);
						pNode->flag = 3;
						pNode = pNode->parent;
					}
				}
				else if (pNode->flag == 2)
				{
					//子节点都遍历过了，向上回溯
					printNode(pNode);
					pNode->flag = 3;
					pNode = pNode->parent;
				}
				else if (pNode->flag == 3)
				{
					//回溯节点，不可能过了
					assert(0);
				}
			}
		}

		static void lastOrderTraverse_NonRecursion1(TreeNode* root)
		{
			if (root == nullptr)
				return;

			std::stack<int> flag;
			std::stack<TreeNode*> st;
			TreeNode* pNode = root;
			while (!st.empty() || pNode)
			{
				if (pNode)
				{
					st.push(pNode);
					flag.push(1);
					pNode = pNode->left;
				}
				else
				{
					pNode = st.top();
					int f = flag.top();
					if (f == 1)
					{
						flag.pop();
						flag.push(2); //pNode 右子节点已访问
						pNode = pNode->right;
					}
					else if (f == 2)
					{
						st.pop();
						flag.pop();
						cout << setw(4) << pNode->val << ' ';
						pNode = nullptr;
					}
				}
			}
		}
		//二叉树的所有路径
		static	vector<string> binaryTreePaths(TreeNode* root)
		{
			vector<string> ret_paths;
			if (root == nullptr)
				return ret_paths;
			vector<TreeNode*> path;
			stack<int> flag;
			path.push_back(root);
			flag.push(0);
			while (path.size() > 0)
			{
				TreeNode* pNode = path.back();
				int t = flag.top();
				if (t == 0)
				{
					flag.pop();
					if (pNode->left)
					{
						flag.push(1);
						path.push_back(pNode->left);	
						flag.push(0);
						continue;
					}
					else if (pNode->right)
					{
						flag.push(2);
						path.push_back(pNode->right);
						flag.push(0);
					}
					else
					{//叶子节点
						std::string s;
						for (auto tmpNode : path)
						{
							if (!s.empty())
								s = s + "->";
							s = s + std::to_string(tmpNode->val);
						}
						ret_paths.push_back(s);
						path.pop_back();
					}
				}
				else if (t == 1)
				{
					flag.pop();
					if (pNode->right)
					{
						flag.push(2);
						path.push_back(pNode->right);
						flag.push(0);
					}
					else
					{
						path.pop_back();
					}
				}
				else if (t == 2)
				{
					flag.pop();
					path.pop_back();
				}
			}
		}
	};
}