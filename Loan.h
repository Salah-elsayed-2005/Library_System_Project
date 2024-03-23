#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
#include "User.h"

using namespace OurString;
#ifndef LIBRARY_SYSTEM_PROJECT_LOAN_H
#define LIBRARY_SYSTEM_PROJECT_LOAN_H


class Loan {
private:
    vector<Book> borrowed_books;
    Str _borrow_date;
    Str _due_date;

protected:
    // This function can track the borrowed books by Member ID or book ID or borrow date or due date
    void viewLoans(Str member_id, Str isbn, Str borrow_date, Str due_date);
};


#endif //LIBRARY_SYSTEM_PROJECT_LOAN_H
