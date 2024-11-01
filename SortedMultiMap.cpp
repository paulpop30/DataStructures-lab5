#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;
/*
  Best Case:
     THETA(1) - The constructor initializes the data structures with fixed sizes.
  Worst Case:
     THETA(n) - Initialization involves iterating over the fixed-size arrays.
  Average Case:
     THETA(n) - Initialization involves iterating over the fixed-size arrays.
  Total Complexity:
     O(n)
 */
SortedMultiMap::SortedMultiMap(Relation r) {
	for (int i = 0; i < 15000; i++)
	{
		dreapta[i] = -1;
		stanga[i] = -1;
	}
	radacina = -1;
	dim = 0;
	prim_liber = 0;
	relatie = r;
	for (int i = 0; i < 15000; i++)
	{
		elements[i].ocupat = false;
		elements[i].key = NULL_TVALUE;
	}
}

/*
 * Best Case:
 *    THETA(1) - The function returns immediately if the first element is not occupied.
 * Worst Case:
 *    THETA(n) - It might iterate over all elements until finding the first unoccupied one.
 * Average Case:
 *    THETA(n) - In average, it iterates over half of the elements.
 * Total Complexity:
 *    O(n)
 */

void SortedMultiMap::actualizare_prim_liber() {
	while (elements[prim_liber].ocupat)
		prim_liber++;
}

/*
 * Best Case:
 *    THETA(log n) - Insertion might take logarithmic time if the tree is balanced.
 * Worst Case:
 *    THETA(n) - Insertion might take linear time if the tree is skewed.
 * Average Case:
 *    THETA(log n) - On average, insertion takes logarithmic time.
 * Total Complexity:
 *    O(n)
 */
void SortedMultiMap::add(TKey c, TValue v) {
	if (dim == 0) {
		radacina = prim_liber;
		elements[radacina].key = c;
		elements[radacina].valori.push_back(v);
		dim++;
		elements[radacina].ocupat = true;
		actualizare_prim_liber();
		return;
	}

	dim++;


	vector<TValue> vect = search(c);
	if (vect.size() == 0) {
		
		int nod_curent = radacina;

		while (true) {
			if (stanga[nod_curent] != -1 && relatie(c, elements[nod_curent].key))
				nod_curent = stanga[nod_curent];
			else if (dreapta[nod_curent] != -1 && relatie(elements[nod_curent].key, c))
				nod_curent = dreapta[nod_curent];
			else {
				if (stanga[nod_curent] == -1 && dreapta[nod_curent] == -1) {

					if (relatie(c, elements[nod_curent].key)) {

						stanga[nod_curent] = prim_liber;
						elements[prim_liber].key = c;
						elements[prim_liber].valori.push_back(v);
						elements[prim_liber].ocupat = true;
						break;
					}
					else {

						dreapta[nod_curent] = prim_liber;
						elements[prim_liber].key = c;
						elements[prim_liber].valori.push_back(v);
						elements[prim_liber].ocupat = true;
						break;
					}
				}
				else {
					if (stanga[nod_curent] == -1) {

						stanga[nod_curent] = prim_liber;
						elements[prim_liber].key = c;
						elements[prim_liber].valori.push_back(v);
						elements[prim_liber].ocupat = true;
						break;

					}
					else if (dreapta[nod_curent] == -1) {

						dreapta[nod_curent] = prim_liber;
						elements[prim_liber].key = c;
						elements[prim_liber].valori.push_back(v);
						elements[prim_liber].ocupat = true;
						break;
					}
				}
			}

		}

		actualizare_prim_liber();
	}
	else {
	
		int nod_curent = radacina;
		while (true) {
			
			if (elements[nod_curent].key == c)
				break;
			else if (stanga[nod_curent] != -1 && relatie(c, elements[nod_curent].key))
				nod_curent = stanga[nod_curent];
			else if (dreapta[nod_curent] != -1 && relatie(elements[nod_curent].key, c))
				nod_curent = dreapta[nod_curent];
		}

		elements[nod_curent].valori.push_back(v);
	}
}

/*
 * Best Case:
 *    THETA(1) - If the searched element is the root.
 * Worst Case:
 *    THETA(n) - If the tree is skewed and the searched element is the last leaf.
 * Average Case:
 *    THETA(log n) - On average, search takes logarithmic time.
 * Total Complexity:
 *    O(n)
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
	int aux;
	int nod_curent = radacina;
	while (true) {
		aux = nod_curent;
		if (elements[nod_curent].key == c)
			return elements[nod_curent].valori;
		if (relatie(c, elements[nod_curent].key) && stanga[nod_curent] != -1) {
			nod_curent = stanga[nod_curent];
		}
		else if (relatie(elements[nod_curent].key, c) && dreapta[nod_curent] != -1) {
			nod_curent = dreapta[nod_curent];
		}
		if (stanga[nod_curent] == -1 && dreapta[nod_curent] == -1 && elements[nod_curent].key != c)
			return vector<TValue>();
		if (aux == nod_curent)
			return vector<TValue>();
	}

}
 
/*
 * Best Case:
 *    THETA(log n) - Removal might take logarithmic time if the tree is balanced.
 * Worst Case:
 *    THETA(n) - Removal might take linear time if the tree is skewed.
 * Average Case:
 *    THETA(log n) - On average, removal takes logarithmic time.
 * Total Complexity:
 *    O(n)
 */
