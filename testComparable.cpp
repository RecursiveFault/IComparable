/*
File Name: testComparable.cpp
Author: Tim McCord
Course/Project: CSC 402/502 Project 4 Test Driver
Date: 01/01/1970
*/

#pragma warning( disable: 4018 )//for VS

#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>     
#include "Comparable.h"
#include "IComparable.h" 

#define SIZE 10

// Uncomment this preprocessor directive for the CSC 502 extra requirement or CSC 402 extra credit  
// #define CSC502

using namespace std;

// forward declarations
template <typename T> void print(const vector<T> & v);
template <typename T> bool isSorted(const vector<T> & v);
template <typename T> void sort(vector<T> & v);

int main()
{
	srand(time(NULL));
	const string SEPARATOR = "=========================================";

	// PREVIEW of I/O Chapter:  Note the use of boolalpha in the output stream. 
	// Once enabled, it stays on until noboolalpha appears
	cout << boolalpha;

	cout << endl << "Comparable<int> constructor, =, and << tests:" << endl << SEPARATOR << endl;
	// default constructor
	Comparable<int> i0;
	cout << "i0 = " << i0 << endl;

	// single-arg constructor in two forms
	Comparable<int> i1 = 0;
	cout << "i1 = " << i1 << endl;
	Comparable<int> i2(10);
	cout << "i2 = " << i2 << endl;

	// Copy constructor
	Comparable<int> i3 = i2;
	cout << "i3 = " << i3 << endl;

	// = operator
	Comparable<int> i4 = 0;
	i4 = i3;
	cout << "i4 = " << i4 << endl;

	cout << endl << " Comparable<int> relational operator tests:" << endl << SEPARATOR << endl;
	(i0 == i1) ? cout << "i0 == i1 is " << (i0 == i1) << endl : cout << "ERROR: i0 == i1 should be true" << endl;
	(i1 < i2) ? cout << "i1 <  i2 is " << (i1 < i2) << endl : cout << "ERROR: i1 <  i2 should be true" << endl;
	(i1 != i2) ? cout << "i1 != i2 is " << (i1 != i2) << endl : cout << "ERROR: i1 != i2 should be true" << endl;
	(i1 <= i2) ? cout << "i1 <= i2 is " << (i1 <= i2) << endl : cout << "ERROR: i1 <= i2 should be true" << endl;
	(i1 == i1) ? cout << "i1 == i1 is " << (i1 == i1) << endl : cout << "ERROR: i1 == i1 should be true" << endl;
	(i2 > i1) ? cout << "i2 >  i1 is " << (i2 > i1) << endl : cout << "ERROR: i2 >  i1 should be true" << endl;
	(i2 == i3) ? cout << "i2 == i3 is " << (i2 == i3) << endl : cout << "ERROR: i2 == i3 should be true" << endl;
	(i2 >= i1) ? cout << "i2 >= i1 is " << (i2 >= i1) << endl : cout << "ERROR: i2 >= i1 should be true" << endl;
	(i3 >= i3) ? cout << "i3 >= i3 is " << (i3 >= i3) << endl : cout << "ERROR: i3 >= i3 should be true" << endl;
	(i4 == i3) ? cout << "i4 == i3 is " << (i4 == i3) << endl : cout << "ERROR: i4 == i3 should be true" << endl;
	cout << endl;

	cout << endl << "Comparable<char> limited tests:" << endl << SEPARATOR << endl;
	Comparable<char> c0;
	cout << "c0 = " << c0 << endl;
	Comparable<char> c1 = 'a';
	cout << "c1 = " << c1 << endl;
	Comparable<char> c2 = 'z';
	cout << "c2 = " << c2 << endl;
	(c1 < c2) ? cout << "c1 < c2 = " << (c1 < c2) << endl : cout << "ERROR: c1 < c2 should be true" << endl;
	cout << endl;

	vector< Comparable<int> > intVector;
	// initialize vector of Comparable<int> objects
	for (int i = 0; i < SIZE; i++)
		intVector.push_back(Comparable<int>(rand()));

	cout << endl << "vector< Comparable<int> > tests:" << endl << SEPARATOR << endl;
	cout << endl << "intVector before sorting:" << endl;
	print(intVector);
	cout << "isSorted(intVector): " << isSorted(intVector) << endl;

#ifndef CSC502 
	cout << "Using local sort" << endl;
	sort(intVector);
#else
	cout << "Using std::sort" << endl;
	std::sort(intVector.begin(), intVector.end());
#endif

	cout << endl << "intVector after sorting:" << endl;
	print(intVector);
	cout << "isSorted(intVector): " << isSorted(intVector) << endl;

	cout << endl << "vector< Comparable<char> > tests:" << endl << SEPARATOR << endl;
	vector< Comparable<char> > charVector;
	// initialize with ASCII characters in the range 33 - 127 only
	for (int i = 0; i < SIZE; i++)
		charVector.push_back(Comparable<char>(rand() % 95 + 33));

	cout << endl << "charVector before sorting:" << endl;
	print(charVector);
	cout << "isSorted(charVector): " << isSorted(charVector) << endl;

#ifndef CSC502
	cout << "Using local sort" << endl;
	sort(charVector);
#else
	cout << "Using std::sort" << endl;
	std::sort(charVector.begin(), charVector.end());
#endif

	cout << endl << "charVector after sorting:" << endl;
	print(charVector);
	cout << "isSorted(charVector): " << isSorted(charVector) << endl;

	cout << endl << "Additional tests with various built-in types:" << endl << SEPARATOR << endl;
	Comparable<double> d1 = 9.0;
	cout << "d1 = " << d1 << endl;
	Comparable<double> d2 = 10.0;
	cout << "d2 = " << d2 << endl;
	cout << "d1 < d2 = " << (d1 < d2) << endl;
	cout << endl;


	/* The GNU g++ compiler does not support the alternate constructor syntax in the lines
	within the #ifndef __GNUG__ blocks.  With g++, we have to first construct the string
	or other object explicitly and let that object be the argument passed to the constructor,
	as shown in the #else blocks

	The typical error is:
	testComparable.cpp:155 : 27 : error : conversion from ‘const char[6]’ to non - scalar type ‘Comparable<std::basic_string<char> >’ requested
	Comparable<string> s1 = "Hello";
	^
	*/

	// However, using the default constructor works as expected with the GNU compiler
	Comparable<string> s0;
	cout << "s0 = " << s0 << endl;

	// Using traditional constructor syntax is OK as well in either VS or GCC (g++)
	Comparable<string> s00("Hi there!");
	cout << "s00 = " << s00 << endl;

	cout << endl;

#ifndef __GNUG__
	Comparable<string> s1 = "Hello";
#else
	string _s1("Hello");
	Comparable<string> s1 = _s1;
#endif 
	cout << "s1 = " << s1 << endl;

#ifndef __GNUG__
	Comparable<string> s2 = "World";
#else 
	string _s2("World");
	Comparable<string> s2 = _s2;
#endif 

	cout << "s2 = " << s2 << endl;
	cout << "s1 < s2 is " << (s1 < s2) << endl;

	cout << endl << "Tests with Project 3 IComparables:" << endl << SEPARATOR << endl;

#ifndef __GNUG__
	Comparable<Integer> ci1 = 0;
#else 
	Integer _ci1 = 0;
	Comparable<Integer> ci1 = _ci1;
#endif
	cout << "ci1 = " << ci1 << endl;

#ifndef __GNUG__
	Comparable<Integer> ci2 = 10;
#else 
	Integer _ci2 = 10;
	Comparable<Integer> ci2 = _ci2;
#endif

	cout << "ci2 = " << ci2 << endl;
	cout << "ciI < ci2 is " << (ci1 < ci2) << endl;
	cout << endl;

#ifndef __GNUG__
	Comparable<Character> cc1 = 'A';
#else
	Character _cc1 = 'A';
	Comparable<Character> cc1 = _cc1;
#endif 
	cout << "cc1 = " << cc1 << endl;

#ifndef __GNUG__
	Comparable<Character> cc2 = 'Z';
#else
	Character _cc2 = 'Z';
	Comparable<Character> cc2 = _cc2;
#endif 

	cout << "cc2 = " << cc2 << endl;
	cout << "cc1 < cc2 is " << (cc1 < cc2) << endl;

	cout << "Hit any key to end the program..." << endl;
	cin.get();    // portable "pause" 

	return 0;

}

