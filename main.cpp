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
    vector<Book*> library_books;
    vector<User*> library_users;
    vector<Loan*> library_loans;

    Book* book = new Book;
    book->setTitle("Calculus");
    book->setAuthor("Stewart");
    book->setPublicationYear(2012);
    book->setAvailability(true);
    book->setGenre("Math");
    book->setIsbn("8624625635653");
    book->setQuantity(32);

    Librarian lib;
    lib.addBook(library_books, book);

     return 0;
}

