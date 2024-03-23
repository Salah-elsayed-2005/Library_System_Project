#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
using namespace std;
using namespace OurString;
using namespace OurBook;
#ifndef LIBRARY_SYSTEM_PROJECT_USER_H
#define LIBRARY_SYSTEM_PROJECT_USER_H

namespace OurUser {

    class User {
        Str username;
        Str password;
    public:
        User() : username(""), password("") {}

        User(const Str &un, const Str &pass) : username(un), password(pass) {}

        Str getUsername() const;

        Str getPassword() const;

        void setUsername();

        void setPassword();

    };

    class Member : public User {

        /****** attributes ******/
        Str name;
        Str id;
        vector<Book *> checkedOutBooks;
        float overdue_fines;
        /****** private methods ******/
    private:

        /****** public methods ******/
    public:
        Book* searchForBook_t(const vector<Book*> &, const Str &title);
        Book *searchForBook_a(const vector<Book*> &, const Str &author);
        Book *searchForBook_g(const vector<Book*> &, const Str &genre);

        void viewCheckedOutBooks();

        void requestLoan();

        void returnBorrowedBooks(const vector<Book *> &, Book *borrowed);

    };

    class Student : public Member {

    };

    class Faculty : public Member {

    };

    class Staff : public Member {

    };

    class Librarian : public User {

    };

}


#endif //LIBRARY_SYSTEM_PROJECT_USER_H
