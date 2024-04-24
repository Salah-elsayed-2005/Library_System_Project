#include <iostream>
#include <vector>
#include "Str.h"
#ifndef LIBRARY_SYSTEM_PROJECT_BOOK_H
#define LIBRARY_SYSTEM_PROJECT_BOOK_H

using namespace std;


namespace OurBook {
    class Book {
    private: // Can only be accessed in this class
        str _title;
        str _author;
        str _isbn;
        unsigned short _publication_year;
        str _genre;
        bool _availability= false;
        unsigned short _quantity=0;

    public:        ///////////// made public for now
        void setTitle(const str&);
        void setAuthor(const str&);
        void setIsbn(const str&);
        void setPublicationYear(unsigned short);
        void setGenre(const str&);
        void setAvailability();
        void setQuantity(unsigned short);

    public: // Seen by the whole program
        Book();
        Book(const str& title, str author, str isbn, short publication_year, str genre,bool availability =0, int quantity=0);
        str getTitle();
        str getAuthor();
        const str getIsbn();
        unsigned short getPublicationYear() const;
        str getGenre();
        bool getAvailability() const;
        void printData();
        unsigned short getQuantity() const ;
        ~Book();

        friend class Librarian;
    };
}
#endif


/*
    class Librarian : public Book, public Member, public Loan {
    private:
        // Data members
        Str _username;
        int _password;
        Str _id;

        // Member functions

        // ************** Operations on books **************

        // (Use allocation for new books and use setters for assigning values)
        void addBook();
        void removeBook();
        void updateBookInfo();

        // ************** Operations on members **************

        // Use "new" to make a new member object and assign values
        void registerMember();

        // Use "delete" to deallocate the member object
        void removeMember();

        // ************** Operations on loans **************

        // Assign book for member then update the book availability and assign borrow date and due date
        void assignBookToMember();

        // Receive book from member then update the book availability
        void receiveReturns();

        // Generate a report for borrowed and overdue books for a certain member
        void showBorrowedBooks();

    public:
        // Default constructor
        Librarian();

        // Parameterized constructor
        Librarian(Str username, int password, Str id);

        // Methods "Note: all functions will ask for the object's unique identity and search for it then do its operations"
        void login();

        This is the mother function, will contain all Methods
        and will ask for a username and password upon calling
        then give you access to the rest of the functions
        */


/*
    class Member {
    private:
        Str _name;
        Str _id;
        Str _type;
        Str _password;
        vector<Book> _checkedOutBooks;
        short _fines;

    protected: // Only Librarian can set the member data
        void setName(Str name);
        void setID(Str ID);
        void setType(Str type);
        void setPassword(Str password);
        void addBookToCheckedOutBooks(Book newBook);
        void setFines(short fines);

    public:
        Member(); // Default constructor
        Member(Str name, Str id, Str type, Str password, vector<Book> checked_out_books); // Parameterized constructor
        Str getName();
        Str getID();
        Str getType();
        vector<Book> getCheckedOutBooks();
        short getFines();
        Book searchForBook(Str title);
        void viewBooks();
        void askForLoan();
        Book returnBorrowedBooks(Book borrowed);
        ~Member(); // Destructor
    };
*/