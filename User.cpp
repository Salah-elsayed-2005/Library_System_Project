#include "User.h"
#include "Loan.h"

///////////////////////////        USER FUNCTIONS
/// setters
void User::setName(str s) {name=s;}
void User::setId(str i) {id=i;}
void User::setPassword(str pass){password = pass;}
///getters
str User::getName() const {return  name;}
str User::getId() const {return id;}
str User::getPassword() const{return password;}

/***********    Search For Books   ************/

/* function that iterates over the library books and returns the book with the wanted title */
Book*  User::searchForBook_title(const vector<Book*>& library_books, const str& title){
    for(auto it : library_books){
        if(it->getTitle() == title)
            return it;
    }
    return nullptr;
}

/* function that iterates over the library books and returns a vector of books with the wanted author */
vector<Book *> User::searchForBook_author(const vector<Book*>& library_books, const str& author){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getAuthor() == author)
            Search_results.push_back(it);
    }
    return Search_results;

}

/* function that iterates over the library books and returns a vector of books with the wanted genre */
vector<Book *> User::searchForBook_genre(const vector<Book*>& library_books, const str& genre){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getGenre() == genre)
            Search_results.push_back(it);
    }
    return Search_results;

}

/* function that iterates over the library books and returns the book with the wanted ISBN */
Book* User::searchForBook_isbn(const vector<Book *> &library_books, const str &isbn) {
    for(auto it : library_books){
        if(it->getIsbn() == isbn)
            return it;
    }
    return nullptr;
}

/* function that iterates over the library books and returns a vector of books with the wanted publication year */
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
Member::Member(str name, str id, str pass):User(name, id, pass), overdue_fines(0.0){}

/********** Setters and Getters **********/
void Member::setCheckedOutBooks(vector<Book*> &co_books){
    checked_out_books = co_books;
}
void Member::setOverdueFines(float& fines){
    overdue_fines = fines;
}
vector<Book*> Member::getCheckedOutBooks() const {
    return checked_out_books;
}
float Member::getOverdueFines() const {
    return overdue_fines;
}
int Member::getCheckedOutBooksSize() const {
    return checked_out_books.size();
}

/* function that adds the passed book to the checked out books of the member */
void Member::addToCheckedOutBooks(Book* &book) {
    checked_out_books.push_back(book);
}

/* function that removes the passed books from the checked out books of the member */
void Member::removeFromCheckedOutBooks(Book* &book){
    for (auto it = checked_out_books.begin(); it != checked_out_books.end(); it++)
    {
        if((*it) == book)
            checked_out_books.erase(it);
        return;
    }
}

/****************       Member functions      ******************/


/*****************   Constructors *****************/
Librarian::Librarian():User(){}
Librarian::Librarian(str n, str i, str p):User(n, i, p){}

/********** overriden methods **********/
void Librarian::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Librarian" << endl;
}
/************* Operation on Books ***********/

/* function to view the books library books with their data */
void Librarian::viewBooks(vector<Book*>& book_list) const{
    cout << "Library Books " << endl;
    for(auto &book : book_list){
        book->printData();
    }

}

/* function that adds a new book to the library with the attributes that the user input */
void Librarian::addBook(vector<Book*> & list){
    str title,isbn,author,genre;
    short year;
    int quantity;
    cout<<"Please Enter Book title : ";
    cin>>title;
    cout<<"Please enter book isbn : ";
    cin>>isbn;
    cout<<"Please enter book author : ";
    cin>>author;
    cout<<"Please enter book genre : ";
    cin>>genre;
    cout<<"Please enter book publication year : ";
    cin>>year;
    cout<<"Please enter book quantity : ";
    cin>>quantity;
    if (searchForBook_title(list,title) || searchForBook_isbn(list ,isbn))
    {
        cout<<"Book Already Added"<<endl;
        return;
    } else{
        Book*tosend=new Book(title,author,isbn,year,genre);
        tosend->setQuantity(quantity);
        list.push_back(tosend);
        cout<<"Book added Successfully";
    }
}

