#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include "library.h"
using namespace std;


void saveIssueRecords(vector<IssueRecord>& issueRecords)
{
    ofstream file("issueRecords.txt");

    for (int i = 0; i < issueRecords.size(); i++)
    {
        file << issueRecords[i].studentID << "|"
             << issueRecords[i].bookID << endl;
    }

    file.close();
}
void loadIssueRecords(vector<IssueRecord>& issueRecords)
{
    ifstream file("issueRecords.txt");

    if (!file)
    {
        return;
    }

    issueRecords.clear();

    int studentID, bookID;
    char separator;

    while (file >> studentID >> separator >> bookID)
    {
        if (separator == '|')
        {
            issueRecords.push_back({studentID, bookID});
        }
    }

    file.close();
}
struct BSTNode
{
    int id;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int value)
    {
        id = value;
        left = NULL;
        right = NULL;
    }
};
BSTNode* insertBST(BSTNode* root, int id)
{
    if (root == NULL)
    {
        return new BSTNode(id);
    }

    if (id < root->id)
    {
        root->left = insertBST(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = insertBST(root->right, id);
    }

    return root;
}
bool searchBST(BSTNode* root, int id)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->id == id)
    {
        return true;
    }

    if (id < root->id)
    {
        return searchBST(root->left, id);
    }

    return searchBST(root->right, id);
}
void inorder(BSTNode* root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);

    cout << root->id << " ";

    inorder(root->right);
}
void merge(vector<Book>& books, int left, int mid, int right)
{
    vector<Book> temp;

    int i = left;
    int j = mid + 1;

    while (i <= mid && j <= right)
    {
        if (books[i].id <= books[j].id)
        {
            temp.push_back(books[i]);
            i++;
        }
        else
        {
            temp.push_back(books[j]);
            j++;
        }
    }

    while (i <= mid)
    {
        temp.push_back(books[i]);
        i++;
    }

    while (j <= right)
    {
        temp.push_back(books[j]);
        j++;
    }

    for (int k = 0; k < temp.size(); k++)
    {
        books[left + k] = temp[k];
    }
}
void mergeSort(vector<Book>& books, int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSort(books, left, mid);

    mergeSort(books, mid + 1, right);

    merge(books, left, mid, right);
}
void saveBooks(vector<Book>& books)
{
    ofstream file("books.txt");

    for (int i = 0; i < books.size(); i++)
    {
        file << books[i].id << "|"
             << books[i].name << "|"
             << books[i].author << "|"
             << books[i].quantity << endl;
    }

    file.close();
}
void loadBooks(vector<Book>& books)
{
    ifstream file("books.txt");

    Book b;
    string line;

    while (getline(file, line))
    {
        stringstream ss(line);

        string id, name, author, quantity;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, author, '|');
        getline(ss, quantity, '|');

        b.id = stoi(id);
        b.name = name;
        b.author = author;
        b.quantity = stoi(quantity);

        books.push_back(b);
    }

    file.close();
}

BSTNode* findMin(BSTNode* root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}


BSTNode* deleteBST(BSTNode* root, int id)
{
    if (root == NULL)
    {
        return root;
    }

    if (id < root->id)
    {
        root->left = deleteBST(root->left, id);
    }
    else if (id > root->id)
    {
        root->right = deleteBST(root->right, id);
    }
    else
    {
        
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }


        else if (root->left == NULL)
        {
            BSTNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == NULL)
        {
            BSTNode* temp = root->left;
            delete root;
            return temp;
        }

        BSTNode* temp = findMin(root->right);

        root->id = temp->id;

        root->right = deleteBST(root->right, temp->id);
    }

    return root;
}


void addBook(vector<Book>& books,
             unordered_map<int, int>& bookHash,
             BSTNode*& root)
            
