#include <stdexcept>
#include <iostream>
using namespace std;

class my_string {
public:
	my_string(); // default constructor
	my_string(int n); // constructor with int n allocated memory
	my_string(const char* p); // constructor with string creates a string with same content
	my_string(const my_string& s); // copy constructor makes a copy of the argument string
	~my_string(); // desctructor
	int size() const; // returns the number of characters of s
	int capacity() const; // returns the length in bytes of allocated memory
	bool empty(); // returns true if s is empty false otherwise
	char& operator[](int i); // returns character at index i of s, no bound checking
	char at(int i) const; // returns character at index i of s, out_of_range error
	void operator+=(const my_string& q); // appends the string q to s
	void operator+=(const char c); // appends the character c to s
	void resize(const int size); // resize function to double the capacity for allocated memory
	my_string& insert(int i, const my_string& s); // insert string s before position i in s and returns a reference
	my_string& operator=(const my_string& q); // assigns a string to another string (s=q)
	friend ostream& operator<<(ostream& os, my_string& q); // output operator
	friend istream& operator>>(istream& is, my_string& s); // input operator
private:
	char* ptr; // pointer to the dynamic arrary of type char
	int sz; // number of characters in the sring sz>=0
	int cap; // length in bytes of ptr allocated memeory, sz <= cap
};