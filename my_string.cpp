#include "my_string.h"

my_string::my_string(){
	// default constructor
	ptr = new char[0]; // create new allocated memory default to zero
	sz = 0; // default size to zero
	cap = 0; // default capacity to zero
}

my_string::my_string(int n){
	// constructor with int n allocated memory
	ptr = new char[n]; // create new allocated memory
	this->cap = n; // capacity
	sz = 0; //  size is equal to zero
}

my_string::my_string(const char* p){
	// constructor with string creates a string with same content
	int i = 0; // initialize counter
	while (p[i] != '\0') { // while loop to detect null character
		i++; // increase counter
	}
	sz = i; // capacity is equal to argument size
	cap = i; // capacity is equal to arguement capacity
	ptr = new char[i]; // create new allocated memory
		
	int j = 0; // initialize index
	while (p[j] != '\0') { // while loop to detect null character
		ptr[j] = p[j]; // assign argument p to ptr
		j++; // increase index
	}
}

my_string::my_string(const my_string& s){
	// copy constructor makes a copy of the argument string
	sz = s.size(); // size is equal to argument size
	cap = s.capacity(); // capacity is equal to argument capacity
	ptr = new char[cap]; // create new allocated memory
	
	for(int i = 0; i<s.sz; i++){
		ptr[i] = s.ptr[i]; // copy argument string to ptr
	}
}

my_string::~my_string(){
	// desctructor
	delete[] ptr;
}

int my_string::size() const {
	// returns the number of characters of s
	return sz; 
}

int my_string::capacity() const{
	// returns the length in bytes of allocated memory
	return cap;
}

bool my_string::empty(){
	// returns true if s is empty false otherwise
	if (sz == 0)
		return true; // return true if size is zero
	else
		return false; // otherwise return false
}

char& my_string::operator[](int i){
	// returns character at index i of s, no bound checking
	return ptr[i]; 
}
	
char my_string::at(int i) const{
	// returns character at index i of s, out_of_range error
	if (i<0||i>sz-1)
		throw out_of_range("Size is Out of Range!");
	return ptr[i]; 
}

void my_string::operator+=(const my_string& q){
	// appends the string q to s
	int size = this->sz + q.size(); // initialize expected string size

	if (cap < size){ // check current capcity with expected size
		resize(size); // call resize function
		
		for(int j = sz; j < size; j++){
			ptr[j] = q.at(j-sz); // attach q to end of ptr
		}
		
		sz = size; // update size
	}
	else{
		for(int j = sz; j < size; j++){
			ptr[j] = q.at(j-sz); // attach q to end of ptr
		}
		sz = size; // update size
	}
}

void my_string::operator+=(const char c){
	// appends the character c to s
	int size = this->sz + 1; // initialize expected string size
	
	if (cap <size){ // check current capcity with expected size
		resize(size); // call resize function
		
		ptr[sz] = c; // attach c to end of ptr
		sz = size; // update size
	}
	else{
		ptr[sz] = c; // attach c to end of ptr
		sz = size; // update size
	}
}


my_string& my_string::insert(int i, const my_string& s){
	// insert string s before position i in s and returns a reference
	int size = this->sz + s.size(); // initialize expected string size
	
	if (cap <size){
		
		while(cap <= size){
		// while loop to check current capaicy
		if(cap == 0)
			cap++; // create capacity if capacity is zero
		else 
			cap *= 2; // double capacity
		
		char* temp = new char[cap]; // create new allocated memory
		
		// insert the first part of ptr before position i into temp
		for(int x = 0; x<i; x++){
			temp[x] = ptr[x];
		}
		
		// insert the rest part of ptr after postion i into temp
		for(int x = i; x<sz; x++){
			temp[x+s.size()] = ptr[x];
		}
		
		// insert content of s into temp
		for(int x = 0; x<s.size(); x++){
			temp[i+x] = s.at(x);
		}
		
		delete[] ptr; // delete old ptr
		ptr = temp; // point ptr to temp
		
		sz = size; // update size
		}
	}
	else{
		
		char* temp = new char[cap]; // create new allocated memory
		
		// insert the first part of ptr before position i into temp
		for(int x = 0; x<i; x++){
			temp[x] = ptr[x];
		}
		
		// insert the rest part of ptr after postion i into temp
		for(int x = i; x<sz; x++){
			temp[x+s.size()] = ptr[x];
		}
		
		// insert content of s into temp
		for(int x = 0; x<s.size(); x++){
			temp[i+x] = s.at(x);
		}
		
		delete[] ptr; // delete old ptr
		ptr = temp; // point ptr to temp
		
		sz = size; // update size
	}
	return *this; // return string reference
}

my_string& my_string::operator=(const my_string& q){
	// assigns a string to another string (s=q)
	char* temp = new char[q.capacity()]; // create new allocated memory

	for(int i = 0; i<q.size(); i++){
		temp[i] = q.at(i); // assign q to temp
	}
		
	delete[] ptr; // delete old ptr
	ptr = temp; // point ptr to temp
	sz = q.size(); // update size
	cap = q.capacity(); // update capacity
	
	return *this; // return string reference
}

ostream& operator<<(ostream& os, my_string& q){
	// overload output operator
	for(int i = 0; i < q.size(); i++){
		os << q[i]; // output q array
	}
	return os;
}

istream& operator>>(istream& is, my_string& s){
	// overload input operator
	int i = 100; // size of new memory for temp
	char* temp = new char[i]; // create new allocated memory
	int j = 0; // initialize temp index j
	is.getline(temp, i); // read user input
	char t = temp[j]; // initialize user input char array
	while(!isspace(t) && t != '\0'){
		// while loop to read input until whitespace is hit
		if(s.size() + 1 > s.cap){ // check current capacity
			s.resize(s.size()+1); // call resize function
		}
		s.sz++; // update size
		s[j] = t; // assign input to t
		j++; // increase index number
		t = temp[j]; // assign t to temp
	}
	delete[] temp;
	return is;
}

void my_string::resize(const int size){
	// resize function to double current capacity
	while(cap <= size){
		// while loop to check current capaicy
		if(cap == 0)
			cap++; // create capacity if capacity is zero
		else 
			cap *= 2; // double capacity
	}
		
	char* temp = new char[cap]; // create new allocated memory
		
	for(int i = 0; i<sz; i++){
		temp[i] = ptr[i]; // assign ptr value to temp
	}
	
	delete[] ptr; // delete old ptr
	ptr = temp; // point ptr to temp	
}
