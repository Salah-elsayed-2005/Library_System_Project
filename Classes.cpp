#include "Classes.h"
#include "str.h"
#include <iostream>

using namespace OurString;
using namespace OurClasses;
using namespace std;

//*********************************** BOOK CLASS IMPLEMENTATION ***********************************
book::book(){_title="NULL",_author="NULL",_ISBN="NULL",_publicationYear=0,_genre="NULL";}                                                                                                  //default constructor
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
book::~book() {}             //destructor



//*********************************** Member CLASS IMPLEMENTATION ***********************************
 member::member(){_name="NONE";_id="NONE",_type="NONE",_password="NONE",_checkedOutBooks={},_fines=0;}
 member::member(str name, str id="NONE", str type="NONE", str password="NONE", vector<book> checkedOutBooks={}):_name(name),_id(id),_type(type),_password(password),_checkedOutBooks(checkedOutBooks){}
 str member::GetName() {return _name;}
 str member:: GetID(){return _id;}
 str member::GetType(){return _type;}
 short member::GetFines(){return _fines;}
 vector<book> member::GetCheckedOutBooks() {return _checkedOutBooks;}
 void member::SetName(str name){_name=name;}
 void member::SetID(str ID){_id=ID;}
 void member::SetType(str type){_type=type;}
 void member:: SetPassword(str password){_password=password;}
 void member:: AddBookToCheckedOutBooks(book newBook){_checkedOutBooks.push_back(newBook);}
 void member::SetFines(short fines){_fines=fines;}

member::~member() = default;

//*********************************** LOAN CLASS IMPLEMENTATION ***********************************
void loan::ViewLoans(str MemberId="NONE", str ISBN="NONE", str BorrowDate="NONE", str DueDate="NONE"){
    //Will implement when database is up
}