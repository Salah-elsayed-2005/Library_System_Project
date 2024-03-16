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
        str _ISBN; // str or Long ?
        short _publicationYear;
        str _genre;
        bool _availability;
        // added
        short _quantity;

    protected:                                                  //seen by class librarian
        void SetTitle(str title);
        void SetAuthor(str author);
        void SetISBN(str ISBN);
        void SetPublicationYear(short year);
        void SetGenre(str genre);
        void SetAvailability(bool availability);
        void SetQuantity(int quantity);

    public:                                                     //seen by the whole program
        book();
        book(str title,str author,str ISBN, short publicationYear, str genre, bool availability);
        str GetTitle();
        str GetAuthor();
        str GetISBN();
        short GetPublicationYear();
        str GetGenre();
        bool GetAvailability();
        void PrintData();
        short GetQuantity();
        ~book();
    };

    class member{
    private:
        str _name;
        str _id;
        str _type;
        str _password;
        vector<book>_checkedOutBooks;
         short _fines;
    protected:                                       //only librarian can set the member data
        void SetName(str name);
        void SetID(str ID);
        void SetType(str type);
        void SetPassword(str password);
        void AddBookToCheckedOutBooks(book newBook);
        void SetFines(short fines);
    public:
        member();           //default constructor
        member(str name,str id, str type,str password,vector<book>checkedOutBooks);          //parameterized constructor
        str GetName();
        str GetID();
        str GetType();
        vector<book> GetCheckedOutBooks();
        short GetFines();
        book SearchForBook(str title);
        void ViewBooks();
        void AskForLoan();
        book ReturnBorrowedBooks(book borrowed);
        ~member();     //destructor
    };


    class loan: public book, member{
        str _BorrowDate;
        str _DueDate;
    protected:
        //This function can track the borrowed books by Member ID or book ID or borrow date or due date
        void ViewLoans(str MemberId, str ISBN , str BorrowDate, str DueDate);
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
        This is the mother function, will contain all Methods
        and will ask for a username and password upon calling
        then give you access to the rest of the functions
        */ 

    };

}

#endif
