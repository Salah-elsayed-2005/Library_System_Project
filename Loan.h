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
    Loan(Member*, Book*); // Parametarized constructor sets the borrower and book borrowed
    //Getters
    Member* getBorrower(); // return pointer to borrower object
    Book* getBorrowedBook();// return pointer to borrowed book object
    bool getStatus(); // get status of loan
    Date getBorrowDate(); // return borrowing date object
    Date getDueDate(); // return due date object


    //Setters
    void set_status(bool); // set status of loan
    void set_borrowingDate(); // set borrowing date of loan
    void set_dueDate(); // set due date of loan
    /*
     over loaded functions to get the borrowing and due dates
     form DB when importing in string format and convert it
     to integers and set it to the borrowing and due date day, month and year
     */
    void set_borrowingDate(const string&);
    void set_dueDate(const string&);

    //Methods
    void generateReport(); // generate a report on the loan and prints the borrower and borrowed book details with their borrowing and duedates
};


#endif //LIBRARY_SYSTEM_PROJECT_LOAN_H