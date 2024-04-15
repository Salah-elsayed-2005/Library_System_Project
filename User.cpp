#include "User.h"
#include "Library_Data.h"
#include "Loan.h"

#include <ctime>
//time_t now = time(0);
//tm *ltm = localtime(&now);



///////////////////////////        USER FUNCTIONS
/// setters
void User::setName(Str s) {name=s;}
void User::setId(Str i) {id=i;}
void User::setPassword(Str pass){password = pass;}
///getters
Str User::getName() const {return  name;}
Str User::getId() const {return id;}
Str User::getPassword() const{return password;}


/***********    Search For Books   ************/
vector <Book *> User::searchForBook_title(const vector<Book*>& library_books, const Str& title){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getTitle() == title)
            //        return it;
            Search_results.push_back(it);
    }
    return Search_results;
    // return nullptr;
}
vector<Book *> User::searchForBook_author(const vector<Book*>& library_books, const Str& author){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getAuthor() == author)
            Search_results.push_back(it);
    }
    //return nullptr;
}
vector<Book *> User::searchForBook_genre(const vector<Book*>& library_books, const Str& genre){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getGenre() == genre)
            Search_results.push_back(it);
    }
    //return nullptr;
}
vector<Book *>User::searchForBook_isbn(const vector<Book *> &library_books, const Str &isbn) {
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getIsbn() == isbn)
            Search_results.push_back(it);
    }
    // return nullptr;
}
vector<Book *>User::searchForBook_publicationyear(const vector<Book *> &library_books, const short &year) {
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getPublicationYear() == year)
            Search_results.push_back(it);
    }
    //return nullptr;
}


/**********************************************************************
///////////////////////////         MEMBER FUNCTIONS
Str Member::getUsername() const {return username;}
Str Member::getPassword() const{return password;}
Str Member::getName() const {return  name;}
Str Member::getId() const {return id;}
/// setters
void Member::setUsername(Str un){username = un;}
void Member::setPassword(Str pass){password = pass;}
void Member::setName(Str s) {name=s;}
void Member::setId(Str i) {id=i;}
///showdata
void Member::showdata() {
    cout<<"Name :   "<<name<<endl
        <<"ID   :   "<<id<<endl
        <<"Fines:   "<<overdue_fines<<endl;
    if (type==0)
        cout<<"Type :   Member"<<endl;
    else if (type==1)
        cout<<"Type :   Staff"<<endl;
    else
        cout<<"Type :   Faculty"<<endl;
    cout<<"******************"<<endl;
}
 ****************************************************************/
/********** Constructors ***********/
Member::Member():User("", "", ""), overdue_fines(0.0){}
Member::Member(Str name, Str id, Str pass, vector<Book*> bk_list, vector<Loan*> ln_list, float o_fines):
        User(name, id, pass), checked_out_books(bk_list), member_loans(ln_list), overdue_fines(o_fines){}
/*
Member::Member(Member& obj) {
    this->name = obj.name;
    this->id = obj.id;
    this->checked_out_books = obj.checked_out_books;
    this->member_loans = obj.member_loans;
    this->overdue_fines = obj.overdue_fines;
}
*/
/********** Setters and Getters **********/
void Member::setCheckedOutBooks(vector<Book*> &co_books){
    checked_out_books = co_books;
}
void Member::setMemberLoans(vector<Loan *> &loans_list) {
    member_loans = loans_list;
}
void Member::setOverdueFines(float& fines){
    overdue_fines = fines;
}

vector<Book*> Member::getCheckedOutBooks() const {
    return checked_out_books;
}
vector<Loan*> Member::getMemberLoans() const {
    return member_loans;
}
float Member::getOverdueFines() const {
    return overdue_fines;
}
    /********** overriden methods **********/




