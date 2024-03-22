#ifndef Classes_h
#define Classes_h

#include <vector>
#include "str.h"
using namespace std;
using namespace OurString;

namespace OurClasses {

    class Book {
    private: // Can only be accessed in this class
        Str _title;
        Str _author;
        Str _isbn; // Str or Long?
        short _publicationYear;
        Str _genre;
        bool _availability;
        // Added
        short _quantity;

    protected: // Seen by class Librarian
        void setTitle(Str title);
        void setAuthor(Str author);
        void setIsbn(Str isbn);
        void setPublicationYear(short year);
        void setGenre(Str genre);
        void setAvailability(bool availability);
        void setQuantity(int quantity);

    public: // Seen by the whole program
        Book();
        Book(Str title, Str author, Str isbn, short publication_year, Str genre, bool availability);
        Str getTitle();
        Str getAuthor();
        Str getIsbn();
        short getPublicationYear();
        Str getGenre();
        bool getAvailability();
        void printData();
        short getQuantity();
        ~Book();
    };

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

    class Loan : public Book, public Member {
    private:
        Str _borrow_date;
        Str _due_date;

    protected:
        // This function can track the borrowed books by Member ID or book ID or borrow date or due date
        void viewLoans(Str member_id, Str isbn, Str borrow_date, Str due_date);
    };

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
        /*
        This is the mother function, will contain all Methods
        and will ask for a username and password upon calling
        then give you access to the rest of the functions
        */
    };

}

#endif
