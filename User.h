#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H

#include <vector>
#include "Str.h"
#include "Book.h"

using namespace std;
using namespace OurString;
using namespace OurBook;

class Librarian;
class Member;
class Loan;
/*****************************************/
class User {
protected:
    Str name;
    Str id;
    Str password;
public:
    User() : name(""), password(""), id(""){}
    User(const Str &n, const Str &i, const Str &pass) : name(n), id(i), password(pass){}

    Str getName() const;
    Str getId() const;
    Str getPassword() const;

    void setName(Str s);
    void setPassword(Str pass);

    /******** overriden methods **********/
    virtual void displayInfo() const = 0;
    virtual void setId(Str i)  = 0;

    /********* User methods *********/
    Book*  searchForBook_title(const vector<Book*> &, const Str &);
    Book*  searchForBook_isbn(const vector<Book*> &, const Str &);
    vector<Book *> searchForBook_author(const vector<Book*> &, const Str &);
    vector<Book *> searchForBook_genre(const vector<Book*> &, const Str &);
    vector<Book *> searchForBook_publicationyear(const vector<Book*> &, const short &);



    virtual ~User(){}
};



/****************************************************************************************/

class Member : public User {
protected:
    /****** attributes ******/
    vector<Book*> checked_out_books;
    vector<Loan*> member_loans;
    float overdue_fines = 0;

    /****** private methods ******/

public:
    /****** public methods ******/

    Member();
    Member(Str, Str, Str);
    ~Member() override{}

    void setCheckedOutBooks(vector<Book*>&);
    void addToCheckedOutBooks(Book* &);
    void setMemberLoans(vector<Loan*>&);
    void setOverdueFines(float&);

    vector<Book*> getCheckedOutBooks() const;
    vector<Loan*> getMemberLoans() const;
    float getOverdueFines() const;
    int getCheckedOutBooksSize() const;

    /********* Member Methods ********/
    void viewCheckedOutBooks() const;

    /********** Loan related methods ********/

    virtual void requestLoan(Member&, Librarian &, const vector<Book*> &) = 0;
    virtual void returnBorrowedBooks(const vector<Book*> &, Book *) = 0;


};
/****************************************************************************************/

class Librarian : public User, private Book{
private:
    bool validateLoan(Loan* &);
    void proceedToCheckOut(Loan* &);
public:
    /************ Constructors ***********/
    Librarian();
    Librarian(Str, Str, Str);
    ~Librarian() override{}
     /********** overriden methods **********/
     void displayInfo() const override;
     void setId(Str i) override;

     /************** Operations on books **************/

    // (Use allocation for new books and use setters for assigning values)
    void viewBooks(vector<Book*>&) const;
    void addBook(vector<Book*> &, Book* &book);
    void removeBook(vector<Book*> &, Book* &book);

    void updateBookTitle(Book* &);
    void updateBookAuthor(Book* &);
    void updateBookISBN(Book* &);
    void updatePublicationYear(Book* &);
    void updateBookGenre(Book* &);
    void updateBookQuantity(Book* &);

    /******************* Opeerations on Members *****************/
    void addMember(vector<User *> &, Member*);
    void removeMember(vector<User *> &, Member*);
    void updateMemberName(Member*);
    void updateMemberId(Member*);
    Member* Searchformember(vector<User*>,Str);

    /******************** Operations on Loans ****************/
    void processLoan(Loan* &);
    void printAllLoans(vector<Loan*>) const;
    void printPendingLoans(vector<Loan*>) const;
};
/****************************************************************************************/

class Student : public Member {
public:
    Student();
    Student(Str, Str, Str);
    ~Student() override{}

    void setId(Str i) override;
    void displayInfo() const override;

    void requestLoan(Book* &, vector<Loan*> &);
    void returnBorrowedBooks(const vector<Book*> &, Book *);

    friend class Librarian;
};

class Faculty : public Member {
public:
    Faculty();
    Faculty(Str, Str, Str);
    ~Faculty() override{}

    void setId(Str i) override;
    void displayInfo() const override;
/*
    void requestLoan(Member&, Librarian &, const vector<Book*> &);
    void returnBorrowedBooks(const vector<Book*> &, Book *);
*/
    friend class Librarian;
};

class Staff : public Member {
    Staff();
    Staff(Str, Str, Str);
    ~Staff() override{}
public:
    void setId(Str i) override;
    void displayInfo() const override;
/*
    void requestLoan(Member&, Librarian &, const vector<Book*> &);
    void returnBorrowedBooks(const vector<Book*> &, Book *);
*/
    friend class Librarian;
};

/****************************************************************************************/

#endif //LIBRARY_SYSTEM_PROJECT_USER_H
