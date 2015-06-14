#include<cstring>
#include<fstream>
#include<cstdlib>
#include "library.h"
#include "book.h"
using namespace std;
#define SIZE_NAME 50

bool check_day(int day, int month, int year);
bool check_month(int month);
bool check_year(int year);
char* make_date(int day, int month, int year);

book::book()
{
	int i;

	for(i=0; i<SIZE_B; i++)
		authors[i] = NULL;
	titles[0] = NULL;

	num_authors = 0;
	available = false;
	strcpy(date, "24.05.2014");
}

void book::set_book()
{
	int i, j, len;
	char p[SIZE_NAME], ch;
	int day, month, year;

	cout << "\n\nEnter title of the book: ";
	cin.getline(p, SIZE_L);
	len = strlen(p) + 1;
	titles[0] = new char[len];
	if(!titles[0])
	{
		cout << "Allocation error.\n";
		exit(1);
	}
	strcpy(titles[0], p);

	do{
		cout << "Enter number of authors: ";
		cin >> num_authors;
		if(num_authors>SIZE_B)
			cout << "Authors may be maximum " << SIZE_B << ".\n" ;
	}while(num_authors<1 || num_authors>SIZE_B);

	cin.ignore(1, '\n');

	for(i=0; i<num_authors; i++)
	{
		cout << "Enter author{" << i+1 << "}: ";
		cin.getline(p, SIZE_NAME);

		len = strlen(p) + 1;
		authors[i] = new char[len];
		if(!p)
		{
			cout << "Allocation error.\n";
			exit(1);
		}
		strcpy(authors[i], p);
	}

	compare_authors();

	do{
		cout << "Enter if the book is available(y/n): ";
		cin >> ch;	
	}while(!check_availability(ch));

	cout << "Enter the date of the loan\n";

	do{
	   cout << "  Enter year: ";
	   cin >> year;
	}while(!check_year(year));

	do{
	   cout << "  Enter month: ";
	   cin >> month;
	}while(!check_month(month));

	do{
	   cout << "  Enter day: ";
	   cin >> day;
	}while(!check_day(day, month, year));

	strcpy(date, make_date(day, month, year));
	cin.ignore(1, '\n');
}

void book::compare_authors()
{
	int i, j, len;
	char p[SIZE_NAME];
	for(i=0; i<num_authors-1; i++)
		for(j=i+1; j<num_authors; j++)
			if(!strcmp(authors[i],authors[j]))
			{
				delete []authors[j];
				cout << "Can't add one author many times in one book. Enter new: ";
				cin.getline(p, SIZE_NAME);
				len = strlen(p) + 1;
				authors[j] = new char[len];
				if(!p)
				{
					cout << "Allocation error.\n";
					exit(1);
				}
				strcpy(authors[j], p);
			}
}

bool book::check_availability(char ch)
{
	if(ch=='y')  
	{
		available = true;
		return true;
	}
	else if(ch=='n')
	{
		available = false;
		return true;
	}
	else 
	{
		cout << "You can choice only between yes and no. Try again.\n";
		return false;
	}
}

book::~book()
{
	int i;
	for(i=0; i<num_authors; i++)
		if(authors[i]!=NULL)
			delete []authors[i];
	if(titles[0]!=NULL)
		delete []titles[0];
}

book &book::operator=(book &book_t)
{
	delete []titles[0];
	titles[0] = new char[strlen(book_t.titles[0]) + 1];
	if(!titles[0])
	{
		cout << "Allocation error.\n";
		exit(1);
	}
	strcpy(titles[0], book_t.titles[0]);
	
	num_authors = book_t.num_authors;
	available = book_t.available;

	int i;
	for(i=0; i<num_authors; i++)
	{
		delete []authors[i];
		authors[i] = new char[strlen(book_t.authors[i]) + 1];
		if(!authors[i])
		{
			cout << "Allocation error.\n";
			exit(1);
		}
		strcpy(authors[i], book_t.authors[i]);
	}
	strcpy(date, book_t.date);

	return *this;
}

