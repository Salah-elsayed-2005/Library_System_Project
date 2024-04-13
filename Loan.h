#if 0

#include <iostream>
#include <vector>
#include "User.h"
#include "Str.h"
#include "Book.h"

#include <ctime>
time_t now = time(0);
tm *ltm = localtime(&now);

/*using namespace OurString;
using namespace OurUser;
using namespace OurBook;*/

#ifndef LIBRARY_SYSTEM_PROJECT_LOAN_H
#define LIBRARY_SYSTEM_PROJECT_LOAN_H


class Loan{
private:
    Str member_id;
    vector<OurBook::Book*> borrowed_books;

    unsigned int borrow_date_day = ltm->tm_mday;
    unsigned int borrow_date_month = 1 + ltm->tm_mon;
    unsigned int borrow_date_year = 1900 + ltm->tm_year;

    unsigned int due_date_day;
    unsigned int due_date_month;
    unsigned int due_date_year;

    bool loan_confirmation_status = false;

public:
    Loan(Str, unsigned int, unsigned int ,unsigned int);
    bool CheckAvailability(Str, const vector<OurBook::Book*> &);
    void complete_loanProcess(Loan &, OurUser::Member & ,OurUser:: Librarian &, Book * &);
    void ProceedToCheckout(OurUser::Member &);

    //Getters
    float get_overduefines();

    //Setters
    void set_loanconfstat(bool);
};


#endif //LIBRARY_SYSTEM_PROJECT_LOAN_H
#endif
