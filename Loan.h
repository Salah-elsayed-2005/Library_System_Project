#include <iostream>
#include <vector>
#include <string>
#include "User.h"
#include "Str.h"
#include "Book.h"
#include "Date.h"
#include <ctime>

using namespace OurBook;
using namespace std;




#ifndef LIBRARY_SYSTEM_PROJECT_LOAN_H
#define LIBRARY_SYSTEM_PROJECT_LOAN_H


class Loan{
private:
    Member* borrower;
    Book* borrowed_book;
    Date borrowing_date;
    Date due_date;
    bool loan_status = false;

public:
    Loan(Member*, Book*);
    //Getters
    Member* getBorrower();
    Book* getBorrowedBook();
    bool getStatus();
    Date getBorrowDate();
    Date getDueDate();


    //Setters
    void set_status(bool);
    //void set_borrower();
    void set_borrowingDate();
    void set_dueDate();
    void set_borrowingDate(string);
    void set_dueDate(string);

    //Methods
    void generateReport();
};


#endif //LIBRARY_SYSTEM_PROJECT_LOAN_H