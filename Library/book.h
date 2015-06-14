#ifndef _BOOK_H_
#define _BOOK_H_
#include "library.h"
using namespace std;

#define SIZE_B 5
#define NUM 5

class book : public library{
private:
	char *authors[SIZE_B];
	int num_authors;
	bool available;
	char date[11];
public:
	book();
	~book();
	void set_book();
	bool check_availability(char ch);
	void compare_authors();
	book &operator=(book &book_t);
	friend ostream& operator<< (ostream& stream, book& ob);
	friend void show_alphabetical(book books[]);
	friend void show_dates(book books[]);
	friend void save_books(book books[]);
};


#endif