/* function that removes the passed book to the library from the library books vector */
void Librarian::removeBook(vector<Book*> &list, Book* &book){
    for(auto it = list.begin(); it != list.end(); it++){
        if((*it)->getIsbn() == book->getIsbn()){
            list.erase(it);
            return;
        }
    }
}

/************ functions to update books attributes *************/
void Librarian::updateBookTitle(Book* & book){
    str new_title;
    cout << "New title: "; cin >> new_title;
    book->setTitle(new_title);
}
void Librarian::updateBookAuthor(Book* & book){
    str new_author;
    cout << "New author: "; cin >> new_author;
    book->setAuthor(new_author);
}
void Librarian::updateBookISBN(Book* & book){
    str new_isbn;
    cout << "New ISBN: "; cin >> new_isbn;
    book->setIsbn(new_isbn);
}
void Librarian::updatePublicationYear(Book* & book){
    unsigned short new_publication_year;
    cout << "New publication year: "; cin >> new_publication_year;
    book->setPublicationYear(new_publication_year);
}
void Librarian::updateBookGenre(Book* & book){
    str new_genre;
    cout << "New Genre: "; cin >> new_genre;
    book->setGenre(new_genre);
}

void Librarian::updateBookQuantity(Book* & book){
    unsigned short new_quantity;
    cout << "New Quantity: "; cin >> new_quantity;
    book->setQuantity(new_quantity);
    book->setAvailability();
}

/************* Operation on Members ***********/

/* function to add member to the users vector in the library */
void Librarian::addMember(vector<User *> & users_list,int type){
    str name,id,pass;
    cout<<"Please enter user Name : ";
    cin>>name;
    cout<<"Please enter user ID : ";
    cin>>id;
    cout<<"Please enter user password : ";
    cin>>pass;
    User *member ;
    if (type == 1){
        Student *student = new Student;
        student->setName(name);
        student->setId(id);
        student->setPassword(pass);
        member=student;
    }
    else if (type == 2){
        Staff *staff = new Staff;

        staff->setName(name);
        staff->setId(id);
        staff->setPassword(pass);
        member=staff;
    }
    else if (type == 3){
        Faculty *faculty = new Faculty;
        faculty->setName(name);
        faculty->setId(id);
        faculty->setPassword(pass);
        member=faculty;
    }
    users_list.push_back(member);
}


/* function to remove the passed member from the user list in the library */
void Librarian::removeMember(vector<User *> &users_list, Member* member){
    for(auto it = users_list.begin(); it != users_list.end(); it++){
        if((*it)->getId() == member->getId()){
            users_list.erase(it);
            return;
        }
    }
}

/* function to update the passed member */
void Librarian::updateMemberName(Member* member ){

    str new_name;
    cout << "New Name: ";
    cin >> new_name;
    member->setName(new_name);

}

/* function to update the passed member id */
void Librarian::updateMemberId(Member* member ){
    str new_id;
    cout << "New Id: ";
    cin >> new_id;
    member->setId(new_id);
}

/* function to search for a member in the library users vector by the member id */
Member* Librarian::Searchformember(vector<User*>library_users,str id){
    for (auto it:library_users) {
        if (it->getId()==id) {
            Member*toreturn=dynamic_cast<Member *>(it);
            return toreturn;
        }
    }
    cout<<"User not found";
    return nullptr;
}

/* function to search for user whether it is member or librarian in library users by the user id */
User*Librarian:: Searchforuser(vector<User*>library_users,str id){
    for (auto it:library_users) {
        if (it->getId()==id) {
            return it;
        }
    }
    cout<<"User not found";
    return nullptr;
}

/* overrided function that sets the librarian id with the prefix "lib-" */
void Librarian::setId(str i) {
    str prefix = "lib-";
    id = prefix + i;
}


/*************** Operations on Loans *************/

