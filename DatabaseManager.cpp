#include <iostream>
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include <string>
#include "Str.h"
#include "DatabaseManager.h"

using namespace OurBook;

vector<Book*> ex_library_books;
vector<User*> ex_library_users;
vector<Loan*> ex_library_loans;

Member* getMemberPtr(str, vector<User*> &);
Book* getBookPtr(str, vector<Book*> &);

DatabaseManager::DatabaseManager(const std::string& databaseName) {
    if (sqlite3_open(databaseName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database opened successfully." << std::endl;
    }
}

DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
    std::cout << "Database connection closed." << std::endl;
}

int DatabaseManager::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " ";
    }
    std::cout << std::endl;
    return 0;
}

int DatabaseManager::execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**), void* data) {
    char* errorMessage;
    int result = sqlite3_exec(db, sql.c_str(), callback, data, &errorMessage);
    if (result != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    }
    return result;
}

void DatabaseManager::createTables() {
    // Creating Books table
    std::string sqlBooks = "CREATE TABLE IF NOT EXISTS Books ("
                           "ISBN VARCHAR(20) PRIMARY KEY,"
                           "Title VARCHAR(255) NOT NULL,"
                           "Author VARCHAR(255),"
                           "PublicationYear INT,"
                           "Genre VARCHAR(100),"
                           "Availability BOOLEAN DEFAULT TRUE,"
                           "Quantity INT DEFAULT 1);";
    execute_sql(sqlBooks);

    // Creating Users table
    std::string sqlUsers = "CREATE TABLE IF NOT EXISTS Users ("
                           "ID VARCHAR(20) PRIMARY KEY,"
                           "Name VARCHAR(255) NOT NULL,"
                           "Password VARCHAR(255) NOT NULL,"
                           "Fines FLOAT);";
    execute_sql(sqlUsers);

    // Creating Loans table
    std::string sqlLoans = "CREATE TABLE IF NOT EXISTS Loans ("
                           "ID VARCHAR(20),"
                           "ISBN VARCHAR(255),"
                           "BorrowingDate VARCHAR(10),"
                           "DueDate VARCHAR(10),"
                           "Status BOOLEAN DEFAULT FALSE,"
                           "PRIMARY KEY (ID, ISBN));";
    execute_sql(sqlLoans);

    std::cout << "Tables created if not exists." << std::endl;
}


void DatabaseManager::insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                                 int publicationYear, const std::string& genre, bool availability, int quantity) {
    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      isbn + "', '" + title + "', '" + author + "', " +
                      std::to_string(publicationYear) + ", '" + genre + "', " + (availability ? "1" : "0") + ", " +
                      std::to_string(quantity) + ");";
    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}
/*void DatabaseManager::insertUser(const std::string& isbn, const std::string& title, const std::string& author,
                                 int publicationYear, const std::string& genre, bool availability, int quantity) {
    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      isbn + "', '" + title + "', '" + author + "', " +
                      std::to_string(publicationYear) + ", '" + genre + "', " + (availability ? "1" : "0") + ", " +
                      std::to_string(quantity) + ");";
    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}*/

void DatabaseManager::insertBook(Book *book) {

    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      book->getIsbn().str2string() + "', '" + book->getTitle().str2string() + "', '" + book->getAuthor().str2string() + "', " +
                      std::to_string(book->getPublicationYear()) + ", '" + book->getGenre().str2string() + "', " +
                      std::string(book->getAvailability() ? "1" : "0") + ", " +
                      std::to_string(book->getQuantity()) + ");";

    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}


void DatabaseManager::insertLoan(Loan* loanPtr){
    // Insert loans details into the Loans table
    //std::cout << loanPtr->getBorrowedBook()->getIsbn().str2string();
    std::string loanSql = "INSERT OR REPLACE INTO Loans (ID, ISBN, BorrowingDate, DueDate, Status) VALUES ('" +
                          loanPtr->getBorrower()->getId().str2string() + "', '" +
                          loanPtr->getBorrowedBook()->getIsbn().str2string() + "', '" +
                          loanPtr->getBorrowDate().getDateString() + "', '"+ loanPtr->getDueDate().getDateString() + "', '" + std::to_string(loanPtr->getStatus()) +
                          "');";
    execute_sql(loanSql);

    std::cout << "Loan records inserted..." << std::endl;
}

