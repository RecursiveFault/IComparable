/*
File Name: Icomparable.h
Author: Tim McCord
Course/Project: CSC 402/502 Spring 2015, Project3 possible solution
Date: 01/01/1970
*/

#pragma once

#include <iostream> 
#include <string>

using namespace std;

class IComparable
{
public:

	// by convention
	virtual ~IComparable() { }

	// Explicit operator= needed to support copy assignment operations of IComparables
	// By providing a default implementation, I can allow subclasses to defer their implementations
	//   but the behavior may not be functionally correct
	virtual const IComparable & operator= (const IComparable & rhs) {
		// cout << "Calling the base class operator= " << endl ; 
		return *this;
	}

	// If you chose the pure virtual option below, you will need two operator= 
	// member functions in each of the Integer and Character classes--one that 
	// provides an implementation with the exact signature and one that provides a 
	// concrete implementation of operator= for 
	// virtual const IComparable & operator= (const IComparable & rhs) =0 ;

	// DEMO: Adds the value stored in rhs to this object's value.   
	//  This was a hint in the assignment to show how to handle overriding in the derived classes
	virtual void add(const IComparable & rhs) = 0;

	// pure virtual function forces derived classes to implement a compare function 
	virtual int  compare(const IComparable & icmp) const = 0;

	// public accessor to faciliate implementation of the << operator; also pure virtual
	virtual void print(ostream & out = cout) const = 0;

	// Each of the following relational operators can now be implemented in the base class
	//    using the compare member function
	virtual bool operator<  (const IComparable & rhs) const {
		return (compare(rhs) < 0);
	}

	virtual bool operator>  (const IComparable & rhs) const {
		return (compare(rhs) > 0);
	}
	virtual bool operator==  (const IComparable & rhs) const {
		return (compare(rhs) == 0);
	}
	virtual bool operator!=  (const IComparable & rhs) const {
		return (compare(rhs) != 0);
	}
	virtual bool operator<= (const IComparable & rhs) const {
		return (compare(rhs) <= 0);
	}
	virtual bool operator>= (const IComparable & rhs) const {
		return (compare(rhs) >= 0);
	}
};

class Integer : public IComparable
{
public:

	Integer(const int i = 0)
		: value(i) { }

	// copy constructor for IComparable references
	Integer(const IComparable & rhs)
		: value(dynamic_cast<const Integer &>(rhs).value) {   }

	// copy assignment operator
	// This overrides the dummy implementation of operator= in the base class
	const IComparable & operator= (const IComparable & rhs) {
		//cout << "Calling the Integer override operator= " << endl;
		value = dynamic_cast<const Integer &>(rhs).value;
		return *this;
	}

	// If I don't provide a default implementation for IComparable::operator=
	//  or make it a pure virtual function, I have to implement specific
	//  subclass versions of operator=
	const Integer & operator= (const Integer & rhs) {
		//cout << "Calling the Integer-specific version of operator=" << endl ;
		value = rhs.value;
		return *this;
	}


	// Adds the value stored in rhs to this object's value
	void add(const IComparable & rhs) {
		value += dynamic_cast<const Integer &>(rhs).value;
	}

	// NO GOOD as far as fulfilling the contract specified by IComparable ... 
	//virtual int compare( const Integer & rhs ) const { return 0 ;} 

	// As per the contract, compare must accept an IComparable reference 
	// return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > this object
	int compare(const IComparable & rhs) const {
		if (this->value < dynamic_cast<const Integer &>(rhs).value)
			return -1;
		else if (this->value > dynamic_cast<const Integer &>(rhs).value)
			return 1;
		else
			return 0;
	}

	void print(ostream & out = cout) const { out << value; }

private:
	int value;
};



class Character : public IComparable
{
public:
	Character(const char c = '?')
		: value(c) { }

	// copy constructor for IComparable references
	Character(const IComparable & rhs)
		: value(dynamic_cast<const Character &>(rhs).value) {   }

	// copy assignment operator
	const IComparable & operator= (const IComparable & rhs) {
		//cout << "Calling the Character override operator= " << endl;
		value = dynamic_cast<const Character &>(rhs).value;
		return *this;
	}

	// Only needed if there is no operator= implementation for IComparables
	const Character & operator= (const Character & rhs) {
		value = rhs.value;
		return *this;
	}

	// Adds the value stored in rhs to this object's value
	void add(const IComparable & rhs) {
		value += dynamic_cast<const Character &>(rhs).value;
	}


	// As per the contract, compare must accept an IComparable reference 
	// return -1 if this object < icmp, 0 if this ojbect == icmp, 1 if icmp > this object
	int compare(const IComparable & rhs) const {
		if (this->value < dynamic_cast<const Character &>(rhs).value)
			return -1;
		else if (this->value > dynamic_cast<const Character &>(rhs).value)
			return 1;
		else
			return 0;
	}

	void print(ostream & out = cout) const { out << value; }

private:
	char value;
};

// This works because we required all IComparable derived classes to implement print()
ostream & operator<< (ostream & out, const IComparable & i) { i.print(out); return out; }


// CSC 502:  functor for use with std::sort
struct LessThan
{
	bool operator() (const IComparable* first, const IComparable* second) {
		return first->compare(*second) < 0;
	}
};

/* Another way to handle the functor that would require a minor change to the test driver
since it is a function, rather than a struct (or class) that overloads the () operator.
*/

bool lessThan(const IComparable * lhs, IComparable * rhs)
{
	return (*lhs < *rhs);
}

/* The call would then changed to this:
#ifdef CSC502
std::sort( intVector.begin(), intVector.end(), lessThan ) ;
#endif
*/

