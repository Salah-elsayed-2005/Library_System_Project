#include <iostream>
#include <vector>
#include <algorithm>
#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include "DatabaseManager.h"


#if defined(_WIN32) || defined(_WIN64)
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear"; 
#endif

using namespace std;
using namespace OurBook;

vector<Book*> library_books; // Assuming you have a vector to store Book objects
vector<User*> library_users;
vector<Loan*> library_loans;

vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
vector<Book*> Cart;

Librarian lib;
Student student;
Staff staff;
Faculty faculty;



void printHeader();
void printMemberMenu();
void printSearchOptions();
void printLibMenu();
bool checkBack();
bool checkClose();
void printExit();
void searchByISBN();
void searchByYear();
void searchByTitle();
void searchByAuthor();
void searchByGenre();
void searchForBook();
void viewAvailableBooks();
void addToCart();
void viewCart();
void updateMemberData();
void updateBookData();
void updateMemberMenu();
void updateBookMenu();
void updatepassword();
void diplaydata();
void loanrequest();
void viewloans();
void processloans();
void checkforoverdues();
void returnbook();
Member* checktype(str);


vector<Book*> ex_library_books(library_books);
vector<User*> ex_library_users(library_users);
vector<Loan*> ex_library_loans(library_loans);


bool endOfProgram=false;
bool backToTheMainMenu=false;

User* login();
void memberMenu();
void libMenu();
int main() {

    DatabaseManager dbManager("test.db");
    dbManager.createTables();
    dbManager.insertSampleData();
    dbManager.insertBook("9780132350884", "Effective C++", "Scott Meyers", 2005, "Programming", true, 10);
    dbManager.displayBooks();




    checkforoverdues();// this function will be called whenever the program runs and will check if there is an overdue on any loan

    student.setName("Ziad");
    student.setId("101285");
    student.setPassword("242004");
    staff.setName("Marwan");
    staff.setId("3akeedo");
    staff.setPassword("<reham>");
    faculty.setName("Elshabeeh");
    faculty.setId("69420");
    faculty.setPassword("password");
    User *user1=&student;
    User *user2=&staff;
    User *user3=&faculty;
    library_users.push_back(user1);
    library_users.push_back(user2);
    library_users.push_back(user3);


    //User* user = login();

    // Adding books to the library
    Book* book1 = new Book("Calculus", "Hussein", "8624625635660", 2013, "Math");
    book1->setQuantity(20);
    Book* book2 = new Book("Discrete", "Atta", "8624625635661", 2012, "Not math");
    book2->setQuantity(30);
    Book* book3 = new Book("Data Structures", "Ziad", "8624625635662", 1984, "Math");
    book3->setQuantity(15);
    Book* book4 = new Book("Object oriented programming", "Larson", "8624625635663", 2012, "maybe Math");
    book4->setQuantity(1);
    Book* book5 = new Book("Linear Algebra", "Stewart", "8624625635669", 2004, "Math");
    Book* book6 = new Book(*book5);
    book4->setQuantity(1);

    library_books.push_back(book1);
    library_books.push_back(book2);
    library_books.push_back(book3);
    library_books.push_back(book4);
    library_books.push_back(book5);
    library_books.push_back(book6);

    dbManager.insertBook(book6);
    dbManager.insertBook(book2);
    dbManager.insertBook(book3);
    dbManager.insertBook(book4);
    dbManager.insertBook(book1);

    ex_library_books = library_books;

    dbManager.displayBooks();
    dbManager.disp();
    dbManager.exportBooks(library_books);
    if(Student* stPtr = dynamic_cast<Student*>(user1)){
        Loan* loan1 = stPtr->requestLoan(book2,Cart.size());
        Loan* loan2 = stPtr->requestLoan(book1,Cart.size());
        Loan* loan3 = stPtr->requestLoan(book3,Cart.size());
        Loan* loan4 = stPtr->requestLoan(book4,Cart.size());

        Librarian* lib = new Librarian();

        lib->processLoanRequest(loan1, true);
        lib->processLoanRequest(loan2, false);
        lib->processLoanRequest(loan3, true);
        lib->processLoanRequest(loan4, true);

        library_loans.push_back(loan1);
        library_loans.push_back(loan2);
        library_loans.push_back(loan3);
        library_loans.push_back(loan4);

        dbManager.insertLoan(loan1);
        dbManager.insertLoan(loan2);
        dbManager.insertLoan(loan3);
        dbManager.insertLoan(loan4);


        Librarian* lib = new Librarian();

        lib->processLoanRequest(loan1, true);
        lib->processLoanRequest(loan2, false);
        lib->processLoanRequest(loan3, true);
    }
    dbManager.insertUser(user1);
    dbManager.insertUser(user2);
    dbManager.exportUsers(library_users); // NOT WORKING YET
    //dbManager.getLoanedBooksByUser("stu-101285");
    //dbManager.tmep();
    memberMenu();
    //libMenu();


    return 0;
}

Book* getBookPtr(str ISBN);