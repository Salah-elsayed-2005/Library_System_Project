#include <iostream>
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include <string>
#include "Str.h"
#include "DatabaseManager.h"

using namespace OurBook;

// The external vectors that holds references to books, users, and loans
vector<Book*> ex_library_books;
vector<User*> ex_library_users;
vector<Loan*> ex_library_loans;


// Function to get the pointer that points to the member by passing the member ID
Member* getMemberPtr(str, vector<User*> &);

// Function to get the pointer that points to the book by passing the book's ISBN
Book* getBookPtr(str, vector<Book*> &);

// Constructor for DatabaseManager, opens the database connection or creates the database if it does not exist
DatabaseManager::DatabaseManager(const std::string& databaseName) {
    if (sqlite3_open(databaseName.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
    } else {
        std::cout << "Database opened successfully." << std::endl;
    }
}

// Destructor for DatabaseManager, closes the database connection
DatabaseManager::~DatabaseManager() {
    sqlite3_close(db);
    std::cout << "Database connection closed." << std::endl;
}

/**
 * Callback function used by SQLite3 to process the results of a database query.
 * This function is invoked by SQLite3 for each row of the query result.
 *
 * @param NotUsed Unused parameter (can be nullptr).
 * @param argc Number of columns in the result set.
 * @param argv Array of strings containing the column values for the current row.
 * @param azColName Array of strings containing the column names.
 * @return Always returns 0 to indicate successful processing of the row.
 */
int DatabaseManager::callback(void *NotUsed, int argc, char **argv, char **azColName) {
    // Loop through each column in the current row
    for (int i = 0; i < argc; i++) {
        // Print the column name and its corresponding value (or "NULL" if the value is NULL)
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << " ";
    }
    // Move to the next line after printing all columns of the current row
    std::cout << std::endl;
    // Return 0 to indicate successful processing of the row
    return 0;
}

/**
 * Executes an SQL statement on the SQLite database.
 *
 * @param sql The SQL statement to execute.
 * @param callback A pointer to a callback function to handle results, if applicable.
 * @param data A pointer to user-defined data that can be passed to the callback function.
 * @return An integer result code indicating the success or failure of the SQL statement execution.
 *         - SQLITE_OK if the statement is executed successfully.
 *         - An error code otherwise.
 * @note This function uses the SQLite C API to execute the SQL statement on the connected database.
 *       If a callback function is provided, it will be invoked for each row of the result set.
 *       Any error messages encountered during execution are printed to the standard error stream.
 */
int DatabaseManager::execute_sql(const std::string& sql, int (*callback)(void*,int,char**,char**), void* data) {
    // Variable to store error message
    char* errorMessage;
    // Execute the SQL statement and store the result code
    int result = sqlite3_exec(db, sql.c_str(), callback, data, &errorMessage);
    // Check if the execution was successful (SQLITE_OK = 0)
    if (result != SQLITE_OK) {
        // Print the SQL error message to the standard error stream
        std::cerr << "SQL error: " << errorMessage << std::endl;
        // Free the error message memory allocated by SQLite
        sqlite3_free(errorMessage);
    }
    // Return the result code (0 if successful)
    return result;
}


/**
 * Creates the necessary tables in the database if they do not already exist.
 * This function creates the Books and Members tables in the database.
 * If the tables already exist, this function does nothing.
 * The Books table stores information about books, and the Members table stores information about library members.
 * Both tables have primary keys: ISBN for Books and MemberID for Members.
 * The Books table has fields: ISBN, Title, Author, PublicationYear, Genre, Availability, and Quantity.
 * The Members table has fields: MemberID, Name, Email, and PhoneNumber.
 * These tables are essential for managing book records and member information in the library system.
 */
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


/**
 * Inserts or updates a book record in the Books table of the database using the provided parameters.
 * This function constructs an SQL statement to insert or replace a book record in the Books table
 * using the specified values for ISBN, title, author, publication year, genre, availability, and quantity.
 *
 * @param isbn            The ISBN (International Standard Book Number) of the book.
 * @param title           The title of the book.
 * @param author          The author of the book.
 * @param publicationYear The publication year of the book.
 * @param genre           The genre of the book.
 * @param availability    The availability status of the book (true if available, false otherwise).
 * @param quantity        The quantity of the book available.
 *
 */
void DatabaseManager::insertBook(const std::string& isbn, const std::string& title, const std::string& author,
                                 int publicationYear, const std::string& genre, bool availability, int quantity) {
    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      isbn + "', '" + title + "', '" + author + "', " +
                      std::to_string(publicationYear) + ", '" + genre + "', " + (availability ? "1" : "0") + ", " +
                      std::to_string(quantity) + ");";
    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}

/**
 * Inserts or updates a book record in the Books table of the database by passing the book pointer.
 * This function constructs an SQL statement to insert or replace a book record in the Books table
 * using the information from the provided Book object that the pointer points to.
 *
 * @param book A pointer to the Book object representing the book record to be inserted or updated.
 *
 */
void DatabaseManager::insertBook(Book *book) {

    std::string sql = "INSERT OR REPLACE INTO Books (ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity) VALUES ('" +
                      book->getIsbn().str2string() + "', '" + book->getTitle().str2string() + "', '" + book->getAuthor().str2string() + "', " +
                      std::to_string(book->getPublicationYear()) + ", '" + book->getGenre().str2string() + "', " +
                      std::string(book->getAvailability() ? "1" : "0") + ", " +
                      std::to_string(book->getQuantity()) + ");";

    std::cout << "Inserting a new book record..." << std::endl;
    execute_sql(sql);
}

/**
 * Inserts or updates a loan record in the Loans table of the database by passing the loan pointer.
 * This function constructs an SQL statement to insert or replace a loan record in the Loans table
 * using the information from the provided Loan object that the pointer points to.
 *
 * @param loanPtr A pointer to the Loan object representing the loan record to be inserted or updated.
 *
 */
void DatabaseManager::insertLoan(Loan* loanPtr){
    // Insert loans details into the Loans table
    std::string loanSql = "INSERT OR REPLACE INTO Loans (ID, ISBN, BorrowingDate, DueDate, Status) VALUES ('" +
                          loanPtr->getBorrower()->getId().str2string() + "', '" +
                          loanPtr->getBorrowedBook()->getIsbn().str2string() + "', '" +
                          loanPtr->getBorrowDate().getDateString() + "', '"+ loanPtr->getDueDate().getDateString() + "', '" + std::to_string(loanPtr->getStatus()) +
                          "');";
    execute_sql(loanSql);

    std::cout << "Loan records inserted..." << std::endl;
}

/**
 * Inserts or updates a user record in the Users table based on the given User pointer.
 * The function inserts a new user record if the user ID does not exist in the Users table,
 * or updates the existing record if the user ID already exists.
 *
 * @param userPtr A pointer to the User object to be inserted or updated.
 *
 */
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
        std::string librarianSql = "INSERT OR REPLACE INTO Users VALUES ('" +
                                   librarianPtr->getId().str2string() + "', '" + librarianPtr->getName().str2string() +
                                   "', '" +
                                   librarianPtr->getPassword().str2string() + "',0);";
        execute_sql(librarianSql);
        std::cout << "Librarian record inserted..." << std::endl;
    } else {
// If neither Member nor Librarian output an error
        std::cerr << "Error: User type not supported for insertion." << std::endl;
        return;
    }
    std::cout << "Inserting a new user record completed." << std::endl;
}

