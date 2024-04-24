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
void Loan::set_borrowingDate() {borrowing_date.getCurrentData();}
void Loan::set_dueDate(){
    if(dynamic_cast<Student*>(borrower)){
        due_date = due_date.addDate(borrowing_date, 7);
    }
    if(dynamic_cast<Faculty*>(borrower)){
        due_date = due_date.addDate(borrowing_date, 10);
    }
    if(dynamic_cast<Staff*>(borrower)){
        due_date = due_date.addDate(borrowing_date, 5);
    }
    due_date.stringDate = std::to_string(due_date.day)+"-"+std::to_string(due_date.month)+"-"+std::to_string(due_date.year);

}
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