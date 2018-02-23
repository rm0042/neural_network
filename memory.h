#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED

#include "matrix.h"
#include "utils.h"
#include "definitions.h"

const int MAXCELLS = 1000;

template <class data>
class tmem{
public:
    data inst;
    data act;
    data outst;
    tmem* next;
};


template <class data>
class tmemory{
    int cells_num_;
    tmem<data> **cells;
public:
    int (*hash_func)(data x);

    tmemory(){};
    ~tmemory(){ delete [] cells; }

    void AllocMemory(int cells_num = MAXCELLS){
        cells = new tmem<data>* [cells_num];
        cells_num_ = cells_num;
    }

    void CleanMemory(){
        for (int i = 0; i < cells_num_; i++){
            tmem<data> *p = cells[i], *buf;
            if (p == nullptr) continue;
            while ((p -> next) != nullptr){
                buf = p -> next;
                delete p;
                p = buf;
            }
        }
    }

    void Addmem(data instate, data action, data outstate){
        int key = hash_func(outstate);
        tmem<data>* addmem = new tmem<data>;
        addmem->inst = instate;
        addmem->act = action;
        addmem->outst = outstate;
        addmem->next = cells[key];
        cells[key] = addmem;
    }

    tmem<data> *Findmem(data outstate)
    {
        int key = hash_func(outstate);
        tmem<data>* p = cells[key];
        while (p != nullptr && p->outst != outstate) p = p -> next;
        if (p != nullptr)
            return p;
        else
            return nullptr;
    }

};




#endif // MEMORY_H_INCLUDED
