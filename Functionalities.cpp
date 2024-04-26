#include "Str.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
extern vector<Book*> library_books; // Assuming you have a vector to store Book objects
extern vector<User*> library_users;
extern vector<Loan*> library_loans;
extern vector<Book*> Search_results; // Defined for every search the user needs and will be cleared after each search
extern vector<Book*> Cart;

#if defined(_WIN32) || defined(_WIN64)
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif
bool endOfProgram= false;
bool backToTheMainMenu=false;
Librarian lib;
Student student;
// 2 Global variables are used to access methods that are the same for all users/members like Search

bool checkBack(){       //check if the user want to back to the last page
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Back to the main menu\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            backToTheMainMenu = true;
    }while(back!=1 && back!=2); //validate input
    return (back==2);
}

/*
 Checkback() function is used all over the other options to check if the user wants to either go back to the previous menu or to go back to the main menu
 It's only used of there exists a previous menu not the main menu
 */
bool checkClose(){  //check if the user want to close the program
    short back=1;
    do {
        cout << "\n\n[1] Back to the last page" << endl << "[2] Close the program\n\n";
        cout << "Please enter your choice : ";
        cin >> back;
        if (back == 2)
            endOfProgram = true;
    }while(back!=1 && back!=2); //validate input
    return (back==2);
}
/*
 CheckClose() function is used all over the other options to check if the user wants to either go back to the main menu or to close the program
 It's only used of the previous menu is the main menu
 */


void returnbook() {         //return the book to library
    system(CLEAR_COMMAND.c_str()); // clear page

    str id;
    do{
        system(CLEAR_COMMAND.c_str());
        cout<<"Please enter your ID: ";
        cin>>id;
    }while(!lib.Searchformember(library_users,id)); //validate ID

    if (!lib.Searchformember(library_users,id)->getCheckedOutBooks().empty()) {     //check if there are checked out books
        Member *member = lib.Searchformember(library_users, id);
        vector<Book *> checkedOutBooks = lib.Searchformember(library_users, id)->getCheckedOutBooks();
        bool flag=false;
        str ans;
        cout<<"\nEnter title or ISBN : ";
        cin>>ans;
        for (auto book: checkedOutBooks) {
            if (book->getIsbn() == ans || book->getTitle()==ans) {      //loop through the library books to find a book
                member->returnBorrowedBook(book, library_loans);    // return the book to the library
                flag=true;
                break;
            }
        }
        if(!flag)
            cout<<"This book isn't in your checked out books!\n";
    }
    else
        cout<<"\nThere is no books to return "<<endl;
    checkClose();
}


User* login(){
    system(CLEAR_COMMAND.c_str());
    User *toReturn;// The returned user will be either member or librarian to check which menu to appear
    bool flag=false;
    do {
        str id, password;
        cout << "Please Enter your ID       : ";
        cin >> id;
        cout << "Please Enter your Password : ";
        cin >> password;
        for (auto it: library_users) {  //loop through the users to find that user
            if (id == it->getId() && password == it->getPassword()) {
                toReturn = it;
                flag = true;
                cout << "\nLogin successful" << endl;
                system("pause>0");
                break;
            }
        }
        if (!flag) {
            cout << "\nCheck Id or password!\n" << endl;
        }
    }while(!flag);  //validate input
    return toReturn;        //return the member
}


void updatepassword(){
    str id="";
    do {
        system(CLEAR_COMMAND.c_str());  //clear screen
        cout << "Please Enter your ID : ";
        cin >> id;
    }while(!lib.Searchforuser(library_users,id));   //validate ID

    cout<<"\nPlease Enter your New password : ";
    str pass;
    cin>>pass;
    lib.Searchforuser(library_users,id)->setPassword(pass); //set the new password
    cout<<"\nPassword Updated Successfully"<<endl;

    checkClose();   //check if the user want to close the program
}


void printHeader(){     //print the header of the main menu
    cout << "Welcome to our university system project. Please choose one of the following options:" << endl;
}
void printMemberMenu(){     // menu for member
    cout << "[1] Search for a book" << endl
         << "[2] View Available books" << endl
         << "[3] Add to cart "<<endl
         << "[4] View Cart "<<endl
         << "[5] Update Password"<<endl
         << "[6] Return Book"<<endl
         << "[7] Pay fines"<<endl
         << "[8] Exit system"<<endl;
}
void printExit(){       //exit menu
    cout<<"--------------------------------------------Thanks for using our program---------------------------------------------\n\n";
    cout<<"-------------------------------------------------------Credits-------------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Salah eldin Elsayed------------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Hussein Sayed---------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Abdulrahman Abogendia----------------------------------------------\n\n";
    cout<<"-----------------------------------------------------Fouad Hashesh---------------------------------------------------\n\n";
    cout<<"--------------------------------------------------Soliman Elhassanin-------------------------------------------------\n\n";
    cout<<"------------------------------------------------------Kareem Yasser---------------------------------------------------\n\n";
    cout<<"-------------------------------------Under the Supervision of Dr. Fatma Elshehaby------------------------------------\n\n";
}