/*else if (Librarian *librarianPtr = dynamic_cast <Librarian*>(userPtr)) {
// Insert user details into the Users table
        std::string librarianSql = "INSERT OR REPLACE INTO Users (ID, Name, Password) VALUES ('" +
                                   librarianPtr->getId().str2string() + "', '" + librarianPtr->getName().str2string() +
                                   "', '" +
                                   librarianPtr->getPassword().str2string() + "');";
        execute_sql(librarianSql);
        std::cout << "Librarian record inserted..." << std::endl;
    } */

void DatabaseManager::insertUser(User* userPtr) {
    if (Member *memberPtr = dynamic_cast<Member *>(userPtr)) {
        // Insert user details into the Users table
        std::string userSql = "INSERT OR REPLACE INTO Users (ID, Name, Password, Fines) VALUES ('" +
                              memberPtr->getId().str2string() + "', '" + memberPtr->getName().str2string() + "', '" +
                              memberPtr->getPassword().str2string() + "', '" +
                              std::to_string(memberPtr->getOverdueFines()) + "');";
        execute_sql(userSql);
        std::cout << "Member record inserted..." << std::endl;

    } else if (Librarian *librarianPtr = dynamic_cast <Librarian*>(userPtr)) {
// Insert user details into the Users table
        std::string librarianSql = "INSERT OR REPLACE INTO Users VALUES ('" +
                                   librarianPtr->getId().str2string() + "', '" + librarianPtr->getName().str2string() +
                                   "', '" +
                                   librarianPtr->getPassword().str2string() + "',0);";
        execute_sql(librarianSql);
        std::cout << "Librarian record inserted..." << std::endl;
    } else {
// If neither Member nor Librarian
        std::cerr << "Error: User type not supported for insertion." << std::endl;
        return;
    }
    std::cout << "Inserting a new user record completed." << std::endl;
}


void insertLoan(Loan*){}

void DatabaseManager::deleteBook(const std::string& isbn) {
    std::string sql = "DELETE FROM Books WHERE ISBN = '" + isbn + "';";
    std::cout << "Deleting book with ISBN " << isbn << "..." << std::endl;
    execute_sql(sql);
}

void DatabaseManager::displayBooks() {
    std::string sql = "SELECT * FROM Books;";
    std::cout << "Current state of the Books table:" << std::endl;
    execute_sql(sql, callback);
}
void DatabaseManager::disp() {
    std::string sql = "SELECT ISBN FROM Books;";
    std::cout << "Current state of the Books table:" << std::endl;
    execute_sql(sql, callback);
}

