#include <iostream>
using namespace std;
typedef int DataType;
struct treeNode{
	DataType data;
	struct treeNode *left = nullptr, *right = nullptr;
};
class binarySearchTree{
private:
	treeNode* root;
	int num;
public:
	binarySearchTree() :num(0){
		root = new treeNode;
		root->left = nullptr;
		root->right = nullptr;
	}
	//�ݹ�ʵ�ֲ���
	bool find(DataType it, treeNode *root){
		if (root == nullptr) return false;

		if (root->data == it) return true;
		else if (it > root->data)
			return find(it, root->right);
		else
			return find(it, root->left);
	}
	bool findData(DataType it){
		return find(it, root);
	}
	//�ǵݹ�ʵ�ֲ���
	void insert(DataType it){
		if (num == 0){
			root->data = it;
			num++;
			return;
		}
		treeNode *p = root;
		while (p != nullptr)
		{
			if (it < p->data)
			{
				if (p->left==nullptr)
				{
					p->left = new treeNode;
					p->left->data = it;
					num++;
					return;
				}
				p = p->left;
			}
			else{//�����ڸýڵ㣬������ұ�
				if (p->right==nullptr)
				{
					p->right = new treeNode;
					p->right->data = it;
					num++;
					return;
				}
				p = p->right;
			}
		}
	}
	void delet(DataType it){
		if (root == nullptr) return;
		treeNode *p = root;
		treeNode *pp = nullptr;//pp��¼p�ĸ��ڵ�
		while (p!=nullptr&&p->data!=it)
		{
			pp = p;
			if (it < p->data) p = p->left;
			else
				p = p->right;
		}

		if (p == nullptr) { cout << "not find the data you want to delete\n"; return; }//û�ҵ�
		//ɾ���Ľڵ��������ӽڵ�
		if (p->left&&p->right)
		{
			treeNode *minp = p->right;
			treeNode *minpp = p;//��¼p�ĸ��ڵ�
			while (minp->left!=nullptr)//Ѱ����������С�ڵ�
			{
				minpp = minp;
				minp = minp->left;
			}
			p->data = minp->data;//��minp�滻��p��
			//��p����Ҷ�ڵ��ϣ�ʹ��Ҷ�ڵ㷽������ɾ��,����ִ�������ɾ��Ҷ�ڵ����
			p = minp;
			pp = minpp;
		}

		//ɾ���ڵ���Ҷ�ڵ���߽���һ���ڵ�
		treeNode* child;
		if (p->left != nullptr) child = p->left;
		else if (p->right != nullptr) child = p->right;
		else child = nullptr;
		if (pp == nullptr) root = child;//ɾ�����Ǹ��ڵ�
		else if (p == pp->left) pp->left = child;
		else pp->right = child;
		delete p;//���սڵ��ڴ�
	}
	DataType getMax(){
		if (root == nullptr) return -1;
		treeNode *p = root;
		while (p->right)
		{
			p = p->right;
		}
		return p->data;
	}
	DataType getMin(){
		if (root == nullptr) return -1;
		treeNode *p = root;
		while (p->left)
		{
			p = p->left;
		}
		return p->data;
	}
	DataType getPreNode(DataType it){
		if (root == nullptr) return -1;
		if (it == root->data) return  -1;
		treeNode *p = root;
		treeNode *pp = nullptr;
		while (p->data!=it && p!=nullptr)
		{
			pp = p;
			if (it < p->data) p = p->left;
			else p = p->right;
		}
		return (p == nullptr) ? -1 : pp->data;
	}
	DataType getPostNode(DataType it){
		if (root == nullptr) return -1;
		treeNode *p = root;
		while (it!=p->data && p!=nullptr)
		{
			if (it < p->data) p = p->left;
			else p = p->right;
		}
		if (p == nullptr) return -1;
		else if (p->left != nullptr) return p->left->data;
		else if (p->right != nullptr) return p->right->data;
		else return -1;
	}
};
int mainBST(){
	binarySearchTree myTree;
	myTree.insert(5);
	myTree.insert(4);
	myTree.insert(6);
	myTree.insert(10);
	myTree.insert(3);
	myTree.insert(8);
	myTree.insert(1);
	if (myTree.findData(3)) cout << "find\n";
	else cout << "not find\n";

	myTree.delet(3);
	
	if (myTree.findData(3)) cout << "find\n";
	else cout << "not find\n";

	cout << "max=" << myTree.getMax()<<endl;
	cout << "min=" << myTree.getMin() << endl;

	cout << "pre node of 5 is " << myTree.getPreNode(4) << endl;
	cout << "post node of 5 is " << myTree.getPostNode(4) << endl;
	return 0;
}