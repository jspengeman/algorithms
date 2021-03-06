#include <iostream>
using namespace std;

class Node {
public:
	Node(int data){ 
		this->nodeCount = 1;
		this->data = data; 
		this->LeftChild = NULL;
		this->RightChild = NULL;
	};
	int data;
	int nodeCount;
	Node* LeftChild;
	Node* RightChild;

};

class BST {
private:
	int count;
	Node* root;

public:
	BST();
	Node* getRoot(){ return this->root; };
	void printTree(Node *root);
	void InsertNode(int data);
	bool FindNode(int data);
	int kthSmallest(Node *node, int k);
	int keysBetween(int start, int end);
	void keysBetweenPrime(Node *root, int start, int end, int *count);
};
