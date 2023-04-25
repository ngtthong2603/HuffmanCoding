#include<iostream>
#include<queue>
using namespace std;
typedef struct Node
{
	char data;
	unsigned frequency;
	Node* left;
	Node* right;
};
typedef struct Node* TREE;
struct frequencyCompare {
	bool operator()(Node* first, Node* second) {
		return first->frequency > second->frequency;
	}
};
void Init(TREE& root)
{
	root = NULL;
}
Node *getNode(char x, int fre) {
	Node *p = new Node();
	if (p != NULL) {
		p->data = x;
		p->frequency = fre;
		p->left = NULL;
		p->right = NULL;
	}
	return p;
}
void addList(TREE &list, int &size, unsigned &sum) {
	char input;
	unsigned fre;
	cout << "Enter your number of elements in table of characters 1: \n";
	cin >> size;
	list = new Node[size];
	for (int i = 0;i < size;i++) {
			cout << "Enter the character: ";
			cin >> input;

			cout << "Enter it's frequency: ";
			cin >> fre;
			sum += fre;
			cout << "\n";
			Node newNode = *getNode(input, fre);
			list[i] = newNode;
	}
}
priority_queue<Node*,vector<Node*>,frequencyCompare> SortNode(TREE& list, int size) {
	priority_queue<Node*, vector<Node*>, frequencyCompare> list_Queue;
	for (int i = 0;i < size;i++) {
		list_Queue.push(&list[i]);
	}
	return list_Queue;
}
Node* sumNode(Node *leftNode, Node *rightNode) {
	Node* sum = new Node();
	sum->frequency = leftNode->frequency + rightNode->frequency;
	sum->data = NULL;
	if (leftNode->frequency <= rightNode->frequency) {
		sum->left = leftNode;
		sum->right = rightNode;
	}
	else {
		sum->left = rightNode;
		sum->right = leftNode;
	}
	return sum;
}

TREE greadyTREE(TREE &root,priority_queue<Node*, vector<Node*>, frequencyCompare> &list_Queue, TREE &sumN) {
	if (list_Queue.size()==1) {
		return root;
	}
	else {
		Node *leftNode = list_Queue.top();
		list_Queue.pop();
		Node *rightNode = list_Queue.top();
		list_Queue.pop();
		sumN = sumNode(leftNode, rightNode);
		list_Queue.push(sumN);
		root = sumN;
		return greadyTREE(root, list_Queue, sumN);
	}
}
void Preorder(TREE node, string huffCode)
{
	if (node == NULL)
		return;
	if (node->left == NULL && node->right == NULL) {
		cout << node->data << "\t" << huffCode << "\n";
		huffCode = huffCode.erase(huffCode.size()-1,1);
	}
	Preorder(node->left, huffCode + "0");

	Preorder(node->right, huffCode + "1");
	
}

int main() {
	Node *list = NULL;
	int size = 0;
	unsigned sum = 0;
	string huffCode = "";
	addList(list, size, sum);
	TREE root=NULL;
	priority_queue<Node*, vector<Node*>, frequencyCompare>list_Queue = SortNode(list, size);
	TREE sumN = new Node();
	TREE huffTREE = greadyTREE(root, list_Queue, sumN);
	Preorder(huffTREE,huffCode);
	system("pause");
	return 0;
}