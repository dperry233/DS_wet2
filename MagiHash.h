//
// Created by Krumpet on 26-Dec-16.
//

#ifndef DS_WET2_MAGIHASH_H
#define DS_WET2_MAGIHASH_H

#include <exception>

#define INIT_SIZE 5;
#define FACTOR 2;

class magiInput : public std::exception {
};

typedef enum {} HashStatus;

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

    ~Magi () {};

    static int getCount ();

    int getId () const;

    int getLevel () const;

    int getRank () const;

    int getBeast () const;

    void setBeast (int beast);
};

class magiHash {
private:
    Magi ** array;
    bool * deleted;
    int size;
    int content;

    void increase() {
        Magi ** oldArray= array;
        int oldSize=size;
        size*=FACTOR;
        array = new Magi*[size];
        for (int i=0;i<size;++i) {
            array[i]=0;
        }
        content=0;
        for (int i=0;i<oldSize;++i) {
            if (oldArray[i] != 0 && !deleted[i]) insert(oldArray[i]);
        }
        // TODO: make new deleted after using it to insert things
        delete[] oldArray;
    }

public:
//    static const Magi * deleted;
    magiHash() {
        size=INIT_SIZE;
        content=0;
        array = new Magi*[size];
        deleted = new bool[size];
        for (int i=0;i<size;++i) {
            array[i]=0;
            deleted[i]=false;
        }
    }
    ~magiHash () {
        delete[] array;
    }

    HashStatus insert (Magi * mage) {

    }
};

#endif //DS_WET2_MAGIHASH_H
