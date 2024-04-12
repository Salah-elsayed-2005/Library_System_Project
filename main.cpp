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
    vector<Loan*> library_loans;
    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search

    Book* book = new Book;
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
    book2->setAvailability(true);
    book2->setGenre("Math");
    book2->setIsbn("8624625635663");
    book2->setQuantity(32);
    library_books.push_back(book2);

    Librarian lib;
  //  lib.addBook(library_books, book);
    //lib.addBook(library_books, book2);

    Member Mem;
    // Search_results=Mem.searchForBook_title(library_books,"Calculus");
    for (auto it :Search_results) {
        it->printData();
    }
    Mem.requestLoan(Mem, lib, library_books);
     return 0;
}

