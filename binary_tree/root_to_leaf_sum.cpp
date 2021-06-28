#include <iostream>
#include <vector>

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

		BinaryTree* getLeft(){
			return leftChild;
		}

		BinaryTree* getRight(){
			return rightChild;
		}

		int getData(){
			return data;
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

};

bool rootToLeafSum(BinaryTree* root, int sum, std::vector<int>& result){
	if (root == NULL) return false;
	if (root->getLeft() == NULL && root->getRight() == NULL){
		if (root->getData() == sum){
			result.push_back(root->getData());
			return true;
		} else return false;
	}
	if (rootToLeafSum(root->getLeft(), sum -root->getData(), result)){
			result.push_back(root->getData());
			return true;
	}
	return false;
}
