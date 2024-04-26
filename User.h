#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H



#include <vector>
#include "Str.h"
#include "Book.h"

using namespace std;
using namespace OurBook;

class Librarian;
class Member;
class Loan;
/*****************************************/
class User {    /* An abstract class represents the general library user */
protected:    /* login attributes for user */
    str name;
    str id;
    str password;
public:
    /***** constructors & destructors *****/
    User() : name(""), password(""), id(""){}
    User(const str &n, const str &i, const str &pass) : name(n), id(i), password(pass){}
    virtual ~User(){}
    /***** setters and getters *****/
    str getName() const;
    str getId() const;
    str getPassword() const;

    void setName(str s);
    void setPassword(str pass);

    /******** overriden methods **********/
    virtual void displayInfo() const = 0;   /* pure virtual function displays user info based on its role */
    virtual void setId(str i)  = 0;     /* pure virtual function sets the user id with the correct prefix based on its role */

    /********* User methods *********/

    /* search by title and returns the book pointer */
    Book*  searchForBook_title(const vector<Book*> &, const str &);

    /* search by ISBN and returns the book pointer */
    Book*  searchForBook_isbn(const vector<Book*> &, const str &);

    /* search by author and returns vector of book pointers that has the wanted author */
    vector<Book *> searchForBook_author(const vector<Book*> &, const str &);

    /* search by author and returns vector of book pointers that has the wanted genre */
    vector<Book *> searchForBook_genre(const vector<Book*> &, const str &);

    /* search by author and returns vector of book pointers that has the wanted publication year */
    vector<Book *> searchForBook_publicationyear(const vector<Book*> &, const short &);



};



/****************************************************************************************/

class Librarian : public User { /* A class which represents the librarian */
private:
    void proceedToCheckOut(Loan* &);
public:
    /************ Constructors ***********/
    Librarian();
    Librarian(str, str, str);
    ~Librarian() override{}

    /********** overriden methods **********/
    void displayInfo() const override;  /* displays info of librarian user */
    void setId(str i) override;     /* sets User id with prefix lib */

    /************** Operations on books **************/

    void viewBooks(vector<Book*>&) const;   /* views library books */
    void addBook(vector<Book*> &);          /* adds new book to library books */
    void removeBook(vector<Book*> &, Book* &book);  /* removes book from library books */

    /* methods to update books information */
    void updateBookTitle(Book* &);
    void updateBookAuthor(Book* &);
    void updateBookISBN(Book* &);
    void updatePublicationYear(Book* &);
    void updateBookGenre(Book* &);
    void updateBookQuantity(Book* &);


    /******************* Opeerations on Members *****************/
    void addMember(vector<User *> &,int);   /* adds new member to the library users */
    void removeMember(vector<User *> &, Member*);   /* removes member from library users */

    /* methods to update member data */
    void updateMemberName(Member*);
    void updateMemberId(Member*);

    /* method to search for member in library users based on id */
    Member* Searchformember(vector<User*>,str);
    User* Searchforuser(vector<User*>,str);

    /******************** Operations on Loans ****************/

    /* function to approve or decline loan requests made by members */
    void processLoanRequest(Loan* &, bool);

    /* function to check for any delay in loans and adds overdue fines based on the delayed time*/
    void CheckForOverdues(Loan* &);

    /* functions to print all loans and the pending loans */
    void printAllLoans(vector<Loan*>) const;
    void printPendingLoans(vector<Loan*>) const;
};

/****************************************************************************************/

class Member : public User {        /* An abstract class represents the borrowing member of the library */
    /* Inherits the login information from the class User */
protected:
    /****** attributes ******/
    vector<Book*> checked_out_books;    /* books borrowed by member */
    float overdue_fines = 0;        /* fines applied to each member for late loans */

    /****** private methods ******/

public:
    /****** public methods ******/

    Member();
    Member(str, str, str);
    //~Member() override{}

    /* setters and getters */
    void setCheckedOutBooks(vector<Book*>&);
    void addToCheckedOutBooks(Book* &);
    void removeFromCheckedOutBooks(Book* &);
    void setOverdueFines(float&);

    vector<Book*> getCheckedOutBooks() const;
    float getOverdueFines() const;
    int getCheckedOutBooksSize() const;

    /********* Member Methods ********/

    /********** Loan related methods ********/

    /* a virtual function to request book loan and set loan constraints based on the member role */
    virtual Loan* requestLoan(Book* &, int) = 0;

    /* a virtual function to return the requested book and set the overdue fines based on the member loans */
    virtual void returnBorrowedBook(Book* &, vector<Loan*> &) = 0;
};

/******************************************************************************************/

class Student : public Member {     /* a class represents the borrowing student user */
public:                             /* inherits from Member class */
    /* constructors and destructors */
    Student();
    Student(str, str, str);
    Student(Member*);
    ~Student() override{}

    void setId(str i) override; /* sets User id with prefix stu */
    void displayInfo() const override; /* displays info of librarian user */

    /* polymorphic function to request loan with student specific constraints */
    Loan* requestLoan(Book* &, int) override;

    /* polymorphic function to return borrowed book and set overdue fines with value specific to student member */
    void returnBorrowedBook(Book* &, vector<Loan*> &) override;

};

class Faculty : public Member {
public:
    /* constructors and destructors */
    Faculty();
    Faculty(str, str, str);
    Faculty(Member*);
    ~Faculty() override{}

    void setId(str i) override; /* sets User id with prefix fac */
    void displayInfo() const override; /* displays info of librarian user */

    /* polymorphic function to request loan with faculty member specific constraints */
    Loan* requestLoan(Book* &, int) override;

    /* polymorphic function to return borrowed book and set overdue fines with value specific to faculty member */
    void returnBorrowedBook(Book* &, vector<Loan*> &) override;

};

class Staff : public Member {
public:
    /* constructors and destructors */
    Staff();
    Staff(str, str, str);
    Staff(Member*);
    ~Staff() override{}

    void setId(str i) override; /* sets User id with prefix sta */
    void displayInfo() const override; /* displays info of staff user */

    /* polymorphic function to request loan with faculty member specific constraints */
    Loan* requestLoan(Book* &, int) override;

    /* polymorphic function to return borrowed book and set overdue fines with value specific to faculty member */
    void returnBorrowedBook(Book* &, vector<Loan*> &) override;

};

/****************************************************************************************/

#endif //LIBRARY_SYSTEM_PROJECT_USER_H