/* function for the librarian to accept or decline the loan request and updates the related variables accordingly */
void Librarian::processLoanRequest(Loan* &loan, bool response){
    Book* book = loan->getBorrowedBook();
    Member* member = loan->getBorrower();
    if(response){
        // assign book to checkoutbooks
        member->addToCheckedOutBooks(book);
        // set borrow date
        loan->set_borrowingDate();
        loan->set_dueDate();
        // set loan status true
        loan->set_status(true);
    }
    else {
        loan->set_status(false);
        book->setQuantity(book->getQuantity()+1);
    }
}

/* function that checks if the loan is delayed and sets the overdue fines according the the member loan */
void Librarian::CheckForOverdues(Loan* &loan){
    int maxborrowingdays;
    float fineperday;
    Member* member = loan->getBorrower();
    if(Student* ptr = dynamic_cast<Student*>(member)){
        maxborrowingdays = 5;
        fineperday = 5;
    }
    else if(Faculty* ptr = dynamic_cast<Faculty*>(member)){
        maxborrowingdays = 10;
        fineperday = 4;
    }
    else if(Staff* ptr = dynamic_cast<Staff*>(member)){
        maxborrowingdays = 6;
        fineperday = 3;
    }
    Date borrowdate = loan->getBorrowDate();
    if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
        int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
        float fineToadd = numOfLateDays * fineperday;
        member->setOverdueFines(fineToadd);
    }
}

/* function to print the details of all library loans */
void Librarian::printAllLoans(vector<Loan*> loans) const {
    cout<<"\t\t--All requests received by members--"<<endl;
    for (auto &&loan : loans)
        loan->generateReport();

}

/* function to print the pending loans requests */
void Librarian::printPendingLoans(vector<Loan*> loans) const {
    cout<<"\t\t--Pending requests received by members--"<<endl;
    for (auto &&loan : loans)
        if(!loan->getStatus())
            loan->generateReport();

}
/************* Student Methods **********/

/* Constructors */
Student::Student():Member(){}
Student::Student(str n, str i, str p):Member(n, i, p){}
Student::Student(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix stu- */
void Student::setId(str i) {
    str prefix = "stu-";
    id = prefix + i;
}

/* function to display the student info */
void Student::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Student" << endl;
}
/*
Student:
   maxNumberofbooks = 4
   maxoverduefines = 10
   overduefinesperday = 5
   maxnumberofborrowingdays = 5
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting student is eligible to loan
 * accoriding to the loan cosntraints applied to students and returns null otherwise */
