#pragma once

#include "SortedMultiMap.h"
#include <stack>

class SMMIterator {
    friend class SortedMultiMap;
private:
    // DO NOT CHANGE THIS PART
    const SortedMultiMap& map;
    SMMIterator(const SortedMultiMap& map);

    int currentNode; // indexul nodului curent în arbore
    int currentValueIndex; // indexul curent al valorii din vectorul de valori asociat cheii
    std::stack<int> s; // stiva pentru traversarea inordine

    void init();

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};
