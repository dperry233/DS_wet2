/*
 * RAVLNode.h
 *
 *  Created on: Dec 27, 2016
 *      Author: user
 */

#ifndef RAVLNODE_H_
#define RAVLNODE_H_

#include <iostream>
#ifndef NULL
#define NULL   ((void *) 0)
#endif

using namespace std;

template<class Y, class T>
class RAVLTree;
template<class Y, class T>
class RAVLNode {
public:
	/***************** nodes structure  ******************/
	Y key; // the key is the way we will sort and manage the nodes
	T value; // the value is the data inside the node
	int height;	//the height of the nodes subtree
	int balanceFactor;
	T* lowestSeniority; //lowest seniority
	T* leftLowest;//leftNumOfNodes;	//left subtree max rate
	T* rightLowest;//rightNumOfNodes;	//right subtree max rate
	RAVLNode* father; //the previous node
	RAVLNode* rightSon;	//pointer to right son
	RAVLNode* leftSon; //pointer to left son

	/***************** nodes methods  ******************/
	//an empty node with no data
	RAVLNode() :
			key(0), value(0), height(0), balanceFactor(0), lowestSeniority(NULL), leftLowest(
					NULL), rightLowest(NULL), father(NULL), rightSon(NULL), leftSon(
			NULL) {
	}
	;
	//a node with data and key
	RAVLNode(Y key, T value) :
			key(key), value(value), height(0), balanceFactor(0), lowestSeniority(NULL), leftLowest(
					NULL), rightLowest(NULL), father(NULL), rightSon(NULL), leftSon(
			NULL) {
	}
	;
	//a fully initiated node
	RAVLNode(Y key, T data, int height, int balanceFactor, int seniority,
			int leftNumOfNodes, int rightNumOfNodes, RAVLNode* father,
			RAVLNode* rightSon, RAVLNode* leftSon) : // a "full" node
			key(key), value(data), height(height), balanceFactor(balanceFactor), lowestSeniority(
					seniority), leftLowest(leftLowest), rightLowest(rightLowest), father(
					father), rightSon(rightSon), leftSon(leftSon) {
	}
	;
	RAVLNode(Y key, T data, int balanceFactor, RAVLNode* rightSon, RAVLNode* leftSon, int height) : // a "full" node
			key(key), value(data), height(height), balanceFactor(balanceFactor), lowestSeniority(
					NULL), leftLowest(NULL), rightLowest(NULL), father(
					NULL), rightSon(rightSon), leftSon(leftSon) {
	}
	;
	//copy creator
	RAVLNode(const RAVLNode<Y, T>& node) {
		this->key = node.key;
		this->value = node.value;
		this->height = 0;
		this->balanceFactor = 0;
		this->lowestSeniority = node.lowestSeniority;
		this->leftLowest = node.leftLowest;
		this->rightLowest = node.rightLowest;
		this->father = NULL;
		this->rightSon = NULL;
		this->leftSon = NULL;
	}
	;
	//Destructor
	~RAVLNode(){};
	// get the height of the node
	int getAndSetHeight() { // this method updates the node height and returns it
		if (NULL != leftSon && NULL != rightSon) {
			if (leftSon->getAndSetHeight() > rightSon->getAndSetHeight()) {
				height = leftSon->getAndSetHeight() + 1;
			}
			else {
				height = rightSon->getAndSetHeight() + 1;
			}
		}
		else if (NULL != leftSon) {
			height = leftSon->getAndSetHeight() + 1;
		}
		else if (NULL != rightSon) {
			height = rightSon->getAndSetHeight() + 1;
		}
		else {
			height = 0;
		}
		return height;
	};
	//update balance factor
	void updateBalanceFactor() { // updates the balance factor
		RAVLNode* tmpNode = this;
		if (NULL != leftSon && NULL != rightSon) {
			tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) - (tmpNode->rightSon->getAndSetHeight());
		}
		else if (NULL != leftSon) {
			tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) + 1;
		}
		else if (NULL != rightSon) {
			tmpNode->balanceFactor = (-1) * (tmpNode->rightSon->getAndSetHeight() + 1);
		}
		else {
			tmpNode->balanceFactor = 0;
		}
	};
	//get the balance factor and set it if needed
	int getBalanceFactor() { // updates and returns the balance-factor
		this->updateBalanceFactor();
		return balanceFactor;
	};
	//set the left son
	RAVLNode* setLeftSon(RAVLNode* newLeftNode) { // sets the node's left son
		if (NULL != newLeftNode) {
			newLeftNode->father = this;
		}
		leftSon = newLeftNode;
		getAndSetHeight();
		return leftSon;
	};
	//set the right son
	RAVLNode* setRightSon(RAVLNode* newRightNode) { // sets the node's right son
		if (newRightNode) {
			newRightNode->father = this;
		}
		rightSon = newRightNode;
		getAndSetHeight();
		return rightSon;
	};
	//returns true if the node is the node that we search for
	bool findByKey(const Y& iKey) { // checks if a node that goes by a the given key exists
		if (this->key == iKey) {
			return true;
		}
		if (this->key > iKey) {
			if (NULL == leftSon) {
				return false;
			}
			return leftSon->findByKey(iKey);
		}
		if (NULL == rightSon) {
			return false;
		}
		return rightSon->findByKey(iKey);
	};
	// returns the node with the key given
	RAVLNode* returnNode(const Y& iKey) { // returns the node that goes by the given key, NULL if it doesn't exist.
		if (this->key == iKey) {
			return this;
		}
		if (this->key > iKey) {
			if (NULL == leftSon) {
				return NULL;
			}
			return leftSon->returnNode(iKey);
		}
		if (NULL ==rightSon) {
			return NULL;
		}
		return rightSon->returnNode(iKey);
	};
	//swap the nodes information
	void swap(RAVLNode* nNode) { //swaps a nodes information with this one
		if (!nNode) {
			return;
		}
		Y tmpKey = nNode->key;
		nNode->key = key;
		key = tmpKey;
		T tmpValue = nNode->value;
		nNode->value = value;
		value = tmpValue;
	};
	Y getKey() {
		return this->key;
	};
	T& getData() {
		return this->value;
	};
	void setKey(Y newKey) {
		this->key = newKey;
	};
	void setValue(T data) {
		this->value = data;
	};

	//return the minimal seniority among left son right son and the node
	int getMin(){

		if (rightSon && leftSon) {
			if (leftLowest <= rightLowest) {
				return *leftLowest <= *lowestSeniority ? *leftLowest : *lowestSeniority;

				}else{
					return *rightLowest <= *lowestSeniority ? *rightLowest : *lowestSeniority;
				}
			}


			if (!rightSon && leftSon) {
				return *leftLowest <= *lowestSeniority ? *leftLowest : *lowestSeniority;
			}
			if (rightSon && !leftSon) {
				return *rightLowest < *lowestSeniority ? *rightLowest : *lowestSeniority;
			}
			return *lowestSeniority;
	};

	void setSeniority(){
		if (rightSon && leftSon) {
			rightLowest=rightSon->lowestSeniority;
			leftLowest=leftSon->lowestSeniority;
			lowestSeniority=&(this->value);
		}
			if (!rightSon && leftSon) {
				rightLowest=NULL;
				leftLowest=leftSon->lowestSeniority;
				lowestSeniority=this->value;			}
			if (rightSon && !leftSon) {
				rightLowest=rightSon->lowestSeniority;
				leftLowest=0;
				lowestSeniority=rightSon->lowestSeniority+1;			}
			if (!rightSon && !leftSon){
				rightLowest=-1;
				leftLowest=0;
				lowestSeniority=1;
			}
	};
	void updateNumOfNodes(){
		RAVLNode<Y,T>* iter=this;
		iter->setSeniority();
		while (iter->father){
			iter=iter->father;
			iter->setSeniority();
		}

	};
	bool operator==(RAVLNode<Y,T>* node){
		if (node->key== this->key){
		return true;
		}
		return false;
	};
	 void printNode(){
		 cout << "key: " ;
		 this->key;
		 cout<< " value: " ;
		 this->value;
		 cout<<endl;
	 }
	friend class RAVLTree<Y,T>;
};


#endif /* RAVLNODE_H_ */
