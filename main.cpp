#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
#include "User.h"

using namespace std;
using namespace OurString;
using namespace OurBook;


User* login(const vector<User*>&);

int main() {
    vector<Book*> library_books; // Assuming you have a vector to store Book objects
    vector<User*> library_users;
    vector<Loan*> library_loans;

    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
    vector<Book*> Cart;

    Librarian lib;
    Student student;
    Staff staff;
    Faculty faculty;

    student.setName("Ziad");
    student.setId("101285");
    student.setPassword("242004");
    staff.setName("Marwan");
    staff.setId("3akeedo");
    staff.setPassword("<reham>");
    faculty.setName("Elshabeeh");
    faculty.setId("69420");
    faculty.setPassword("password");
    User *user1=&student;
    User *user2=&staff;
    User *user3=&faculty;
    library_users.push_back(user1);
    library_users.push_back(user2);
    library_users.push_back(user3);
    User* user = login(library_users);

    Str cart_input;
    // Adding books to the library
    Book* book1 = new Book("Calculus", "Taha", "8624625635660", 2013, "Math");
    book1->setQuantity(20);
    Book* book2 = new Book("Discrete", "Atta", "8624625635661", 2012, "Not math");
    book2->setQuantity(30);
    Book* book3 = new Book("Data Structures", "Ziad", "8624625635662", 1984, "Math");
    book3->setQuantity(15);
    Book* book4 = new Book("Object oriented programming", "Larson", "8624625635663", 2012, "maybe Math");
    Book* book5 = new Book("Linear Algebra", "Stewart", "8624625635669", 2004, "Math");
    library_books.push_back(book1);
    library_books.push_back(book2);
    library_books.push_back(book3);
    library_books.push_back(book4);
    library_books.push_back(book5);
    library_books.push_back(book5);

    // Main loop
    while (true) {
        int menuoption_intro;
        bool breakflag = false;

        cout << "Welcome to our university system project. Please choose one of the following options:" << endl;
        cout << "1- Search for a book" << endl
             << "2- View Available books" << endl
             << "3- Add to cart "<<endl
             << "4- View Cart "<<endl
             << "5- Exit system : ";
        cin >> menuoption_intro;
        bool cartfound = false;
        Book* cartbook;
        switch (menuoption_intro) {
            case 1: {
                int case1_option;
                Str case1_answer;
                cout << "Search by : " << endl
                     << "1- isbn" << endl
                     << "2- year" << endl
                     << "3- title" << endl
                     << "4- author" << endl
                     << "5- genre : ";

                cin >> case1_option;
                switch (case1_option) {
                    case 1: {
                          cout << "Enter ISBN: ";
                        cin >> case1_answer;
                          Search_results[0]= searchForBook_isbn(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    }
                    case 2:
                        short year;
                         cout << "Enter year: ";
                         cin >> year;
                         Search_results = searchForBook_publicationyear(library_books, year);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 3:
                         cout << "Enter Title: ";
                        cin >> case1_answer;
                        Search_results[0] = searchForBook_title(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 4:
                         cout << "Enter Author: ";
                        cin >> case1_answer;
                        Search_results = searchForBook_author(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 5:
                         cout << "Enter Genre: ";
                        cin >> case1_answer;
                        Search_results = searchForBook_genre(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    default:
                        cout << "Invalid option." << endl;
                        break;
                }
                break; // Exiting the case 1 block
            }
            case 2:
                for (auto it : library_books) {
                    if (it->getAvailability())
                        it->printData();
                }
                break;
            case 3:
                cout<<"Please Enter the title or isbn of the needed book :";
                cin>>cart_input;
                for (auto it:library_books) {
                    if ((it->getTitle() == cart_input || it->getIsbn() == cart_input) && it->getAvailability()) {
                        cartfound = true;
                        cartbook = it;
                    }
                }
                if (cartfound){
                    cout<<"Book added to Cart successfully!"<<endl;
                    Cart.push_back(cartbook);
                    cartbook->setQuantity(cartbook->getQuantity()-1);

                }
                break;
            case 4:
                for(auto it:Cart){
                    it->printData();
                }
                break;
            case 5:
                breakflag = true;
                break;
            default:
                cout << "Please enter a valid input." << endl;
                break;
        }

        if (breakflag)
            break;
    }

    return 0;
}

User* login(const vector<User*>& library_users){
    label:
    Str id,password;
    cout<<"Please Enter your ID : ";
    cin>>id;
    cout<<"Please Enter your Password : ";
    cin>>password;
    bool flag = false;
    User*toreturn;
    for (auto it:library_users) {
        if (id==it->getId() && password==it->getPassword()){
            toreturn=it;
            flag= true;
            cout << "Login successful" <<endl;
        }
    }
    if (!flag) {
        cout << "Check Id or password " <<endl;
        goto label;
    }

     return toreturn;
}

#if 0
#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
#include "User.h"
using namespace std;
using namespace OurString;
using namespace OurBook;
int main()
{
    vector<Book*> library_books={};
    vector<User*> library_users;
    //vector<Loan*> library_loans;
    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
    Librarian lib;
    Student st;


    Book* book1=new Book("Calculus","Larson","8624625635663",2012 ,"Math" );
    Book* book2=new Book("Calculus","Larson","8624625635663",2012 ,"Math" );
    Book* book3=new Book("Calculus","Larson","8624625635663",2012 ,"Math" );
    Book* book4=new Book("Calculus","Larson","8624625635663",2012 ,"Math" );
    Book* book5=new Book("Calculus","Stewart","8624625635669",2004 ,"Math" );
    library_books.push_back(book1);
    library_books.push_back(book2);
    library_books.push_back(book3);
    library_books.push_back(book3);
    library_books.push_back(book5);

/***************************************************/
///////////////MAIN/////////////////////////////////
/**************************************************/
/**************User MESSAGE ----------> Sign in()****************/
    while (1){
        int menuoption_intro;
        bool breakflag= false;
        cout<<"Welcome to our university system project please choose one of the following : "<<endl;
        cout<<"1-Search for a book "<<endl
            <<"2-View Available books"<<endl
            <<"3-Exit system : ";
        cin>>menuoption_intro;
        switch (menuoption_intro) {
            case 1:
                int case1_option;
                cout << "Search by : " << endl
                     << "1-isbn" << endl
                     << "2-name" << endl
                     << "3-title" << endl
                     << "4-author" << endl
                     << "5-title" << endl
                     << "6-genre : " << endl;
                cin >> case1_option;
                switch (case1_option) {
                    Str case1_answer;
                    cout << "Enter : " << endl;
                    cin >> case1_answer;
                    case 1 :
                        Search_results = st.searchForBook_isbn(library_books, case1_answer);
                        break;
                    case 2 :
                        break;
                    case 3 :
                        break;
                    case 4 :
                        break;
                    case 5 :
                        break;
                    case 6 :
                        break;
                    default:
                        break;

                }
                break;

            case 2:
                for (auto it :library_books) {
                        it->printData();
                }
                break;
            case 3:
                breakflag= true;
                break;
            default:
                cout<<"please enter a valid input"<<endl;
                //goto
                break;
        }
        if (breakflag)
        break;
    }

      return 0;
}


# endif