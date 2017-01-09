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
    int height;    //the height of the nodes subtree
    int balanceFactor;
    RAVLNode * lowestSeniority; //lowest seniority
    RAVLNode * father; //the previous node
    RAVLNode * rightSon;    //pointer to right son
    RAVLNode * leftSon; //pointer to left son

    /***************** nodes methods  ******************/
    //an empty node with no data
    RAVLNode () :
            key(0), value(0), height(0), balanceFactor(0), lowestSeniority(NULL), father(NULL), rightSon(NULL),
            leftSon(NULL) {
    };

    //a node with data and key
    RAVLNode (Y key, T value) :
            key(key), value(value), height(0), balanceFactor(0), lowestSeniority(NULL), father(NULL), rightSon(NULL),
            leftSon(NULL) {
    };

    //a fully initiated node
    RAVLNode (Y key, T data, int height, int balanceFactor, int seniority,
              int leftNumOfNodes, int rightNumOfNodes, RAVLNode * father,
              RAVLNode * rightSon, RAVLNode * leftSon) : // a "full" node
            key(key), value(data), height(height), balanceFactor(balanceFactor), lowestSeniority(
            this), father(father), rightSon(rightSon), leftSon(leftSon) {
    };

    RAVLNode (Y key, T data, int balanceFactor, RAVLNode * rightSon, RAVLNode * leftSon, int height) : // a "full" node
            key(key), value(data), height(height), balanceFactor(balanceFactor), lowestSeniority(
            this), father(NULL), rightSon(rightSon), leftSon(leftSon) {
    };

    //copy creator
    RAVLNode (const RAVLNode<Y, T> & node) {
        this->key = node.key;
        this->value = node.value;
        this->height = node.height;
        this->balanceFactor = node.balanceFactor;
        this->lowestSeniority = node.lowestSeniority;
        this->father = node.father;
        this->rightSon = node.rightSon;
        this->leftSon = node.leftSon;
    };

    //Destructor
    ~RAVLNode () {};

    // get the height of the node
    int getAndSetHeight () { // this method updates the node height and returns it
        if (NULL != leftSon && NULL != rightSon) {
            if (leftSon->getAndSetHeight() > rightSon->getAndSetHeight()) {
                height = leftSon->getAndSetHeight() + 1;
            } else {
                height = rightSon->getAndSetHeight() + 1;
            }
        } else if (NULL != leftSon) {
            height = leftSon->getAndSetHeight() + 1;
        } else if (NULL != rightSon) {
            height = rightSon->getAndSetHeight() + 1;
        } else {
            height = 0;
        }
        return height;
    };

    //update balance factor
    void updateBalanceFactor () { // updates the balance factor
        RAVLNode * tmpNode = this;
        if (NULL != leftSon && NULL != rightSon) {
            tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) - (tmpNode->rightSon->getAndSetHeight());
        } else if (NULL != leftSon) {
            tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) + 1;
        } else if (NULL != rightSon) {
            tmpNode->balanceFactor = (-1) * (tmpNode->rightSon->getAndSetHeight() + 1);
        } else {
            tmpNode->balanceFactor = 0;
        }
    };

    //get the balance factor and set it if needed
    int getBalanceFactor () { // updates and returns the balance-factor
        this->updateBalanceFactor();
        return balanceFactor;
    };

    //set the left son
    RAVLNode * setLeftSon (RAVLNode * newLeftNode) { // sets the node's left son
        if (NULL != newLeftNode) {
            newLeftNode->father = this;
        }
        leftSon = newLeftNode;
        getAndSetHeight();
        return leftSon;
    };

    //set the right son
    RAVLNode * setRightSon (RAVLNode * newRightNode) { // sets the node's right son
        if (newRightNode) {
            newRightNode->father = this;
        }
        rightSon = newRightNode;
        getAndSetHeight();
        return rightSon;
    };

    //returns true if the node is the node that we search for
    bool findByKey (const Y & iKey) { // checks if a node that goes by a the given key exists
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
    RAVLNode * returnNode (const Y & iKey) { // returns the node that goes by the given key, NULL if it doesn't exist.
        if (this->key == iKey) {
            return this;
        }
        if (this->key > iKey) {
            if (NULL == leftSon) {
                return NULL;
            }
            return leftSon->returnNode(iKey);
        }
        if (NULL == rightSon) {
            return NULL;
        }
        return rightSon->returnNode(iKey);
    };

    //swap the nodes information
    void swap (RAVLNode * nNode) { //swaps a nodes information with this one
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

    Y getKey () {
        return this->key;
    };

    T & getData () {
        return this->value;
    };

    void setKey (Y newKey) {
        this->key = newKey;
    };

    void setValue (T data) {
        this->value = data;
    };

    //return the minimal seniority among left son right son and the node
    RAVLNode<Y,T> * getMinWithCriteria (int criteria) {
        if (*this < criteria) { // can't go higher, return NULL for no fitting node found
            if (!rightSon) {
                return NULL;
            } else return rightSon->getMinWithCriteria(criteria); // go right recursively
        }

        RAVLNode<Y, T> * youngestRight = NULL;
        RAVLNode<Y, T> * youngestLeft = NULL;
        if (*this == criteria) { // starting from this, the nodes fit the criteria
            if (!rightSon) {
                return this; // this node fits and there are no bigger ones
            } else { // this and to the right, are fitting candidates
                youngestRight = rightSon->getYoungest();
                return *this < *youngestRight ? this : youngestRight;
            }
        }

        if (*this > criteria) { // this node fits, its right son fits, and maybe some on it's left fit
            if (!leftSon) { // nothing to the left, check to the right
                if (!rightSon) { // this leaf is the only one that fits
                    return this;
                } else { // this, and to the right, are the two options
                    youngestRight = rightSon->getYoungest();
                    return *this < *youngestRight ? this : youngestRight;
                }
            } else { // we have a left son
                youngestLeft = leftSon->getMinWithCriteria(criteria); // recurse to the left to find if anyone fits
                if (!rightSon) { // this node and maybe someone on the left fit
                    if (!youngestLeft) { // didn't find anyone on left, no right son, only this guy
                        return this;
                    } else { // compare left with this one
                        return *this < *youngestLeft ? this : youngestLeft;
                    }
                } else { // we have a left and right son
                    youngestRight = rightSon->getYoungest();
                    if (!youngestLeft) { // no matches on the left, compare only this and right
                        return *this < *youngestRight ? this : youngestRight;
                    } else { // we have three candidates
                        if ((*this < *youngestLeft) && (*this < *youngestRight)) { // this is the youngest that fits
                            return this;
                        } else if ((*youngestLeft < *this) &&
                                   (*youngestLeft < *youngestRight)) { // left guy is youngest
                            return youngestLeft;
                        } else if ((*youngestRight < *this) &&
                                   (*youngestRight < *youngestLeft)) { // right guy is youngest
                            return youngestRight;
                        }
                    }
                }
            }
        }
//		if (rightSon && leftSon) {
//			if (leftSon->lowestSeniority <= rightLowest) {
//				return *leftLowest <= *lowestSeniority ? *leftLowest : *lowestSeniority;
//
//			}else{
//				return *rightLowest <= *lowestSeniority ? *rightLowest : *lowestSeniority;
//			}
//		}
//
//
//		if (!rightSon && leftSon) {
//			return *leftLowest <= *lowestSeniority ? *leftLowest : *lowestSeniority;
//		}
//		if (rightSon && !leftSon) {
//			return *rightLowest < *lowestSeniority ? *rightLowest : *lowestSeniority;
//		}
        return NULL; // shouldn't happen
    };

    void setSeniority () {
//		int currSen,rightSen,leftSen;
//
//
//		if (rightSon && leftSon) {
//
//
//		}
//		if (!rightSon && leftSon) {
//
//			lowestSeniority=this->value;			}
//		if (rightSon && !leftSon) {
//
//			lowestSeniority=rightSon->lowestSeniority+1;			}
//		if (!rightSon && !leftSon){
//			*lowestSeniority= &this->value;
//
//		}
        if (!leftSon && !rightSon) { // this is a leaf
            lowestSeniority = this;
            return;
        }
        RAVLNode * minLeft = NULL; // from here on down, we know there's a son
        RAVLNode * minRight = NULL;
        if (leftSon) {
            minLeft = leftSon->getYoungest();
        } else {                    // no leftSon, compare this and rightSon
            minRight = rightSon->getYoungest();
            lowestSeniority = *this < *minRight ? this : minRight;
            return;
        }
        if (rightSon) {
            minRight = rightSon->getYoungest();
        } else {                    // no rightSon, compare this and leftSon
            lowestSeniority = *this < *minLeft ? this : minLeft;
            return;
        }

        if ((*this < *minLeft) && (*this < *minRight)) { // here there are two sons for sure
            lowestSeniority = this;
        } else if ((*minLeft < *this) && (*minLeft < *minRight)) {
            lowestSeniority = minLeft;
        } else if ((*minRight < *this) && (*minRight < *minLeft)) {
            lowestSeniority = minRight;
        }

        return;
    };

    bool operator< (const RAVLNode & rhs) {
        return this->key.isYoungerThan(rhs.key);
    }

    bool operator< (int criteria) {
        return this->key.getLevel() < criteria;
    }

    bool operator== (int criteria) {
        return this->key.getLevel() == criteria;
    }

    bool operator> (int criteria) {
        return this->key.getLevel() > criteria;
    }

    void updateNumOfNodes () {
        RAVLNode<Y, T> * iter = this;
//		iter->setSeniority();
//		while (iter->father){
//			iter=iter->father;
//			iter->setSeniority();
//		}

        do {
            iter->setSeniority();
            iter = iter->father;
        } while (iter->father);

    };

    bool operator== (RAVLNode<Y, T> * node) {
        return node->key == this->key;
    };

    RAVLNode * getYoungest () {
        return lowestSeniority;
    }

    void printNode () {
        cout << "key: " << this->key << " value: " << this->value << endl;
    }

    friend class RAVLTree<Y, T>;
};


#endif /* RAVLNODE_H_ */
