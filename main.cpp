#include <iostream>
#include <vector>
#include <algorithm>
#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include "DatabaseManager.h"
#include "Functionalities.h"

using namespace std;
using namespace OurBook;

vector<Book*> library_books; // Assuming you have a vector to store Book objects
vector<User*> library_users;
vector<Loan*> library_loans;

vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
vector<Book*> Cart;
DatabaseManager dbManager("test.db");


void importFromDB(){
    dbManager.createTables();   /* creates 3 tables in database */
    dbManager.insertSampleData();

    /* importing books from database to library_books and copies it to ex_library_books to use it in DatabaseManager */
    dbManager.importBooks(library_books);
    ex_library_books = library_books;

    /* importing Users and Loans data from database to library vectors */
    dbManager.importUsers(library_users);
    ex_library_users = library_users;

    dbManager.importLoans(library_loans);
    ex_library_loans=library_loans;
}

void exportToDB(){
    dbManager.boomboom();   /* clearing database */

    /* exporting library vectors to database */
    for(auto &it : library_books){
        dbManager.insertBook(it);
    }
    for(auto &it : library_users){
        dbManager.insertUser(it);
    }
    for(auto &it : library_loans){
        dbManager.insertLoan(it);
    }
}
void free_vectors(){
    for(auto &it : library_books)
        delete it;
    for(auto &it : library_users)
        delete it;
    for(auto &it : library_loans)
        delete it;
}



int main() {


    importFromDB();
    checkforoverdues();// this function will be called whenever the program runs and will check if there is an overdue on any loan

    User* user = login();

    if(Librarian *librarianPtr = dynamic_cast <Librarian*>(user))
        libMenu();
    else
        memberMenu();
    exportToDB();
    free_vectors();

    return 0;
}

Book* getBookPtr(str ISBN);