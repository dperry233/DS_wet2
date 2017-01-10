/*
 * RAVLTree.h
 *
 *  Created on: Dec 27, 2016
 *      Author: user
 */

#ifndef RAVLTREE_H_
#define RAVLTREE_H_

#include <iostream>
#include "RAVLNode.h"

using namespace std;

#ifndef NULL
#define NULL   ((void *) 0)
#endif


typedef enum {
    RAVLTREE_SUCCESS,
    RAVLTREE_ALLOCATION_ERROR,
    RAVLTREE_NODE_ALREADY_EXISTS,
    RAVLTREE_NODE_NOT_FOUND,
    RAVLTREE_INVALID_INPUT,
    RAVLTREE_FAILURE
} RTreeResult;

template<class Y, class T>
class RAVLTree {
/***************** tree structure  ******************/
public:
    RAVLNode<Y, T> * rootNode;
    int size;

/***************** nodes methods  ******************/
    //creator
    RAVLTree () {
        rootNode = NULL;
        size = 0;
    };

    //get the size of the tree
    int treeGetSize () {
        return size;
    }

    //get the root of the tree
    RAVLNode<Y, T> * getRoot () const {
        return rootNode;
    }

    //copy creators referaece and pointer
    RAVLTree (const RAVLTree & tTree) { // copy cTor
        this->size = tTree.size;
        this->rootNode = copyNodes(tTree.rootNode);
        updatePrevNode(this->rootNode);

        if (this->rootNode != NULL) {
            this->rootNode->father = NULL;
        }
    };

    RAVLTree (const RAVLTree * tTree) { // copy cTor
        this->size = tTree->size;
        this->rootNode = copyNodes(tTree->rootNode);
        updatePrevNode(this->rootNode);

        if (this->rootNode != NULL) {
            this->rootNode->father = NULL;
        }
    };

    //operator =
    const RAVLTree<Y, T> & operator= (const RAVLTree<Y, T> & tree) {
        if (this == &tree) {
            return *this;
        }

        this->emptyTree();

        this->size = tree.size;
        this->rootNode = copyNodes(tree.rootNode);

        updatePrevNode(this->rootNode);

        if (this->rootNode != NULL) {
            this->rootNode->father = NULL;
        }

        return *this;
    }

    //operator ==
    inline bool operator== (const RAVLTree<Y, T> & tTree) {
        return this->rootNode == tTree.rootNode;
    };

    //destructor
    ~RAVLTree () {
        emptyTree();
    };

    //create an empty tree
    void emptyTree () {
        if (!rootNode) {
            return;
        }
        RAVLNode<Y, T> * tmp = rootNode;
//		RAVLNode<Y,T>* remove = rootNode;
        while (tmp->leftSon) {
            tmp = tmp->leftSon;
        }
        RAVLNode<Y, T> ** NodesArray = new RAVLNode<Y, T> * [size]; //Array of Node*
        int i = 0;
        while (returnNextNode(tmp)) { //Saving the nodes in the array in an "In-Order" method. - O(n)
            NodesArray[i] = tmp;
            tmp = returnNextNode(tmp);
            i++;
        }
        NodesArray[i] = tmp; //Saving all the nodes in an array - O(n)
        for (int j = 0; j < size; j++) { //Deleting all of them - O(n)
            delete NodesArray[j];
        }
        delete[] NodesArray;
        size = 0;
        rootNode = NULL; //This complexity is O( n + n ) = O(n)
    };

    //update the father node
    static void updatePrevNode (RAVLNode<Y, T> * nNode) {
        if (nNode == NULL) {
            return;
        }
        if (nNode->rightSon != NULL) {
            RAVLNode<Y, T> * tmp = nNode->rightSon;
            tmp->father = nNode;
            updatePrevNode(nNode->rightSon);
        }
        if (nNode->leftSon != NULL) {
            RAVLNode<Y, T> * tmp = nNode->leftSon;
            tmp->father = nNode;
            updatePrevNode(nNode->leftSon);
        }
    };

    //copy the nodes of the tree
    static RAVLNode<Y, T> * copyNodes (RAVLNode<Y, T> * nNode) {
        if (nNode != NULL) {
            RAVLNode<Y, T> * left = copyNodes(nNode->leftSon);
            RAVLNode<Y, T> * right = copyNodes(nNode->rightSon);
            return new RAVLNode<Y, T>(nNode->key, nNode->value, nNode->balanceFactor, left, right, nNode->height);
        } else {
            return NULL;
        }
    };

