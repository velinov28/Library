#include<cstring>
#include "library.h"
using namespace std;

library::library()
{
	int i;
	num_books = 0;
	num_titles = 0;

	for(i=0; i<SIZE_L; i++)
		titles[i] = NULL;
}

void library::set_library()
{
	int i, j, len;
	char p[SIZE_L];

	do{
	   cout << "Enter number of books: ";
	   cin >> num_books;
	} while(num_books<0);
	
	do{
	   cout << "Enter number of titles: ";
	   cin >> num_titles;

	   if(num_books < num_titles)
		   cout << "Books must be more than titles.\n";
	} while((num_books < num_titles) || num_titles<0);
	
	cin.ignore(1, '\n');

	for(i=0; i<num_titles; i++)
	{
		cout << "Enter title{" << i+1 << "}: ";
		cin.getline(p, SIZE_L);
		len = strlen(p) + 1;

		titles[i] = new char[len];
		if(!titles[i])
		{
			cout << "Allocation error.\n";
			exit(1);
		}
		strcpy(titles[i], p);

	}
	compare_titles();
}

void library::compare_titles()
{
	int i, j, len;
	char p[SIZE_L];
	for(i=0; i<num_titles-1; i++)
		for(j=i+1; j<num_titles; j++)
			if(!strcmp(titles[i],titles[j]))
			{
				delete []titles[j];
				cout << "Can't add existing title. Enter new: ";
				cin.getline(p, SIZE_L);
				len = strlen(p) + 1;
				titles[j] = new char[len];
				if(!p)
				{
					cout << "Allocation error.\n";
					exit(1);
				}
				strcpy(titles[j], p);
			}
}

library::~library()
{
	int i;
	for(i=0; i<num_titles; i++)
		if(titles[i]!=NULL)
		   delete []titles[i];
}

ostream &operator<<(ostream &stream, library &ob)
{
	int i;

	stream << "Number of books: " << ob.num_books << endl;
	stream << "Number of titles: " << ob.num_titles << endl;
	stream << "Titles of the books: " << endl;
	for(i=0; i<ob.num_titles; i++)
		stream << "  " << ob.titles[i] << endl;

	return stream;
}