ostream& operator<<(ostream& stream, book& ob)
{
	int i;
	stream << "Name of the book: " << ob.titles[0] << endl;
	stream <<"Name/s of the author/s:  ";
	for(i=0; i<ob.num_authors; i++)
		stream << "Author{" << i+1 << "}: " << ob.authors[i] << "\n\t\t\t ";
	stream << "The book is: ";
	if(ob.available)
		stream << "available\n";
	else
		stream << "unavailable\n";
	stream << "Date of loan of the book: " << ob.date << "\n\n\n";

	return stream;
}

void show_alphabetical(book books[])
{
	int i, j;
	book temp;

	cout << "The available books in alplabetical order of the authors:\n";

	for(i=0; i<NUM-1; i++)
	{
		for(j=i+1; j<NUM; j++)
			if(books[i].available && books[j].available)
			  if(strcmp(books[i].authors[0], books[j].authors[0])==1)
			  {
				 temp = books[i];
				 books[i] = books[j];
				 books[j] = temp;
			 }
	}
	for(i=0; i<NUM; i++)
	{	
		if(books[i].available)
		  cout << books[i] << endl;
	}
}

void show_dates(book books[])
{
	int i;
	int day, month, year;
	bool flag;
	char the_date[11];

	cout << "Enter the date you want\n";
	do{
	   cout << "  Enter year: ";
	   cin >> year;
	}while(!check_year(year));

	do{
	   cout << "  Enter month: ";
	   cin >> month;
	}while(!check_month(month));

	
	do{
	   cout << "  Enter day: ";
	   cin >> day;
	}while(!check_day(day, month, year));
	

	strcpy(the_date, make_date(day, month, year));

	flag = false;
	cout << "Titles:\n";
	for(i=0; i<NUM; i++)
		if(!strcmp(the_date, books[i].date))
		{
			cout << "\t" << books[i].titles[0] << endl;
			flag = true;
		}
	if(!flag)
		cout << "There aren't occupied books on this date.\n\n";
}

void save_books(book books[])
{
	int i;
	ofstream file_authors("many_authors.txt");
	if(!file_authors)
	{
		cout << "Can't open 'many_authors.txt'\n";
		exit(1);
	}
	for(i=0; i<NUM; i++)
		if(books[i].num_authors>1)
			file_authors << books[i];

	cout << "The information is saved in 'many_authors.txt'\n\n\n";
	file_authors.close();
}

bool check_year(int year)
{
	if(year<2001 || year>2014)
	{
	  cout << "Year must be between 2001 and 2014.\n";
      return false;
	}
	return true;
}

bool check_month(int month)
{
	if(month<1 || month>12)
	{
	  cout << "Month must be between 1 and 12.\n";
	  return false;
	}
	return true;
}

bool check_day(int day, int month, int year)
{
	   if((month==4 || month==6 || month==9 || month==11) && (day>30 || day<1))
	   {
			cout << "The month you entered has 30 days.\n";
			return false;
	   }
	   else if(month==2 && (day>28 || day<1) && year%4!=0)
	   {
			cout << "February has 28 days.\n";
			return false;
	   }
	   else if(month==2 && (day>29 || day<1) && year%4==0)
	   {
			cout << "February has 29 days.\n";
			return false;
	   }
	   else if(day<1 || day>31)
	   {
		   cout << "The month you entered has 31 days.\n";
		   return false;
	   }
	   else
		    return true;
}

char* make_date(int day, int month, int year)
{
	char d[3], m[3], y[5], res[11];
	itoa(day, d, 10);
	itoa(month, m, 10);
	itoa(year, y, 10);

	if(day<10)
		strcpy(res, "0");
	strcat(res, d);
	strcat(res, ".");
	if(month<10)
		strcat(res, "0");
	strcat(res, m);
	strcat(res, ".");
	strcat(res, y);

	return res;
}