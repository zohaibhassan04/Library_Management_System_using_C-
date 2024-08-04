#include <iostream>
#include <string>

using namespace std;

struct Book {
    int isbn;
    string title;
    string author;
};

struct Node {
    Book book;
    Node* left;
    Node* right;
};

Node* createNode(const Book& book) {
    Node* newNode = new Node();
    newNode->book = book;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, const Book& book) {
    if (root == NULL) {
        return createNode(book);
    }
    if (book.isbn < root->book.isbn) {
        root->left = insert(root->left, book);
    } else if (book.isbn > root->book.isbn) {
        root->right = insert(root->right, book);
    }
    return root;
}

Node* search(Node* root, int isbn) {
    if (root == NULL || root->book.isbn == isbn) {
        return root;
    }
    if (isbn < root->book.isbn) {
        return search(root->left, isbn);
    }
    return search(root->right, isbn);
}

Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

Node* deleteNode(Node* root, int isbn) {
    if (root == NULL) {
        return root;
    }
    if (isbn < root->book.isbn) {
        root->left = deleteNode(root->left, isbn);
    } else if (isbn > root->book.isbn) {
        root->right = deleteNode(root->right, isbn);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = findMin(root->right);
        root->book = temp->book;
        root->right = deleteNode(root->right, temp->book.isbn);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << "ISBN: " << root->book.isbn << ", Title: " << root->book.title << ", Author: " << root->book.author << endl;
        inorder(root->right);
    }
}

void displayMenu() {
    cout << "\nLibrary Management System\n";
    cout << "1. Add Book\n";
    cout << "2. Search Book\n";
    cout << "3. Delete Book\n";
    cout << "4. Display All Books\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void deleteTree(Node* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = NULL;
    int choice, isbn;
    string title, author;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ISBN: ";
                cin >> isbn;
                cin.ignore();
                cout << "Enter Book Title: ";
                getline(cin, title);
                cout << "Enter Book Author: ";
                getline(cin, author);
                root = insert(root, {isbn, title, author});
                cout << "Book added successfully.\n";
                break;
            case 2:
                cout << "Enter ISBN to search: ";
                cin >> isbn;
                {
                    Node* found = search(root, isbn);
                    if (found) {
                        cout << "Book found: ISBN: " << found->book.isbn << ", Title: " << found->book.title << ", Author: " << found->book.author << endl;
                    } else {
                        cout << "Book not found.\n";
                    }
                }
                break;
            case 3:
                cout << "Enter ISBN to delete: ";
                cin >> isbn;
                if (search(root, isbn) != NULL) {
                    root = deleteNode(root, isbn);
                    cout << "Book deleted successfully.\n";
                } else {
                    cout << "Book not found.\n";
                }
                break;
            case 4:
                cout << "Library books in order:\n";
                inorder(root);
                break;
            case 5:
                cout << "Exiting the system. Goodbye!\n";
                deleteTree(root);
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