void printSearchOptions(){  //menu for search
    cout << "Search by : " << endl
         << "[1] isbn" << endl
         << "[2] year" << endl
         << "[3] title" << endl
         << "[4] author" << endl
         << "[5] genre ";
}

void searchByISBN(){    //search by ISBN
    system(CLEAR_COMMAND.c_str());  //clear the screen
    str isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;
    if((student.searchForBook_isbn(library_books, isbn))==nullptr)  //isbn doesn't exist
        cout<<"\nNo results\n";
    else {
        Search_results.push_back(student.searchForBook_isbn(library_books, isbn));  //return only one book
        Search_results.at(0)->printData();  //print book data
    }
    Search_results={};
}

void searchByYear(){    //search by year
    system(CLEAR_COMMAND.c_str());  //clear screen
    short year;
    cout << "Enter year : ";
    cin >> year;
    Search_results = student.searchForBook_publicationyear(library_books, year);
    if(Search_results.empty())  //no books
        cout<<"\nNo results\n";
    else {
        for (auto it: Search_results) {
            it->printData();
        }
    }
    Search_results={};

}
void searchByTitle(){   //by title
    system(CLEAR_COMMAND.c_str());  //clear screen
    str title;
    cout << "Enter Title : ";
    cin >> title;
    if((student.searchForBook_title(library_books, title))==nullptr)    //no books
        cout<<"\nNo results\n";
    else {
        Search_results.push_back( student.searchForBook_title(library_books, title)); //return only one book
        Search_results.at(0)->printData();
    }
    Search_results={};
}
void searchByAuthor(){  //by author
    system(CLEAR_COMMAND.c_str()); //clear screen
    str author;
    cout << "Enter Author: ";
    cin >> author;
    Search_results = student.searchForBook_author(library_books, author);
    if(Search_results.empty())  //no books
        cout<<"\nNo results\n";
    else {
        for (auto it: Search_results) {
            it->printData();
        }
    }
    Search_results={};
}
void searchByGenre(){ //by genre
    system(CLEAR_COMMAND.c_str()); //clear screen
    str genre;
    cout << "Enter Genre: ";
    cin >> genre;
    Search_results = student.searchForBook_genre(library_books, genre);
    if(Search_results.empty())  //no books
        cout<<"\nNo results\n";
    else {
        for (auto it: Search_results) {
            it->printData();
        }
    }
    Search_results={};
}
void printLibMenu(){    //menu for librarian
    cout << "[1] Search for a book" << endl
         << "[2] View Available books" << endl
         << "[3] Update Users Data "<<endl
         << "[4] Update Book Data "<<endl
         << "[5] View User Data"<<endl
         << "[6] Update password"<<endl
         << "[7] View Loan Requests"<<endl
         << "[8] Process Loan Requests"<<endl
         << "[9] Exit system"<<endl;
}
void searchForBook(){
    short choice=1;
    do{
        system(CLEAR_COMMAND.c_str());  //clear screen
        printSearchOptions();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchByISBN();
        else if(choice==2)
            searchByYear();
        else if(choice==3)
            searchByTitle();
        else if(choice==4)
            searchByAuthor();
        else if(choice==5)
            searchByGenre();
        if(choice>0 && choice<6)
            checkBack();    //if user want to back to the last page
        Search_results.clear();
    }while(!backToTheMainMenu);     //if the user want to back to the main menu
}
void viewAvailableBooks(){  //view all books in the library

    system(CLEAR_COMMAND.c_str());  //clear screen

    for (auto it : library_books) {
        if (it->getAvailability())  //if the books available, print it
            it->printData();
    }
    checkClose();   //check if the user want to close
}
void addToCart(){
    system(CLEAR_COMMAND.c_str()); //clear screen
    str input;
    bool cartFound = false;
    Book* cartBook;
    cout<<"Please Enter the title or isbn of the needed book :";
    cin>>input;
    for (auto it:library_books) {   //loop through the library books to find that book
        if ((it->getTitle() == input || it->getIsbn() == input) && it->getAvailability()) {
            cartFound = true;
            cartBook = it;
        }
    }
    if (cartFound){ // if the book exists
        cout<<"Book added to Cart successfully!"<<endl;
        Cart.push_back(cartBook);
        cartBook->setQuantity(cartBook->getQuantity()-1);
    }
    else{// the book doesn't exist
        cout<<"\nThis book doesn't exist\n";
    }
    checkClose();
}
void loanrequest(str id){
    Member* member = lib.Searchformember(library_users,id); //get the user
    Loan* new_loan ;
    new_loan= member->requestLoan(Cart.front(),Cart.size()); // assign the loan object returned by requestLoan function to new_loan
    library_loans.push_back(new_loan); // add new_loan object to library_loans vector in main to be checked later by librarian
    Cart.erase(Cart.begin()); // remove book from cart to checkout
}
void viewCart(){
    system(CLEAR_COMMAND.c_str());  //clear screen
    if(Cart.empty())
        cout<<"The cart is empty\n\n";
    else
        for(auto it:Cart)   //print the books in the cart
            it->printData();
    if(!Cart.empty()) {
        char confirmLoanRequest = '1';
        do {
            cout << "\nDo you want to request loan ? " << endl
                 << "[0] No" << endl
                 << "[1] Yes" << endl;
            cout << "Please enter your choice : ";
            cin >> confirmLoanRequest;
        }while(confirmLoanRequest!='0' && confirmLoanRequest!='1');

        if (confirmLoanRequest == '1') {
            str id;
            cout<<"Please Enter your id : ";
            cin>>id;
            if (lib.Searchformember(library_users,id)) {    //if the ID is correct
                while (!Cart.empty())
                    loanrequest(id);
            }
            else
                cout<<"\nPlease Try again"<<endl; //wrong ID
        }
    }
    checkClose();
}
void payFines(){
    system(CLEAR_COMMAND.c_str()); //clear screen
    str id="";
    do{
        cout<<"\nEnter your ID : ";
        cin>>id;
    }while(!lib.Searchforuser(library_users,id));
    if ((dynamic_cast<Member*>(lib.Searchforuser(library_users,id)))->getOverdueFines()) {
        cout<<"You need to pay "<<(dynamic_cast<Member*>(lib.Searchforuser(library_users,id)))->getOverdueFines()<<endl;
        float toPay;
        cout << "Enter the amount you want to pay : ";
        cin >> toPay;
        toPay=(dynamic_cast<Member*>(lib.Searchforuser(library_users,id)))->getOverdueFines() - toPay;
        if (toPay<0)
          toPay=0;
        lib.Searchformember(library_users, id)->setOverdueFines(toPay);
        cout << "Paid successfully-)\n";
    }
    else
        cout<<"\nThere is no fines to pay "<<endl;
    checkClose();
}
void memberMenu(){  //menu for members
    system(CLEAR_COMMAND.c_str()); //clear screen
    printHeader();
    short choice=1;
    do{
        printMemberMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchForBook();
        else if(choice==2)
            viewAvailableBooks();
        else if(choice==3)
            addToCart();
        else if(choice==4)
            viewCart();
        else if(choice==5)
            updatepassword();
        else if(choice==6)
            returnbook();
        else if(choice==7)
            payFines();
        system(CLEAR_COMMAND.c_str()); //clear screen
        if(backToTheMainMenu) { //check if the user want to back to the main menu
            choice = 1;
            backToTheMainMenu=false;
        }
        if(endOfProgram)    //if the user want to end the program
            break;
    }while(choice!=8);

    printExit();
    system("pause>0");
}

