#include "Classes.h"
#include "str.h"
#include <iostream>

using namespace OurString;
using namespace OurClasses;
using namespace std;

book::book(){}                                                                                              //default constructor
book::book(str title,str author,str ISBN, short publicationYear, str genre, bool availability){                //parameterized constructor
    _title=title;
    _author=author;
    _ISBN=ISBN;
    _publicationYear=publicationYear;
    _genre=genre;
    _availability=availability;
}

//setters and getters
void book::SetTitle(str title){
    _title=title;
}
str book::GetTitle(){
    return _title;
}
void book::SetAuthor(str author){
    _author=author;
}
str book::GetAuthor(){
    return _author;
}
void book::SetISBN(str ISBN){
    _ISBN=ISBN;
}
str book::GetISBN(){
    return _ISBN;
}
void book::SetPublicationYear(short year){
    _publicationYear=year;
}
short book::GetPublicationYear(){
    return _publicationYear;
}
void book::SetGenre(str genre){
    _genre=genre;
}
str book::GetGenre(){
    return _genre;
}
void book::SetAvailability(bool availability){
    _availability=availability;
}
bool book::GetAvailability(){
    return _availability;
}

void book::PrintData() {                                                                    //print the data of the book
    cout<<"----------------------Book Info----------------------------\n";
    cout<<"Title            : "<<_title<<endl;
    cout<<"Author           : "<<_author<<endl;
    cout<<"ISBN             : "<<_ISBN<<endl;
    cout<<"Publication Year : "<<_title<<endl;
    cout<<"Genre            : "<<_genre<<endl;
    cout<<"Availability     : "<<(_availability ? "Available" : "Not available")<<endl;
    cout<<"-----------------------------------------------------------"<<endl;
}