    void setAsRoot (RAVLNode<Y, T> * nNode) {
        this->rootNode = copyNodes(nNode);
    };

    //creates an array out of the tree
    void inOrderToArray (RAVLNode<Y, T> * nNode, T * array, int * i) {
        if (!nNode) {
            return;
        }
        inOrderToArray(nNode->leftSon, array, i);
        array[(*i)++] = nNode->value;
        inOrderToArray(nNode->rightSon, array, i);
    };

    //return the next node inorder
    RAVLNode<Y, T> *
    returnNextNode (RAVLNode<Y, T> * node) { // returns the following node by order (according to the key)
        if (!node) {
            return NULL;
        }
        RAVLNode<Y, T> * tmp = node;
        if (!node->father) { //means he's the root.
            if (!tmp->rightSon) {
                return NULL;
            }
            tmp = tmp->rightSon;
            while (tmp->leftSon) {
                tmp = tmp->leftSon;
            }
            return tmp;
        } else if (!tmp->rightSon && (tmp->key < node->father->key)) {
            return tmp->father;
        } else if (tmp->rightSon) {
            tmp = tmp->rightSon;
            while (tmp->leftSon) {
                tmp = tmp->leftSon;
            }
            return tmp;
        } else if (!tmp->rightSon && (tmp->key > node->father->key)) {
            while (tmp->father) {
                if (tmp->key > tmp->father->key) {
                    tmp = tmp->father;
                } else {
                    return tmp->father;
                }
            }
        }
        return tmp->key > node->key ? tmp : NULL;
    };

    //function on tree inorder
    template<class Function>
    void inorder (RAVLNode<Y, T> * node, Function f) {
        if (!node) {
            return;
        }
        inorder(node->leftSon, f);
        f(node);
        inorder(node->rightSon, f);
    };

    //find max value
    T * findMax () {
        if (NULL == rootNode) {
            return NULL;
        }
        RAVLNode<Y, T> * node = rootNode;
        while (node->rightSon) {
            node = node->rightSon;
        }
        return &(node->value);
    };

    //check balance
    void checkBalance (RAVLNode<Y, T> * nNode) {
        int balanceFactor = nNode->getBalanceFactor();
        if (balanceFactor > 1) {
            if (nNode->leftSon->getBalanceFactor() < 0) {
                rotateLeft(nNode->leftSon);
            }
            rotateRight(nNode);
        } else if (balanceFactor < -1) {
            if (nNode->rightSon->getBalanceFactor() > 0) {
                rotateRight(nNode->rightSon);
            }
            rotateLeft(nNode);
        }
    };

    //rotate right
    void rotateRight (RAVLNode<Y, T> * nNode) {
        RAVLNode<Y, T> * parent = nNode->father;
        int flag;
        if (NULL != parent) {
            flag = parent->leftSon == nNode ? 1 : 2;
        }
        RAVLNode<Y, T> * tmpNode = nNode->leftSon;
        nNode->setLeftSon(tmpNode->rightSon);
        tmpNode->setRightSon(nNode);
        if (NULL != parent) {
            if (flag == 1) {
                parent->leftSon = tmpNode;
            } else {
                parent->rightSon = tmpNode;
            }
        } else {
            rootNode = tmpNode;
            if (rootNode) {
                rootNode->father = NULL;
            }
        }
        tmpNode->father = parent;

        nNode->setSeniority();
        nNode->updateBalanceFactor();
        tmpNode->setSeniority();
        tmpNode->updateBalanceFactor();
        if (parent) {
            parent->setSeniority();
            parent->updateBalanceFactor();
        }

    };

    //rotate left
    void rotateLeft (RAVLNode<Y, T> * nNode) {
        RAVLNode<Y, T> * parent = nNode->father;
        int flag;
        if (NULL != parent) {
            flag = parent->leftSon == nNode ? 1 : 2;
        }
        RAVLNode<Y, T> * tmp = nNode->rightSon;
        nNode->setRightSon(tmp->leftSon);
        tmp->setLeftSon(nNode);
        if (NULL != parent) {
            if (flag == 1) {
                parent->setLeftSon(tmp);
            } else {
                parent->setRightSon(tmp);
            }
        } else {
            rootNode = tmp;
            if (rootNode) {
                rootNode->father = NULL;
            }
        }
        tmp->father = parent;

        nNode->setSeniority();
        nNode->updateBalanceFactor();
        tmp->setSeniority();
        tmp->updateBalanceFactor();
        if (parent) {
            parent->setSeniority();
            parent->updateBalanceFactor();
        }
    };

