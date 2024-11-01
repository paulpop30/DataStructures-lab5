#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
#include <algorithm>
using std::min;
using std::find_if;
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);
class Nod {
public:
    TKey key;
    vector<TValue> valori;
    bool ocupat;
};
class SortedMultiMap {
    friend class SMMIterator;
private:
    Nod elements[15000];
    int stanga[15000];
    int dreapta[15000];
    int radacina;
    int prim_liber;
    Relation relatie;
    int dim;
    void actualizare_prim_liber();
    int get_index(TKey c);
    bool sterge_frunza(TKey c, TValue v);
    bool are_un_copil(int poz);
    bool sterge_nod_cu_un_copil(TKey c, TValue v);
    bool sterge_nod_cu_doi_copii(TKey c, TValue v);
    int get_inorder_succesor(int nod);
    int minValue(int nod);
    int maxValue(int nod);
    void stergere_totala_frunza(TKey c);
    void stergere_totala_nod_cu_fiu_drept(TKey c);

public:

    // constructor
    SortedMultiMap(Relation r);

    //adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

    //returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

    //removes a key value pair from the sorted multimap
    //returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};