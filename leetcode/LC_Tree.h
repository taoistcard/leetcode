#pragma once
#include "LC_Base.h"
namespace LeetCode{
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode() : val(0), left(NULL), right(NULL) {}
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
	class Solution105 {
	public:
/*
		根据一棵树的前序遍历与中序遍历构造二叉树。
		注意:
		你可以假设树中没有重复的元素。
		例如，给出
		前序遍历 preorder = [3,9,20,15,7]
		中序遍历 inorder = [9,3,15,20,7]
		返回如下的二叉树：
			 3
			/ \
		   9  20
			 /  \
			15   7
		通过次数86,500提交次数128,813
*/
		TreeNode* buildTree(std::map<int, int>& pre_index_val_map, vector<int>& inorder) {
			if (pre_index_val_map.empty() || inorder.empty())
				return nullptr;
			if (pre_index_val_map.size() != inorder.size())
				return nullptr;

			//int root_index = -1;
			auto it = pre_index_val_map.begin();
			int root_val = it->second;
			
			std::map<int, int> pre_val_index_map;
			for (auto& pr : pre_index_val_map)
			{
				pre_val_index_map[pr.second] = pr.first;
			}

			TreeNode* pRoot = new TreeNode(root_val);
			std::map<int, int> preorder_i_v_left, preorder_i_v_right;
			vector<int> inorder_left, inorder_right;

			bool found = false;
			for (int i = 0; i < inorder.size(); i++)
			{
				if (inorder[i] == root_val)
				{
					found = true;
				}
				else if (found)
				{
					int index = pre_val_index_map[inorder[i]];
					preorder_i_v_right[index] = inorder[i];
					inorder_right.push_back(inorder[i]);
				}
				else
				{
					int index = pre_val_index_map[inorder[i]];
					preorder_i_v_left[index] = inorder[i];
					inorder_left.push_back(inorder[i]);
				}
			}
			pRoot->left = buildTree(preorder_i_v_left, inorder_left);
			pRoot->right = buildTree(preorder_i_v_right, inorder_right);
			return pRoot;
		}

		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || inorder.empty())
				return nullptr;
			std::map<int, int> pre_index_val_map;
			for (int i = 0; i < preorder.size(); i++)
			{
				pre_index_val_map[i] = preorder[i];
			}
			TreeNode* pRoot = buildTree(pre_index_val_map, inorder);
			return pRoot;
		}

		TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder, int pl, int pr, int il, int ir)
		{
			if (preorder.size() != inorder.size() || inorder.empty())
				return nullptr;
			
			TreeNode* pNode = new TreeNode(preorder[pl]);
			if (pl == pr)
			{
				return pNode;
			}
			int idx = m_index[preorder[pl]]; //根节点位置
			int left_count = idx - il; //左子树节点数
			if (left_count > 0)
				pNode->left = buildTree(preorder, inorder, pl + 1, pl + 1 + left_count - 1, il, il + left_count - 1);
			int right_count = ir - idx;
			if (right_count > 0)
				pNode->right = buildTree(preorder, inorder, pl + 1 + left_count - 1 + 1, pr, il + left_count + 1, ir);
			return pNode;
		}
		TreeNode* buildTree2(vector<int>& preorder, vector<int>& inorder) {
			if (preorder.empty() || inorder.empty())
				return nullptr;
			for (int i = 0; i < inorder.size(); i++)
			{
				m_index[inorder[i]] = i;
			}
			TreeNode* pRoot = buildTree(preorder, inorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
			return pRoot;
		}
	public:
		std::unordered_map<int, int> m_index;
	public:
		static void test()
		{
			Solution105 sol;
			std::vector<int> preorder = { 3, 9, 20, 15, 7 };
			std::vector<int> inorder = { 9, 3, 15, 20, 7 };
			TreeNode* pRoot = sol.buildTree2(preorder, inorder);
		}
	};

	
	REG_TEST(105);

	class Solution297 {
	public:
		/**
		序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

		请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

		示例: 

		你可以将以下二叉树：

			 1
			/ \
		   2   3
			  / \
			 4   5

		序列化为 "[1,2,3,null,null,4,5]"
		提示: 这与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

		说明: 不要使用类的成员 / 全局 / 静态变量来存储状态，你的序列化和反序列化算法应该是无状态的

		来源：力扣（LeetCode）
		链接：https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree
		著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
		*/
		// Encodes a tree to a single string.
		string serialize(TreeNode* root) {
			vector<string> vals;
			std::vector<TreeNode*> st{root};
			while (!st.empty())
			{
				if (st[0] == nullptr)
				{
					vals.push_back("null");
				}
				else
				{
					vals.push_back(std::to_string(st[0]->val));
					st.push_back(st[0]->left);
					st.push_back(st[0]->right);
				}
				st.erase(st.begin());
			}
			std::stringstream ss;
			ss << "[";
			for (int i = 0; i < vals.size(); i++)
			{
				if (i != 0)
					ss << ",";
				ss << vals[i];
			}
			ss << "]";
			return ss.str();
		}
		// Decodes your encoded data to tree.
		TreeNode* deserialize(string data) {
			int i = 0;
			int s = -1, e = -1;
			int val = 0;
			int flag = 0;// 1,-1表示正负号;0表示没有找到数字，应该输出null
			bool not_num = false;

			std::vector<TreeNode*> tree;
			while (i < data.length())
			{
				char ch = data[i++];
				if (not_num && ch != ',')
				{
					continue;
				}
				if (ch == '[')
					continue;

				if (ch == '-')
				{
					flag = -1;
					continue;
				}
				if (ch >= '0' && ch <= '9')
				{
					if (flag == 0)
					{
						flag = 1;
						not_num = false;
					}

					val = val * 10 + ch - '0';
				}
				else if (ch == ',' || ch == ']')
				{
					if (flag == 0)
					{
						std::cout << "val = null" << std::endl;
						not_num = false;
						tree.push_back(nullptr);
					}
					else
					{
						val *= flag;
						std::cout << "val = " << val << std::endl;
						TreeNode* node = new TreeNode(val);
						tree.push_back(node);
						flag = 0;
						val = 0;
					}
					if (ch == ']')
						break;
				}
				else
				{
					flag = 0;
					not_num = true;
				}
			}
			for (unsigned int i = 0; i < tree.size()/2; i++)
			{
				if (tree[i] == nullptr)
					continue;
				int left = 2 * i + 1;
				if (left < tree.size())
					tree[i]->left = tree[left];
				if (left + 1< tree.size())
					tree[i]->right = tree[left + 1];
			}
			return tree.size() > 0 ? tree[0] : nullptr;
		}
	public:
		static void test()
		{
			Solution297 sol;
			string s = "[1,2,3,null,null,4,5]";
			TreeNode* root = sol.deserialize(s);
			string res = sol.serialize(root);
			std::cout << res << std::endl;
		}
	};

	REG_TEST(297);

	/**
	* Definition for a binary tree node.
	* struct TreeNode {
	*     int val;
	*     TreeNode *left;
	*     TreeNode *right;
	*     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	* };
	*/
	class Solution1028 {
	public:
		/*
		*/
		TreeNode* recoverSubTree(string& S, int& i, int depth)
		{
			if (i >= S.length())
				return NULL;
			int v = 0;
			int d = 0;
			bool reach_num = false;
			int tmp = i;
			//for (; i < S.lenght(); i++)
			while (i < S.length())
			{
				if (S[i] == '-')
				{
					if (reach_num)
						break;
					d++;
				}
				else
				{
					if (d <= depth)
					{
						i = tmp;
						return NULL;
					}
					reach_num = true;
					v = v * 10 + S[i] - '0';
				}
				++i;
			}
			TreeNode* pNode = new TreeNode(v);
			pNode->left = recoverSubTree(S, i, d);
			pNode->right = recoverSubTree(S, i, d);
			return pNode;
		}
		TreeNode* recoverFromPreorder(string S) {
			int i = 0;
			TreeNode* root = recoverSubTree(S, i, -1);
			return root;
		}
	public:
		static void test()
		{
			Solution1028 sol;
			string s = "1-2--3---4-5--6---7";
			TreeNode* root = sol.recoverFromPreorder(s);
		}
	};
	REG_TEST(1028);
}