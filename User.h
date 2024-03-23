#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H

#include <vector>
#include "Str.h"
#include "Book.h"
using namespace std;
using namespace OurString;
using namespace OurBook;


namespace OurUser {

    class User {
        Str username;
        Str password;
        Str name;
    public:
        User() : username(""), password(""), name(""){}
        User(const Str &un, const Str &pass, const Str &n) : username(un), password(pass), name(n) {}

        Str getUsername() const;
        Str getPassword() const;
        void setUsername(Str);
        void setPassword(Str);

    };

    class Member : public User {

        /****** attributes ******/
        Str id;
        vector<Book*> checkedOutBooks;
        float overdue_fines;
        /****** private methods ******/
    private:

        /****** public methods ******/
    public:
        Book* searchForBook_t(const vector<Book*> &, const Str &title);
        Book* searchForBook_a(const vector<Book*> &, const Str &author);
        Book* searchForBook_g(const vector<Book*> &, const Str &genre);

        void viewCheckedOutBooks();
        void requestLoan();
        void returnBorrowedBooks(const vector<Book*> &, Book *borrowed);


    };

    class Student : public Member {

    };

    class Faculty : public Member {

    };

    class Staff : public Member {

    };

    class Librarian : public User, public Book {
    public:
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


    };

}


#endif //LIBRARY_SYSTEM_PROJECT_USER_H