/**
 * Deletes a book record from the Books table based on the given ISBN.
 * @param isbn The ISBN of the book to be deleted.
 * This function deletes the record associated with the given ISBN from the Books table.
 */
void DatabaseManager::deleteBook(const std::string& isbn) {
    std::string sql = "DELETE FROM Books WHERE ISBN = '" + isbn + "';";
    std::cout << "Deleting book with ISBN " << isbn << "..." << std::endl;
    execute_sql(sql);
}

/**
 * Displays all the records in the Books table.
 * This function retrieves and prints all columns (the whole record) of each record in the Books table.
 */
void DatabaseManager::displayBooks() {
    std::string sql = "SELECT * FROM Books;";
    std::cout << "Current state of the Books table:" << std::endl;
    execute_sql(sql, callback);
}

/**
 * Searches for book records in the Books table based on the provided attribute and value.
 * The attribute can be any column name in the Books table, and the search is performed using a LIKE query.
 *
 * @param attribute The attribute to search for (e.g., ISBN, Title, Author, PublicationYear, Genre, Availability, Quantity).
 * @param value The value to search for within the specified attribute.
 */
void DatabaseManager::searchBooks(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Books WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

/**
 * Searches for user records in the Users table based on the provided attribute and value.
 * The attribute can be any column name in the Users table, and the search is performed using a LIKE query.
 *
 * @param attribute The attribute to search for (e.g., ID, Name, Password, Fines).
 * @param value The value to search for within the specified attribute.
 */
void DatabaseManager::searchUsers(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Users WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

/**
 * Searches for loan records in the Loans table based on the provided attribute and value.
 * The attribute can be any column name in the Loans table, and the search is performed using a LIKE query.
 *
 * @param attribute The attribute to search for (e.g., ID, ISBN, BorrowingDate, DueDate, Status).
 * @param value The value to search for within the specified attribute.
 */
void DatabaseManager::searchLoans(const std::string& attribute, const std::string& value) {
    std::string sql = "SELECT * FROM Loans WHERE " + attribute + " LIKE '%" + value + "%';";
    std::cout << "Searching for books with " << attribute << " like " << value << ":" << std::endl;
    execute_sql(sql, callback);
}

/**
 * Decrements the quantity of a book by 1 in the database based on the provided ISBN.
 * If the quantity becomes zero after decrementing, the availability of the book is set to false (0).
 *
 * @param isbn The ISBN of the book to decrement the quantity.
 */
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
        // Setting the availability automatically
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



/**
 * Inserts sample data into the Books, Users, and Loans tables in the database.
 * This function is used for testing purposes to populate the database with sample records.
 * It inserts sample books, users, and loans with there attributes into their respective tables.
 *
 */
void DatabaseManager::insertSampleData() {
    // Inserting sample data into Books
    std::string sqlBooks = "INSERT OR IGNORE INTO Books VALUES ('8624625635653', 'Calculus', 'Stewart', 2012, 'Math', 1, 13),('8624625635673', 'Advanced Calculus', 'Larson', 2010, 'Math', 1, 12),('8622625632663', 'Physics', 'Mo. Ismail', 2016, 'Physics', 1, 11),('8622625632673', 'Quantum Mechanics', 'Dirac', 1988, 'Physics', 1, 10),('8622625632683', 'Classical Mechanics', 'Taylor', 2005, 'Physics', 1, 13),('8624625635683', 'Statistics', 'Freedman', 2009, 'Math', 1, 13),('8624625635693', 'Algebra', 'Artin', 2011, 'Math', 0, 0),('8624625635703', 'Geometry', 'Coxeter', 1969, 'Math', 1, 1),('8624625635713', 'Trigonometry', 'Lial', 1992, 'Math', 1, 1),('8622625632693', 'Thermodynamics', 'Salah', 1985, 'Physics', 1, 69),('8622625632703', 'Electrodynamics', 'Griffiths', 1999, 'Physics', 1, 1),('8622625632713', 'Particle Physics', 'Griffiths', 2008, 'Physics', 0, 0),('8622625632723', 'Astrophysics', 'Carroll', 2007, 'Physics', 1, 2),('8624625635733', 'Differential Equations', 'Arnold', 1973, 'Math', 1, 3),('8624625635743', 'Real Analysis', 'Rudin', 1976, 'Math', 1, 7),('8624625635753', 'Complex Analysis', 'Ahlfors', 1966, 'Math', 1, 16),('8624625635763', 'Number Theory', 'Hardy', 1938, 'Math', 1, 31),('8624625635773', 'Topology', 'Munkres', 1975, 'Math', 1, 1),('8622625632733', 'Fluid Mechanics', 'Batchelor', 1967, 'Physics', 1, 2),('8622625632743', 'Relativity', 'Hartle', 2003, 'Physics', 1, 8),('8622625632753', 'Quantum Field Theory', 'Peskin', 1995, 'Physics', 1, 1),('8622625632763', 'Solid State Physics', 'Ashcroft', 1976, 'Physics', 1, 11),('8622625632773', 'Optics', 'Hecht', 1987, 'Physics', 1, 22),('8624625635783', 'Probability', 'Ross', 2010, 'Math', 1, 24),('8624625635793', 'Biostatistics', 'Daniel', 1999, 'Math', 1, 12),('8624625635803', 'Discrete Mathematics', 'Rosen', 2012, 'Math', 1, 4),('8624625635813', 'Combinatorics', 'Bona', 2011, 'Math', 1, 6),('8624625635823', 'Logic and Proofs', 'Velleman', 2006, 'Math', 1, 15),('8622625632783', 'Nuclear Physics', 'Krane', 1988, 'Physics', 1, 10),('8622625632793', 'Molecular Physics', 'McQuarrie', 2008, 'Physics', 1, 4),('8622625632803', 'Cosmology', 'Weinberg', 2008, 'Physics', 1, 16),('8622625632813', 'Signal Processing', 'Oppenheim', 1999, 'Electronics', 1, 16),('8622625632823', 'Microelectronics', 'Sedra', 2004, 'Electronics', 1, 17),('8622625632833', 'VLSI Design', 'West', 2012, 'Electronics', 1, 12),('8622625632843', 'Antenna Theory', 'Balanis', 2016, 'Electronics', 1, 15),('8622625632853', 'Digital Communication', 'Proakis', 2007, 'Electronics', 1, 14),('8622625632863', 'Control Systems', 'Ogata', 2010, 'Electronics', 1, 6),('8622625632873', 'Robotics', 'Craig', 2005, 'Engineering', 1, 21),('8622625632883', 'Thermal Physics', 'Schroeder', 2000, 'Physics', 1, 14),('8622625632893', 'Organic Chemistry', 'Carey', 2013, 'Chemistry', 1, 13),('8622625632903', 'Inorganic Chemistry', 'Housecroft', 2010, 'Chemistry', 1, 16),('8622625632913', 'Biochemistry', 'Voet', 2016, 'Chemistry', 1, 21),('8622625632923', 'Analytical Chemistry', 'Skoog', 2014, 'Chemistry', 1, 19),('8622625632933', 'Environmental Science', 'Keller', 2018, 'Biology', 1, 14),('8622625632943', 'Molecular Biology', 'Weaver', 2012, 'Biology', 1, 18),('8622625632953', 'Cell Biology', 'Pollard', 2017, 'Biology', 1, 19),('8622625632963', 'Genetics', 'Pierce', 2014, 'Biology', 1, 12),('8622625632973', 'Evolutionary Biology', 'Freeman', 2011, 'Biology', 1, 13),('8622625632983', 'Neuroscience', 'Bear', 2015, 'Biology', 1, 17),('8622625632993', 'Ecology', 'Smith', 2014, 'Biology', 1, 14),('8622625633003', 'Anatomy and Physiology', 'Marieb', 2019, 'Biology', 1, 1),('8622625633013', 'Pathophysiology', 'Copstead', 2013, 'Medicine', 1, 11),('8622625633023', 'Pharmacology', 'Katzung', 2018, 'Medicine', 1, 11),('8622625633033', 'Public Health', 'Turnock', 2016, 'Medicine', 1, 11),('8622625633043', 'Epidemiology', 'Gordis', 2014, 'Medicine', 1, 12);";

    // Inserting sample data into Users
    std::string sqlUsers = "INSERT OR IGNORE INTO Users VALUES "
                           "('stu-100', 'AboGendya', 'password123',0),"
                           "('fac-101', 'Salah', 'Donuts',0),"
                           "('stu-101285', 'Ziad', '242004',0),"
                           "('sta-103', 'Hussein', 'Rehab',0),"
                           "('sta-105', 'Tarek', 'Somaya',0),"
                           "('lib-103', 'Fouad Hashesh', 'DEVVV',0),"
                           "('lib-101', 'Yasser', 'Legend',0),"
                           "('lib-102', 'Mohamed', 'Goat',0);"
    ;

    std::cout << "Inserting sample data..." << std::endl;
    execute_sql(sqlBooks);
    execute_sql(sqlUsers);
}

/**
 * Imports book records from the Books table in the database and populates a vector with Book objects.
 * This function executes an SQL query to retrieve book data from the Books table,
 * constructs Book objects using the retrieved data, and adds them to the provided vector.
 *
 * @param book_list A reference to a vector of Book pointers where the imported Book objects will be stored.
 *
 */
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


/**
 * Callback function used by `sqlite3_exec` to handle the results of a query when importing user data from the database.
 * This function interprets each row of the results as a User object. Depending on the user ID prefix, it creates specific
 * user types such as Staff, Faculty, Student, or Librarian. It dynamically casts users to a Member type to set overdue fines
 * where applicable. Each created user object is added to a vector passed through the `data` parameter.
 *
 * @param data Pointer to a vector<User*> where the user objects will be stored.
 * @param argc The number of columns in the row.
 * @param argv Array of strings representing each field in the row.
 * @param azColName Array of strings representing the names of each column in the result.
 * @return Returns 0 to continue processing rows, or a non-zero value to abort.
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

/**
 * Imports user records from the Users table in the database and populates a vector with User objects.
 * This function executes an SQL query to retrieve user data from the Users table,
 * constructs User objects using the retrieved data, and pass them to getMemberPtr and getBookPtr to get
 * the corresponding pointers for each one then adds them to the provided vector.
 * It also sets overdue fines for Member-type users based on the retrieved data.
 *
 * @param user_list A reference to a vector of User pointers where the imported User objects will be stored.
 *                  This vector is cleared before populating it with the newly imported User objects.
 */
void DatabaseManager::importUsers(vector<User*>& user_list) {
    // Clear existing users in the list
    user_list.clear();

    std::string sql = "SELECT ID, Name, Password, Fines FROM Users;";
    execute_sql(sql, userCallback, &user_list);

    // After fetching all users, get their loaned books
    for (User* user : user_list) {
        Member* member = dynamic_cast<Member*>(user);
        if (member) {
            vector<Book*> loanedBooks = getLoanedBooksByUser(member->getId().str2string());
            member->setCheckedOutBooks(loanedBooks);

        }
    }
}


/**
* Imports loan records from the Loans table in the database and populates a vector with Loan objects.
* This function executes an SQL query to retrieve loan data from the Loans table,
* constructs Loan objects using the retrieved data, and pass them to getMemberPtr and getBookPtr to get
* the corresponding pointers for each one then adds them to the provided vector.
*
* @param loan_list A reference to a vector of Loan pointers where the imported Loan objects will be stored.
*                  This vector is cleared before populating it with the newly imported Loan objects.
*/
void DatabaseManager::importLoans(vector<Loan*> &loan_list){
    loan_list.clear();

    std::string sql = "SELECT ID, ISBN, BorrowingDate, DueDate, Status FROM Loans;";
    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Loan*>* loan_list = static_cast<vector<Loan*>*>(data);
        if (argc == 5) {
            std::string id = argv[0];
            std::string isbn = argv[1];
            // Check if argv[2] and argv[3] is not empty (not null pointer and not an empty string), if empty assign "0-0-0" to borrowingDate and/or dueDate
            std::string borrowingDate = (argv[2] && argv[2][0] != '\0') ? argv[2] : "0-0-0";
            std::string dueDate = (argv[3] && argv[3][0] != '\0') ? argv[3] : "0-0-0";
            bool status = std::stoi(argv[4]) != 0;

            Loan *loan = new Loan(getMemberPtr(id, ex_library_users), getBookPtr(isbn, ex_library_books));
            loan->set_borrowingDate(borrowingDate);
            loan->set_dueDate(dueDate);
            loan->set_status(status);
            loan_list->push_back(loan);
        }
        return 0;
    };

    std::cout << "Importing Loans..." << std::endl;
    execute_sql(sql, callback, &loan_list);
}

/**
 * Deletes all records from the Books, Users, and Loans tables in the database.
 * This function is potentially destructive as it clears all data within these tables,
 * making it suitable for scenarios like resetting the database to a clean state before
 * running tests or initializing the system afresh.
 *
 * It constructs and executes SQL commands to delete all entries from each specified table.
 * This method does not return any value, but outputs to the console to indicate the completion
 * of the table clearing process.
 */
void DatabaseManager::boomboom() {
    // SQL command that deletes all rows from Books, Users, and Loans tables
    std::string sql ="DELETE FROM Books;DELETE FROM Users;DELETE FROM Loans;";
    std::cout << "Clearing all Tables..." << std::endl;
    execute_sql(sql);
}


/**
 * Retrieves all loaned books for a given user ID and returns them as a vector of Book pointers.
 * This function executes a SQL query to join the Books and Loans tables based on the ISBN
 * and filters the results by the user ID and loan status (active loans only). It then populates
 * a vector with pointers to Book objects corresponding to the loaned books.
 *
 * The function assumes that the Book objects already exist in memory, typically in a global or externally managed vector,
 * and this function will only fetch pointers to those existing objects based on the ISBNs retrieved from the database.
 *
 * @param userId The user ID string used to identify the user whose loaned books are being retrieved.
 * @return A vector containing pointers to Book objects that the specified user has currently loaned.
 */
vector<Book*> DatabaseManager::getLoanedBooksByUser(const std::string& userId) {
    vector<Book*> loanedBooks;

// SQL query that joins Books and Loans tables to find books currently loaned by the user
    std::string sql = "SELECT b.ISBN, b.Title, b.Author, b.PublicationYear, b.Genre, b.Availability, b.Quantity "
                      "FROM Books b "
                      "JOIN Loans l ON b.ISBN = l.ISBN "
                      "WHERE l.ID = '" + userId + "' AND l.Status = 1;";

    auto callback = [](void* data, int argc, char** argv, char** azColName) -> int {
        vector<Book*>* loanedBooks = static_cast<vector<Book*>*>(data);
        if (argc == 7) {

            // Create a new Book object and add it to the vector (pointer fetched from existing list)
            loanedBooks->push_back(getBookPtr(argv[0],ex_library_books));
        }
        return 0;
    };

    execute_sql(sql, callback, &loanedBooks);

    return loanedBooks;
}

/**
 * Retrieves a pointer to a Book object from a list of books using the book's ISBN.
 * This function iterates over a vector of Book pointers and returns the pointer
 * to the book whose ISBN matches the provided string identifier.
 *
 * @param isbn The ISBN string used to identify the book.
 * @param book_list The vector containing pointers to Book objects.
 * @return A pointer to the Book object if found, or nullptr if no match is found.
 */
Member* getMemberPtr(str id, vector<User*> &user_list){
    for(auto &it : user_list){
        if(it->getId() == id){
            return dynamic_cast<Member*>(it);
        }
    }
    return nullptr;
}

/**
 * Retrieves a pointer to a Member object from a list of users using the user's ID.
 * This function iterates over a vector of User pointers and returns the pointer
 * to the Member derived from the User whose ID matches the provided string identifier.
 * This is particularly useful when needing to manipulate or access Member-specific data.
 *
 * @param id The user ID string used to identify the member.
 * @param user_list The vector containing pointers to User objects (ex_library_books).
 * @return A pointer to the Member object if found and the User is a Member, or nullptr if no match is found or the User is not a Member.
 */
Book* getBookPtr(str isbn, vector<Book*> &book_list){
    for(auto &it : book_list){
        if(it->getIsbn() == isbn){
            return it;
        }
    }
    return nullptr;
}