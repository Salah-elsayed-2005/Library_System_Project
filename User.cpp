#include "User.h"
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

Book*  User::searchForBook_title(const vector<Book*>& library_books, const Str& title){
    Book* Search_results;
    for(auto it : library_books){
        if(it->getIsbn() == title)
            Search_results=it;
    }
    return Search_results;

}
vector<Book *> User::searchForBook_author(const vector<Book*>& library_books, const Str& author){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getAuthor() == author)
            Search_results.push_back(it);
    }
    return Search_results;

}
vector<Book *> User::searchForBook_genre(const vector<Book*>& library_books, const Str& genre){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getGenre() == genre)
            Search_results.push_back(it);
    }
    return Search_results;

}
Book* User::searchForBook_isbn(const vector<Book *> &library_books, const Str &isbn) {
    Book* Search_results;
    for(auto it : library_books){
        if(it->getIsbn() == isbn)
            Search_results=it;
    }
    return Search_results;
}
vector<Book *> User::searchForBook_publicationyear(const vector<Book *> &library_books, const short &year) {
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getPublicationYear() == year)
            Search_results.push_back(it);
    }
    return Search_results;
}


/****************************************************************/
/********** Constructors ***********/
Member::Member():User("", "", ""), overdue_fines(0.0){}
Member::Member(Str name, Str id, Str pass, vector<Book*> bk_list, vector<Loan*> ln_list, float o_fines):
        User(name, id, pass), checked_out_books(bk_list), member_loans(ln_list), overdue_fines(o_fines){}

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
Member* Librarian::Searchformember(vector<User*>library_users,Str id){
    for (auto it:library_users) {
        if (it->getId()==id) {
            Member*toreturn=dynamic_cast<Member *>(it);
            return toreturn;
        }
    }
    cout<<"User not found";
    return nullptr;
}

/************* Librarian Methods ***********/

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