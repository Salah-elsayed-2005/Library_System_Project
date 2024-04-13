#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
using namespace std;
using namespace OurString;
using namespace OurBook;
using namespace OurUser;

int main()
{
    vector<Book*> library_books={};
    vector<User*> library_users;
    //vector<Loan*> library_loans;
    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
    Member tst1;
    Librarian lib;

   /* Book* book = new Book;
    book->setTitle("Calculus");
    book->setAuthor("Stewart");
    book->setPublicationYear(2012);
    book->setAvailability(true);
    book->setGenre("Math");
    book->setIsbn("8624625635653");
    book->setQuantity(32);
    library_books.push_back(book);

    Book* book2 = new Book;
    book2->setTitle("Calculus");
    book2->setAuthor("Larson");
    book2->setPublicationYear(2004);
    book2->setAvailability(false);
    book2->setGenre("Math");
    book2->setIsbn("8624625635669");
    book2->setQuantity(18);
*/
    Book* book3=new Book("Calculus","Larson","8624625635663",2012 ,"Math" );
    Book* book4=new Book("Calculus","Stewart","8624625635669",2004 ,"Math" );
    book3->setQuantity(32);
    book4->setQuantity(0);
    library_books.push_back(book3);
    library_books.push_back(book4);

    Search_results=tst1.searchForBook_title(library_books,"Calculus");
    for(auto it:Search_results){
        it->printData();
    }
     lib.addBook(library_books, book3);
     lib.addBook(library_books, book4);


     library_users.push_back(&tst1);
     library_users.push_back(&lib);

     Search_results=tst1.searchForBook_title(library_books,"Calculus");
     for(auto it:Search_results){
         it->printData();
     }
    for (auto it:library_users) {
        it->showdata();
    }
      return 0;
}

