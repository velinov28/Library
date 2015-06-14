#include<fstream>
#include "library.h"
#include "book.h"
using namespace std;

int menu()
{
	int i;
	char ch;
	do{
		cout << "+------------------------------------------------------------------------------\n";
	    cout << "|Menu:\n";
		cout << "|    1.Display info about available books alphabetical ordered by author's name\n";
		cout << "|    2.Display books'titles which are occupied on a specified date\n";
		cout << "|    3.Store in file info about books which have more than one author\n";
		cout << "|    4.Exit the application\n";
		cout << "|  Enter your choice: ";
		cin >> i;
		
		do{
		   cout << "Clean screen?(y/n): ";
		   cin >> ch;
		   if(ch=='y')
			   system("cls");
		}while(ch!='y' && ch!='n');


		if(i<1 || i>4)
			cout << "Invalid option.\n";

	} while(i<1 || i>4);

	return i;
}


int main()
{
	book *knigi = new book[NUM];
	if(!knigi)
	{
		cout << "Allocation error.\n";
		return 1;
	}
	int i;
	int choice;
	ofstream info("all_info.txt");
	if(!info)
	{
		cout << "Can't open 'all_info.txt'.\n";
		return 1;
	}

	cout << "First enter " << NUM << " books.";
	for(i=0; i<NUM; i++)
		knigi[i].set_book();

	for(i=0; i<NUM; i++)
		info << knigi[i];
	cout << "The information is saved in 'all_info.txt'\n\n\n";
	info.close();

	while(true)
	{
	  choice = menu();
	  switch(choice){
	      case 1: show_alphabetical(knigi);
		  		  break;
		  case 2: show_dates(knigi);
			      break;
		  case 3: save_books(knigi);
				   break;
		  case 4: exit(7);
		          break; 
	  }
	}
	delete []knigi;

	system("pause");
	return 0;
}