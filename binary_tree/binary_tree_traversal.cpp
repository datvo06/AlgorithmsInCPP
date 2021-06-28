#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

class BinaryTree{
	int data;
	BinaryTree* leftChild;
	BinaryTree* rightChild;
	BinaryTree* parent;
	public:
	 	BinaryTree(int data): data(data), leftChild(NULL), rightChild(NULL){}

		void setLeft(BinaryTree* leftChild){
			leftChild->parent = this;
			this->leftChild = leftChild;
		}

		void setRight(BinaryTree* rightChild){
			rightChild->parent = this;
			this->rightChild = rightChild;
		}

		std::vector<int> preorder(){
			std::vector<int> result;
			result.push_back(data);
			if (leftChild != NULL){
				auto lefts = leftChild->preorder();
				result.insert(result.end(), lefts.begin(), lefts.end());
			}
			if (rightChild != NULL){
				auto rights = rightChild->preorder();
				result.insert(result.end(), rights.begin(), rights.end());
			}
			return result;
		}
		std::vector<int> inorder(){
			std::vector<int> result;
			if (leftChild != NULL){
				auto lefts = leftChild->inorder();
				result.insert(result.end(), lefts.begin(), lefts.end());
			}
			result.push_back(data);
			if (rightChild != NULL){
				auto rights = rightChild->inorder();
				result.insert(result.end(), rights.begin(), rights.end());
			}
			return result;
		}
	std::vector<int> postorder(){
			std::vector<int> result;
			if (leftChild != NULL){
				auto lefts = leftChild->postorder();
				result.insert(result.end(), lefts.begin(), lefts.end());
			}
			if (rightChild != NULL){
				auto rights = rightChild->postorder();
				result.insert(result.end(), rights.begin(), rights.end());
			}
			result.push_back(data);
			return result;
		}

	static std::vector<int> levelorder(BinaryTree* pRoot){
		std::vector<int> result;
		if (pRoot == NULL) return result;
		std::queue<BinaryTree*> datas;
		datas.push(pRoot);
		while (!datas.empty()){
			pRoot = datas.front();
			datas.pop();
			result.push_back(pRoot->data);
			if (pRoot->leftChild != NULL)
				datas.push(pRoot->leftChild);
			if(pRoot->rightChild != NULL)
				datas.push(pRoot->rightChild);
		}
		return result;
	}
};
