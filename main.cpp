#include <iostream>
#include <vector>
#include <string>
#include "sqlite3.h"
#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include "DatabaseManager.h"


using namespace std;
using namespace OurString;
using namespace OurBook;

int main(){
    Student st;
    User* ptr

    DatabaseManager dbManager("test.db");
    dbManager.createTable();
    dbManager.insertSampleData();
    dbManager.insertBook("9780132350884", "Effective C++", "Scott Meyers", 2005, "Programming", true, 10);
    dbManager.insertBook("9780132350000", "Not Effective C++", "Fouad", 2010, "Programming", true, 1);
    dbManager.searchBooks("Title","Not Effective C++");
    dbManager.searchBooks("ISBN","9780132350884");
    dbManager.displayBooks();
    dbManager.decrementBookQuantity("9780132350000");
    dbManager.deleteBook("9780132350884");
    dbManager.displayBooks();



    vector<Book*> library_books={};
    vector<User*> library_users;
    vector<Loan*> library_loans;

    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search

    Book* book = new Book;
    book->setTitle("Calculus");
    book->setAuthor("Stewart");
    book->setPublicationYear(2012);
    book->setGenre("Math");
    book->setIsbn("8624625635653");
    book->setQuantity(32);
    library_books.push_back(book);

    Book* book2 = new Book;
    book2->setTitle("Calculus");
    book2->setAuthor("Larson");
    book2->setPublicationYear(2004);
    book2->setGenre("Math");
    book2->setIsbn("8624625635663");
    book2->setQuantity(32);
    library_books.push_back(book2);

    Librarian lib;

*/
     return 0;
}