Loan* Student::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 10 ;
    int maxnumberofbooksborrowed = 4;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size() + cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;
            }
        }
        else{
            cout<<"Can't request loan, you have maximum allowed number of borrowed books!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, you have maximum allowed overdue fines!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the student according to the fines rules applied to students */
void Student::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 5;
    float fineperday = 5;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();

        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
/************* Faculty Methods **********/
Faculty::Faculty():Member(){}
Faculty::Faculty(str n, str i, str p):Member(n, i, p){}
Faculty::Faculty(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix stu- */
void Faculty::setId(str i) {
    str prefix = "fac-";
    id = prefix + i;
}

/* function to display the student info */
void Faculty::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Faculty Member" << endl;
}
/*
Faculty:
      maxNumberofbooks = 6
     maxoverduefines = 12
      overduefinesperday = 4
      maxnumberofborrowingdays = 10
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting faculty member is eligible to loan
 * accoriding to the loan cosntraints applied to faculty members and returns null otherwise */
Loan* Faculty::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 12;
    int maxnumberofbooksborrowed = 6;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size()+cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;

            }
        }
        else{
            cout<<"Can't request loan, total number of borrowed books exceed the limit!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, overdue fines exceed the limit!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the faculty member according to the fines rules applied to faculty members */
void Faculty::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 10;
    float fineperday = 4;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();
        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
/************* Staff Methods **********/

/* cosntructors */
Staff::Staff():Member(){}
Staff::Staff(str n, str i, str p):Member(n, i, p){}
Staff::Staff(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix sta- */
void Staff::setId(str i) {
    str prefix = "sta-";
    id = prefix + i;
}

/* function to display the staff member info */
void Staff::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Staff" << endl;
}
/*
Staff:
      maxNumberofbooks = 3
      maxoverduefines = 6
      overduefinesperday = 3
      maxnumberofborrowingdays = 6
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting staff is eligible to loan
 * according to the loan constraints applied to staff members and returns null otherwise */
Loan* Staff::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 6;
    int maxnumberofbooksborrowed = 3;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size()+cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;

            }
        }
        else{
            cout<<"Can't request loan, total number of borrowed books exceed the limit!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, overdue fines exceed the limit!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the staff member according to the fines rules applied to staff */
void Staff::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 6;
    float fineperday = 3;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();
        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
# if 0
#include "User.h"
#include "Loan.h"



///////////////////////////        USER FUNCTIONS
/// setters
void User::setName(str s) {name=s;}
void User::setId(str i) {id=i;}
void User::setPassword(str pass){password = pass;}
///getters
str User::getName() const {return  name;}
str User::getId() const {return id;}
str User::getPassword() const{return password;}

/***********    Search For Books   ************/

/* function that iterates over the library books and returns the book with the wanted title */
Book*  User::searchForBook_title(const vector<Book*>& library_books, const str& title){
    for(auto it : library_books){
        if(it->getTitle() == title)
            return it;
    }
    return nullptr;
}

/* function that iterates over the library books and returns a vector of books with the wanted author */
vector<Book *> User::searchForBook_author(const vector<Book*>& library_books, const str& author){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getAuthor() == author)
            Search_results.push_back(it);
    }
    return Search_results;

}

/* function that iterates over the library books and returns a vector of books with the wanted genre */
vector<Book *> User::searchForBook_genre(const vector<Book*>& library_books, const str& genre){
    vector<Book*> Search_results;
    for(auto it : library_books){
        if(it->getGenre() == genre)
            Search_results.push_back(it);
    }
    return Search_results;

}

/* function that iterates over the library books and returns the book with the wanted ISBN */
Book* User::searchForBook_isbn(const vector<Book *> &library_books, const str &isbn) {
    for(auto it : library_books){
        if(it->getIsbn() == isbn)
            return it;
    }
    return nullptr;
}

/* function that iterates over the library books and returns a vector of books with the wanted publication year */
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
Member::Member(str name, str id, str pass):User(name, id, pass), overdue_fines(0.0){}

/********** Setters and Getters **********/
void Member::setCheckedOutBooks(vector<Book*> &co_books){
    checked_out_books = co_books;
}
void Member::setOverdueFines(float& fines){
    overdue_fines = fines;
}
vector<Book*> Member::getCheckedOutBooks() const {
    return checked_out_books;
}
float Member::getOverdueFines() const {
    return overdue_fines;
}
int Member::getCheckedOutBooksSize() const {
    return checked_out_books.size();
}

/* function that adds the passed book to the checked out books of the member */
void Member::addToCheckedOutBooks(Book* &book) {
    checked_out_books.push_back(book);
}

/* function that removes the passed books from the checked out books of the member */
void Member::removeFromCheckedOutBooks(Book* &book){
    for (auto it = checked_out_books.begin(); it != checked_out_books.end(); it++)
    {
        if((*it) == book) {
            checked_out_books.erase(it);
            return;
        }
    }
}

/****************       Member functions      ******************/


/*****************   Constructors *****************/
Librarian::Librarian():User(){}
Librarian::Librarian(str n, str i, str p):User(n, i, p){}

/********** overriden methods **********/
void Librarian::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Librarian" << endl;
}
/************* Operation on Books ***********/

/* function to view the books library books with their data */
void Librarian::viewBooks(vector<Book*>& book_list) const{
    cout << "Library Books " << endl;
    for(auto &book : book_list){
        book->printData();
    }

}

