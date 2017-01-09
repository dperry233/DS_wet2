//
// Created by Krumpet on 29-Dec-16.
//

#ifndef DS_WET2_ANIMALUNIONFIND_H
#define DS_WET2_ANIMALUNIONFIND_H

#include "MagiHash.h"

class animalInput : public std::exception {
};

typedef enum {
    UF_INVALID_INPUT,
    UF_FAILURE,
    UF_SUCCESS
} UFStatus;

class Animal {
private:
    static int counter;
    int id;
    int level;
    Magi * owner;
    int root;
    int size;

public:
    Animal () : id(counter++), level(0), owner(0), root(id), size(1) {}

    Animal (const Animal & rhs) : id(rhs.id), level(rhs.level), owner(rhs.owner), root(rhs.root), size(rhs.size) {}

    Animal & operator= (const Animal & rhs);

    int getId () const;

    void setId (int id);

    int getLevel () const;

    void setLevel (int level);

    Magi * getOwner () const;

    void setOwner (Magi * owner);

    int getRoot () const;

    void setRoot (int root);

    int getSize () const;

    void setSize (int size);
};

class animalUF {
private:
    int n;
    Animal * array;

    bool isValid (int id) {
        return ((id >= 0) && (id < n));
    }

    int find (int id) {
        if (!isValid(id)) return notFound;
        int currentRoot = array[id].getRoot();
        int rootRoot = array[currentRoot].getRoot();
        while (currentRoot != rootRoot) {
            currentRoot = rootRoot;
            rootRoot = array[currentRoot].getRoot();
        }  // now rootRoot is has the index that's the root of the whole tree
        do { // Shrinking paths
            currentRoot = array[id].getRoot();
            array[id].setRoot(rootRoot);
            id = currentRoot;
        } while (id != rootRoot);
        return rootRoot;
    }

public:
    const static int notFound = -1;

    animalUF (int n, int * levels) : n(n) {
        if ((n <= 0) || (!levels)) throw animalInput();
        array = new Animal[n];
        for (int i = 0; i < n; ++i) {
            array[i].setLevel(levels[i]);
        }
    }

    UFStatus sameArea (int id1, int id2, bool * answer) {
        if (!isValid(id1) || !isValid(id2) || (0 == answer)) return UF_INVALID_INPUT;
        *answer = (find(id1) == find(id2));
        return UF_SUCCESS;
    }

    UFStatus getSizeofArea (int id, int * sizeOfArea) {
        if (!isValid(id) || (0 == sizeOfArea)) return UF_INVALID_INPUT;
        int root = find(id);
        if (notFound == root) return UF_INVALID_INPUT; // shouldn't happen
        *sizeOfArea = array[root].getSize();
        return UF_SUCCESS;
    }

    UFStatus getLevelofArea (int id, int * levelOfArea) {
        if (!isValid(id) || (0 == levelOfArea)) return UF_INVALID_INPUT;
        int root = find(id);
        if (notFound == root) return UF_INVALID_INPUT; // shouldn't happen
        *levelOfArea = array[root].getLevel();
        return UF_SUCCESS;
    }

    UFStatus removeBarrier (int id1, int id2) {
        if (!isValid(id1) || !isValid(id2)) return UF_INVALID_INPUT;
        int root1 = find(id1);
        int root2 = find(id2);
        if ((notFound == id1) || (notFound == id2)) return UF_INVALID_INPUT; // shouldn't happen
        if (root1 == root2) return UF_FAILURE;
        if (array[root1].getSize() >= array[root2].getSize()) { // attach 2 to 1
            array[root2].setRoot(root1);
            array[root1].setSize(array[root1].getSize() + array[root2].getSize());
            array[root1].setLevel(array[root1].getLevel() + array[root2].getLevel());
        } else {                                                // attach 1 to 2
            array[root1].setRoot(root2);
            array[root2].setSize(array[root1].getSize() + array[root2].getSize());
            array[root2].setLevel(array[root2].getLevel() + array[root1].getLevel());
        }
        return UF_SUCCESS;
    }

    ~AnimalUF () {
        delete[] array;
    }
};

#endif //DS_WET2_ANIMALUNIONFIND_H
