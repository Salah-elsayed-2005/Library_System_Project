#include "User.h"
#include "Loan.h"

#include <ctime>
time_t now = time(0);
tm *ltm = localtime(&now);

using namespace OurUser;
///////////////////////////        USER FUNCTIONS
Str User::getUsername() const {
    return username;
}
Str User::getPassword() const{
    return password;
}
void User::setUsername(Str un){
    username = un;
}
void User::setPassword(Str pass){
    password = pass;
}




///////////////////////////         MEMBER FUNCTIONS
/***********    Search For Books   ************/
Book* Member::searchForBook_title(const vector<Book*>& library_books, const Str& title){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getTitle() == title)
            return it;
            // Search_results.push_back(it);
    }
    // return Search_results;
   // return nullptr;
}
vector<Book *> Member::searchForBook_author(const vector<Book*>& library_books, const Str& author){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getAuthor() == author)
            Search_results.push_back(it);
    }
    //return nullptr;
}
vector<Book *> Member::searchForBook_genre(const vector<Book*>& library_books, const Str& genre){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getGenre() == genre)
            Search_results.push_back(it);
    }
    //return nullptr;
}
vector<Book *>Member::searchForBook_isbn(const vector<Book *> &library_books, const Str &isbn) {
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getIsbn() == isbn)
            Search_results.push_back(it);
    }
   // return nullptr;
}
vector<Book *>Member::searchForBook_publicationyear(const vector<Book *> &library_books, const short &year) {
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getPublicationYear() == year)
            Search_results.push_back(it);
    }
    //return nullptr;
}

/****************             ******************/
void Member::viewCheckedOutBooks(){
    cout << "Your books: " << endl;
    for(auto it : checkedOutBooks){
        cout << "Title: "<< it->getTitle() << endl;
        cout << "Author: " << it->getAuthor() << endl;
        cout << "Due Date: " << "//////// will be added" << endl;
        cout << "__________________________________________" << endl;
    }
}

void Member::returnBorrowedBooks(const vector<Book*>& library_books, Book* borrowed){
    for(auto it = library_books.begin(); it != library_books.end(); it++){

        if((*it)->getTitle() == borrowed->getTitle()){
            (*it)->setQuantity(((*it)->getQuantity()) + 1);
            (*it)->setAvailability(true);
        }

    }
    for(auto it = checkedOutBooks.begin(); it != checkedOutBooks.end(); it++){
        if((*it)->getTitle() == borrowed->getTitle()){
            checkedOutBooks.erase(it);
        }
    }
}
void Member::requestLoan(Member & member, Librarian &librarian, const vector<Book*> & library_books){
    // Librarian must receive request and save the loan details in the loan class
    Str book_title;
    cout<<"Enter book title: "<<endl;
    cin>>book_title;
    unsigned int duedate_day;
    unsigned int duedate_month;
    unsigned int duedate_year;
    cout<<"Enter due date day: "<<endl;
    cin>>duedate_day;
    cout<<"Enter due date month: "<<endl;
    cin>>duedate_month;
    cout<<"Enter due date year: "<<endl;
    cin>>duedate_year;
    Str member_id = member.id;
    Loan loan(member_id, duedate_day, duedate_month, duedate_year);
    if(loan.get_overduefines()!=0){
        cout<<"Can not take loan due to having an existing overdue!"<<endl;
    }
    else if(loan.CheckAvailability(book_title, library_books)){
        Book* book = member.searchForBook_title(library_books, book_title);
        loan.complete_loanProcess(loan, member, librarian, book);
    }
    else{
        cout<<"Book does not exist in library!"<<endl;
    }
}

/////////////////////////   LIBRARIAN FUNCTIONS

void Librarian::addBook(vector<Book*> & list, Book* &book){
    /*
    Str title;
    Str author;
    Str isbn; // Str or Long?
    unsigned short publication_year;
    Str genre;

    cout << "Enter book title : ";         cin >> title;                book->setTitle(title);
    cout << "Enter book author : ";        cin >> author;               book->setAuthor(author);
    cout << "Enter book ISBN : ";          cin >> isbn;                 book->setIsbn(isbn);
    cout << "Enter publication year : ";   cin >> publication_year;     book->setPublicationYear(publication_year);
    cout << "Enter book genre : ";         cin >> genre;                book->setGenre(genre);
*/
    book->setAvailability(true);
    book->setQuantity(book->getQuantity() + 1);

    list.push_back(book);
}
void removeBook(vector<Book*> &list, Book* &book){
    for(auto it = list.begin(); it != list.end(); it++){
        if((*it)->getTitle() == book->getTitle()){
            list.erase(it);
        }
    }
}
void updateBookTitle(Book* & book){
    Str new_title;
    cout << "New title: "; cin >> new_title;
    book->setTitle(new_title);
}
void updateBookAuthor(Book* & book){
    Str new_author;
    cout << "New author: "; cin >> new_author;
    book->setAuthor(new_author);
}
void updateBookISBN(Book* & book){
    Str new_isbn;
    cout << "New ISBN: "; cin >> new_isbn;
    book->setIsbn(new_isbn);
}
void updatePublicationYear(Book* & book){
    unsigned short new_publication_year;
    cout << "New publication year: "; cin >> new_publication_year;
    book->setPublicationYear(new_publication_year);
}
void updateBookGenre(Book* & book){
    Str new_genre;
    cout << "New title: "; cin >> new_genre;
    book->setGenre(new_genre);
}
void updateBookAvailabitlity(Book* & book){
    bool new_availability;
    cout << "New Availability status: "; cin >> new_availability;
    book->setAvailability(new_availability);
}
void updateBookQuantity(Book* & book){
    unsigned short new_quantity;
    cout << "New title: "; cin >> new_quantity;
    book->setQuantity(new_quantity);
}
void processLoanRequest(Member & member, Loan & loan){ 
    loan.set_loanconfstat(true);
}

void PrintTime(){
    cout<< ltm->tm_mday<<"/"
        << 1 + ltm->tm_mon << "/" 
        << 1900 +ltm->tm_year<<endl;
}

