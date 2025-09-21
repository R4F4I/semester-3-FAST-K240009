/*



* Name:         Rafay Siddiqui
* roll number:  24k-0009
* section:      BAI-3A


*/

#include <iostream>
#include <vector>

using namespace std;


class Book {
public:
    // Default constructor
    Book() {
        std::cout << "Default constructor called." << std::endl;
    }

    // Parameterized constructor
    Book(const std::string& title, const std::string& author) : title_(title), author_(author) {
        std::cout << "Parameterized constructor called for '" << title << "'." << std::endl;
    }

    // Copy Constructor
    // This is called when a new object is created from an existing one.
    Book(const Book& other) : title_(other.title_), author_(other.author_) {
        std::cout << "Copy constructor called to create a copy of '" << other.title_ << "'." << std::endl;
    }

    // Destructor
    // This is called when a Book object goes out of scope.
    ~Book() {
        std::cout << "Destructor called for '" << title_ << "'." << std::endl;
    }

    // Method to display book details
    void display() const {
        std::cout << "Title: " << title_ << ", Author: " << author_ << std::endl;
    }

private:
    std::string title_;
    std::string author_;
};

// Recursive function to display a list of books
// It takes a constant reference to a vector of books and the current index.
void displayBooksRecursively(const std::vector<Book>& books, int index) {
    // Base Case: If the index is out of bounds, we have reached the end of the list.
    if (index >= books.size()) {
        return;
    }

    // Display the current book's details.
    books[index].display();

    // Recursive Step: Call the function again for the next book in the vector.
    displayBooksRecursively(books, index + 1);
}


int main(){

     // Create a vector to store our book objects.
    std::vector<Book> bookstore_catalog;

    // Create and add some books to the catalog.
    bookstore_catalog.push_back(Book("The Hitchhiker's Guide to the Galaxy", "Douglas Adams"));
    bookstore_catalog.push_back(Book("Dune", "Frank Herbert"));
    bookstore_catalog.push_back(Book("1984", "George Orwell"));

    // Demonstrate the copy constructor by creating a new book from an existing one.
    // This will trigger the copy constructor.
    Book new_book = bookstore_catalog[1];
    std::cout << "\nDisplaying a single book created with the copy constructor:\n";
    new_book.display();

    std::cout << "\nDisplaying all books in the catalog recursively:\n";
    // Call the recursive function to display all the books.
    displayBooksRecursively(bookstore_catalog, 0);

    std::cout << "\nProgram finished. Destructors will be called as objects go out of scope.\n";
    return 0;



    return 0;
}