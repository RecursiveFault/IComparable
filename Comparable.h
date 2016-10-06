/*
File Name: Comparable.h
Author: Matthew Moellman
Course: CSC 402
Date: 10 April 2016
*/
#pragma once
using namespace std; 


template <typename T>
class Comparable
{
	/*
	Assume that all 6 relational operators are built in for any types passed, so the operator overloads function correctly. (note that this is the case for the iComparable classes)

	Assume << is built in for any type passed. (Note that this is the case for the iComparable classes)

	No-arg constructor assumes that the type passed holds a value of whatever type it was declared with, and it must be able to have a no-arg constructor itself. If a class was passed that did not have either of these 
	conditions, it would break the logic in the constructor. (note that this is the case for the iComparable classes)

	The external << overload for T assumes that a print function will correctly be implemented for all types passed. 
	*/
public:

	Comparable(const T & initialValue = T()) //This lets the value be passed, or have a default empty value of the type declared.
		:value(initialValue) {} //I also just assumed having any char passed default to empty was fine

	Comparable(const Comparable<T> & rhs) //the default constructors worked just as well, but I just wanted to write explicit ones
	{
		value = rhs.value;
	}

	const Comparable<T> & operator= (const Comparable<T> & rhs)  //same as copy constructor
	{
		value = rhs.value;
		return *this;
	}


	//6 relational operator overrides, see comment block at the top for assumptions
	bool operator< (const Comparable<T> & rhs) const
	{
		if (this->value < rhs.value)
			return true;
		else
			return false;
	}
	bool operator<= (const Comparable<T> & rhs) const
	{
		if (this->value <= rhs.value)
			return true;
		else
			return false;
	}
	bool operator== (const Comparable<T> & rhs) const
	{
		if (this->value == rhs.value)
			return true;
		else
			return false;
	}
	bool operator!= (const Comparable<T> & rhs) const
	{
		if (this->value != rhs.value)
			return true;
		else
			return false;
	}
	bool operator> (const Comparable<T> & rhs) const
	{
		if (this->value > rhs.value)
			return true;
		else
			return false;
	}
	bool operator>= (const Comparable<T> & rhs) const
	{
		if (this->value >= rhs.value)
			return true;
		else
			return false;
	}

	//print is again used to utilize the external << operator
	void print(ostream & out=cout) const
	{
		out << value;
	}

private:
	T value;
};

template <typename T> //see comment block at the start for assumptions
ostream & operator<< (ostream & out, const Comparable<T> ii) { ii.print(out); return out; }