bool SortedMultiMap::remove(TKey c, TValue v) {
	if (dim == 0)
		return false;
	vector<TValue> a = search(c);
	if (a.size() == 0)
		return false;

	dim--;
	int index = get_index(c);

	if (stanga[index] == -1 && dreapta[index] == -1)
		return sterge_frunza(c, v);

	if (are_un_copil(index)) {
		return sterge_nod_cu_un_copil(c, v);
	}
	else {

		return sterge_nod_cu_doi_copii(c, v);
	}
}

/*
 * Best Case:
 *    THETA(1) - Removal from a leaf node is constant time.
 * Worst Case:
 *    THETA(n) - It might traverse the entire tree to find the leaf node.
 * Average Case:
 *    THETA(1) - Removal from a leaf node is typically constant time.
 * Total Complexity:
 *    O(n)
 */
bool SortedMultiMap::sterge_frunza(TKey c, TValue v) {
	
	int nod_curent = radacina;
	int parinte = -1;

	while (elements[nod_curent].key != c) {
		if (relatie(c, elements[nod_curent].key)) {
			parinte = nod_curent;
			nod_curent = stanga[nod_curent];
		}
		else {
			parinte = nod_curent;
			nod_curent = dreapta[nod_curent];
		}
	}
	
	auto it = find_if(elements[nod_curent].valori.begin(), elements[nod_curent].valori.end(), [v](TValue val) { return v == val; });
	if (it == elements[nod_curent].valori.end()) {
		dim++;
		return false;
	}
	else {
		if (elements[nod_curent].valori.size() == 1) {
			stanga[nod_curent] = -1;
			dreapta[nod_curent] = -1;

			elements[nod_curent].key = NULL_TVALUE;
			elements[nod_curent].ocupat = false;

			if (parinte == -1)
				radacina = -1;
			else {
				if (stanga[parinte] == nod_curent)
					stanga[parinte] = -1;
				else {
					dreapta[parinte] = -1;
				}
			}
			/*stanga[parinte] = -1;
		dreapta[parinte] = -1;*/

			prim_liber = nod_curent;
			actualizare_prim_liber();
		}
		elements[nod_curent].valori.erase(it);
		
		return true;
	}

}
/*
 * Best Case:
 *    THETA(1) - Removal from a node with only one child is constant time.
 * Worst Case:
 *    THETA(n) - It might traverse the entire tree to find the node.
 * Average Case:
 *    THETA(1) - Removal from a node with only one child is typically constant time.
 * Total Complexity:
 *    O(n)
 */
bool SortedMultiMap::sterge_nod_cu_un_copil(TKey c, TValue v) {
	

	int nod_curent = radacina;
	int parinte = -1;
	while (elements[nod_curent].key != c) {
		if (relatie(c, elements[nod_curent].key)) {
			parinte = nod_curent;
			nod_curent = stanga[nod_curent];
		}
		else {
			parinte = nod_curent;
			nod_curent = dreapta[nod_curent];
		}
	}

	auto it = find_if(elements[nod_curent].valori.begin(), elements[nod_curent].valori.end(), [v](TValue val) { return v == val; });
	if (it == elements[nod_curent].valori.end()) {
		dim++;
		return false;
	}

	if (elements[nod_curent].valori.size() > 1) {
		elements[nod_curent].valori.erase(it);
		return true;
	}

	if (parinte == -1) {
		if (stanga[radacina] != -1) {
			prim_liber = radacina;
			elements[radacina].valori.clear();
			radacina = stanga[radacina];
			elements[radacina].ocupat = false;
			return true;
		}
		else {
			prim_liber = radacina;
			elements[radacina].valori.clear();
			radacina = dreapta[radacina];
			elements[radacina].ocupat = false;
			return true;
		}
	}
	else {
		if (stanga[parinte] == nod_curent) {
			if (stanga[nod_curent] != -1) {
				stanga[parinte] = stanga[nod_curent];
				stanga[nod_curent] = -1;
				elements[nod_curent].key = NULL_TVALUE;
				elements[nod_curent].valori.erase(it);
				elements[nod_curent].ocupat = false;
				prim_liber = nod_curent;
				return true;
			}
			else {
				stanga[parinte] = dreapta[nod_curent];
				dreapta[nod_curent] = -1;
				elements[nod_curent].key = NULL_TVALUE;
				elements[nod_curent].valori.erase(it);
				elements[nod_curent].ocupat = false;
				prim_liber = nod_curent;
				return true;
			}
		}
		else {
			if (stanga[nod_curent] != -1) {
				dreapta[parinte] = stanga[nod_curent];
				stanga[nod_curent] = -1;
				elements[nod_curent].key = NULL_TVALUE;
				elements[nod_curent].valori.erase(it);
				elements[nod_curent].ocupat = false;
				prim_liber = nod_curent;
				return true;
			}
			else {
				dreapta[parinte] = dreapta[nod_curent];
				dreapta[nod_curent] = -1;
				elements[nod_curent].key = NULL_TVALUE;
				elements[nod_curent].valori.erase(it);
				elements[nod_curent].ocupat = false;
				prim_liber = nod_curent;
				return true;
			}
		}
	}
}
/*
 * Best Case:
 *    THETA(1) - Removal from a node with two children is constant time if the successor has no children.
 * Worst Case:
 *    THETA(n) - It might traverse the entire tree to find the node.
 * Average Case:
 *    THETA(1) - Removal from a node with two children is typically constant time.
 * Total Complexity:
 *    O(n)
 */