/****************       Member functions      ******************/
void Member::viewCheckedOutBooks() const{
    cout << "Your books: " << endl;
    for(auto it : checked_out_books){
        cout << "Title: "<< it->getTitle() << endl;
        cout << "Author: " << it->getAuthor() << endl;
        cout << "Due Date: " << "//////// will be added" << endl;
        cout << "__________________________________________" << endl;
    }
}
/*********************************
void Member::returnBorrowedBooks(const vector<Book*>& library_books, Book* borrowed){
    for(auto it = library_books.begin(); it != library_books.end(); it++){

        if((*it)->getTitle() == borrowed->getTitle()){
            (*it)->setQuantity(((*it)->getQuantity()) + 1);
           // (*it)->setAvailability();
        }

    }
    for(auto it = checked_out_books.begin(); it != checked_out_books.end(); it++){
        if((*it)->getTitle() == borrowed->getTitle()){
            checked_out_books.erase(it);
        }
    }
}
************************************/

/*
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
*/


     /*****************   Constructors *****************/
Librarian::Librarian():User(){}
Librarian::Librarian(Str n, Str i, Str p):User(n, i, p){}

    /********** overriden methods **********/
void Librarian::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Librarian" << endl;
}
    /************* Operation on Books ***********/

void Librarian::viewBooks(vector<Book*>& book_list) const{
    cout << "Available Books " << endl;
    for(auto &book : book_list){
        book->printData();
    }

}
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
    book->setQuantity(book->getQuantity() + 1);
    book->setAvailability();
    list.push_back(book);
}
void Librarian::removeBook(vector<Book*> &list, Book* &book){
    for(auto it = list.begin(); it != list.end(); it++){
        if((*it)->getIsbn() == book->getIsbn()){
            list.erase(it);
        }
    }
}
void Librarian::updateBookTitle(Book* & book){
    Str new_title;
    cout << "New title: "; cin >> new_title;
    book->setTitle(new_title);
}
void Librarian::updateBookAuthor(Book* & book){
    Str new_author;
    cout << "New author: "; cin >> new_author;
    book->setAuthor(new_author);
}
void Librarian::updateBookISBN(Book* & book){
    Str new_isbn;
    cout << "New ISBN: "; cin >> new_isbn;
    book->setIsbn(new_isbn);
}
void Librarian::updatePublicationYear(Book* & book){
    unsigned short new_publication_year;
    cout << "New publication year: "; cin >> new_publication_year;
    book->setPublicationYear(new_publication_year);
}
void Librarian::updateBookGenre(Book* & book){
    Str new_genre;
    cout << "New title: "; cin >> new_genre;
    book->setGenre(new_genre);
}

void Librarian::updateBookQuantity(Book* & book){
    unsigned short new_quantity;
    cout << "New title: "; cin >> new_quantity;
    book->setQuantity(new_quantity);
    book->setAvailability();
}

/************* Operation on Members ***********/

void Librarian::addMember(vector<User *> & users_list, Member* member){
    users_list.push_back(member);
}
void Librarian::removeMember(vector<User *> &users_list, Member* member){
    for(auto it = users_list.begin(); it != users_list.end(); it++){
        if((*it)->getId() == member->getId()){
            users_list.erase(it);
        }
    }
}
void Librarian::updateMemberName(Member* member){
    Str new_name;
    cout << "New Name: "; cin >> new_name;
    member->setName(new_name);
}

void Librarian::updateMemberId(Member* member){
    Str new_id;
    cout << "New Id: "; cin >> new_id;
    member->setId(new_id);
}

void Librarian::setId(Str i) {
    Str prefix = "lib-";
    id = prefix + i;
}

/*************** Operations on Loans *************/
/*
void processLoanRequest(Member & member, Loan & loan){ 
    loan.set_loanconfstat(true);
}

void PrintTime(){
    cout<< ltm->tm_mday<<"/"
        << 1 + ltm->tm_mon << "/" 
        << 1900 +ltm->tm_year<<endl;
}

*/
/************* Student Methods **********/
void Student::setId(Str i) {
    Str prefix = "stu-";
    id = prefix + i;
}
void Student::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Student" << endl;
}
/************* Faculty Methods **********/
void Faculty::setId(Str i) {
    Str prefix = "fac-";
    id = prefix + i;
}
void Faculty::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Faculty Member" << endl;
}
/************* Staff Methods **********/
void Staff::setId(Str i) {
    Str prefix = "sta-";
    id = prefix + i;
}
void Staff::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Staff" << endl;
}