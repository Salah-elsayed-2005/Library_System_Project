//
// Created by Asteroid on 3/23/2024.
//
#include "Book.h"
#include "User.h"
using namespace OurUser;
using namespace OurBook;
/***********    Search For Books   ************/
Book* Member::searchForBook_t(const vector<Book*>& library_books, const Str& title){
    for(auto it : library_books){
        if(it->getTitle() == title)
            return it;
    }
    return nullptr;
}
Book* Member::searchForBook_a(const vector<Book*>& library_books, const Str& author){
    for(auto it : library_books){
        if(it->getAuthor() == author)
            return it;
    }
    return nullptr;
}
Book* Member::searchForBook_g(const vector<Book*>& library_books, const Str& genre){
    for(auto it : library_books){
        if(it->getGenre() == genre)
            return it;
    }
    return nullptr;
}

/****************             ******************/
void Member::viewCheckedOutBooks(){
    cout << "Your books: " << endl;
    for(auto it : checkedOutBooks){
        cout << "Title: "<< it->getTitle() << endl;
        cout << "Author: " << it->getAuthor() << endl;
        cout << "Due Date: " << "//////// will be added" << endl;
        cout << "__________________________________________" << endl;
    }
}

void Member::returnBorrowedBooks(const vector<Book*>& library_books, Book* borrowed){
    for(auto it = library_books.begin(); it != library_books.end(); it++){

        if((*it)->getTitle() == borrowed->getTitle()){
            (*it)->setQuantity(((*it)->getQuantity()) + 1);
            (*it)->setAvailability(true);
        }

    }
    for(auto it = checkedOutBooks.begin(); it != checkedOutBooks.end(); it++){
        if((*it)->getTitle() == borrowed->getTitle()){
            checkedOutBooks.erase(it);
        }
    }
}
void Member::requestLoan(){

}