bool SortedMultiMap::sterge_nod_cu_doi_copii(TKey c, TValue v) {
	

	int nod_curent = radacina;
	int parinte = -1;
	while (elements[nod_curent].key != c) {
		if (relatie(c, elements[nod_curent].key)) {
			parinte = nod_curent;
			nod_curent = stanga[nod_curent];
		}
		else {
			parinte = nod_curent;
			nod_curent = dreapta[nod_curent];
		}
	}

	auto it = find_if(elements[nod_curent].valori.begin(), elements[nod_curent].valori.end(), [v](TValue val) { return v == val; });
	if (it == elements[nod_curent].valori.end()) {
		dim++;
		return false;
	}

	if (elements[nod_curent].valori.size() == 1) {
		int min_din_partea_dreapta = get_inorder_succesor(nod_curent);
		elements[nod_curent].key = elements[min_din_partea_dreapta].key;
		elements[nod_curent].valori = elements[min_din_partea_dreapta].valori;
		if (stanga[min_din_partea_dreapta] == -1 && dreapta[min_din_partea_dreapta] == -1) {
			stergere_totala_frunza(elements[min_din_partea_dreapta].key);
			return true;
		}
		else {
			stergere_totala_nod_cu_fiu_drept(elements[min_din_partea_dreapta].key);
			return true;
		}
	}
	else {
		elements[nod_curent].valori.erase(it);
		return true;
	}
}

/*
 * SortedMultiMap::stergere_totala_nod_cu_fiu_drept(TKey c)
 *
 * Best Case:
 *    THETA(1) - If the node to be removed has no left child.
 * Worst Case:
 *    THETA(h) - If the right subtree of the node being removed has maximum depth.
 * Average Case:
 *    THETA(h) - Average depth of the right subtree.
 * Total Complexity:
 *    O(h)
 */
void SortedMultiMap::stergere_totala_nod_cu_fiu_drept(TKey c) {
	int nod_curent = radacina;
	int parinte = -1;
	while (elements[nod_curent].key != c) {
		if (relatie(elements[stanga[nod_curent]].key, elements[nod_curent].key)) {
			parinte = nod_curent;
			nod_curent = stanga[nod_curent];
		}
		else {
			parinte = nod_curent;
			nod_curent = dreapta[nod_curent];
		}
	}

	if (stanga[parinte] != -1) {

		stanga[parinte] = dreapta[nod_curent];
		dreapta[nod_curent] = -1;
		elements[nod_curent].key = NULL_TVALUE;
		elements[nod_curent].valori.clear();
		elements[nod_curent].ocupat = false;
		return;
	}
	else {

		dreapta[parinte] = dreapta[nod_curent];
		dreapta[nod_curent] = -1;
		elements[nod_curent].key = NULL_TVALUE;
		elements[nod_curent].valori.clear();
		elements[nod_curent].ocupat = false;
		return;
	}

}

/*
 * SortedMultiMap::stergere_totala_frunza(TKey c)
 *
 * Best Case:
 *    THETA(1) - If the node to be removed is a leaf node.
 * Worst Case:
 *    THETA(h) - If the node to be removed is at maximum depth.
 * Average Case:
 *    THETA(h) - Average depth of the node being removed.
 * Total Complexity:
 *    O(h)
 */
