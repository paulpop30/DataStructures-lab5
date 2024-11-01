#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>
using namespace std;
/*
 * Best Case:
 *    THETA(1) - Construction initializes member variables and calls `init()`.
 * Worst Case:
 *    THETA(n) - `init()` might traverse the entire left subtree.
 * Average Case:
 *    THETA(n) - Average case for traversing the left subtree.
 * Total Complexity:
 *    O(n)
 */

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d) {
    init();
}

/*
 * Best Case:
 *    THETA(1) - Initializing the stack and setting current node when the tree is empty.
 * Worst Case:
 *    THETA(n) - Traversing the entire left subtree to initialize the stack.
 * Average Case:
 *    THETA(n) - Average case for traversing the left subtree.
 * Total Complexity:
 *    O(n)
 */
void SMMIterator::init() {

    s = stack<int>(); //MODIF
    currentNode = map.radacina;
    currentValueIndex = 0;

    while (currentNode != -1) {
        s.push(currentNode);
        currentNode = map.stanga[currentNode];
    }

    if (!s.empty()) {
        currentNode = s.top();
    }
    else {
        currentNode = -1;
    }
}
/*
 * Best Case:
 *    THETA(1) - The iterator is already initialized, no operation is needed.
 * Worst Case:
 *    THETA(n) - Calls `init()` which might traverse the entire left subtree.
 * Average Case:
 *    THETA(n) - Average case for traversing the left subtree.
 * Total Complexity:
 *    O(n)
 */
void SMMIterator::first() {
   /*while (!s.empty()) {
        s.pop();
    }*/
    init();
}
/*
 * Best Case:
 *    THETA(1) - Moving to the next element when the current node has more values.
 * Worst Case:
 *    THETA(n) - Traversing the entire tree to find the next element.
 * Average Case:
 *    THETA(log n) - Average case for finding the next element.
 * Total Complexity:
 *    O(n)
 */
void SMMIterator::next() {
    if (!valid()) {
        throw std::exception("Invalid iterator");
    }

    if (currentValueIndex < map.elements[currentNode].valori.size() - 1) {
        currentValueIndex++;
    }
    else {
        int node = s.top();
        s.pop();

        if (map.dreapta[node] != -1) {
            node = map.dreapta[node];
            while (node != -1) {
                s.push(node);
                node = map.stanga[node];
            }
        }

        if (!s.empty()) {
            currentNode = s.top();
            currentValueIndex = 0; //MODIF
        }
        else {
            currentNode = -1;
        }
    }
}
/*
 * Best Case:
 *    THETA(1) - Checking if the iterator is valid.
 * Worst Case:
 *    THETA(1) - Checking if the iterator is valid.
 * Average Case:
 *    THETA(1) - Checking if the iterator is valid.
 * Total Complexity:
 *    O(1)
 */
bool SMMIterator::valid() const {
    return currentNode != -1;
}

/*
 * Best Case:
 *    THETA(1) - Getting the current element.
 * Worst Case:
 *    THETA(1) - Getting the current element.
 * Average Case:
 *    THETA(1) - Getting the current element.
 * Total Complexity:
 *    O(1)
 */
TElem SMMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception("Invalid iterator");
    }
    return std::make_pair(map.elements[currentNode].key, map.elements[currentNode].valori[currentValueIndex]);
}