{
    Book b;

    cout << "\nEnter Book ID: ";
    cin >> b.id;

    if (bookHash.find(b.id) != bookHash.end())
    {
        cout << "Book ID already exists!\n";
        return;
    }

    cin.ignore();

    cout << "Enter Book Name: ";
    getline(cin, b.name);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    cout << "Enter Quantity: ";
    cin >> b.quantity;

    books.push_back(b);
    saveBooks(books);

    // Store Book ID and its index
    bookHash[b.id] = books.size() - 1;
    root = insertBST(root, b.id);

    cout << "\nBook Added Successfully!\n";
}

// Function to display books
void displayBooks(vector<Book>& books)
{
    cout << "\n------ LIBRARY BOOKS ------\n";

    for (int i = 0; i < books.size(); i++)
    {
        cout << "\nBook ID: " << books[i].id;
        cout << "\nBook Name: " << books[i].name;
        cout << "\nAuthor: " << books[i].author;
        cout << "\nQuantity: " << books[i].quantity;
        cout << "Available Books: "
     << books[i].quantity - books[i].issued << endl;

cout << "Issued Books: "
     << books[i].issued << endl;
        cout << "\n--------------------------\n";
    }
}

// Function to search a book
void searchBook(vector<Book>& books)
{
    int searchID;

    cout << "\nEnter Book ID to search: ";
    cin >> searchID;

    bool found = false;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].id == searchID)
        {
            cout << "\n===== BOOK FOUND =====\n";

            cout << "Book ID: " << books[i].id << endl;
            cout << "Book Name: " << books[i].name << endl;
            cout << "Author: " << books[i].author << endl;
            cout << "Quantity: " << books[i].quantity << endl;

            found = true;
            break;
        }
    }

    if (found == false)
    {
        cout << "\nBook Not Found!\n";
    }
}
void searchBookHash(vector<Book>& books,
                    unordered_map<int, int>& bookHash)
{
    int id;

    cout << "\nEnter Book ID: ";
    cin >> id;

    if (bookHash.find(id) != bookHash.end())
    {
        int index = bookHash[id];

        cout << "\n===== BOOK FOUND =====\n";

        cout << "Book ID: " << books[index].id << endl;
        cout << "Book Name: " << books[index].name << endl;
        cout << "Author: " << books[index].author << endl;
        cout << "Quantity: " << books[index].quantity << endl;
    }
    else
    {
        cout << "\nBook Not Found!\n";
    }
}
void issueBook(vector<Book>& books, vector<Student>& students, vector<IssueRecord>& issueRecords)
{
    int studentID, bookID;
    bool studentFound = false;

    cout << "\nEnter Student ID: ";
    cin >> studentID;

    // Check Student
    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == studentID)
        {
            studentFound = true;
            break;
        }
    }

    if (!studentFound)
    {
        cout << "\nStudent Not Found! Please Register First.\n";
        return;
    }

    cout << "Enter Book ID to issue: ";
    cin >> bookID;

    // Check Book
    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].id == bookID)
        {
            if (books[i].quantity > books[i].issued)
            {
                books[i].issued++;
                issueRecords.push_back({studentID, bookID});
                saveBooks(books);
                saveIssueRecords(issueRecords);

                cout << "\nBook Issued Successfully!\n";
                cout << "Book Name: " << books[i].name << endl;
                cout << "Available Books: "
                     << books[i].quantity - books[i].issued << endl;
            }
            else
            {
                cout << "\nNo Books Available!\n";
            }

            return;
        }
    }

    cout << "\nBook Not Found!\n";
}
void returnBook(vector<Book>& books,
                vector<Student>& students,
                vector<IssueRecord>& issueRecords)
{
    int studentID, bookID;

    cout << "\nEnter Student ID: ";
    cin >> studentID;

    cout << "Enter Book ID to return: ";
    cin >> bookID;

    // Check issue record
    for (int i = 0; i < issueRecords.size(); i++)
    {
        if (issueRecords[i].studentID == studentID &&
            issueRecords[i].bookID == bookID)
        {
            for (int j = 0; j < books.size(); j++)
            {
                if (books[j].id == bookID && books[j].issued > 0)
                {
                    books[j].issued--;

                    issueRecords.erase(issueRecords.begin() + i);
                    saveIssueRecords(issueRecords);

                    saveBooks(books);

                    cout << "\nBook Returned Successfully!\n";
                    cout << "Book Name: " << books[j].name << endl;
                    cout << "Available Books: "
                         << books[j].quantity - books[j].issued << endl;

                    return;
                }
            }
        }
    }

    cout << "\nNo Matching Issue Record Found!\n";
}
void saveStudents(vector<Student>& students);
void addStudent(vector<Student>& students)
{
    Student s;

    cout << "\nEnter Student ID: ";
    cin >> s.id;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == s.id)
        {
            cout << "Student ID already exists!\n";
            return;
        }
    }

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, s.name);

    cout << "Enter Department: ";
    getline(cin, s.department);

    students.push_back(s);
    saveStudents(students);

    cout << "\nStudent Added Successfully!\n";
}
void displayStudents(vector<Student>& students)
{
    if (students.empty())
    {
        cout << "\nNo Students Found!\n";
        return;
    }

    cout << "\n===== STUDENT RECORDS =====\n";

    for (int i = 0; i < students.size(); i++)
    {
        cout << "\nStudent ID: " << students[i].id << endl;
        cout << "Student Name: " << students[i].name << endl;
        cout << "Department: " << students[i].department << endl;

        cout << "-------------------------\n";
    }
}
void searchStudent(vector<Student>& students)
{
    int id;

    cout << "\nEnter Student ID to search: ";
    cin >> id;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == id)
        {
            cout << "\n===== STUDENT FOUND =====\n";

            cout << "Student ID: " << students[i].id << endl;
            cout << "Student Name: " << students[i].name << endl;
            cout << "Department: " << students[i].department << endl;

            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}
