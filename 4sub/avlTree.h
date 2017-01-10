/*
 * AVLTree.h
 *
 *  Created on: Nov 27, 2016
 *      Author: user
 */

#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <iostream>
#include <cmath>


template<class keyType, class dataType>
class AVLNode {
public:
    AVLNode<keyType, dataType> * father;
    AVLNode<keyType, dataType> * rightSon;
    AVLNode<keyType, dataType> * leftSon;
    keyType key;
    dataType value;
    int height;
    int balanceFactor;

    AVLNode () :
            father(NULL),
            rightSon(NULL),
            leftSon(NULL),
            key(0),
            height(0),
            balanceFactor(0) {}

    AVLNode (keyType iKey, dataType tData) :
            father(NULL),
            rightSon(NULL),
            leftSon(NULL),
            key(iKey),
            value(tData),
            height(0),
            balanceFactor(0) {}

    AVLNode (keyType iKey, dataType tData, int iBalanceFactor, AVLNode * nLeftSon, AVLNode * nRightSon, AVLNode * nPrev,
             int iHeight) : // a "full" node
            key(iKey),
            value(tData),
            balanceFactor(iBalanceFactor),
            height(iHeight),
            father(nPrev),
            rightSon(nRightSon),
            leftSon(nLeftSon) {}

    AVLNode (keyType iKey, dataType tData, int iBalanceFactor, AVLNode * nLeftSon, AVLNode * nRightSon, int iHeight) :
            father(NULL),
            rightSon(nRightSon),
            leftSon(nLeftSon),
            key(iKey),
            value(tData),
            height(iHeight),
            balanceFactor(iBalanceFactor) {}

    AVLNode (const AVLNode<keyType, dataType> & nNode) :
            father(nNode.father),
            rightSon(nNode.rightSon),
            leftSon(nNode.leftSon),
            key(nNode.key),
            value(nNode.value),
            height(nNode.height),
            balanceFactor(nNode.balanceFactor) {}

    int getAndSetHeight () {
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
    }

    int getBalanceFactor () {
        this->updateBalanceFactor();
        return balanceFactor;
    }

    void updateBalanceFactor () {
        AVLNode<keyType, dataType> * tmpNode = this;
        if (NULL != leftSon && NULL != rightSon) {
            tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) - (tmpNode->rightSon->getAndSetHeight());
        } else if (NULL != leftSon) {
            tmpNode->balanceFactor = (tmpNode->leftSon->getAndSetHeight()) + 1;
        } else if (NULL != rightSon) {
            tmpNode->balanceFactor = (-1) * (tmpNode->rightSon->getAndSetHeight() + 1);
        } else {
            tmpNode->balanceFactor = 0;
        }
    }

    AVLNode<keyType, dataType> * setLeftSon (AVLNode<keyType, dataType> * newLeftNode) {
        if (NULL != newLeftNode) {
            newLeftNode->father = this;
        }
        leftSon = newLeftNode;
        getAndSetHeight();
        return leftSon;
    }

    AVLNode<keyType, dataType> * setRightSon (AVLNode<keyType, dataType> * newRightNode) {
        if (newRightNode) {
            newRightNode->father = this;
        }
        rightSon = newRightNode;
        getAndSetHeight();
        return rightSon;
    }

    bool findByKey (keyType & iKey) {
        if (this->key == iKey) {
            return true;
        }
        if (this->key > iKey) {
            return NULL != leftSon && leftSon->findByKey(iKey);
        }
        return NULL != rightSon && rightSon->findByKey(iKey);
    }

    AVLNode<keyType, dataType> * returnNode (keyType iKey) {
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
    }

    void swap (AVLNode<keyType, dataType> * nNode) {
        if (!nNode) {
            return;
        }
        keyType tmpKey = nNode->key;
        nNode->key = key;
        key = tmpKey;
        dataType tmpValue = nNode->value;
        nNode->value = value;
        value = tmpValue;
    }

    void emptySubTree (AVLNode<keyType, dataType> * nNode) {
        if (!nNode) {
            return;
        }

        emptySubTree(nNode->leftSon);
        emptySubTree(nNode->rightSon);
        delete nNode;
    }

};


