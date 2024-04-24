#include "Loan.h"
#include "Book.h"
#include "User.h"


Loan::Loan(Member* member, Book* book):
        borrower(member), borrowed_book(book), loan_status(false){}

//Getters
Member* Loan::getBorrower() { return borrower; }
Book* Loan::getBorrowedBook() { return borrowed_book; }
bool Loan::getStatus() { return loan_status; }
Date Loan::getBorrowDate() { return borrowing_date; }
Date Loan::getDueDate() { return due_date;}
//Setters
void Loan::set_status(bool status) { loan_status = status; }
void Loan::set_borrowingDate(Date& date) {borrowing_date = date;}
void Loan::set_dueDate(Date &){}
//Methods
void Loan::generateReport(){
    cout << "-------Loan Report-------" << endl;
    cout
            <<"Member Name: "<<borrower->getName()<<endl
            <<"Borrowed Book: "<<borrowed_book->getTitle()<<endl
            <<"Borrowing Date: "<<borrowing_date.day<<"/"<<borrowing_date.month<<"/"<<borrowing_date.year<<endl;
    if(Student* ptr = dynamic_cast<Student*>(borrower)){
        cout<<"Member Role: "<<"student"<<endl;
    }
    else if(Faculty* ptr = dynamic_cast<Faculty*>(borrower)){
        cout<<"Member Role: "<<"faculty"<<endl;
    }
    else if(Staff* ptr = dynamic_cast<Staff*>(borrower)){
        cout<<"Member Role: "<<"staff"<<endl;
    }
}