/* function that adds a new book to the library with the attributes that the user input */
void Librarian::addBook(vector<Book*> & list){
    str title,isbn,author,genre;
    short year;
    int quantity;
    cout<<"Please Enter Book title : ";
    cin>>title;
    cout<<"Please enter book isbn : ";
    cin>>isbn;
    cout<<"Please enter book author : ";
    cin>>author;
    cout<<"Please enter book genre : ";
    cin>>genre;
    cout<<"Please enter book publication year : ";
    cin>>year;
    cout<<"Please enter book quantity : ";
    cin>>quantity;
    if (searchForBook_title(list,title) || searchForBook_isbn(list ,isbn))
    {
        cout<<"Book Already Added"<<endl;
        return;
    } else{
        Book*tosend=new Book(title,author,isbn,year,genre);
        tosend->setQuantity(quantity);
        list.push_back(tosend);
        cout<<"Book added Successfully";
    }
}

/* function that removes the passed book to the library from the library books vector */
void Librarian::removeBook(vector<Book*> &list, Book* &book){

    for(auto it = list.begin(); it != list.end(); it++){
        if((*it)->getIsbn() == book->getIsbn()){
            list.erase(it);
            return;
        }
    }
}

/************ functions to update books attributes *************/
void Librarian::updateBookTitle(Book* & book){
    str new_title;
    cout << "New title: "; cin >> new_title;
    book->setTitle(new_title);
}
void Librarian::updateBookAuthor(Book* & book){
    str new_author;
    cout << "New author: "; cin >> new_author;
    book->setAuthor(new_author);
}
void Librarian::updateBookISBN(Book* & book){
    str new_isbn;
    cout << "New ISBN: "; cin >> new_isbn;
    book->setIsbn(new_isbn);
}
void Librarian::updatePublicationYear(Book* & book){
    unsigned short new_publication_year;
    cout << "New publication year: "; cin >> new_publication_year;
    book->setPublicationYear(new_publication_year);
}
void Librarian::updateBookGenre(Book* & book){
    str new_genre;
    cout << "New Genre: "; cin >> new_genre;
    book->setGenre(new_genre);
}

void Librarian::updateBookQuantity(Book* & book){
    unsigned short new_quantity;
    cout << "New Quantity: "; cin >> new_quantity;
    book->setQuantity(new_quantity);
    book->setAvailability();
}

/************* Operation on Members ***********/

/* function to add member to the users vector in the library */
void Librarian::addMember(vector<User *> & users_list,int type){
    str name,id,pass;
    cout<<"Please enter user Name : ";
    cin>>name;
    cout<<"Please enter user ID : ";
    cin>>id;
    cout<<"Please enter user password : ";
    cin>>pass;
    User *member ;
    if (type == 1){
        Student *student = new Student;
        student->setName(name);
        student->setId(id);
        student->setPassword(pass);
        member=student;
    }
    else if (type == 2){
        Staff *staff = new Staff;

        staff->setName(name);
        staff->setId(id);
        staff->setPassword(pass);
        member=staff;
    }
    else if (type == 3){
        Faculty *faculty = new Faculty;
        faculty->setName(name);
        faculty->setId(id);
        faculty->setPassword(pass);
        member=faculty;
    }
    users_list.push_back(member);
}


/* function to remove the passed member from the user list in the library */
void Librarian::removeMember(vector<User *> &users_list, Member* member){
    for(auto it = users_list.begin(); it != users_list.end(); it++){
        if((*it)->getId() == member->getId()){
            users_list.erase(it);
            return;
        }
    }
}

/* function to update the passed member */
void Librarian::updateMemberName(Member* member ){

    str new_name;
    cout << "New Name: ";
    cin >> new_name;
    member->setName(new_name);

}

/* function to update the passed member id */
void Librarian::updateMemberId(Member* member ){
    str new_id;
    cout << "New Id: ";
    cin >> new_id;
    member->setId(new_id);
}