typedef enum {
    AVLTREE_SUCCESS, AVLTREE_ALLOCATION_ERROR, AVLTREE_NODE_ALREADY_EXISTS, AVLTREE_NODE_NOT_FOUND
} TreeResult;

typedef enum {
    RIGHT, LEFT
} Direction;

template<class keyType, class dataType>
class AVLTree {
public:
    AVLNode<keyType, dataType> * rootNode;
    int size;

    static AVLNode<keyType, dataType> * copyNodes (AVLNode<keyType, dataType> * nNode) {
        if (nNode != NULL) {
            AVLNode<keyType, dataType> * left = copyNodes(nNode->leftSon);
            AVLNode<keyType, dataType> * right = copyNodes(nNode->rightSon);
            return new AVLNode<keyType, dataType>(nNode->key, nNode->value, nNode->balanceFactor, left, right,
                                                  nNode->height);
        } else {
            return NULL;
        }
    }

    static void updatePrevNode (AVLNode<keyType, dataType> * nNode) {
        if (nNode == NULL) {
            return;
        }
        if (nNode->rightSon != NULL) {
            AVLNode<keyType, dataType> * tmp = nNode->rightSon;
            tmp->father = nNode;
            updatePrevNode(nNode->rightSon);
        }
        if (nNode->leftSon != NULL) {
            AVLNode<keyType, dataType> * tmp = nNode->leftSon;
            tmp->father = nNode;
            updatePrevNode(nNode->leftSon);
        }
    }

    AVLTree (const AVLTree & tTree) { // copy cTor
        this->size = tTree.size;
        this->rootNode = copyNodes(tTree.rootNode);
        updatePrevNode(this->rootNode);

        if (this->rootNode != NULL) {
            this->rootNode->father = NULL;
        }
    }

    AVLTree (const AVLTree * tTree) { // copy cTor
        this->size = tTree->size;
        this->rootNode = copyNodes(tTree->rootNode);
        updatePrevNode(this->rootNode);

        if (this->rootNode != NULL) {
            this->rootNode->father = NULL;
        }
    }

    const AVLTree<keyType, dataType> & operator= (const AVLTree & tree) {
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

    AVLTree () {
        rootNode = NULL;
        size = 0;
    }

    inline bool operator== (const AVLTree<keyType, dataType> & tTree) {
        return this->rootNode == tTree.rootNode;
    }

    void rotateRight (AVLNode<keyType, dataType> * nNode) {
        AVLNode<keyType, dataType> * parent = nNode->father;
        int flag;
        if (NULL != parent) {
            flag = parent->leftSon == nNode ? 1 : 2;
        }
        AVLNode<keyType, dataType> * tmpNode = nNode->leftSon;
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
                return;
            }
        }
        tmpNode->father = parent;
    }

    void rotateLeft (AVLNode<keyType, dataType> * nNode) {
        AVLNode<keyType, dataType> * parent = nNode->father;
        int flag;
        if (NULL != parent) {
            flag = parent->leftSon == nNode ? 1 : 2;
        }
        AVLNode<keyType, dataType> * tmp = nNode->rightSon;
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
    }

    void checkBalance (AVLNode<keyType, dataType> * nNode) {
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
    }

    template<class Function>
    void inorder (AVLNode<keyType, dataType> * node, Function f) {
        if (!node) {
            return;
        }
        inorder(node->leftSon, f);
        f(node);
        inorder(node->rightSon, f);
    }

    dataType * findMax () {
        if (NULL == rootNode) {
            return NULL;
        }
        AVLNode<keyType, dataType> * node = rootNode;
        while (node->rightSon) {
            node = node->rightSon;
        }
        return &(node->value);
    }

    dataType * findMin () {
        if (NULL == rootNode) {
            return NULL;
        }
        AVLNode<keyType, dataType> * node = rootNode;
        while (node->leftSon) {
            node = node->leftSon;
        }
        return &(node->value);
    }

    AVLNode<keyType, dataType> *
    returnNextNode (AVLNode<keyType, dataType> * node) { // returns the following node by order (according to the key)
        if (!node) {
            return NULL;
        }
        AVLNode<keyType, dataType> * tmp = node;
        if (!node->father) {
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
    }

    void emptyTree ();

    ~AVLTree () {
        emptyTree();
    }

    bool findIfValueExists (keyType & iKey);

    TreeResult insertData (const keyType & iKey, const dataType & data);

    TreeResult removeValue (keyType & iKey);

    AVLNode<keyType, dataType> * getNodeByKey (keyType & iKey);

    dataType * getValue (keyType & iKey);

    AVLNode<keyType, dataType> * returnRoot () {
        return this->rootNode;
    }

};

