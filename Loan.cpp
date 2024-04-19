
#include "Loan.h"
#include "Book.h"
#include "User.h"
# if 0




Loan::Loan(Str memberid, unsigned int dueday, unsigned int duemonth ,unsigned int dueyear){
    member_id = memberid;

    due_date_day = dueday;
    due_date_month = duemonth;
    due_date_year = dueyear;
}

bool Loan::CheckAvailability(Str booktitle, const vector<Book*> & library_books){
    for(auto it : library_books){
        if(it->getTitle() == booktitle)
            return true;
    }
}

void Loan::complete_loanProcess(Loan & loan, Member & member, Librarian &librarian, Book* &book){
    book->setQuantity(book->getQuantity()-1);
    if(book->getQuantity() >=0)
        librarian.processLoanRequest(member, loan);
    else
        book->setAvailability(false);
}

void Loan::set_loanconfstat(bool stat){
    loan_confirmation_status = stat;
}

void Loan::ProceedToCheckout(Member & member){
    
    for (size_t i = 0; i < member.checkedOutBooks.size(); i++){
        member.checkedOutBooks.push_back(borrowed_books.front());
    }
    
}



# endif