    bool findIfValueExists (const Y & iKey);

    RTreeResult insertData (const Y & iKey, T data);

    RTreeResult removeValue (const Y & iKey);

    RAVLNode<Y, T> * returnRoot () {
        return rootNode;
    };

    RAVLNode<Y, T> * getNodeByKey (const Y & iKey);

    T * getValue (const Y & iKey);


    void RprintTree (RAVLNode<Y, T> * nNode) {
        if (!nNode) {
            return;
        }
        RprintTree(nNode->leftSon);
        nNode->printNode();
        RprintTree(nNode->rightSon);
    }

    T * findYoungestBiggerThan (int criteria);
};

template<class Y, class T>
bool RAVLTree<Y, T>::findIfValueExists (const Y & iKey) {
    if (!rootNode) { //nothing in the tree
        return false;
    }
    return rootNode->findByKey(iKey);
}

template<class Y, class T>
RAVLNode<Y, T> * RAVLTree<Y, T>::getNodeByKey (const Y & iKey) {
    if (NULL == rootNode) {
        return NULL; //The tree is empty
    }
    return rootNode->returnNode(iKey);
}

template<class Y, class T>
T * RAVLTree<Y, T>::getValue (const Y & iKey) {
    if (!this->findIfValueExists(iKey)) {
        return NULL;
    }
    return &(rootNode->returnNode(iKey)->value);
}

template<class Y, class T>
RTreeResult RAVLTree<Y, T>::insertData (const Y & iKey, T data) {
    if (NULL == rootNode) {
        try {
            rootNode = new RAVLNode<Y, T>(iKey, data);
        }
        catch (std::bad_alloc &) {
            return RAVLTREE_ALLOCATION_ERROR;
        }
        size++;
        return RAVLTREE_SUCCESS;
    }
    RAVLNode<Y, T> * tmpNode = rootNode;
    RAVLNode<Y, T> * newNode;
    while (1) { //while (true)
        if (tmpNode->key > iKey) {
            if (!tmpNode->leftSon) {
                newNode = new RAVLNode<Y, T>(iKey, data);
                tmpNode->setLeftSon(newNode);
                break;
            } else {
                tmpNode = tmpNode->leftSon;
            }
        } else if (tmpNode->key < iKey) {
            if (!tmpNode->rightSon) {
                newNode = new RAVLNode<Y, T>(iKey, data);
                tmpNode->setRightSon(newNode);
                break;
            } else {
                tmpNode = tmpNode->rightSon;
            }
        } else {

            return RAVLTREE_NODE_ALREADY_EXISTS;

        }
    }
    tmpNode = newNode;
    newNode->updateSeniority();
    while (tmpNode) { //updating the node ruined path
        tmpNode->getAndSetHeight(); //Updating the height
        tmpNode->updateBalanceFactor();
        checkBalance(tmpNode);
        if (tmpNode == rootNode) {
            break;
        }
        tmpNode = tmpNode->father;
    }
    size++;
    return RAVLTREE_SUCCESS;
}

