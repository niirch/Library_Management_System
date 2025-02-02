#include <bits/stdc++.h>
using namespace std;

class Book {
    int bookID;
    string title;
    string author;
    bool issued;

public:
    Book(int id = 0, string t = "", string a = "", bool i = false)
        : bookID(id), title(t), author(a), issued(i) {}

    int getBookID() const { return bookID; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isIssued() const { return issued; }

    void issueBook() { issued = true; }
    void returnBook() { issued = false; }

    void saveToFile(ofstream &out) const {
        out << bookID << "," << title << "," << author << "," << issued << endl;
    }

    static Book loadFromFile(string line) {
        stringstream ss(line);
        int id;
        string t, a;
        bool i;
        char comma;
        ss >> id >> comma;
        getline(ss, t, ',');
        getline(ss, a, ',');
        ss >> i;
        return Book(id, t, a, i);
    }
};

class Library {
    vector<Book> books;
    const string fileName = "library.txt";

public:
    Library() { loadBooksFromFile(); }

    void addBook(int id, string title, string author) {
        for (const auto &book : books) {
            if (book.getBookID() == id) {
                cout << "Error: Book ID already exists!\n";
                return;
            }
        }

        books.push_back(Book(id, title, author, false));
        saveBooksToFile();
        cout << "Book added successfully!\n";
    }

    void showBooks() const {
        if (books.empty()) {
            cout << "No books available in the library.\n";
            return;
        }

        cout << "\n<<<<< Library Books >>>>>\n";
        for (const auto &book : books) {
            cout << "ID: " << book.getBookID() << " | Title: " << book.getTitle()
                 << " | Author: " << book.getAuthor()
                 << " | Status: " << (book.isIssued() ? "Issued" : "Available") << endl;
        }
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (auto &book : books) {
            if (book.getBookID() == id) {
                if (book.isIssued()) {
                    cout << "Error: This book is already issued!\n";
                } else {
                    book.issueBook();
                    saveBooksToFile();
                    cout << "Book issued successfully!\n";
                }
                return;
            }
        }
        cout << "Error: Book not found!\n";
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.getBookID() == id) {
                if (!book.isIssued()) {
                    cout << "Error: This book is already available!\n";
                } else {
                    book.returnBook();
                    saveBooksToFile();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Error: Book not found!\n";
    }

    void modifyBook() {
        int id;
        cout << "Enter Book ID to modify: ";
        cin >> id;

        for (auto &book : books) {
            if (book.getBookID() == id) {
                string newTitle, newAuthor;
                cout << "Enter new title: ";
                cin.ignore();
                getline(cin, newTitle);
                cout << "Enter new author: ";
                getline(cin, newAuthor);

                book = Book(id, newTitle, newAuthor, book.isIssued());
                saveBooksToFile();
                cout << "Book updated successfully!\n";
                return;
            }
        }
        cout << "Error: Book not found!\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        for (size_t i = 0; i < books.size(); ++i) {
            if (books[i].getBookID() == id) {
                books.erase(books.begin() + i);
                saveBooksToFile();
                cout << "Book deleted successfully!\n";
                return;
            }
        }
        cout << "Error: Book not found!\n";
    }

private:
    void loadBooksFromFile() {
        ifstream file(fileName);
        if (!file.is_open()) {
            cout << "Starting with an empty library. No data found.\n";
            return;
        }

        string line;
        while (getline(file, line)) {
            books.push_back(Book::loadFromFile(line));
        }
        file.close();
    }

    void saveBooksToFile() {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Error: Unable to save books to file!\n";
            return;
        }

        for (const auto &book : books) {
            book.saveToFile(file);
        }
        file.close();
    }
};

int main() {
    Library library;
    char choice;

    do {
        cout << "\n<<<<< Library Management System >>>>>\n";
        cout << "1. Show Books\n";
        cout << "2. Add New Book\n";
        cout << "3. Issue Book\n";
        cout << "4. Return Book\n";
        cout << "5. Modify Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "Select your option (1-7): ";
        cin >> choice;

        switch (choice) {
        case '1':
            library.showBooks();
            break;
        case '2': {
            int id;
            string title, author;
            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Enter Title: ";
            getline(cin, title);
            cout << "Enter Author: ";
            getline(cin, author);
            library.addBook(id, title, author);
            break;
        }
        case '3':
            library.issueBook();
            break;
        case '4':
            library.returnBook();
            break;
        case '5':
            library.modifyBook();
            break;
        case '6':
            library.deleteBook();
            break;
        case '7':
            cout << "Exiting the system. Thank you!\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != '7');

    return 0;
}