/* function to search for a member in the library users vector by the member id */
Member* Librarian::Searchformember(vector<User*>library_users,str id){
    for (auto it:library_users) {
        if (it->getId()==id) {
            Member*toreturn=dynamic_cast<Member *>(it);
            return toreturn;
        }
    }
    cout<<"User not found";
    return nullptr;
}

/* function to search for user whether it is member or librarian in library users by the user id */
User*Librarian:: Searchforuser(vector<User*>library_users,str id){
    for (auto it:library_users) {
        if (it->getId()==id) {
            return it;
        }
    }
    cout<<"User not found";
    return nullptr;
}

/* overrided function that sets the librarian id with the prefix "lib-" */
void Librarian::setId(str i) {
    str prefix = "lib-";
    id = prefix + i;
}


/*************** Operations on Loans *************/

/* function for the librarian to accept or decline the loan request and updates the related variables accordingly */
void Librarian::processLoanRequest(Loan* &loan, bool response){
    Book* book = loan->getBorrowedBook();
    Member* member = loan->getBorrower();
    if(response){
        // assign book to checkoutbooks
        member->addToCheckedOutBooks(book);
        // Decrement book quantity by 1
        book->setQuantity(book->getQuantity() - 1);
        // set borrow date
        loan->set_borrowingDate();
        loan->set_dueDate();
        // set loan status true
        loan->set_status(true);
    }
    else {
        loan->set_status(false);
    }
}

/* function that checks if the loan is delayed and sets the overdue fines according the the member loan */
void Librarian::CheckForOverdues(Loan* &loan){
    int maxborrowingdays;
    float fineperday;
    Member* member = loan->getBorrower();
    if(Student* ptr = dynamic_cast<Student*>(member)){
        maxborrowingdays = 5;
        fineperday = 5;
    }
    else if(Faculty* ptr = dynamic_cast<Faculty*>(member)){
        maxborrowingdays = 10;
        fineperday = 4;
    }
    else if(Staff* ptr = dynamic_cast<Staff*>(member)){
        maxborrowingdays = 6;
        fineperday = 3;
    }
    Date borrowdate = loan->getBorrowDate();
    if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
        int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
        float fineToadd = numOfLateDays * fineperday;
        member->setOverdueFines(fineToadd);
    }
}

/* function to print the details of all library loans */
void Librarian::printAllLoans(vector<Loan*> loans) const {
    cout<<"\t\t--All requests received by members--"<<endl;
    for (auto loan : loans)
        loan->generateReport();
}

/* function to print the pending loans requests */
void Librarian::printPendingLoans(vector<Loan*> loans) const {
    cout<<"\t\t--Pending requests received by members--"<<endl;
    for (auto loan : loans)
        if(!loan->getStatus())
            loan->generateReport();

}
/************* Student Methods **********/

/* Constructors */
Student::Student():Member(){}
Student::Student(str n, str i, str p):Member(n, i, p){}
Student::Student(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix stu- */
void Student::setId(str i) {
    str prefix = "stu-";
    id = prefix + i;
}

/* function to display the student info */
void Student::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Student" << endl;
}
/*
Student:
   maxNumberofbooks = 4
   maxoverduefines = 10
   overduefinesperday = 5
   maxnumberofborrowingdays = 5
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting student is eligible to loan
 * accoriding to the loan cosntraints applied to students and returns null otherwise */
