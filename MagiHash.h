//
// Created by Krumpet on 26-Dec-16.
//

#ifndef DS_WET2_MAGIHASH_H
#define DS_WET2_MAGIHASH_H

#include <exception>
#include <new>

class magiInput : public std::exception {
};

typedef enum {
    ALLOCATION_ERROR,
    INVALID_INPUT,
    FAILURE,
    SUCCESS
} HashStatus;

class Magi {
private:
    static int count;
    int id;
    int level;
    int rank;
    int beast;
public:
    Magi (int id, int level) : id(id), level(level), rank(count), beast(0) {
        if ((id <= 0) || (level <= 0)) throw magiInput();
        ++count;
    }

    Magi (const Magi & rhs) : id(rhs.id), level(rhs.level), rank(rhs.rank), beast(rhs.beast) {}
    // TODO: verify that copying means copying rank

    Magi & operator= (const Magi & rhs);

    ~Magi () {};

    static int getCount ();

    int getId () const;

    int getLevel () const;

    int getRank () const;

    int getBeast () const;

    void setBeast (int beast);
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
    const static int init_size = 5;
    const static int factor = 2;
    int size;
    int content;
    hashCell * array;

    HashStatus increase () {
        hashCell * oldArray = array;
        int oldSize = size;
        size *= factor;
        try {
            array = new hashCell[size];
        } catch (std::bad_alloc &) {
            array = oldArray;
            size = oldSize;
            return ALLOCATION_ERROR;
        }
        content = 0;
        for (int i = 0; i < oldSize; ++i) {
            if (oldArray[i].magi != 0 && !oldArray[i].deleted) insert(oldArray[i].magi);
        }
        delete[] oldArray;
        return SUCCESS;
    }

public:
//    static const Magi * deleted;
    magiHash ();

    ~magiHash () {
        delete[] array;
    }

    HashStatus insert (Magi * magi) {

    }
};

#endif //DS_WET2_MAGIHASH_H
