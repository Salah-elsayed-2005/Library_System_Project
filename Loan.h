
#include <iostream>
#include <vector>
#include "User.h"
#include "Str.h"
#include "Book.h"
#include "Date.h"
#include <ctime>
time_t now = time(0);
tm *ltm = localtime(&now);

using namespace OurString;
 using namespace OurBook;

#ifndef LIBRARY_SYSTEM_PROJECT_LOAN_H
#define LIBRARY_SYSTEM_PROJECT_LOAN_H


class Loan{
private:
    Member* borrower ;
    Book* borrowed_book;
    Date borrowing_date;
    Date Due_date;
    bool loan_status;

public:
    Loan(Member*, Book*);
    //Getters
    Member* getBorrower();
    Book* getBorrowedBook();
    bool getStatus();
    //Setters
    void set_status(bool);
    void set_borrowingDate(Date);
    void set_dueDate(Date);
};


#endif //LIBRARY_SYSTEM_PROJECT_LOAN_H