template<class keyType, class dataType>
bool AVLTree<keyType, dataType>::findIfValueExists (keyType & iKey) {
    return rootNode != NULL && rootNode->findByKey(iKey);
}

template<class keyType, class dataType>
AVLNode<keyType, dataType> * AVLTree<keyType, dataType>::getNodeByKey (keyType & iKey) {
    if (NULL == rootNode) {
        return NULL;
    }
    return rootNode->returnNode(iKey);
}

template<class keyType, class dataType>
dataType * AVLTree<keyType, dataType>::getValue (keyType & iKey) {
    if (!this->findIfValueExists(iKey)) {
        return NULL;
    }
    return &(rootNode->returnNode(iKey)->value);
}

template<class keyType, class dataType>
TreeResult AVLTree<keyType, dataType>::insertData (const keyType & iKey, const dataType & data) {
    if (NULL == rootNode) {
        try {
            rootNode = new AVLNode<keyType, dataType>(iKey, data);
        }
        catch (std::bad_alloc &) {
            return AVLTREE_ALLOCATION_ERROR;
        }
        size++;
        return AVLTREE_SUCCESS;
    }
    AVLNode<keyType, dataType> * tmpNode = rootNode;
    AVLNode<keyType, dataType> * newNode;
    while (true) {
        if (tmpNode->key > iKey) {
            if (!tmpNode->leftSon) {
                newNode = new AVLNode<keyType, dataType>(iKey, data);
                tmpNode->setLeftSon(newNode);
                break;
            } else {
                tmpNode = tmpNode->leftSon;
            }
        } else if (tmpNode->key < iKey) {
            if (!tmpNode->rightSon) {
                newNode = new AVLNode<keyType, dataType>(iKey, data);
                tmpNode->setRightSon(newNode);
                break;
            } else {
                tmpNode = tmpNode->rightSon;
            }
        } else {
            return AVLTREE_NODE_ALREADY_EXISTS;
        }
    }
    tmpNode = newNode;
    while (tmpNode) { //updating the node ruined path
        tmpNode->getAndSetHeight(); //Updating the height
        tmpNode->updateBalanceFactor();
        checkBalance(tmpNode);
        tmpNode = tmpNode->father;
    }
    size++;
    return AVLTREE_SUCCESS;
}

template<class keyType, class dataType>
TreeResult AVLTree<keyType, dataType>::removeValue (keyType & iKey) {
    if (!rootNode || !findIfValueExists(iKey)) {
        return AVLTREE_NODE_NOT_FOUND;
    }
    /*else if (size == 1) { // TODO: testing debug solution
        delete rootNode;
        size--;
        rootNode = NULL;
        return AVLTREE_SUCCESS;
    }*/
    AVLNode<keyType, dataType> * parent = NULL;
    AVLNode<keyType, dataType> * tmp = rootNode->returnNode(iKey);
    AVLNode<keyType, dataType> * replace = NULL;
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
        }
    } else if (!tmp->leftSon) {
        if (parent) {
            if (parent->key < tmp->key) { //then tmp is a right son.
                parent->setRightSon(tmp->rightSon);
            } else {
                parent->setLeftSon(tmp->rightSon);
            }
            delete tmp;
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
        }
    } else {
        replace = tmp->rightSon;
        while (replace->leftSon) {
            replace = replace->leftSon;
        }
        //tmp->swap(replace); TODO: We swap pointers instead of doing a value and key swap
        // replace is the following node
        // tmp is the one to be deleted
        AVLNode<keyType, dataType> * swap;
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
    return AVLTREE_SUCCESS;
}


template<class keyType, class dataType>
void inOrderToArray (AVLNode<keyType, dataType> * nNode, dataType * array, int * i) {
    if (!nNode) { // TODO: Check array isn't NULL before dereferencing
        return;
    }
    inOrderToArray(nNode->leftSon, array, i);
    array[(*i)++] = nNode->value;
    inOrderToArray(nNode->rightSon, array, i);
}