Loan* Student::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 10 ;
    int maxnumberofbooksborrowed = 4;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size() + cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;
            }
        }
        else{
            cout<<"Can't request loan, you have maximum allowed number of borrowed books!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, you have maximum allowed overdue fines!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the student according to the fines rules applied to students */
void Student::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 5;
    float fineperday = 5;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();

        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
/************* Faculty Methods **********/
Faculty::Faculty():Member(){}
Faculty::Faculty(str n, str i, str p):Member(n, i, p){}
Faculty::Faculty(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix stu- */
void Faculty::setId(str i) {
    str prefix = "fac-";
    id = prefix + i;
}

/* function to display the student info */
void Faculty::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Faculty Member" << endl;
}
/*
Faculty:
      maxNumberofbooks = 6
     maxoverduefines = 12
      overduefinesperday = 4
      maxnumberofborrowingdays = 10
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting faculty member is eligible to loan
 * accoriding to the loan cosntraints applied to faculty members and returns null otherwise */
Loan* Faculty::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 12;
    int maxnumberofbooksborrowed = 6;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size()+cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;

            }
        }
        else{
            cout<<"Can't request loan, total number of borrowed books exceed the limit!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, overdue fines exceed the limit!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the faculty member according to the fines rules applied to faculty members */
void Faculty::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 10;
    float fineperday = 4;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();
        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
/************* Staff Methods **********/

/* cosntructors */
Staff::Staff():Member(){}
Staff::Staff(str n, str i, str p):Member(n, i, p){}
Staff::Staff(Member*member){name=member->getName();id=member->getId();password=member->getPassword();overdue_fines=member->getOverdueFines();checked_out_books=member->getCheckedOutBooks();}

/* a function that sets the student user with the prefix sta- */
void Staff::setId(str i) {
    str prefix = "sta-";
    id = prefix + i;
}

/* function to display the staff member info */
void Staff::displayInfo() const{
    cout << "User Info:" << endl;
    cout << "Name: " << name << endl;
    cout << "Id: " << id << endl;
    cout << "Access type: Staff" << endl;
}
/*
Staff:
      maxNumberofbooks = 3
      maxoverduefines = 6
      overduefinesperday = 3
      maxnumberofborrowingdays = 6
*/

/* function that requests loan with the desired book, returns the loan pointer if the requesting staff is eligible to loan
 * according to the loan constraints applied to staff members and returns null otherwise */
Loan* Staff::requestLoan(Book* &book, int cartSize) {
    float maxoverduefines = 6;
    int maxnumberofbooksborrowed = 3;
    if(overdue_fines < maxoverduefines){
        if(checked_out_books.size()+cartSize <= maxnumberofbooksborrowed){
            if(book->getQuantity() > 0){
                Loan* new_loan = new Loan(this, book);
                cout<<"Loan requested successfully!"<<endl;
                return new_loan;
            }
            else {
                cout<<"Sorry, Book is unavailable!"<<endl;

            }
        }
        else{
            cout<<"Can't request loan, total number of borrowed books exceed the limit!"<<endl;
        }
    }
    else {
        cout<<"Can't request loan, overdue fines exceed the limit!"<<endl;
    }
    return nullptr;
}

/* function to return the passed book to the library books vector and change the related vectors accordingly in addition to setting the overdue fines
 * to the staff member according to the fines rules applied to staff */
void Staff::returnBorrowedBook(Book* &book, vector<Loan*> &loans){
    int maxborrowingdays = 6;
    float fineperday = 3;

    for (auto it = loans.begin(); it != loans.end(); it++)
    {
        Member * memberborrowed = (*it)->getBorrower();
        Book* borrowedbook = (*it)->getBorrowedBook();
        Date borrowdate = (*it)->getBorrowDate();
        if( borrowedbook->getIsbn() == book->getIsbn()){
            memberborrowed->removeFromCheckedOutBooks(borrowedbook); // remove borrowed book from member checked out books
            borrowedbook->setQuantity(borrowedbook->getQuantity() + 1); // increase the book quantity by 1
            if(borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) > maxborrowingdays){
                int numOfLateDays = borrowdate.getDifference(borrowdate.day, borrowdate.month, borrowdate.year) - maxborrowingdays;
                float fineToadd = numOfLateDays * fineperday;
                overdue_fines = fineToadd;
            }
            loans.erase(it); // remove loan object from library loans in main
            return;
        }
    }
}
# endif