void DatabaseManager::searchBooks(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Books WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

void DatabaseManager::searchUsers(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Users WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

void DatabaseManager::searchLoans(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Loans WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}


void DatabaseManager::decrementBookQuantity(const std::string& isbn) {
    // First, check the current quantity
    std::string checkQuantitySql = "SELECT Quantity FROM Books WHERE ISBN = '" + isbn + "';";
    int quantity = -1;
    auto callback = [](void *data, int argc, char **argv, char **azColName) -> int {
        if (argc > 0 && argv[0]) {
            *(int*)data = std::stoi(argv[0]);
        }
        return 0;
    };

    execute_sql(checkQuantitySql, callback, &quantity);

    // If quantity is greater than 0, decrement it and update the table
    if (quantity > 0) {
        quantity--;
        bool newAvailability = quantity > 0;
        std::string updateSql = "UPDATE Books SET Quantity = " + std::to_string(quantity) +
                                ", Availability = " + (newAvailability ? "1" : "0") +
                                " WHERE ISBN = '" + isbn + "';";
        execute_sql(updateSql);
        std::cout << "Updated quantity for ISBN " << isbn << ". New quantity is " << quantity << "." << std::endl;
    } else {
        std::cout << "No more books available for ISBN " << isbn << ". Cannot decrement quantity." << std::endl;
    }
}



// TEST ONLY. DELETE ME !
void DatabaseManager::insertSampleData() {
    // Inserting sample data into Books
    std::string sqlBooks = "INSERT OR IGNORE INTO Books VALUES ('8624625635653', 'Calculus', 'Stewart', 2012, 'Math', 1, 13),('8624625635673', 'Advanced Calculus', 'Larson', 2010, 'Math', 1, 12),('8622625632663', 'Physics', 'Mo. Ismail', 2016, 'Physics', 1, 11),('8622625632673', 'Quantum Mechanics', 'Dirac', 1988, 'Physics', 1, 10),('8622625632683', 'Classical Mechanics', 'Taylor', 2005, 'Physics', 1, 13),('8624625635683', 'Statistics', 'Freedman', 2009, 'Math', 1, 13),('8624625635693', 'Algebra', 'Artin', 2011, 'Math', 0, 0),('8624625635703', 'Geometry', 'Coxeter', 1969, 'Math', 1, 1),('8624625635713', 'Trigonometry', 'Lial', 1992, 'Math', 1, 1),('8622625632693', 'Thermodynamics', 'Salah', 1985, 'Physics', 1, 69),('8622625632703', 'Electrodynamics', 'Griffiths', 1999, 'Physics', 1, 1),('8622625632713', 'Particle Physics', 'Griffiths', 2008, 'Physics', 0, 0),('8622625632723', 'Astrophysics', 'Carroll', 2007, 'Physics', 1, 2),('8624625635733', 'Differential Equations', 'Arnold', 1973, 'Math', 1, 3),('8624625635743', 'Real Analysis', 'Rudin', 1976, 'Math', 1, 7),('8624625635753', 'Complex Analysis', 'Ahlfors', 1966, 'Math', 1, 16),('8624625635763', 'Number Theory', 'Hardy', 1938, 'Math', 1, 31),('8624625635773', 'Topology', 'Munkres', 1975, 'Math', 1, 1),('8622625632733', 'Fluid Mechanics', 'Batchelor', 1967, 'Physics', 1, 2),('8622625632743', 'Relativity', 'Hartle', 2003, 'Physics', 1, 8),('8622625632753', 'Quantum Field Theory', 'Peskin', 1995, 'Physics', 1, 1),('8622625632763', 'Solid State Physics', 'Ashcroft', 1976, 'Physics', 1, 11),('8622625632773', 'Optics', 'Hecht', 1987, 'Physics', 1, 22),('8624625635783', 'Probability', 'Ross', 2010, 'Math', 1, 24),('8624625635793', 'Biostatistics', 'Daniel', 1999, 'Math', 1, 12),('8624625635803', 'Discrete Mathematics', 'Rosen', 2012, 'Math', 1, 4),('8624625635813', 'Combinatorics', 'Bona', 2011, 'Math', 1, 6),('8624625635823', 'Logic and Proofs', 'Velleman', 2006, 'Math', 1, 15),('8622625632783', 'Nuclear Physics', 'Krane', 1988, 'Physics', 1, 10),('8622625632793', 'Molecular Physics', 'McQuarrie', 2008, 'Physics', 1, 4),('8622625632803', 'Cosmology', 'Weinberg', 2008, 'Physics', 1, 16),('8622625632813', 'Signal Processing', 'Oppenheim', 1999, 'Electronics', 1, 16),('8622625632823', 'Microelectronics', 'Sedra', 2004, 'Electronics', 1, 17),('8622625632833', 'VLSI Design', 'West', 2012, 'Electronics', 1, 12),('8622625632843', 'Antenna Theory', 'Balanis', 2016, 'Electronics', 1, 15),('8622625632853', 'Digital Communication', 'Proakis', 2007, 'Electronics', 1, 14),('8622625632863', 'Control Systems', 'Ogata', 2010, 'Electronics', 1, 6),('8622625632873', 'Robotics', 'Craig', 2005, 'Engineering', 1, 21),('8622625632883', 'Thermal Physics', 'Schroeder', 2000, 'Physics', 1, 14),('8622625632893', 'Organic Chemistry', 'Carey', 2013, 'Chemistry', 1, 13),('8622625632903', 'Inorganic Chemistry', 'Housecroft', 2010, 'Chemistry', 1, 16),('8622625632913', 'Biochemistry', 'Voet', 2016, 'Chemistry', 1, 21),('8622625632923', 'Analytical Chemistry', 'Skoog', 2014, 'Chemistry', 1, 19),('8622625632933', 'Environmental Science', 'Keller', 2018, 'Biology', 1, 14),('8622625632943', 'Molecular Biology', 'Weaver', 2012, 'Biology', 1, 18),('8622625632953', 'Cell Biology', 'Pollard', 2017, 'Biology', 1, 19),('8622625632963', 'Genetics', 'Pierce', 2014, 'Biology', 1, 12),('8622625632973', 'Evolutionary Biology', 'Freeman', 2011, 'Biology', 1, 13),('8622625632983', 'Neuroscience', 'Bear', 2015, 'Biology', 1, 17),('8622625632993', 'Ecology', 'Smith', 2014, 'Biology', 1, 14),('8622625633003', 'Anatomy and Physiology', 'Marieb', 2019, 'Biology', 1, 1),('8622625633013', 'Pathophysiology', 'Copstead', 2013, 'Medicine', 1, 11),('8622625633023', 'Pharmacology', 'Katzung', 2018, 'Medicine', 1, 11),('8622625633033', 'Public Health', 'Turnock', 2016, 'Medicine', 1, 11),('8622625633043', 'Epidemiology', 'Gordis', 2014, 'Medicine', 1, 12);";

    // Inserting sample data into Users
    std::string sqlUsers = "INSERT OR IGNORE INTO Users VALUES "
                           "('stu-100', 'AboGendya', 'password123',0),"
                           "('fac-101', 'Salah', 'Donuts',0),"
                           "('stu-101285', 'Ziad', '242004',0),"
                           "('sta-103', 'Hussein', 'Rehab',0),"
                           "('lib-102', 'Fouad Hashesh', 'helloWorld',0);"
                           ;

    std::cout << "Inserting sample data..." << std::endl;
    execute_sql(sqlBooks);
    execute_sql(sqlUsers);
}

void DatabaseManager::importBooks(vector<Book*> &book_list) {
    std::string sql = "SELECT ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity FROM Books;";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Book*>* bookList = static_cast<vector<Book*>*>(data);
        if (argc == 7) {  // Make sure all columns are retrieved
            // Create a new Book instance using the retrieved data
            Book* book = new Book(
                    str(argv[1]),     // Title
                    str(argv[2]),     // Author
                    str(argv[0]),     // ISBN
                    std::stoi(argv[3]), // PublicationYear
                    str(argv[4]),    // Genre
                    argv[5], // Availability (assuming '1' for true, '0' for false)
                    std::stoi(argv[6]) // Quantity
            );
            bookList->push_back(book);
        }
        return 0;
    };

    std::cout << "importing books..." << std::endl;
    execute_sql(sql, callback, &book_list);
}



/*
void DatabaseManager::importUsers(vector<User*>& user_list) {
    // Clear existing users in the list
    for (auto user : user_list) {
        delete user;  // Proper memory management
    }
    user_list.clear();

    // SQL query to fetch all users
    std::string sql = "SELECT ID, Name, Password, Fines FROM Users;";
    auto callback = [this](void* data, int argc, char** argv, char** azColName) -> int {
        vector<User*>* userList = static_cast<vector<User*>*>(data);
        if (argc == 4) {
            std::string id = argv[0];
            std::string name = argv[1];
            std::string password = argv[2];
            float fines = std::stof(argv[3]);

            User* user = nullptr;
            if (id.find("sta-") == 0) {
                user = new Staff(name, id, password);
            } else if (id.find("fac-") == 0) {
                user = new Faculty(name, id, password);
            } else if (id.find("stu-") == 0) {
                user = new Student(name, id, password);
            } else if (id.find("lib-") == 0) {
                user = new Librarian(name, id, password);
            }

            if (user) {
                dynamic_cast<Member*>(user)->setOverdueFines(fines);
                userList->push_back(user);
            }
        }
        return 0;
    };

    execute_sql(sql, callback, &user_list);

    // After fetching all users, get their loaned books
    for (User* user : user_list) {
        Member* member = dynamic_cast<Member*>(user);
        if (member) {
            vector<Book*> loanedBooks = getLoanedBooksByUser(member->getId().str2string());  // Convert str to std::string if needed
            member->setCheckedOutBooks(loanedBooks);  // Make sure this function takes a vector by value or modifies it properly
        }
    }
}
 */
int DatabaseManager::userCallback(void *data, int argc, char **argv, char **azColName) {
    vector<User*>* userList = static_cast<vector<User*>*>(data);
    if (argc == 4) {
        std::string id = argv[0];
        std::string name = argv[1];
        std::string password = argv[2];
        float fines = std::stof((argv[3]));

        User* user = nullptr;
        if (id.find("sta-") == 0) {
            user = new Staff(name, id, password);
        } else if (id.find("fac-") == 0) {
            user = new Faculty(name, id, password);
        } else if (id.find("stu-") == 0) {
            user = new Student(name, id, password);
        } else if (id.find("lib-") == 0) {
            user = new Librarian(name, id, password);
        }
        if ( Member* member = dynamic_cast<Member*>(user)) {
            member->setOverdueFines(fines);
        }
        userList->push_back(user);
    }
    return 0;
}

void DatabaseManager::importUsers(vector<User*>& user_list) {
    // Clear existing users in the list
    // for (auto user : user_list) {
    //   delete user;  // Proper memory management
    //}
    user_list.clear();

    std::string sql = "SELECT ID, Name, Password, Fines FROM Users;";
    execute_sql(sql, userCallback, &user_list);

    // After fetching all users, get their loaned books
    for (User* user : user_list) {
        Member* member = dynamic_cast<Member*>(user);
        if (member) {
            vector<Book*> loanedBooks = getLoanedBooksByUser(member->getId().str2string());
            member->setCheckedOutBooks(loanedBooks);


            /*vector<Loan*> loanData = getLoanedDataByUser(member->getId().str2string());
            member->setMemberLoans(loanData);*/
        }
    }
}




void DatabaseManager::importLoans(vector<Loan*> &loan_list){
    loan_list.clear();

    std::string sql = "SELECT ID, ISBN, BorrowingDate, DueDate, Status FROM Loans;";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Loan*>* loan_list = static_cast<vector<Loan*>*>(data);
        if (argc == 5) {
            std::string id = argv[0];
            std::string isbn = argv[1];
            std::string borrowingDate = argv[2];
            std::string dueDate = argv[3];
            bool status = std::stoi(argv[4]) != 0;

            Loan *loan = new Loan(getMemberPtr(id, ex_library_users), getBookPtr(isbn, ex_library_books));
            loan->set_borrowingDate(borrowingDate);
            loan->set_dueDate(dueDate); // format of the string: 25-4-2024
            loan->set_status(status);
        }
        return 0;
    };

    std::cout << "Importing Loans..." << std::endl;
    execute_sql(sql, callback, &loan_list);
}


