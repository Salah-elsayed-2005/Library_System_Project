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
    protected:                                                      //only librarian can set the member data
        void SetName(str name);
        void SetID(str ID);
        void SetType(str type);
        void SetPassword(str password);
        void AddBookToCheckedOutBooks(book newBook);
        void SetFines(short fines);
    public:
        member();
        member(str name,str id, str type,str password,vector<book>checkedOutBooks);
        str GetName();
        str GetID();
        str GetType();
        vector<book> GetCheckedOutBooks();
        short GetFines();
        book SearchForBook(str title);
        void ViewBooks();
        void AskForLoan();
        book ReturnBorrowedBooks(book borrowed);
    };

}

#endif
