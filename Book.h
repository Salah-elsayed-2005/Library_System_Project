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