template<class Y, class T>
RTreeResult RAVLTree<Y, T>::removeValue (const Y & iKey) {
    if (!rootNode || !findIfValueExists(iKey)) {
        return RAVLTREE_NODE_NOT_FOUND;
    }
    /*else if (size == 1) { // TODO: testing debug solution
        delete rootNode;
        size--;
        rootNode = NULL;
        return RAVLTREE_SUCCESS;
    }*/
    RAVLNode<Y, T> * parent = NULL;
    RAVLNode<Y, T> * tmp = rootNode->returnNode(iKey);
    RAVLNode<Y, T> * replace = NULL;
    if (tmp->father) {
        parent = tmp->father;
    }
    if (!tmp->leftSon && !tmp->rightSon) { //if this node is a leaf
        if (parent) {
            if (parent->key < tmp->key) { //then tmp is a right son.
                parent->rightSon = NULL;
            } else {
                parent->leftSon = NULL;
            }
            delete tmp;
            parent->updateSeniority();
            while (parent) {
                parent->getAndSetHeight();
                parent->updateBalanceFactor();
                checkBalance(parent);
                parent = parent->father;
            }
        } else { //then this one is the root. // TODO: check if commenting out delete tmp does the trick
            rootNode = NULL;
            delete tmp;
        }
    } else if (!tmp->rightSon) {
        if (parent) {
            if (parent->key < tmp->key) { //then tmp is a right son.
                parent->setRightSon(tmp->leftSon);
            } else {
                parent->setLeftSon(tmp->leftSon);
            }
            delete tmp;
            parent->updateSeniority();
            while (parent) {
                parent->getAndSetHeight();
                parent->updateBalanceFactor();
                checkBalance(parent);
                parent = parent->father;
            }
        } else {
            rootNode = tmp->leftSon;
            tmp->leftSon->father = NULL;
            delete tmp;
            rootNode->updateSeniority();
        }
    } else if (!tmp->leftSon) {
        if (parent) {
            if (parent->key < tmp->key) { //then tmp is a right son.
                parent->setRightSon(tmp->rightSon);
            } else {
                parent->setLeftSon(tmp->rightSon);
            }
            delete tmp;
            parent->updateSeniority();
            while (parent) {
                parent->getAndSetHeight();
                parent->updateBalanceFactor();
                checkBalance(parent);
                parent = parent->father;
            }
        } else {
            rootNode = tmp->rightSon;
            tmp->rightSon->father = NULL;
            delete tmp;
            rootNode->updateSeniority();
        }
    } else {
        replace = tmp->rightSon;
        while (replace->leftSon) {
            replace = replace->leftSon;
        }
        //tmp->swap(replace); TODO: We swap pointers instead of doing a value and key swap
        // replace is the following node
        // tmp is the one to be deleted
        RAVLNode<Y, T> * swap;
        swap = tmp->father;
        tmp->father = replace->father;
        replace->father = swap;
        if (tmp->father == tmp) {
            (tmp->father = replace);
        }

        swap = tmp->leftSon;
        tmp->leftSon = replace->leftSon;
        replace->leftSon = swap;

        swap = tmp->rightSon;
        tmp->rightSon = replace->rightSon;
        replace->rightSon = swap;
        if (replace->rightSon == replace) { // if switching between father and right son
            replace->rightSon = tmp;
        }// now replace is in the right place but his friends don't know yet
        // and tmp is in the place of his follower and needs to be deleted

        if (replace->father) {
            if (replace->father->rightSon->key == tmp->key) { // this guy is the right son because temp was the right
                replace->father->rightSon = replace;
            } else replace->father->leftSon = replace;
        }

        if (replace->rightSon) {
            replace->rightSon->father = replace;
        }

        if (replace->leftSon) {
            replace->leftSon->father = replace;
        }

//        if (tmp->father) {
//            if (tmp->father->rightSon->key == replace->key) { // to be deleted is the right son
//                tmp->father->rightSon = tmp;
//            } else tmp->father->leftSon = tmp;
//        }

        if (tmp->rightSon) {
            tmp->rightSon->father = tmp;
        }

        parent = tmp->father;
        if (parent->rightSon) {
            if (parent->rightSon->key == tmp->key) {
                parent->setRightSon(tmp->rightSon);
            } else {
                parent->setLeftSon(tmp->rightSon);
            }
        } else {
            parent->setLeftSon(tmp->rightSon);
        }

        delete tmp;
        parent->updateSeniority();
        while (parent) {
            parent->getAndSetHeight();
            parent->updateBalanceFactor();
            checkBalance(parent);
            parent = parent->father;
        }
    }
    size--;
    if (replace != NULL && !replace->father) {
        this->rootNode = replace;
    }
    return RAVLTREE_SUCCESS;
}


template<class Y, class T>
void inOrderToArray (RAVLNode<Y, T> * nNode, T * array, int * i) {
    if (!nNode) {
        return;
    }
    inOrderToArray(nNode->leftSon, array, i);
    array[(*i)++] = nNode->value;
    inOrderToArray(nNode->rightSon, array, i);
}



template<class Y, class T>
T * RAVLTree<Y, T>::findYoungestBiggerThan (int criteria) {
    if (!rootNode) {
        return NULL;
    }
    RAVLNode<Y, T> * youngNode = rootNode->getMinWithCriteria(criteria);
    if (!youngNode) {
        return NULL;
    }
    return &(youngNode->value);
};


#endif /* RAVLTREE_H_ */
