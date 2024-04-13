#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H

#include <vector>
#include "Str.h"
#include "Book.h"
#include "Loan.h"
using namespace std;
using namespace OurString;
using namespace OurBook;
enum UserType{member,staff,faculty};
 namespace OurUser {
    class Librarian;

    class User {
    protected:
        Str username;
        Str password;
        Str name;
        Str id;
        int type=0;
    public:
        User() : username("Null"), password("Null"), name("Null"),id("Null"){}
        User(const Str &un, const Str &pass, const Str &n,const Str &i) : username(un), password(pass), name(n),id(i){}

        virtual Str getUsername() const=0;
        virtual Str getPassword() const=0;
        virtual Str getName()const=0;
        virtual Str getId()const=0;

        virtual void setUsername(Str)=0;
        virtual void setPassword(Str)=0;
        virtual void setName(Str)=0;
        virtual void setId(Str)=0;

        virtual void showdata()=0;

        ~User(){}
    };



    /****************************************************************************************/

    class Member : public User {
    private:
        /****** attributes ******/
        float overdue_fines = 0;
        /****** private methods ******/

    public:
        /****** public methods ******/
        Str getUsername() const;
        Str getPassword() const;
        Str getName()const;
        Str getId()const;

        void setUsername(Str);
        void setPassword(Str);
        void setName(Str);
        void setId(Str);

        void showdata();
        vector<Book *>searchForBook_title(const vector<Book*> &, const Str &title);
        vector<Book *> searchForBook_author(const vector<Book*> &, const Str &author);
        vector<Book *>  searchForBook_genre(const vector<Book*> &, const Str &genre);
        vector<Book *> searchForBook_isbn(const vector<Book*> &, const Str &isbn);
        vector<Book *>  searchForBook_publicationyear(const vector<Book*> &, const short &publicationyear);

        vector<Book*> checkedOutBooks;
        void viewCheckedOutBooks();
        void requestLoan(Member&, Librarian &, const vector<Book*> &);
        void returnBorrowedBooks(const vector<Book*> &, Book *borrowed);

    };

# if 0
  ///  Do we really need classes for each type ?
    class Student : public Member {

    };

    class Faculty : public Member {

    };

    class Staff : public Member {

    };
# endif
    class Librarian : public User, public Book {
    public:
        Str getUsername() const;
        Str getPassword() const;
        Str getName()const;
        Str getId()const;

        void setUsername(Str);
        void setPassword(Str);
        void setName(Str);
        void setId(Str);

        void showdata();
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