template<class keyType, class dataType>
void AVLTree<keyType, dataType>::emptyTree () {
    if (!rootNode) {
        return;
    }
    rootNode->emptySubTree(rootNode);

    size = 0;
    rootNode = NULL;
}

//static bool powerOf2 (int num) {
//    if (num == 0) return false;
//
//    bool isPower = !(num & (num - 1));
//    return isPower;
//}

template<class keyType, class dataType>
TreeResult buildFullTree (AVLTree<keyType, dataType> * tree, AVLNode<keyType, dataType> * root, int numOfRows,
                          AVLNode<keyType, dataType> * parent,
                          Direction direction) {
    if (0 == numOfRows) {
        return AVLTREE_SUCCESS;
    } // we're done
    try {
        root = new AVLNode<keyType, dataType>(keyType(), dataType());
        if (NULL != parent) {
            root->father = parent;
            if (LEFT == direction) root->father->leftSon = root;
            else root->father->rightSon = root;
        } else { // this is the first node!
            tree->rootNode = root;
        }
    }
    catch (std::bad_alloc &) {
        return AVLTREE_ALLOCATION_ERROR;
    }
    TreeResult res = buildFullTree(tree, root->leftSon, numOfRows - 1, root, LEFT);
    if (res != AVLTREE_SUCCESS) {
        if (root->leftSon) delete root->leftSon;
        delete root;
        return res;
    }

    res = buildFullTree(tree, root->rightSon, numOfRows - 1, root, RIGHT);
    if (res != AVLTREE_SUCCESS) {
        if (root->rightSon) delete root->rightSon;
        delete root->leftSon;
        delete root;
        return res;
    }

    return AVLTREE_SUCCESS;
};

template<class keyType, class dataType>
void trimHighestNodesHelper (AVLNode<keyType, dataType> * root, int * num) {
    if (0 == *num) return; // nothing left to delete
    if (!root) return;
    if (root->rightSon) {
        trimHighestNodesHelper(root->rightSon, num);
    }
    if ((!root->leftSon) && (!root->rightSon) && (0 != *num)) {
        if (root->father) {
            if (root->father->leftSon == root) root->father->leftSon = NULL; // deleting left leaf
            else root->father->rightSon = NULL; // deleting right leaf
        }
        delete root;
        (*num)--;
        return;
    }
    if (root->leftSon) {
        trimHighestNodesHelper(root->leftSon, num);
    }
    return;
};

template<class keyType, class dataType>
AVLTree<keyType, dataType> * trimHighestNodes (AVLTree<keyType, dataType> * tree, int num) {
    if (0 == num) return tree;
    tree->size -= num;
    trimHighestNodesHelper(tree->rootNode, &num);
    tree->rootNode->getAndSetHeight();
    return tree;
};

template<class keyType, class dataType>
AVLTree<keyType, dataType> * buildEmptyHelper (int numOfRows, int toRemove) {
    AVLTree<keyType, dataType> * fullTree = new AVLTree<keyType, dataType>;
    if (AVLTREE_SUCCESS !=
        buildFullTree<keyType, dataType>(fullTree, fullTree->rootNode, numOfRows, NULL,
                                         RIGHT)) { // direction doesn't matter here
        delete fullTree;
        return NULL;
    }
    fullTree->size = (int) pow(2, numOfRows) - 1;
    // Now we have a full tree of height numOfRows-1, (2^numOfRows)-1 nodes, need to delete toRemove of them
    return trimHighestNodes(fullTree, toRemove);
};

// returns empty tree if n==0 or NULL if there was an error
template<class keyType, class dataType>
AVLTree<keyType, dataType> * buildEmpty (int n) {
    if (0 == n) return new AVLTree<keyType, dataType>; // empty tree
    if (1 == n) { // just the root
        AVLTree<keyType, dataType> * tree = new AVLTree<keyType, dataType>;
        tree->insertData(keyType(), dataType());
        return tree;
    }
    int numOfNodes = 1, powOfTwo = 0;
    do {
        numOfNodes *= 2;
        powOfTwo++;
        if (numOfNodes - 1 >= n) break;
    } while (numOfNodes - 1 < n);
    return buildEmptyHelper<keyType, dataType>(powOfTwo, numOfNodes - n - 1);
}

#endif /* AVLTREE_H_ */