void DatabaseManager::boomboom() {
    std::string sql ="DELETE FROM Books;DELETE FROM Users;DELETE FROM Loans;";
    std::cout << "Clearing all Tables..." << std::endl;
    execute_sql(sql);
}


// Method to get all loaned books by user and return it as a vector of type Book
vector<Book*> DatabaseManager::getLoanedBooksByUser(const std::string& userId) {
    vector<Book*> loanedBooks;

    std::string sql = "SELECT b.ISBN, b.Title, b.Author, b.PublicationYear, b.Genre, b.Availability, b.Quantity "
                      "FROM Books b "
                      "JOIN Loans l ON b.ISBN = l.ISBN "
                      "WHERE l.ID = '" + userId + "' AND l.Status = 1;";

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Book*>* loanedBooks = static_cast<vector<Book*>*>(data);
        if (argc == 7) {
            // Create a new Book object and add it to the vector
            //  Book* book = new Book(argv[0], argv[1], argv[2], std::stoi(argv[3]), argv[4], argv[5], std::stoi(argv[6]));
            loanedBooks->push_back(getBookPtr(argv[0],ex_library_books));
        }
        return 0;
    };

    execute_sql(sql, callback, &loanedBooks);

    return loanedBooks;
}


// Incomplete
/*vector<Loan*> DatabaseManager::getLoanedDataByUser(const std::string& userId){
    vector<Loan*> loaningMembers;

    std::string sql = "SELECT ISBN, BorrowingDate, DueDate "
                      "FROM Loans "
                      "WHERE ID = '" + userId + "' AND Status = 1;";

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Member*>* member = static_cast<vector<Member*>*>(data);
        if (argc == 7) {
            // Create a new Book object and add it to the vector
            member->push_back(getMemberPtr(argv[0],ex_library_users));
        }
        return 0;
    };

    execute_sql(sql, callback, &loaningMembers);

    return loaningMembers;
}*/


Member* getMemberPtr(str id, vector<User*> & user_list){
    for(auto &it : user_list){
        if(it->getId() == id){
            return dynamic_cast<Member*>(it);
        }
    }
    return nullptr;
}

Book* getBookPtr(str isbn, vector<Book*> & book_list){ // ex_library_books
    for(auto &it : book_list){
        if(it->getIsbn() == isbn){
            return it;
        }
    }
    return nullptr;
}

void DatabaseManager::tmep(){
    std::string sql =
            "SELECT Books.* FROM Books INNER JOIN Loans ON Books.ISBN = Loans.ISBN WHERE Loans.ID = 'stu-101285';";
    cout << "IIIIIIIIIIIIIIIIIIIIIIIIIIII"<< endl;
    execute_sql(sql, callback);
    cout << endl;
}
