#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Structure to represent a book
struct Book {
    string title;
    string author;
    int year;
    string genre;
};

// Class to represent the Library
class Library {
private:
    vector<Book> books; // Vector to store all books in the library
    const string filename = "library.txt"; // File to store books data

    // Function to load books from file
    void loadBooks() {
        ifstream file(filename);
        if (!file) { // Check if the file opened successfully
            cerr << "Error opening file for reading: " << filename << endl;
            return;
        }
        Book book;
        while (getline(file, book.title)) {
            getline(file, book.author);
            file >> book.year;
            file.ignore(); // To ignore the newline after the year
            getline(file, book.genre);
            books.push_back(book);
        }
        file.close();
    }

    // Function to save books to file
    void saveBooks() {
        ofstream file(filename);
        if (!file) { // Check if the file opened successfully
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }
        for (const auto& book : books) {
            file << book.title << endl;
            file << book.author << endl;
            file << book.year << endl;
            file << book.genre << endl;
        }
        file.close();
    }

public:
    // Constructor to load books from file when the program starts
    Library() {
        loadBooks();
        addDefaultBooks(); // Add some predefined books to the library
    }

    // Destructor to save books to file when the program exits
    ~Library() {
        saveBooks();
    }

    // Function to add a book to the library
    void addBook() {
        Book newBook;
        cout << "Enter book title: ";
        cin.ignore();  // To ignore any leftover newline characters in the input buffer
        getline(cin, newBook.title);
        
        cout << "Enter author name: ";
        getline(cin, newBook.author);
        
        cout << "Enter publication year: ";
        cin >> newBook.year;
        
        cout << "Enter genre: ";
        cin.ignore();  // To ignore any leftover newline characters in the input buffer
        getline(cin, newBook.genre);
        
        // Add the new book to the books vector
        books.push_back(newBook);
        cout << "Book added successfully!" << endl;
    }

    // Function to view all books in the library
    void viewBooks() {
        if (books.empty()) {
            cout << "No books in the library!" << endl;
            return;
        }

        cout << "\nAll books in the library:\n";
        cout << "---------------------------------\n";
        for (int i = 0; i < books.size(); i++) {
            cout << "Title: " << books[i].title << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Year: " << books[i].year << endl;
            cout << "Genre: " << books[i].genre << endl;
            cout << "---------------------------------\n";
        }
    }

    // Function to search for a book by title
    void searchBook() {
        string searchTitle;
        cout << "Enter book title to search: ";
        cin.ignore();  // To ignore any leftover newline characters in the input buffer
        getline(cin, searchTitle);

        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == searchTitle) {
                cout << "\nBook found:\n";
                cout << "Title: " << books[i].title << endl;
                cout << "Author: " << books[i].author << endl;
                cout << "Year: " << books[i].year << endl;
                cout << "Genre: " << books[i].genre << endl;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Book not found!" << endl;
        }
    }

    // Function to delete a book by title
    void deleteBook() {
        string deleteTitle;
        cout << "Enter book title to delete: ";
        cin.ignore();  // To ignore any leftover newline characters in the input buffer
        getline(cin, deleteTitle);

        bool found = false;
        for (int i = 0; i < books.size(); i++) {
            if (books[i].title == deleteTitle) {
                books.erase(books.begin() + i); // Erase the book from the vector
                cout << "Book deleted successfully!" << endl;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Book not found!" << endl;
        }
    }

    // Function to add default books (e.g., Computer Science, Inspirational, Grammar)
    void addDefaultBooks() {
        // Predefined books in different categories
        books.push_back({"Introduction to Algorithms", "Thomas H. Cormen", 2009, "Computer Science"});
        books.push_back({"Clean Code", "Robert C. Martin", 2008, "Computer Science"});
        books.push_back({"The Pragmatic Programmer", "Andrew Hunt & David Thomas", 1999, "Computer Science"});
        
        books.push_back({"The Power of Positive Thinking", "Norman Vincent Peale", 1952, "Inspirational"});
        books.push_back({"You Are a Badass", "Jen Sincero", 2013, "Inspirational"});
        books.push_back({"Atomic Habits", "James Clear", 2018, "Inspirational"});
        
        books.push_back({"English Grammar in Use", "Raymond Murphy", 1990, "English Grammar"});
        books.push_back({"Practical English Usage", "Michael Swan", 2005, "English Grammar"});
        books.push_back({"Advanced Grammar in Use", "Martin Hewings", 2009, "English Grammar"});

        cout << "\nDefault books added to the library.\n";
    }

    // Function to display the menu
    void displayMenu() {
        cout << "\nLibrary Management System\n";
        cout << "1. Add a book\n";
        cout << "2. View all books\n";
        cout << "3. Search a book by title\n";
        cout << "4. Delete a book by title\n";
        cout << "5. Exit\n";
    }
};

// Main function
int main() {
    Library library;
    int choice;

    do {
        library.displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;
            case 2:
                library.viewBooks();
                break;
            case 3:
                library.searchBook();
                break;
            case 4:
                library.deleteBook();
                break;
            case 5:
                cout << "Exiting the system...\n";
                break;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

