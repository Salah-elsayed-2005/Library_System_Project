#ifndef Classes_h
#define Classes_h

#include <vector>
#include "str.h"
using namespace std;
using namespace OurString;

namespace OurClasses{

    class book{
    private:                                                    //can only be accessed in this class
        str _title;
        str _author;
        str _ISBN;
        short _publicationYear;
        str _genre;
        bool _availability;
    protected:                                                  //seen by class librarian
        void SetTitle(str title);
        void SetAuthor(str author);
        void SetISBN(str ISBN);
        void SetPublicationYear(short year);
        void SetGenre(str genre);
        void SetAvailability(bool availability);
    public:                                                     //seen by th whole program
        book();
        book(str title,str author,str ISBN, short publicationYear, str genre, bool availability);
        str GetTitle();
        str GetAuthor();
        str GetISBN();
        short GetPublicationYear();
        str GetGenre();
        bool GetAvailability();
        void PrintData();
    };

    class member{
    private:
        str _name;
        str _id;
        str _type;
        vector<book>_checkedOutBooks;
        short _fines;
    public:
        member();
        member(str name,str id, str type,vector<book>checkedOutBooks);
        book SearchForBook(str title);
        void ViewBooks();
        void AskForLoan();
        book ReturnBorrowedBooks(book borrowed);
    };

    class librarian :public book, member, loan{
    private:
    //Data members
        str _Username;
        int _Password;
        str _Id;
    
    //Member functions
    
        //************** operations on books **************

        // (use allocation for new books and use setters for assigning values)
        void AddBook();
        void RemoveBook();
        void UpdateBookInfo();

        //************** operations on members **************

        //waiting for setters and getters function for member class (hussein)

        //use "new" to make a new member object and assign values
        void Register_Member();

        // use "delete" to deallocate the member object
        void Remove_Member();

        //************** operations on loans **************

        // assign book for member then update the book availability and assign borrow date and due date
        void AssignBookToMember();

        //receive book from member then update the book availability
        void ReceiveReturns(); 

        // Generate a report for borrowed and overdue books for a certain member
        void ShowBorrowedBooks();

    public:
        //Default constructor
        librarian();

        //Parametarized constructor
        librarian(str username, int pass, int id);

        //METHODS "Note: all functions will ask for the object's unique identity and search for it then do it's operations"

        void login(); 
        /*
        This is the mother functin, will contain all Methods 
        and will ask for a username and password uppon calling
        then give you access to the rest of the functions
        */ 

    };

    class loan: public book, member{
    protected:
        //This function can track the borrowed books by Member ID or book ID or borrow date or due date
        void ViewLoans(str MemberId="NONE", str ISBN="NONE", str BorrowDate, str DueDate="NONE");
    };

}

#endif
