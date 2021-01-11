#ifndef AUXFUNCTIONS_H_
#define AUXFUNCTIONS_H_

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class NoRepeating {
public:
    static vector<int> AllNifs;
    static vector<string> AllBakeryAddresses;
};

class NifAlreadyUsed {
    int nif;
public:
    NifAlreadyUsed(int nif) : nif(nif) {
        cout << "The nif " << nif << " is already being used\n";
    }
};

class BakeryAddressAlreadyUsed {
    string address;
public:
    BakeryAddressAlreadyUsed(string address) : address(address) {
        cout << "This address, " << address << ",is already being used by another bakery\n";
    }
};

template <class T>
void insertionSort(vector<T> &v)
{
    for (unsigned int p = 1; p < v.size(); p++)
    {
    	T tmp = v[p];
    	int j;
    	for (j = p; j > 0 && tmp < v[j-1]; j--)
    		v[j] = v[j-1];
    	v[j] = tmp;
    }
}

template <class T, class A>
int sequencialSearch(vector<T> vec, A x) {
	for (unsigned int i = 0; i < vec.size(); i++)
		if (vec[i] == x)
			return i;
	return -1;
}

#endif /* AUXFUNCTIONS_H_ */