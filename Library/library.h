#ifndef _LIBRARY_H_
#define _LIBRARY_H_
#include<iostream>
using namespace std;

#define SIZE_L 25

class library{
protected:
	int num_books;
	int num_titles;
	char *titles[SIZE_L];
public:
	library();
	~library();
	void set_library();
	void compare_titles();
	friend ostream &operator<<(ostream &stream, library &ob);
};

#endif