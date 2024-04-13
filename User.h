#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H

#include <vector>
#include "Str.h"
#include "Book.h"
#include "Loan.h"
using namespace std;
using namespace OurString;
using namespace OurBook;
//enum UserType{member,staff,faculty};
 namespace OurUser {
    class Librarian;
    class Member;

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
        void setId(Str i);
        void setPassword(Str pass);

        //virtual void showdata()=0;

        /************ MEMBER METHODS ***********/
        virtual void setCheckedOutBooks(vector<Book*>&) = 0;
        virtual void setMemberLoans(vector<Loan*>&) = 0;
        virtual void setOverdueFines(float&) = 0;

        virtual vector<Book*> getCheckedOutBooks() const = 0;
        virtual vector<Loan*> getMemberLoans() const = 0;
        virtual float getOverdueFines() const = 0;

        virtual vector<Book *> searchForBook_title(const vector<Book*> &, const Str &) = 0;
        virtual vector<Book *> searchForBook_author(const vector<Book*> &, const Str &) = 0;
        virtual vector<Book *> searchForBook_genre(const vector<Book*> &, const Str &) = 0;
        virtual vector<Book *> searchForBook_isbn(const vector<Book*> &, const Str &) = 0;
        virtual vector<Book *> searchForBook_publicationyear(const vector<Book*> &, const short &) = 0;

        virtual void viewCheckedOutBooks() = 0;
        virtual void requestLoan(Member&, Librarian &, const vector<Book*> &) = 0;
        virtual void returnBorrowedBooks(const vector<Book*> &, Book*) = 0;

        /*************** LIBRARIAN METHODS *************/
        virtual void addBook(vector<Book*> &, Book* &book) = 0;
        virtual void removeBook(vector<Book*> &, Book* &book) = 0;


        virtual void updateBookTitle(Book* &) = 0;
        virtual void updateBookAuthor(Book* &) = 0;
        virtual void updateBookISBN(Book* &) = 0;
        virtual void updatePublicationYear(Book* &) = 0;
        virtual void updateBookGenre(Book* &) = 0;
        virtual void updateBookAvailabitlity(Book* &) = 0;
        virtual void updateBookQuantity(Book* & ) = 0;
        //  virtual void processLoanRequest(Member &,Loan &) = 0;
        virtual void PrintTime() = 0;
        ~User(){}
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
        /************************************************
        Str getUsername() const;
        Str getPassword() const;
        Str getName()const;
        Str getId()const;

        void setUsername(Str);
        void setPassword(Str);
        void setName(Str);
        void setId(Str);

        ***************************************************/

        Member();
        Member(Str, Str, Str, vector<Book*>, vector<Loan*>, float);
        Member(Member&);

        void setCheckedOutBooks(vector<Book*>&) override;
        void setMemberLoans(vector<Loan*>&) override;
        void setOverdueFines(float&) override;

        vector<Book*> getCheckedOutBooks() const override;
        vector<Loan*> getMemberLoans() const override;
        float getOverdueFines() const override;

        vector<Book *> searchForBook_title(const vector<Book*> &, const Str &) override;
        vector<Book *> searchForBook_author(const vector<Book*> &, const Str &) override;
        vector<Book *> searchForBook_genre(const vector<Book*> &, const Str &) override;
        vector<Book *> searchForBook_isbn(const vector<Book*> &, const Str &) override;
        vector<Book *> searchForBook_publicationyear(const vector<Book*> &, const short &) override;

        void viewCheckedOutBooks() override;
        void requestLoan(Member&, Librarian &, const vector<Book*> &) override;
        void returnBorrowedBooks(const vector<Book*> &, Book *) override;

       // void showdata() override;
    };
  ///  Do we really need classes for each type ?
    class Student : public Member {

    };

    class Faculty : public Member {

    };

    class Staff : public Member {

    };

    class Librarian : public User{
    public:
//        Str getUsername() const;
//        Str getPassword() const;
//        Str getName()const;
//        Str getId()const;
//
//        void setUsername(Str);
//        void setPassword(Str);
//        void setName(Str);
//        void setId(Str);

        //void showdata();

        Librarian();
        Librarian(Str, Str, Str);
        // ************** Operations on books **************

        // (Use allocation for new books and use setters for assigning values)
        void addBook(vector<Book*> &, Book* &book);
        void removeBook(vector<Book*> &, Book* &book);


        void updateBookTitle(Book* &);
        void updateBookAuthor(Book* &);
        void updateBookISBN(Book* &);
        void updatePublicationYear(Book* &);
        void updateBookGenre(Book* &);
        void updateBookAvailabitlity(Book* &);
        void updateBookQuantity(Book* & );
        //  void processLoanRequest(Member &,Loan &);
        void PrintTime();
    };

}


#endif //LIBRARY_SYSTEM_PROJECT_USER_H
