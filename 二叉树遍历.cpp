#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void make_tree(TreeNode *root, TreeNode *left, TreeNode *right)
{
	root->left = left;
	root->right = right;
}

vector<int> inorderTraversal(TreeNode* root) {
	vector<int> traverse;
	stack<TreeNode*> s1;
	if (root == nullptr)
		return traverse;
	TreeNode* cur = root;
	TreeNode* last = nullptr;
	while (cur != nullptr || !s1.empty())
	{
		while (cur != nullptr)//如果cur非空，则入栈
		{
			s1.push(cur);
			cur = cur->left;
		}
		cur = s1.top();//cur为空，结点出栈，右节点进栈,判断右节点是否已访问决定是否进栈
		if (cur->right != nullptr && last != cur->right)
			cur = cur->right;
		else if (cur->right == nullptr || last == cur->right)
		{
			traverse.push_back(cur->val);
			last = cur;//记录上一次访问的结点
			s1.pop();
			cur = nullptr;
		}
		
	}
	for (vector<int>::iterator it = traverse.begin(); it != traverse.end(); it++)
		cout << *it << " ";
	cout << endl;
	return traverse;
}


int main(int argc, char* argv[])
{
	TreeNode *one = new TreeNode(1);
	TreeNode *two = new TreeNode(4);
	TreeNode * three = new TreeNode(3);
	TreeNode *four = new TreeNode(5);
	TreeNode *five = new TreeNode(2);
	make_tree(one, two, three);
	make_tree(two, nullptr, four);
	make_tree(three, five, nullptr);
	inorderTraversal(one);

	return 0;
}