void updateMemberMenu(){
    cout<<"[1] Add a member"<<endl
        <<"[2] Remove a member"<<endl;
}
void updateMemberData(){
    system(CLEAR_COMMAND.c_str()); //clear screen
    short choice;
    str id;
    do{
        updateMemberMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice<1 || choice > 2) {
            system(CLEAR_COMMAND.c_str());
            continue;
        }
        if (choice == 1) {  //add member
            int type;
            cout<<"Please Enter type of member to add "<<endl
                <<"[1] Student"<<endl
                <<"[2] Staff"<<endl
                <<"[3] Faculty"<<endl;
            cout<<"\nPlease enter your choice : ";
            cin>>type;
            if (type>0 && type< 4) {
                lib.addMember(library_users, type);
                cout<<"\nMember Added Successfully"<<endl;
            }else
                cout<<"\nWrong choice Please try again"<<endl;
        }
        else if (choice == 2) {     //remove member
            cout<<"please Enter member ID : ";
            cin>>id;
            Member*tosend=lib.Searchformember(library_users, id);
            if (!tosend)
                cout<<"Member not found"<<endl;
            else {
                lib.removeMember(library_users,lib.Searchformember(library_users, id));
                cout << "Member Removed Successfully" << endl;
            }
        }
        if(choice>0 && choice<5)
            checkBack();    //check if the user want to back to the last menu

    }while(!backToTheMainMenu); //check if the user want to back to the main menu
}

