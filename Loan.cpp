
#include "Loan.h"
#include "Book.h"
#include "User.h"


Loan::Loan(Member* member, Book* book):
borrower(member), borrowed_book(book), loan_status(false){}

//Getters
Member* Loan::getBorrower() { return borrower; }
Book* Loan::getBorrowedBook() { return borrowed_book; }
bool Loan::getStatus() { return loan_status; }

//Setters
void Loan::set_status(bool status) { loan_status = status; }

# endif


