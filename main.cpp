#include <iostream>
#include <vector>
#include "Str.h"
#include "Book.h"
#include "User.h"

using namespace std;
using namespace OurString;
using namespace OurBook;

int main() {
    vector<Book*> library_books = {}; // Assuming you have a vector to store Book objects
    vector<User*> library_users;
    vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
    Librarian lib;
    Student st;

    // Adding books to the library
    Book* book1 = new Book("Calculus", "Taha", "8624625635660", 2013, "Math");
    Book* book2 = new Book("Discrete", "Atta", "8624625635661", 2012, "Not math");
    Book* book3 = new Book("Data Structures", "Ziad", "8624625635662", 1984, "Math");
    Book* book4 = new Book("Object oriented programming", "Larson", "8624625635663", 2012, "maybe Math");
    Book* book5 = new Book("Linear Algebra", "Stewart", "8624625635669", 2004, "Math");
    library_books.push_back(book1);
    library_books.push_back(book2);
    library_books.push_back(book3);
    library_books.push_back(book4);
    library_books.push_back(book5);

    // Main loop
    while (true) {
        int menuoption_intro;
        bool breakflag = false;

        cout << "Welcome to our university system project. Please choose one of the following options:" << endl;
        cout << "1- Search for a book" << endl
             << "2- View Available books" << endl
             << "3- Exit system : ";
        cin >> menuoption_intro;

        switch (menuoption_intro) {
            case 1: {
                int case1_option;
                cout << "Search by : " << endl
                     << "1- isbn" << endl
                     << "2- year" << endl
                     << "3- title" << endl
                     << "4- author" << endl
                     << "5- genre : ";

                cin >> case1_option;
                Str case1_answer;
                switch (case1_option) {
                    case 1: {
                         cout << "Enter ISBN: ";
                        cin >> case1_answer;
                        Search_results = st.searchForBook_isbn(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    }
                    case 2:
                         cout << "Enter year: ";
                        cin >> case1_answer;
                        Search_results = st.searchForBook_publicationyear(library_books, 0);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 3:
                         cout << "Enter Title: ";
                        cin >> case1_answer;
                        Search_results = st.searchForBook_title(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 4:
                         cout << "Enter Author: ";
                        cin >> case1_answer;
                        Search_results = st.searchForBook_author(library_books, case1_answer);
                        for (auto it:Search_results) {
                            it->printData();
                        }
                        break;
                    case 5:
                         cout << "Enter Genre: ";
                        cin >> case1_answer;
                        Search_results = st.searchForBook_genre(library_books, case1_answer);
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
                    it->printData();
                }
                break;
            case 3:
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