void updateBookMenu(){  //menu for update
    cout<<"[1] Add book "<<endl
        <<"[2] Remove book"<<endl
        <<"[3] Update title"<<endl
        <<"[4] Update Author"<<endl
        <<"[5] Update ISBN"<<endl
        <<"[6] Update Genre"<<endl
        <<"[7] Update Quantity"<<endl
        <<"[8] Update Year"<<endl;
}

void updateBookData() {
    system(CLEAR_COMMAND.c_str());  //clear screen
    short choice;
    str ans;
    do {
        system(CLEAR_COMMAND.c_str());  //clear screen
        updateBookMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice<1 || choice > 8) {
            system(CLEAR_COMMAND.c_str());
            continue;
        }
        if (choice==1){
            lib.addBook(library_books);
        } else if(choice==2){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend=new Book;
            tosend=(lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.removeBook(library_books, tosend);
        }else if(choice==3){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookTitle(tosend);

        }else if (choice==4){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookAuthor( tosend);

        } else if (choice == 5){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookISBN(  tosend);
        } else if (choice == 6){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found "<<endl;
            else
                lib.updateBookGenre(  tosend);
        }else if(choice == 7){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found\n";
            else
                lib.updateBookQuantity(  tosend);
        } else if(choice==8){
            cout << "Please enter Book isbn or title : ";
            cin>>ans;
            Book*tosend= (lib.searchForBook_isbn(library_books,ans))?lib.searchForBook_isbn(library_books,ans):lib.searchForBook_title(library_books,ans);
            if (!tosend)
                cout<<"Book not found\n";
            else
                lib.updatePublicationYear(  tosend);
        }
        if(choice>0 && choice<9)
            checkBack();
    } while (!backToTheMainMenu);
}

void diplaydata(){
    system(CLEAR_COMMAND.c_str());//clear screen
    str id;
    cout<<"Please Enter Id : " ;
    cin>>id;
    if (lib.Searchforuser(library_users,id)){
        lib.Searchforuser(library_users,id)->displayInfo();
    }
    else{
        cout<<"\nNo results\n";
    }
    checkClose();
}

void viewloans(){
    system(CLEAR_COMMAND.c_str());  //clear screen
    short choice;

    do {
        system(CLEAR_COMMAND.c_str());
        cout << "[1] View All Loan Requests"<<endl
             << "[2] View Pending Loan Requests"<<endl;
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if (choice == 1)
            lib.printAllLoans(library_loans);
        if (choice == 2)
            lib.printPendingLoans(library_loans);
        if (choice==1 || choice==2)
            checkBack();
    }while(!backToTheMainMenu);
}

void processloans(){
    system(CLEAR_COMMAND.c_str());  //clear screen
    char response;
    for (auto loan:library_loans) {
        loan->generateReport(); //report for loans
        do {
            cout << "Do you want to accept this loan" << endl
                 << "[1] Yes"
                 << "[2] No" << endl;
            cin >> response;
            if (response == '1') {
                lib.processLoanRequest(loan, true);
                cout << "Loan accepted." << endl;
            }
            else if(response=='2') {
                lib.processLoanRequest(loan, false);
                cout << "Loan rejected." << endl;
            }
        }while(response!='1' && response!='2');
    }
}

void checkforoverdues(){
    for (auto &loan:library_loans) {
        lib.CheckForOverdues(loan);
    }
}

void libMenu(){
    system(CLEAR_COMMAND.c_str());
    printHeader();
    short choice=1;
    do{
        printLibMenu();
        cout<<"\nPlease enter your choice : ";
        cin>>choice;
        if(choice==1)
            searchForBook();
        else if(choice==2)
            viewAvailableBooks();
        else if(choice==3)
            updateMemberData();
        else if(choice==4)
            updateBookData();
        else if(choice==5)
            diplaydata();
        else if (choice==6)
            updatepassword();
        else if(choice==7)
            viewloans();
        else if(choice==8)
            processloans();
        system(CLEAR_COMMAND.c_str());
        if(backToTheMainMenu) {
            choice = 1;
            backToTheMainMenu=false;
        }
        if(endOfProgram)
            break;
    }while(choice!=9);

    printExit();
    system("pause>0");
}