template <typename T>
void print(const vector<T>  & v)
{
	// if the vector is larger than 100 print only the first
	// ten elements and the last ten
	int size = v.size();
	if (size > 100) {
		for (int i = 0; i < 10; i++)
			cout << v[i] << "\t";
		cout << " ... " << endl;
		for (int i = 0; i < 10; i++)
			cout << v[size - (i + 1)] << "\t";
		cout << endl;
	}
	else {
		for (auto item : v)
			cout << item << "\t";

		// If you use g++ and don't have a C++11 compatible version, use these lines instead
		// for (int i = 0; i << v.size(); i++)
		//  cout << v[i] << "\t";

		cout << endl;
	}
}

template <typename T>
bool isSorted(const vector<T> & v) {
	bool sorted = true;
	for (int i = 1; i < v.size(); i++)
		if (v[i] < v[i - 1]) {
			sorted = false;
			break;
		}
	return sorted;
}

template <typename T>
void sort(vector<T> & v) {
	int i, j, min;
	T tmp;

	// selection sort for simplicity... not efficiency 
	for (j = 0; j < v.size(); j++) {
		min = j;
		for (i = j + 1; i < v.size(); i++) {
			if (v[i] < v[min]) {
				min = i;
			}
		}

		if (min != j) {
			tmp = v[j];
			v[j] = v[min];
			v[min] = tmp;
		}
	}
}

