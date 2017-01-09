//
// Created by Krumpet on 26-Dec-16.
//

#ifndef DS_WET2_MAGIHASH_H
#define DS_WET2_MAGIHASH_H

#include <exception>
#include <new>
#include <iostream>

//using namespace std;

class magiInput : public std::exception {
};

typedef enum {
    INCREASE, DECREASE
} sizeChange;

typedef enum {
    HASH_ALLOCATION_ERROR,
    HASH_INVALID_INPUT,
    HASH_FAILURE,
    HASH_SUCCESS
} HashStatus;

class Magi {
private:
    static int count;
    int id;
    int level;
    int rank;
    int beast;
    int index;
public:
    const static int unassigned = -1;

    Magi (int id, int level) : id(id), level(level), rank(count), beast(unassigned), index(unassigned) {
      //  if ((id <= 0) || (level <= 0)) throw magiInput();
        ++count;
    }

    Magi (const Magi & rhs) : id(rhs.id), level(rhs.level), rank(rhs.rank), beast(rhs.beast), index(rhs.index) {}

    // TODO: verify that copying means copying rank

    Magi & operator= (const Magi & rhs);

    ~Magi () {};

    static int getCount ();

    int getId () const;

    int getLevel () const;

    bool operator== (const Magi & rhs) const;

    bool operator!= (const Magi & rhs) const;

    int getRank () const;

    int getBeast () const;

    int getIndex () const;

    void setBeast (int beast);

    void setIndex (int index);

    bool operator< (const Magi & rhs) const;

    bool operator> (const Magi & rhs) const;

    bool operator<= (const Magi & rhs) const;

    bool operator>= (const Magi & rhs) const;

    bool isYoungerThan (const Magi & rhs) {
        return this->rank > rhs.rank;
    }
};

// initialized to 0 and false, respectively
class hashCell {
public:
    Magi * magi;
    bool deleted;

    explicit hashCell (Magi * magi = 0) : magi(magi), deleted(false) {}

};

class magiHash {
private:
    const static int init_size = 7;
    const static int step_const = 3;
    const static int factor = 2;
    const static float threshold = 0.75;
    int size;
    int content;
    hashCell * array;

    HashStatus resize (sizeChange type) {
        hashCell * oldArray = array;
        int oldSize = size;
        size *= (type == INCREASE) ? factor : 1.0 / factor;
        try {
            array = new hashCell[size];
        } catch (std::bad_alloc &) {
            array = oldArray;
            size = oldSize;
            return HASH_ALLOCATION_ERROR;
        }
        content = 0;
        for (int i = 0; i < oldSize; ++i) {
            if (oldArray[i].magi != 0 && !oldArray[i].deleted) insert(oldArray[i].magi);
        }
        delete[] oldArray;
        return HASH_SUCCESS;
    }

public:
//    static const Magi * deleted;
    magiHash ();

    ~magiHash () {
        delete[] array;
    }

    HashStatus insert (Magi * magi) {
        int hash = (magi->getId()) % size;
        int step = 1 + (magi->getId() % (size - step_const));
        int i = hash;
        do {
            if (array[i].deleted || 0 == array[i].magi) {
                array[i].magi = magi;
                array[i].magi->setIndex(i);
                array[i].deleted = false;
                break;
            }
            i = (i + step) % size;
        } while (hash != i);
        content++;
        //HashStatus increase_result;
        if ((float) content / size >= threshold) return resize(INCREASE);
        return HASH_SUCCESS;
    }

    // returns -1 if magi not found
    int findMagi (int id) {
        //if (id <= 0) return Magi::unassigned;
        int hash = id % size;
        int step = 1 + (id % (size - step_const));
        int i = hash;
        do {
            if (0 == array[i].magi) return Magi::unassigned;
            if (id == array[i].magi->getId() && (!array[i].deleted)) {
                return i;
            }
            i = (i + step) % size;
        } while (hash != i);
        return Magi::unassigned;
    }

    HashStatus getCreature (int id, int * creature) {
        if (0 == creature || id <= 0) return HASH_INVALID_INPUT;
        int index = findMagi(id);
        if ((Magi::unassigned == index) || (Magi::unassigned == array[index].magi->getBeast())) return HASH_FAILURE;
        *creature = array[index].magi->getBeast();
        return HASH_SUCCESS;
    }

    HashStatus eraseMagi (int id) {
        if (id <= 0) return HASH_INVALID_INPUT;
        int index = findMagi(id);
        if (Magi::unassigned == index) return HASH_FAILURE;
        array[index].magi->setIndex(Magi::unassigned);
        array[index].magi->setBeast(Magi::unassigned);
        array[index].deleted = true;
        content--;
        if (((float) content / size < 1.0 - threshold) && (size > init_size)) return resize(DECREASE);
        return HASH_SUCCESS;
    }

    int getSize () const;

    int getContent () const;

    hashCell * getArray () const;
};

#endif //DS_WET2_MAGIHASH_H