void deleteStudent(vector<Student>& students)
{
    int id;

    cout << "Enter Student ID to Delete: ";
    cin >> id;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == id)
        {
            students.erase(students.begin() + i);

            saveStudents(students);

            cout << "\nStudent Deleted Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}
void displayIssuedBooks(vector<IssueRecord>& issueRecords)
{
    if (issueRecords.empty())
    {
        cout << "\nNo Books Issued!\n";
        return;
    }

    cout << "\n===== ISSUED BOOK RECORDS =====\n";

    for (int i = 0; i < issueRecords.size(); i++)
    {
        cout << "Student ID: "
             << issueRecords[i].studentID << endl;

        cout << "Book ID: "
             << issueRecords[i].bookID << endl;

        cout << "----------------------\n";
    }
}
void displayDashboard(vector<Book>& books,
                      vector<Student>& students)
{
    int totalBooks = 0;
    int issuedBooks = 0;

    for (int i = 0; i < books.size(); i++)
    {
        totalBooks += books[i].quantity;
        issuedBooks += books[i].issued;
    }

    cout << "\n========== LIBRARY DASHBOARD ==========\n";

    cout << "Total Book Copies : " << totalBooks << endl;
    cout << "Total Students    : " << students.size() << endl;
    cout << "Issued Books      : " << issuedBooks << endl;
    cout << "Available Books   : "
         << totalBooks - issuedBooks << endl;

    cout << "=======================================\n";
}
void updateStudent(vector<Student>& students)
{
    int id;
    cout << "Enter Student ID to Update: ";
    cin >> id;

    for (int i = 0; i < students.size(); i++)
    {
        if (students[i].id == id)
        {
            cin.ignore();

            cout << "Enter New Name: ";
            getline(cin, students[i].name);

            cout << "Enter New Department: ";
            getline(cin, students[i].department);

            saveStudents(students);

            cout << "\nStudent Updated Successfully!\n";
            return;
        }
    }

    cout << "\nStudent Not Found!\n";
}
void saveStudents(vector<Student>& students) {
    ofstream file("students.txt");

    for (int i = 0; i < students.size(); i++) {
        file << students[i].id << "|"
             << students[i].name << "|"
             << students[i].department << endl;
    }

    file.close();
}
void loadStudents(vector<Student>& students) {
    ifstream file("students.txt");

    if (!file) {
        return;
    }

    students.clear();

    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, department;

        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, department);

        Student s;
        s.id = stoi(id);
        s.name = name;
        s.department = department;

        students.push_back(s);
    }

    file.close();
}
int main()
{
    vector<Book> books;
    unordered_map<int, int> bookHash; // id -> index
    BSTNode* root = NULL;
    vector<Student> students;
    vector<IssueRecord> issueRecords;
    loadIssueRecords(issueRecords);
    loadStudents(students);

    loadBooks(books);

// Rebuild Hash Table and BST
for (int i = 0; i < books.size(); i++)
{
    bookHash[books[i].id] = i;
    root = insertBST(root, books[i].id);
}

cout << "Books Loaded Successfully!\n";

    int choice;

    do
    {
       cout << "\n===== SMART LIBRARY MANAGEMENT =====\n";
cout << "1. Add Book\n";
cout << "2. Display Books\n";
cout << "3. Search Book (Linear Search)\n";
cout << "4. Search Book (Hashing)\n";
cout << "5. Search Book (BST)\n";
cout << "6. Display BST (Inorder)\n";
cout << "7. Delete Book (BST)\n";
cout << "8. Sort Books (Merge Sort)\n";
cout << "9. Issue Book\n";
cout << "10. Return Book\n";
cout << "11. Invalid Option\n";
cout << "12. Add Student\n";
cout << "13. Display Students\n";
cout << "14. Search Student\n";
cout << "15. Update Student\n";
cout << "16. Delete Student\n";
cout << "17. Display Issued Books\n";
cout << "18. Library Dashboard\n";
cout << "19. Exit\n";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            addBook(books, bookHash, root);
    break;

                

            case 2:
                displayBooks(books);
                break;

            case 3:
                searchBook(books);
                break;

            case 4:
                searchBookHash(books, bookHash);
                break;

            case 5:
               {
                    int id;

    cout << "Enter Book ID: ";
    cin >> id;

    if (searchBST(root, id))
        cout << "Book Found in BST!\n";
    else
        cout << "Book Not Found!\n";

    break;
}

case 6:
    cout << "BST Inorder Traversal: ";
    inorder(root);
    cout << endl;
    break;

   
   case 7:
{
    int id;

    cout << "Enter Book ID to delete: ";
    cin >> id;

    if (bookHash.find(id) != bookHash.end())
    {
        root = deleteBST(root, id);

        int index = bookHash[id];

        books.erase(books.begin() + index);
saveBooks(books);
        bookHash.clear();

        for (int i = 0; i < books.size(); i++)
        {
            bookHash[books[i].id] = i;
        }

        cout << "Book Deleted Successfully!\n";
    }
    else
    {
        cout << "Book Not Found!\n";
    }

    break;
}
            

           case 8:
    if (books.empty())
    {
        cout << "No books available!\n";
    }
    else
    {
        mergeSort(books, 0, books.size() - 1);

        cout << "\nBooks Sorted Successfully!\n";

        displayBooks(books);
    }
    break;
            case 9:
    issueBook(books, students, issueRecords);
    break;
            case 10:
    returnBook(books, students, issueRecords);
    break;
    case 11:
    cout << "\nInvalid Option!\n";
    break;
                case 12:
    addStudent(students);
    break;

case 13:
    displayStudents(students);
    break;

case 14:
    searchStudent(students);
    break;
    case 15:
    deleteStudent(students);
    break;
    case 16:
    updateStudent(students);
    break;
    case 17:
    displayIssuedBooks(issueRecords);
    break;
    case 18:
    displayDashboard(books, students);
    break;
    case 19:
            saveBooks(books);
            saveIssueRecords(issueRecords);
                cout << "\nThank You!\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 19);

    return 0;
}