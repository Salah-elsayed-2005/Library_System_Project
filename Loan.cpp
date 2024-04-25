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
void Loan::set_borrowingDate(const string& dateInString) { // format of the string: 25-4-2024 <<<<<
    string buffer = "";
    int dashCount = 0;

    // Loop through each character in the string
    for (size_t i = 0; i <= dateInString.size(); i++) {
        // Check for dash or end of string
        if (i == dateInString.size() || dateInString[i] == '-') {
            if (dashCount == 0) {
                borrowing_date.day = stoi(buffer); // First part is the day
            } else if (dashCount == 1) {
                borrowing_date.month = stoi(buffer); // Second part is the month
            } else if (dashCount == 2) {
                borrowing_date.year = stoi(buffer); // Third part is the year
            }
            buffer = ""; // Reset buffer for next number
            dashCount++; // Increment dash count to move to the next date component
        } else {
            buffer += dateInString[i]; // Accumulate digits in buffer
        }
    }
}

void Loan::set_dueDate(const string& dateInString) { // format of the string: 25-4-2024
    string buffer = "";
    int dashCount = 0;

    // Loop through each character in the string
    for (size_t i = 0; i <= dateInString.size(); i++) {
        // Check for dash or end of string
        if (i == dateInString.size() || dateInString[i] == '-') {
            if (dashCount == 0) {
                due_date.day = stoi(buffer); // First part is the day
            } else if (dashCount == 1) {
                due_date.month = stoi(buffer); // Second part is the month
            } else if (dashCount == 2) {
                due_date.year = stoi(buffer); // Third part is the year
            }
            buffer = ""; // Reset buffer for next number
            dashCount++; // Increment dash count to move to the next date component
        } else {
            buffer += dateInString[i]; // Accumulate digits in buffer
        }
    }
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