void SortedMultiMap::stergere_totala_frunza(TKey c) {
	int nod_curent = radacina;
	int parinte = -1;
	while (elements[nod_curent].key != c) {
		if (relatie(elements[stanga[nod_curent]].key, elements[nod_curent].key)) {
			parinte = nod_curent;
			nod_curent = stanga[nod_curent];
		}
		else {
			parinte = nod_curent;
			nod_curent = dreapta[nod_curent];
		}
	}


	stanga[nod_curent] = dreapta[nod_curent] = stanga[parinte] = dreapta[parinte] = -1;
	elements[nod_curent].key = NULL_TVALUE;
	elements[nod_curent].ocupat = false;
	elements[nod_curent].valori.clear();
}

/*
 * SortedMultiMap::get_index(TKey c)
 *
 * Best Case:
 *    THETA(1) - If the searched key is found at the root.
 * Worst Case:
 *    THETA(h) - If the tree is completely unbalanced and the key is at the maximum depth.
 * Average Case:
 *    THETA(h) - Average depth of the tree.
 * Total Complexity:
 *    O(h)
 */
int SortedMultiMap::get_index(TKey c)
{
	int nod_curent = radacina;
	while (elements[nod_curent].key != c && nod_curent != -1) {
		if (relatie(elements[stanga[nod_curent]].key, elements[nod_curent].key)) {
			nod_curent = stanga[nod_curent];
		}
		else {
			nod_curent = dreapta[nod_curent];
		}
	}
	return nod_curent;
}
/*
 * SortedMultiMap::are_un_copil(int poz)
 *
 * Best Case:
 *    THETA(1) - If the node has no children.
 * Worst Case:
 *    THETA(1) - If the node has no children.
 * Average Case:
 *    THETA(1) - If the node has no children.
 * Total Complexity:
 *    O(1)
 */
bool SortedMultiMap::are_un_copil(int poz)
{
	if (stanga[poz] == -1 && dreapta[poz] != -1)
		return true;
	if (dreapta[poz] == -1 && stanga[poz] != -1)
		return true;
	return false;
}


/*
 * SortedMultiMap::size() const
 *
 * Best Case:
 *    THETA(1) - Retrieving the size is constant time.
 * Worst Case:
 *    THETA(1) - Retrieving the size is constant time.
 * Average Case:
 *    THETA(1) - Retrieving the size is constant time.
 * Total Complexity:
 *    O(1)
 */
int SortedMultiMap::size() const {
	return dim;
}
/*
 * SortedMultiMap::isEmpty() const
 *
 * Best Case:
 *    THETA(1) - Checking if the map is empty is constant time.
 * Worst Case:
 *    THETA(1) - Checking if the map is empty is constant time.
 * Average Case:
 *    THETA(1) - Checking if the map is empty is constant time.
 * Total Complexity:
 *    O(1)
 */

bool SortedMultiMap::isEmpty() const {
	return dim == 0;
}

/*
 * SortedMultiMap::get_inorder_succesor(int nod)
 *
 * Best Case:
 *    THETA(1) - If the node has a right child, its leftmost descendant is the successor.
 * Worst Case:
 *    THETA(h) - If the node is the maximum value in the tree, the successor is the root.
 * Average Case:
 *    THETA(h) - Average height of the tree.
 * Total Complexity:
 *    O(h)
 */

int SortedMultiMap::get_inorder_succesor(int nod)
{
	if (dreapta[nod] != -1)
		return minValue(dreapta[nod]);

	return maxValue(stanga[nod]);
}

/*
 * SortedMultiMap::minValue(int nod)
 *
 * Best Case:
 *    THETA(1) - If the node is the leftmost node in the tree.
 * Worst Case:
 *    THETA(h) - If the leftmost node is at the maximum depth of the tree.
 * Average Case:
 *    THETA(h) - Average depth of the tree.
 * Total Complexity:
 *    O(h)
 */
int SortedMultiMap::minValue(int nod)
{
	int curent = nod;
	while (stanga[curent] != -1) {
		curent = stanga[curent];
	}
	return curent;
}
/*
 * SortedMultiMap::maxValue(int nod)
 *
 * Best Case:
 *    THETA(1) - If the node is the rightmost node in the tree.
 * Worst Case:
 *    THETA(h) - If the rightmost node is at the maximum depth of the tree.
 * Average Case:
 *    THETA(h) - Average depth of the tree.
 * Total Complexity:
 *    O(h)
 */
int SortedMultiMap::maxValue(int nod) {
	int curent = nod;
	while (dreapta[curent] != -1)
		curent = dreapta[curent];
	return curent;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}
/*
 * SortedMultiMap::~SortedMultiMap()
 *
 * Best Case:
 *    THETA(1) - The destructor runs constant time operations for cleanup.
 * Worst Case:
 *    THETA(n) - The destructor might deallocate memory for each element.
 * Average Case:
 *    THETA(n) - Average case for deallocating memory.
 * Total Complexity:
 *    O(n)
 */
SortedMultiMap::~SortedMultiMap() {

}